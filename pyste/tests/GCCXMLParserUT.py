import sys
sys.path.append('../src') 
import unittest
import tempfile
import os.path
import GCCXMLParser
from declarations import *

    
class Tester(unittest.TestCase):

    def TestConstructor(self, class_, method, visib):
        self.assert_(isinstance(method, Constructor))
        self.assertEqual(method._FullName(), class_._FullName() + '::' + method._name)
        self.assertEqual(method._result, None)
        self.assertEqual(method._visibility, visib)
        self.assert_(not method._virtual)
        self.assert_(not method._abstract)
        self.assert_(not method._static)
        
    def TestDefaultConstructor(self, class_, method, visib):
        self.TestConstructor(class_, method, visib)
        self.assert_(method._IsDefault())

    def TestCopyConstructor(self, class_, method, visib):    
        self.TestConstructor(class_, method, visib)
        self.assertEqual(len(method._parameters), 1)
        param = method._parameters[0]
        self.TestType(
            param, 
            ReferenceType, 
            class_._FullName(), 
            'const %s&' % class_._FullName(),
            True)
        self.assert_(method._IsCopy())


    def TestType(self, type_, classtype_, name, fullname, const):
        self.assert_(isinstance(type_, classtype_))
        self.assertEqual(type_._name, name)
        self.assertEqual(type_._namespace, None)
        self.assertEqual(type_._FullName(), fullname)
        self.assertEqual(type_._const, const)
        
        
class ClassBaseTest(Tester):

    def setUp(self):
        self.base = GetDecl('Base')
        
    def testClass(self):
        'test the properties of the class Base'
        self.assert_(isinstance(self.base, Class))
        self.assert_(self.base._abstract)
                

    def testFoo(self):
        'test function foo in class Base' 
        foo = GetMember(self.base, 'foo')
        self.assert_(isinstance(foo, Method))
        self.assertEqual(foo._visibility, Scope.public)
        self.assert_(foo._virtual)
        self.assert_(foo._abstract)
        self.failIf(foo._static)
        self.assertEqual(foo._class, 'test::Base')
        self.failIf(foo._const)
        self.assertEqual(foo._FullName(), 'test::Base::foo')        
        self.assertEqual(foo._result._name, 'void')
        self.assertEqual(len(foo._parameters), 1)
        param = foo._parameters[0]
        self.TestType(param, FundamentalType, 'int', 'int', False)  
        self.assertEqual(foo._namespace, None)
        self.assertEqual(
            foo._PointerDeclaration(1), '(void (test::Base::*)(int) )&test::Base::foo')

    def testX(self):
        'test the member x in class Base'
        x = GetMember(self.base, 'x')
        self.assertEqual(x._class, 'test::Base')
        self.assertEqual(x._FullName(), 'test::Base::x')
        self.assertEqual(x._namespace, None)
        self.assertEqual(x._visibility, Scope.private)
        self.TestType(x._type, FundamentalType, 'int', 'int', False)  
        self.assertEqual(x._static, False)

    def testConstructors(self):
        'test constructors in class Base'
        constructors = GetMembers(self.base, 'Base')
        for cons in constructors:
            if len(cons._parameters) == 0:
                self.TestDefaultConstructor(self.base, cons, Scope.public)
            elif len(cons._parameters) == 1: # copy constructor
                self.TestCopyConstructor(self.base, cons, Scope.public)
            elif len(cons._parameters) == 2: # other constructor
                intp, floatp = cons._parameters
                self.TestType(intp, FundamentalType, 'int', 'int', False)
                self.TestType(floatp, FundamentalType, 'float', 'float', False)

    def testSimple(self):
        'test function simple in class Base'
        simple = GetMember(self.base, 'simple')
        self.assert_(isinstance(simple, Method))
        self.assertEqual(simple._visibility, Scope.protected)
        self.assertEqual(simple._FullName(), 'test::Base::simple')
        self.assertEqual(len(simple._parameters), 1)
        param = simple._parameters[0]
        self.TestType(param, ReferenceType, 'std::string', 'const std::string&', True)
        self.TestType(simple._result, FundamentalType, 'bool', 'bool', False)
        self.assertEqual(
            simple._PointerDeclaration(1), 
            '(bool (test::Base::*)(const std::string&) )&test::Base::simple')
        
          
    def testZ(self):
        z = GetMember(self.base, 'z')
        self.assert_(isinstance(z, Variable))
        self.assertEqual(z._visibility, Scope.public)
        self.assertEqual(z._FullName(), 'test::Base::z')
        self.assertEqual(z._type._name, 'int')
        self.assertEqual(z._type._const, False)
        self.assert_(z._static)
        
        
