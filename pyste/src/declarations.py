'''
Defines classes that represent declarations found in C++ header files.
    
'''

#==============================================================================
# Declaration
#==============================================================================
class Declaration(object):
    '''Base class for all declarations.
    @ivar _name: The name of the declaration.
    @ivar _namespace: The namespace of the declaration.
    '''

    def __init__(self, name, namespace):
        '''
        @type name: string
        @param name: The name of this declaration
        @type namespace: string
        @param namespace: the full namespace where this declaration resides.
        '''
        self._name = name
        self._namespace = namespace
        self._location = '', -1  # (filename, line)
        self._incomplete = False
        self._is_unique = True


    def _FullName(self):
        '''
        Returns the full qualified name: "boost::inner::Test"
        @rtype: string
        @return: The full name of the declaration.
        '''
        namespace = self._namespace or ''
        if namespace and not namespace.endswith('::'):
            namespace += '::'
        return namespace + self._name
    
    
    def __repr__(self):        
        return '<Declaration %s at %s>' % (self._FullName(), id(self))


    def __str__(self):
        return 'Declaration of %s' % self._FullName()
    


#==============================================================================
# Class
#==============================================================================
class Class(Declaration):
    '''
    Represents a C++ class or struct. Iteration through it yields its members.

    @type _abstract: bool
    @ivar _abstract: if the class has any abstract methods.

    @type _bases: tuple
    @ivar _bases: tuple with L{Base} instances, representing the most direct
    inheritance.

    @type _hierarchy: list
    @ivar _hierarchy: a list of tuples of L{Base} instances, representing
    the entire hierarchy tree of this object. The first tuple is the parent 
    classes, and the other ones go up in the hierarchy.
    '''
    
    def __init__(self, name, namespace, members, abstract):
        Declaration.__init__(self, name, namespace)
        self.__members = members
        self._abstract = abstract
        self._bases = ()
        self._hierarchy = ()
        self.operator = {}


    def __iter__(self):
        '''iterates through the class' members.
        '''
        return iter(self.__members)            


    def _Constructors(self, publics_only=True):
        '''Returns a list of the constructors for this class.
        @rtype: list
        '''
        constructors = []
        for member in self:
            if isinstance(member, Constructor):
                if publics_only and member._visibility != Scope.public:
                    continue
                constructors.append(member)
        return constructors

    
    def _HasCopyConstructor(self):
        '''Returns true if this class has a public copy constructor.
        @rtype: bool
        '''
        for cons in self._Constructors():
            if cons._IsCopy():
                return True
        return False


    def _HasDefaultConstructor(self):
        '''Returns true if this class has a public default constructor.
        @rtype: bool
        '''
        for cons in self.Constructors():
            if cons._IsDefault():
                return True
        return False


    def _AddMember(self, member):
        slot = getattr(self, member._name, [])
        if slot:
            member._is_unique = False
            for m in slot:
                m._is_unique = False
        slot.append(member)
        setattr(self, member._name, slot)
        self.__members.append(member)
        if isinstance(member, ClassOperator):
            self.operator[member._name] = member
                


#==============================================================================
# NestedClass
#==============================================================================
class NestedClass(Class):
    '''The declaration of a class/struct inside another class/struct.
    
    @type _class: string
    @ivar _class: fullname of the class where this class is contained.

    @type _visibility: L{Scope} 
    @ivar _visibility: the visibility of this class.
    '''

    def __init__(self, name, _class, visib, members, abstract):
        Class.__init__(self, name, None, members, abstract)
        self._class = _class
        self._visibility = visib


    def _FullName(self):
        '''The full name of this class, like ns::outer::inner.
        @rtype: string
        '''
        return '%s::%s' % (self._class, self._name)
    

#==============================================================================
# Scope    
#==============================================================================
class Scope:    
    '''Used to represent the visibility of various members inside a class.
    @cvar public: public visibility
    @cvar private: private visibility
    @cvar protected: protected visibility
    '''
    public = 'public'
    private = 'private'
    protected = 'protected'
    
 
#==============================================================================
# Base    
#==============================================================================
class Base:
    '''Represents a base class of another class.
    @ivar _name: the full name of the base class.
    @ivar _visibility: the visibility of the derivation.
    '''

    def __init__(self, name, visibility=Scope.public):
        self._name = name
        self._visibility = visibility

    
#==============================================================================
# Function    
#==============================================================================
class Function(Declaration):
    '''The declaration of a function.
    @ivar _result: instance of L{Type} or None.
    @ivar _parameters: list of L{Type} instances.
    '''
    
    def __init__(self, name, namespace, result, params):
        Declaration.__init__(self, name, namespace)
        # the result type: instance of Type, or None (constructors)            
        self._result = result
        # the parameters: instances of Type
        self._parameters = params


    def _PointerDeclaration(self, force=False):
        '''Returns a declaration of a pointer to this function.
        @param force: If True, returns a complete pointer declaration regardless
        if this function is unique or not.
        '''
        if self._is_unique and not force:
            return '&%s' % self._FullName()
        else:
            result = self._result._FullName()
            params = ', '.join([x._FullName() for x in self._parameters]) 
            return '(%s (*)(%s))&%s' % (result, params, self._FullName())

    
    def _MinArgs(self):
        min = 0
        for arg in self._parameters:
            if arg._default is None:
                min += 1
        return min

    _minArgs = property(_MinArgs)
    

    def _MaxArgs(self):
        return len(self._parameters)

    _maxArgs = property(_MaxArgs)

    
    
