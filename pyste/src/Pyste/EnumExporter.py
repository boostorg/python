from Exporter import Exporter
from settings import *
import utils

#==============================================================================
# EnumExporter 
#==============================================================================
class EnumExporter(Exporter):
    'Exports enumerators'

    def __init__(self, info):
        Exporter.__init__(self, info)


    def SetDeclarations(self, declarations):
        Exporter.SetDeclarations(self, declarations)
        if self.declarations:
            self.enum = self.GetDeclaration(self.info.name)
        else:
            self.enum = None

    TYPE_COUNT = 0
    
    def Export(self, codeunit, exported_names):
        if not self.info.exclude:
            indent = self.INDENT
            in_indent = self.INDENT*2
            rename = self.info.rename or self.enum.name
            full_name = self.enum.FullName()
            unnamed_enum = False
            if rename.startswith('$_') or rename.startswith('._'):
                unnamed_enum = True
                self.ExportUniqueInt(codeunit)
                full_name = namespaces.pyste + 'UniqueInt<%d>' % EnumExporter.TYPE_COUNT
                EnumExporter.TYPE_COUNT += 1
                rename = "unnamed"
            code = indent + namespaces.python
            code += 'enum_< %s >("%s")\n' % (full_name, rename)
            for name in self.enum.values:         
                rename = self.info[name].rename or name
                value_fullname = self.enum.ValueFullName(name)
                code += in_indent + '.value("%s", %s)\n' % (rename, value_fullname)
            if self.info.export_values or unnamed_enum:
                code += in_indent + '.export_values()\n'
            code += indent + ';\n\n'
            codeunit.Write('module', code)
            exported_names[self.enum.FullName()] = 1


    UNIQUE_INT_EXPORTED = False
    
    def ExportUniqueInt(self, codeunit):
        if not EnumExporter.UNIQUE_INT_EXPORTED:
            write = lambda s: codeunit.Write('declaration', s)
            write('// Unique type for unnamed enums\n')
            write('template<int num>\n')
            write('struct UniqueInt {\n')
            write('   int v;\n')
            write('   enum { value=num };\n')
            write('   UniqueInt(int v_):\n') 
            write('       v(v_)\n')
            write('   {}\n')
            write('   operator int() const\n')
            write('   { return v; }\n')
            write('};\n')
            EnumExporter.UNIQUE_INT_EXPORTED = True
            

    #def Export(self, codeunit, exported_names):
    #    if not self.info.exclude:
    #        indent = self.INDENT
    #        in_indent = self.INDENT*2
    #        rename = self.info.rename or self.enum.name
    #        full_name = self.enum.FullName()
    #        if rename == "$_0" or rename == '._0':
    #            full_name = "int"
    #            rename = "unnamed"
    #        code = indent + namespaces.python
    #        code += 'enum_< %s >("%s")\n' % (full_name, rename)
    #        for name in self.enum.values:         
    #            rename = self.info[name].rename or name
    #            value_fullname = self.enum.ValueFullName(name)
    #            code += in_indent + '.value("%s", %s)\n' % (rename, value_fullname)
    #        code += indent + ';\n\n'
    #        codeunit.Write('module', code)
    #        exported_names[self.Name()] = 1


    def Name(self):
        return self.info.name
