from declarations import *
from elementtree.ElementTree import ElementTree
from xml.parsers.expat import ExpatError
from copy import deepcopy
from utils import enumerate


class InvalidXMLError(Exception): pass

class ParserError(Exception): pass

class InvalidContextError(ParserError): pass


class GCCXMLParser(object):
    'Parse a GCC_XML file and extract the top-level declarations.'
    
    interested_tags = {'Class':0, 'Function':0, 'Variable':0, 'Enumeration':0}
    
    def Parse(self, filename):
        self.elements = self.GetElementsFromXML(filename)
        # high level declarations
        self.declarations = []
        # parse the elements
        for id in self.elements:
            element, decl = self.elements[id]
            if decl is None: 
                try:
                    self.ParseElement(id, element)
                except InvalidContextError:
                    pass # ignore those nodes with invalid context 
                         # (workaround gccxml bug)
         

    def Declarations(self):
        return self.declarations


    def AddDecl(self, decl):
        self.declarations.append(decl)

        
    def ParseElement(self, id, element):
        method = 'Parse' + element.tag
        if hasattr(self, method):
            func = getattr(self, method)
            func(id, element)
        else:
            self.ParseUnknown(id, element)

            
    def GetElementsFromXML(self,filename):
        'Extracts a dictionary of elements from the gcc_xml file.'
        
        tree = ElementTree()
        try:
            tree.parse(filename)
        except ExpatError:
            raise InvalidXMLError, 'Not a XML file: %s' % filename

        root = tree.getroot()
        if root.tag != 'GCC_XML':
            raise InvalidXMLError, 'Not a valid GCC_XML file'

        # build a dictionary of id -> element, None
        elementlist = root.getchildren()
        elements = {}
        for element in elementlist:
            id = element.get('id')
            if id:
                elements[id] = element, None
        return elements


    def GetDecl(self, id):
        if id not in self.elements:
            if id == '_0':
                raise InvalidContextError, 'Invalid context found in the xml file.'
            else: 
                msg = 'ID not found in elements: %s' % id
                raise ParserError, msg

        elem, decl = self.elements[id]
        if decl is None:
            self.ParseElement(id, elem)
            elem, decl = self.elements[id]
            if decl is None:
                raise ParserError, 'Could not parse element: %s' % elem.tag
        return decl
    

    def GetType(self, id):
        def Check(id, feature):
            pos = id.find(feature)
            if pos != -1:
                id = id[:pos] + id[pos+1:]
                return True, id
            else:
                return False, id
        const, id = Check(id, 'c')
        volatile, id = Check(id, 'v')
        restricted, id = Check(id, 'r')
        decl = self.GetDecl(id)
        if isinstance(decl, Type):
            res = decl.Copy()
            if const:
                res.const = const
            if volatile: 
                res.volatile = volatile
            if restricted:
                res.restricted = restricted
        else:
            res = Type(decl.FullName(), const)
            res.volatile = volatile
            res.restricted = restricted
            res.incomplete = decl.incomplete
        return res            
        
                
    def GetLocation(self, location):
        file, line = location.split(':')
        file = self.GetDecl(file)
        return file, int(line)

        
    def Update(self, id, decl):
        element, _ = self.elements[id]
        self.elements[id] = element, decl

        
    def ParseUnknown(self, id, element):
        name = '__Unknown_Element_%s' % id
        namespace = '::'
        decl = Declaration(name, namespace)
        self.Update(id, decl)
        
        
    def ParseNamespace(self, id, element):
        namespace = element.get('name')
        context = element.get('context')
        if context:
            outerns = self.GetDecl(context)
            if not outerns.endswith('::'):
                outerns += '::'
            namespace = outerns + namespace
        if namespace.startswith('::'):
            namespace = namespace[2:]
        self.Update(id, namespace)


    def ParseFile(self, id, element):
        filename = element.get('name')
        self.Update(id, filename)

        
    def ParseVariable(self, id, element):
        # in gcc_xml, a static Field is declared as a Variable, so we check
        # this and call the Field parser if apply.
        context = self.GetDecl(element.get('context'))
        if isinstance(context, Class):
            self.ParseField(id, element)
            elem, decl = self.elements[id]
            decl.static = True
        else:
            namespace = context
            name = element.get('name')                    
            type_ = self.GetType(element.get('type'))
            location = self.GetLocation(element.get('location'))
            variable = Variable(type_, name, namespace)
            variable.location = location
            self.AddDecl(variable)
            self.Update(id, variable)
        

    def GetArguments(self, element):
        args = []
        for child in element:
            if child.tag == 'Argument':
                type_ = self.GetType(child.get('type'))
                type_.default = child.get('default')                
                args.append(type_)
        return args

    
    def ParseFunction(self, id, element, functionType=Function):
        '''functionType is used because a Operator is identical to a normal 
        function, only the type of the function changes.'''
        name = element.get('name')
        returns = self.GetType(element.get('returns'))
        namespace = self.GetDecl(element.get('context'))
        location = self.GetLocation(element.get('location'))
        params = self.GetArguments(element)
        function = functionType(name, namespace, returns, params)
        function.location = location
        self.AddDecl(function)
        self.Update(id, function)


    def ParseOperatorFunction(self, id, element):
        self.ParseFunction(id, element, Operator)

        
    def GetHierarchy(self, bases):       
        '''Parses the string "bases" from the xml into a list of tuples of Base
        instances. The first tuple is the most direct inheritance, and then it
        goes up in the hierarchy. 
        '''

        if bases is None:
            return []
        base_names = bases.split()
        this_level = []      
        next_levels = []
        for base in base_names:
            # get the visibility
            split = base.split(':')
            if len(split) == 2:
                visib = split[0]
                base = split[1]
            else:
                visib = Scope.public                            
            decl = self.GetDecl(base) 
            base = Base(decl.FullName(), visib)
            this_level.append(base)
            # normalize with the other levels
            for index, level in enumerate(decl.hierarchy):
                if index < len(next_levels):
                    next_levels[index] = next_levels[index] + level
                else:
                    next_levels.append(level)
        hierarchy = []
        if this_level:
            hierarchy.append(tuple(this_level))
        if next_levels:
            hierarchy.extend(next_levels)
        return hierarchy

        
    def GetMembers(self, members):
        # members must be a string with the ids of the members
        if members is None:
            return []
        memberobjs = []
        for member in members.split():
            memberobjs.append(self.GetDecl(member)) 
        return memberobjs


    def ParseClass(self, id, element):
        name = element.get('name')
        abstract = bool(int(element.get('abstract', '0')))
        location = self.GetLocation(element.get('location'))
        context = self.GetDecl(element.get('context'))
        incomplete = bool(element.get('incomplete', False))
        if isinstance(context, str): 
            class_ = Class(name, context, [], abstract)
        else:
            # a nested class
            visib = element.get('access', Scope.public)
            class_ = NestedClass(
                name, context.FullName(), visib, [], abstract)
        self.AddDecl(class_)
        # we have to add the declaration of the class before trying        
        # to parse its members and bases, to avoid recursion.
        class_.location = location
        class_.incomplete = incomplete
        self.Update(id, class_)       
        # now we can get the members and the bases
        class_.hierarchy = self.GetHierarchy(element.get('bases'))        
        if class_.hierarchy:
            class_.bases = class_.hierarchy[0]
        class_.members = self.GetMembers(element.get('members'))


    def ParseStruct(self, id, element):
        self.ParseClass(id, element)


    def ParseFundamentalType(self, id, element):
        name = element.get('name')
        type_ = FundamentalType(name)
        self.Update(id, type_)


    def ParseArrayType(self, id, element):
        type_ = self.GetType(element.get('type'))
        min = element.get('min')
        max = element.get('max')
        array = ArrayType(type_.name, type_.const)
        array.min = min
        array.max = max
        self.Update(id, array)

        
    def ParseReferenceType(self, id, element):
        type_ = self.GetType(element.get('type'))
        expand = not isinstance(type_, FunctionType)
        ref = ReferenceType(type_.name, type_.const, None, type_.incomplete, expand)
        self.Update(id, ref)
        
        
    def ParsePointerType(self, id, element):
        type_ = self.GetType(element.get('type'))
        expand = not isinstance(type_, FunctionType)
        ref = PointerType(type_.name, type_.const, None, type_.incomplete, expand)
        self.Update(id, ref)
        
        
    def ParseFunctionType(self, id, element):
        result = self.GetType(element.get('returns'))
        args = self.GetArguments(element)
        func = FunctionType(result, args)
        self.Update(id, func)


    def ParseMethodType(self, id, element):
        class_ = self.GetDecl(element.get('basetype')).FullName()
        result = self.GetType(element.get('returns'))
        args = self.GetArguments(element)
        method = MethodType(result, args, class_)
        self.Update(id, method)

        
    def ParseField(self, id, element):
        name = element.get('name')
        visib = element.get('access', Scope.public)
        classname = self.GetDecl(element.get('context')).FullName()
        type_ = self.GetType(element.get('type'))
        static = bool(int(element.get('extern', '0')))
        location = self.GetLocation(element.get('location'))
        var = ClassVariable(type_, name, classname, visib, static)
        var.location = location
        self.Update(id, var)


    def ParseMethod(self, id, element, methodType=Method):
        name = element.get('name')
        result = self.GetType(element.get('returns'))
        classname = self.GetDecl(element.get('context')).FullName()
        visib = element.get('access', Scope.public)
        static = bool(int(element.get('static', '0')))
        virtual = bool(int(element.get('virtual', '0')))
        abstract = bool(int(element.get('pure_virtual', '0')))
        const = bool(int(element.get('const', '0')))
        location = self.GetLocation(element.get('location'))
        params = self.GetArguments(element)
        method = methodType(
            name, classname, result, params, visib, virtual, abstract, static, const)
        method.location = location
        self.Update(id, method)


    def ParseOperatorMethod(self, id, element):
        self.ParseMethod(id, element, ClassOperator)

        
    def ParseConstructor(self, id, element):
        name = element.get('name')
        visib = element.get('access', Scope.public)
        classname = self.GetDecl(element.get('context')).FullName()
        location = self.GetLocation(element.get('location'))
        params = self.GetArguments(element)
        ctor = Constructor(name, classname, params, visib)
        ctor.location = location
        self.Update(id, ctor)


    def ParseDestructor(self, id, element):
        name = element.get('name')
        visib = element.get('access', Scope.public)
        classname = self.GetDecl(element.get('context')).FullName()
        virtual = bool(int(element.get('virtual', '0')))
        location = self.GetLocation(element.get('location'))
        des = Destructor(name, classname, visib, virtual)
        des.location = location
        self.Update(id, des)


    def ParseConverter(self, id, element):
        self.ParseMethod(id, element, ConverterOperator)


    def ParseTypedef(self, id, element):
        name = element.get('name')
        type = self.GetType(element.get('type'))        
        context = self.GetDecl(element.get('context'))
        if isinstance(context, Class):
            context = context.FullName()
        typedef = Typedef(type, name, context)
        self.Update(id, typedef)
        self.AddDecl(typedef)


    def ParseEnumeration(self, id, element):
        name = element.get('name')
        location = self.GetLocation(element.get('location'))
        context = self.GetDecl(element.get('context'))
        if isinstance(context, str):
            enum = Enumeration(name, context)
        else:
            visib = element.get('access', Scope.public)
            enum = ClassEnumeration(name, context.FullName(), visib)
        self.AddDecl(enum)
        enum.location = location
        for child in element:
            if child.tag == 'EnumValue':
                name = child.get('name')
                value = int(child.get('init'))
                enum.values[name] = value
        self.Update(id, enum)


    def ParseUnimplemented(self, id, element):
        'No idea of what this is'
        self.Update(id, Declaration('', ''))
        

    def ParseUnion(self, id, element):
        name = element.get('name')
        context = self.GetDecl(element.get('context'))
        location = self.GetLocation(element.get('location'))
        if isinstance(context, str):
            # a free union
            union = Union(name, context)
            self.AddDecl(union)
        else:
            visib = element.get('access', Scope.public)
            union = ClassUnion(name, context.FullName(), visib)
        union.location = location
        self.Update(id, union)
        


def ParseDeclarations(filename):
    'Returns a list of the top declarations found in the gcc_xml file.'
        
    parser = GCCXMLParser() 
    parser.Parse(filename)
    return parser.Declarations()


if __name__ == '__main__':
    ParseDeclarations(r'D:\Programming\Libraries\boost-cvs\boost\libs\python\pyste\example\test.xml')