#==============================================================================
# Operator
#==============================================================================
class Operator(Function):
    '''The declaration of a custom operator. Its name is the same as the 
    operator name in C++, ie, the name of the declaration "operator+(..)" is
    "+".
    '''
    
    def _FullName(self):
        namespace = self._namespace or ''
        if not namespace.endswith('::'):
            namespace += '::'
        return namespace + 'operator' + self._name 


#==============================================================================
# Method
#==============================================================================
class Method(Function):
    '''The declaration of a method.
    
    @ivar _visibility: the visibility of this method.
    @ivar _virtual: if this method is declared as virtual.
    @ivar _abstract: if this method is virtual but has no default implementation.
    @ivar _static: if this method is static.
    @ivar _class: the full name of the class where this method was declared.
    @ivar _const: if this method is declared as const.
    '''

    def __init__(self, name, class_, result, params, visib, virtual, abstract, static, const):
        Function.__init__(self, name, None, result, params)
        self._visibility = visib
        self._virtual = virtual
        self._abstract = abstract
        self._static = static
        self._class = class_
        self._const = const

    
    def _FullName(self):
        return self._class + '::' + self._name


    def _PointerDeclaration(self, force=False):
        '''Returns a declaration of a pointer to this member function.
        @param force: If True, returns a complete pointer declaration regardless
        if this function is unique or not. 
        '''
        if self._static:
            # static methods are like normal functions
            return Function._PointerDeclaration(self, force)
        if self._is_unique and not force:
            return '&%s' % self._FullName()
        else:
            result = self._result._FullName()
            params = ', '.join([x._FullName() for x in self._parameters]) 
            const = ''
            if self._const:
                const = 'const'            
            return '(%s (%s::*)(%s) %s)&%s' %\
                (result, self._class, params, const, self._FullName()) 


#==============================================================================
# Constructor
#==============================================================================
class Constructor(Method):
    '''A class' constructor.
    '''

    def __init__(self, name, class_, params, visib):
        Method.__init__(self, name, class_, None, params, visib, False, False, False, False)


    def _IsDefault(self):
        '''Returns True if this constructor is a default constructor.
        '''
        return len(self._parameters) == 0 and self._visibility == Scope.public


    def _IsCopy(self):
        '''Returns True if this constructor is a copy constructor.
        '''
        if len(self._parameters) != 1:
            return False
        param = self._parameters[0]
        class_as_param = self._parameters[0]._name == self._class
        param_reference = isinstance(param, ReferenceType) 
        is_public = self._visibility = Scope.public
        return param_reference and class_as_param and param._const and is_public
        

#==============================================================================
# Destructor
#==============================================================================
class Destructor(Method):
    'The destructor of a class.'

    def __init__(self, name, class_, visib, virtual):
        Method.__init__(self, name, class_, None, [], visib, virtual, False, False, False)

    def _FullName(self):
        return self._class + '::~' + self._name



#==============================================================================
# ClassOperator
#==============================================================================
class ClassOperator(Method):
    'A custom operator in a class.'
    
    def _FullName(self):
        return self._class + '::operator ' + self._name



#==============================================================================
# ConverterOperator
#==============================================================================
class ConverterOperator(ClassOperator):
    'An operator in the form "operator OtherClass()".'
    
    def _FullName(self):
        return self._class + '::operator ' + self._result._FullName()

    

#==============================================================================
# Type
#==============================================================================
class Type(Declaration):
    '''Represents the type of a variable or parameter.
    @ivar _const: if the type is constant.
    @ivar _default: if this type has a default value associated with it.
    @ivar _volatile: if this type was declared with the keyword volatile.
    @ivar _restricted: if this type was declared with the keyword restricted.
    @ivar _suffix: Suffix to get the full type name. '*' for pointers, for
    example.
    '''

    def __init__(self, name, const=False, default=None, suffix=''):
        Declaration.__init__(self, name, None)
        # whatever the type is constant or not
        self._const = const
        # used when the Type is a function argument
        self._default = default
        self._volatile = False
        self._restricted = False
        self._suffix = suffix

    def __repr__(self):
        if self.const:
            const = 'const '
        else:
            const = ''
        return '<Type ' + const + self.name + '>'


    def _FullName(self):
        if self._const:
            const = 'const '
        else:
            const = ''
        return const + self._name + self._suffix