class ClassTemplateTest(Tester):        
    
    def setUp(self):
        self.template = GetDecl('Template<int>')

    def testClass(self):
        'test the properties of the Template<int> class'
        self.assert_(isinstance(self.template, Class))
        self.assert_(not self.template._abstract)
        self.assertEqual(self.template._FullName(), 'Template<int>')
        self.assertEqual(self.template._namespace, '')
        self.assertEqual(self.template._name, 'Template<int>')

    def testConstructors(self):
        'test the automatic constructors of the class Template<int>'
        constructors = GetMembers(self.template, 'Template')
        for cons in constructors:
            if len(cons._parameters) == 0:
                self.TestDefaultConstructor(self.template, cons, Scope.public)
            elif len(cons._parameters) == 1:
                self.TestCopyConstructor(self.template, cons, Scope.public)
                    

    def testValue(self):
        'test the class variable value'
        value = GetMember(self.template, 'value')
        self.assert_(isinstance(value, ClassVariable))
        self.assert_(value._name, 'value')
        self.TestType(value._type, FundamentalType, 'int', 'int', False)  
        self.assert_(not value._static)
        self.assertEqual(value._visibility, Scope.public)
        self.assertEqual(value._class, 'Template<int>')
        self.assertEqual(value._FullName(), 'Template<int>::value')

    def testBase(self):
        'test the superclasses of Template<int>'
        bases = self.template._bases
        self.assertEqual(len(bases), 1)
        base = bases[0]
        self.assert_(isinstance(base, Base))
        self.assertEqual(base._name, 'test::Base')
        self.assertEqual(base._visibility, Scope.protected)

        
        
class FreeFuncTest(Tester):

    def setUp(self):
        self.func = GetDecl('FreeFunc')

    def testFunc(self):
        'test attributes of FreeFunc'
        self.assert_(isinstance(self.func, Function))
        self.assertEqual(self.func._name, 'FreeFunc')
        self.assertEqual(self.func._FullName(), 'test::FreeFunc')
        self.assertEqual(self.func._namespace, 'test')
        self.assertEqual(
            self.func._PointerDeclaration(1), 
            '(const test::Base& (*)(const std::string&, int))&test::FreeFunc')


    def testResult(self):
        'test the return value of FreeFunc'
        res = self.func._result
        self.TestType(res, ReferenceType, 'test::Base', 'const test::Base&', True)

    def testParameters(self):
        'test the parameters of FreeFunc'
        self.assertEqual(len(self.func._parameters), 2)
        strp, intp = self.func._parameters
        self.TestType(strp, ReferenceType, 'std::string', 'const std::string&', True)
        self.assertEqual(strp._default, None)
        self.TestType(intp, FundamentalType, 'int', 'int', False)
        self.assertEqual(intp._default, '10')
        
        

class testFunctionPointers(Tester):

    def testMethodPointer(self):
        'test declaration of a pointer-to-method'
        meth = GetDecl('MethodTester')
        param = meth._parameters[0]
        fullname = 'void (test::Base::*)(int)'
        self.TestType(param, PointerType, fullname, fullname, False)

    def testFunctionPointer(self):
        'test declaration of a pointer-to-function'
        func = GetDecl('FunctionTester')
        param = func._parameters[0]
        fullname = 'void (*)(int)'
        self.TestType(param, PointerType, fullname, fullname, False)

        
        
# =============================================================================
# Support routines
# =============================================================================

cppcode = '''
namespace std {
    class string;
}
namespace test {
class Base
{
public:
    Base();
    Base(const Base&);
    Base(int, float);

    virtual void foo(int = 0.0) = 0;
    static int z;
protected:    
    bool simple(const std::string&);
private:
    int x;
};

void MethodTester( void (Base::*)(int) );
void FunctionTester( void (*)(int) );


const Base & FreeFunc(const std::string&, int=10);

}

template <class T>
struct Template: protected test::Base
{
    T value;        
    virtual void foo(int);
};
 
Template<int> __aTemplateInt;
'''

def GetXMLFile():
    '''Generates an gccxml file using the code from the global cppcode. 
    Returns the xml's filename.'''
    # write the code to a header file
    tmpfile = tempfile.mktemp() + '.h'
    f = file(tmpfile, 'w')
    f.write(cppcode)
    f.close()
    # run gccxml
    outfile = tmpfile + '.xml'
    if os.system('gccxml "%s" "-fxml=%s"' % (tmpfile, outfile)) != 0:
        raise RuntimeError, 'Error executing GCCXML.'
    # read the output file into the xmlcode
    f = file(outfile)
    xmlcode = f.read()
    #print xmlcode
    f.close()
    # remove the header
    os.remove(tmpfile)
    return outfile       



def GetDeclarations():
    'Uses the GCCXMLParser module to get the declarations.'
    xmlfile = GetXMLFile()
    declarations = GCCXMLParser.ParseDeclarations(xmlfile)
    os.remove(xmlfile)
    return declarations

# the declarations to be analysed
declarations = GetDeclarations()


def GetDecl(name):
    'returns one of the top declarations given its name'
    for decl in declarations:
        if decl._name == name:
            return decl
    else:
        raise RuntimeError, 'Declaration not found: %s' % name


def GetMember(class_, name):
    'gets the member of the given class by its name'
                
    res = None
    multipleFound = False
    for member in class_:
        if member._name == name:
            if res is not None:
                multipleFound = True
                break
            res = member
    if res is None or multipleFound:
        raise RuntimeError, \
            'No member or more than one member found in class %s: %s' \
                % (class_._name, name)
    return res            
    

def GetMembers(class_, name):
    'gets the members of the given class by its name'
    res = []
    for member in class_:
        if member._name == name:
            res.append(member)
    if len(res) in (0, 1):            
        raise RuntimeError, \
            'GetMembers: 0 or 1 members found in class %s: %s' \
                % (class_._name, name)
    return res            


if __name__ == '__main__':
    unittest.main()
