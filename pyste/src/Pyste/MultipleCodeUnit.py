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
    to be exported by pyste. Another cpp, named <module>.cpp is created too.
    '''

    def __init__(self, modulename, outdir):
        self.modulename = modulename
        self.outdir = outdir
        self.codeunits = {}  # maps from a (filename, function) to a SingleCodeUnit
        self.functions = []
        self._current = None
        self.all = SingleCodeUnit(None, None)

    
    def _FunctionName(self, export_name):
        return 'Export_%s' % utils.makeid(export_name)
    

    def _FileName(self, interface_file):
        filename = os.path.basename(interface_file)
        filename = '_%s.cpp' % os.path.splitext(filename)[0] 
        return os.path.join(self.outdir, filename)

    
    def SetCurrent(self, interface_file, export_name):
        'Changes the current code unit'
        if export_name is None:
            self._current = None
        elif export_name is '__all__':
            self._current = self.all
        else:
            filename = self._FileName(interface_file)
            function = self._FunctionName(export_name)  
            try:
                codeunit = self.codeunits[(filename, function)]
            except KeyError:
                codeunit = SingleCodeUnit(None, filename)
                codeunit.module_definition = 'void %s()' % function
                self.codeunits[(filename, function)] = codeunit
                if function not in self.functions:
                    self.functions.append(function)
            self._current = codeunit


    def Current(self):
        return self._current

    current = property(Current, SetCurrent)
        
            
    def Write(self, section, code):
        if self._current is not None:
            self.current.Write(section, code)


    def Section(self, section):
        if self._current is not None: 
            return self.current.Section(section)


    def _CreateOutputDir(self):
        try:
            os.mkdir(self.outdir)
        except OSError: pass # already created

        
    def Save(self):
        # create the directory where all the files will go
        self._CreateOutputDir();
        # order all code units by filename, and merge them all
        codeunits = {} # filename => list of codeunits
        # the main_unit holds all the include, declaration and declaration-outside sections
        # to keep them all in the top of the source file
        main_unit = None
        for (filename, _), codeunit in self.codeunits.items(): 
            if filename not in codeunits:                
                codeunits[filename] = [codeunit]
                main_unit = codeunit
                main_unit.Merge(self.all)
            else:
                for section in ('include', 'declaration', 'declaration-outside'):
                    main_unit.code[section] = main_unit.code[section] + codeunit.code[section]
                    codeunit.code[section] = ''
                codeunits[filename].append(codeunit)
        # write all the codeunits, merging first the contents of
        # the special code unit named __all__
        for codeunits in codeunits.values():
            append = False
            for codeunit in codeunits:
                codeunit.Save(append)
                if not append:
                    append = True
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
        fout.write('}\n')
        
    
        
