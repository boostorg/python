from SingleCodeUnit import SingleCodeUnit
import os
import utils
from SmartFile import SmartFile


#==============================================================================
# MultipleCodeUnit
#==============================================================================
class MultipleCodeUnit(object):
    '''
    Represents a bunch of cpp files, where each cpp file represents a header
    to be exported by pyste. Another header, named _main.cpp is created too.
    '''

    def __init__(self, modulename, outdir):
        self.modulename = modulename
        self.outdir = outdir
        self.codeunits = {}  # maps from a header to a SingleCodeUnit
        self.functions = []
        self._current = None

    
    def _FunctionName(self, code_unit_name):
        return '_Export_%s' % utils.makeid(code_unit_name)

    def _FileName(self, code_unit_name):
        filename = os.path.basename(code_unit_name)
        filename = '_%s.cpp' % os.path.splitext(filename)[0] 
        return os.path.join(self.outdir, filename)

    
    def SetCurrent(self, code_unit_name):
        'Changes the current code unit'
        try:
            codeunit = self.codeunits[code_unit_name]
        except KeyError:
            filename = self._FileName(code_unit_name)
            function_name = self._FunctionName(code_unit_name)
            codeunit = SingleCodeUnit(None, filename)
            codeunit.module_definition = 'void %s()' % function_name
            self.codeunits[code_unit_name] = codeunit
            if code_unit_name != '__all__':
                self.functions.append(function_name)
        self._current = codeunit


    def Current(self):
        return self._current

    current = property(Current, SetCurrent)
        
            
    def _CheckCurrent(self):
        if self.current is None:
            raise RuntimeError, "No current code unit to write to!" 
        
        
    def Write(self, section, code):
        self._CheckCurrent()
        self.current.Write(section, code)


    def Section(self, section):
        self._CheckCurrent()
        return self.current.Section(section)


    def _CreateOutputDir(self):
        try:
            os.mkdir(self.outdir)
        except OSError: pass # already created

        
    def Save(self):
        # create the directory where all the files will go
        self._CreateOutputDir();
        # write all the codeunits, merging first the contents of
        # the special code unit named __all__
        __all__ = self.codeunits.get('__all__')
        for name, codeunit in self.codeunits.items():
            if name != '__all__':                
                if __all__:
                    codeunit.Merge(__all__)
                codeunit.Save()
        # generate the main cpp
        filename = os.path.join(self.outdir, '_main.cpp')
        fout = SmartFile(filename, 'w')
        fout.write(utils.left_equals('Include'))
        fout.write('#include <boost/python.hpp>\n\n')
        fout.write(utils.left_equals('Exports'))
        for function in self.functions:
            fout.write('void %s();\n' % function)
        fout.write('\n')
        fout.write(utils.left_equals('Module'))
        fout.write('BOOST_PYTHON_MODULE(%s)\n' % self.modulename)
        fout.write('{\n')
        indent = ' ' * 4
        for function in self.functions:
            fout.write(indent)
            fout.write('%s();\n' % function)
        fout.write('}')
        
    
        
