from settings import namespaces
import settings
from utils import remove_duplicated_lines, left_equals
from SmartFile import SmartFile


#==============================================================================
# SingleCodeUnit
#==============================================================================
class SingleCodeUnit:
    '''
    Represents a cpp file, where other objects can write in one of the     
    predefined sections.
    The avaiable sections are:
        include - The include area of the cpp file
        declaration - The part before the module definition
        module - Inside the BOOST_PYTHON_MODULE macro
    '''
    
    def __init__(self, modulename, filename):
        self.modulename = modulename
        self.filename = filename
        # define the avaiable sections
        self.code = {}
        self.code['include'] = ''
        self.code['declaration'] = ''
        self.code['module'] = ''
        # create the default module definition
        self.module_definition = 'BOOST_PYTHON_MODULE(%s)' % modulename


    def Write(self, section, code):
        'write the given code in the section of the code unit'
        if section not in self.code:
            raise RuntimeError, 'Invalid CodeUnit section: %s' % section
        self.code[section] += code
        

    def Merge(self, other):
        for section in ('include', 'declaration', 'module'):
            self.code[section] = self.code[section] + other.code[section]    

        
    def Section(self, section):
        return self.code[section]

    
    def Save(self):
        'Writes this code unit to the filename'
        space = '\n\n'
        fout = SmartFile(self.filename, 'w')
        # includes
        includes = remove_duplicated_lines(self.code['include'])
        fout.write('\n' + left_equals('Includes'))        
        fout.write('#include <boost/python.hpp>\n')
        fout.write(includes)
        fout.write(space)
        # using
        if settings.USING_BOOST_NS:
            fout.write(left_equals('Using'))
            fout.write('using namespace boost::python;\n\n')
        # declarations
        if self.code['declaration']:
            pyste_namespace = namespaces.pyste[:-2]
            fout.write(left_equals('Declarations'))
            fout.write('namespace %s {\n\n\n' % pyste_namespace)
            fout.write(self.code['declaration']) 
            fout.write('\n\n}// namespace %s\n' % pyste_namespace)
            fout.write(space)
        # module
        fout.write(left_equals('Module'))
        fout.write(self.module_definition + '\n')
        fout.write('{\n')
        fout.write(self.code['module']) 
        fout.write('}\n')

        
    def _leftEquals(self, s):
        s = '// %s ' % s
        return s + ('='*(80-len(s))) + '\n'