#==============================================================================
# ArrayType
#==============================================================================
class ArrayType(Type):
    '''Represents an array.
    @ivar min: the lower bound of the array, usually 0. Can be None.
    @ivar max: the upper bound of the array. Can be None.
    '''

    def __init__(self, name, const, min, max): 
        'min and max can be None.'
        Type.__init__(self, name, const)
        self.min = min
        self.max = max        



#==============================================================================
# ReferenceType    
#==============================================================================
class ReferenceType(Type): 
    '''A reference type.'''

    def __init__(self, name, const=False, default=None, expandRef=True, suffix=''):
        Type.__init__(self, name, const, default)
        if expandRef:
            self._suffix = suffix + '&'
        
        
#==============================================================================
# PointerType
#==============================================================================
class PointerType(Type):
    'A pointer type.'
    
    def __init__(self, name, const=False, default=None, expandPointer=False, suffix=''):
        Type.__init__(self, name, const, default)
        if expandPointer:
            self._suffix = suffix + '*'
   

#==============================================================================
# FundamentalType
#==============================================================================
class FundamentalType(Type): 
    'One of the fundamental types, like int, void, etc.'

    def __init__(self, name, const=False, default=None): 
        Type.__init__(self, name, const, default)



#==============================================================================
# FunctionType
#==============================================================================
class FunctionType(Type):
    '''A pointer to a function.
    @ivar _result: the return value
    @ivar _parameters: a list of Types, indicating the parameters of the function.
    @ivar _name: the name of the function.
    '''

    def __init__(self, result, parameters):  
        Type.__init__(self, '', False)
        self._result = result
        self._parameters = parameters
        self._name = self._FullName()


    def _FullName(self):
        full = '%s (*)' % self._result._FullName()
        params = [x._FullName() for x in self._parameters]
        full += '(%s)' % ', '.join(params)        
        return full
    
    
#==============================================================================
# MethodType
#==============================================================================
class MethodType(FunctionType):
    '''A pointer to a member function of a class.
    @ivar _class: The fullname of the class that the method belongs to.
    '''

    def __init__(self, result, parameters, class_):  
        self._class = class_
        FunctionType.__init__(self, result, parameters)


    def _FullName(self):
        full = '%s (%s::*)' % (self._result._FullName(), self._class)
        params = [x._FullName() for x in self._parameters]
        full += '(%s)' % ', '.join(params)
        return full
    
     
#==============================================================================
# Variable
#==============================================================================
class Variable(Declaration):
    '''Represents a global variable.

    @type _type: L{Type}
    @ivar _type: The type of the variable.
    '''
    
    def __init__(self, type, name, namespace):
        Declaration.__init__(self, name, namespace)
        self._type = type


#==============================================================================
# ClassVariable
#==============================================================================
class ClassVariable(Variable):
    '''Represents a class variable.

    @type _visibility: L{Scope}
    @ivar _visibility: The visibility of this variable within the class.

    @type _static: bool
    @ivar _static: Indicates if the variable is static.

    @ivar _class: Full name of the class that this variable belongs to.
    '''

    def __init__(self, type, name, class_, visib, static):
        Variable.__init__(self, type, name, None)
        self._visibility = visib
        self._static = static
        self._class = class_
    

    def _FullName(self):
        return self._class + '::' + self._name

        
#==============================================================================
# Enumeration    
#==============================================================================
class Enumeration(Declaration):
    '''Represents an enum.

    @type _values: dict of str => int
    @ivar _values: holds the values for this enum.
    '''
    
    def __init__(self, name, namespace):
        Declaration.__init__(self, name, namespace)
        self._values = {} # dict of str => int


    def _ValueFullName(self, name):
        '''Returns the full name for a value in the enum.
        '''
        assert name in self._values
        namespace = self._namespace
        if namespace:
            namespace += '::'
        return namespace + name



class ClassEnumeration(Enumeration):
    '''Represents an enum inside a class.

    @ivar _class: The full name of the class where this enum belongs.
    @ivar _visibility: The visibility of this enum inside his class.
    '''

    def __init__(self, name, class_, visib):
        Enumeration.__init__(self, name, None)
        self._class = class_
        self._visibility = visib


    def _FullName(self):
        return '%s::%s' % (self._class, self._name)


    def _ValueFullName(self, name):
        assert name in self._values
        return '%s::%s' % (self._class, name)

    
#==============================================================================
# Typedef
#==============================================================================
class Typedef(Declaration):
    '''A Typedef declaration.

    @type _type: L{Type}
    @ivar _type: The type of the typedef.

    @type _visibility: L{Scope}
    @ivar _visibility: The visibility of this typedef.
    '''

    def __init__(self, type, name, namespace):
        Declaration.__init__(self, name, namespace)
        self._type = type
        self._visibility = Scope.public


#==============================================================================
# Unknown        
#==============================================================================
class Unknown(Declaration):
    '''A declaration that Pyste does not know how to handle.
    '''

    def __init__(self, name):
        Declaration.__init__(self, name, None)
