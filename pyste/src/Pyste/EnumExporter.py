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


    def Export(self, codeunit, exported_names):
        if not self.info.exclude:
            indent = self.INDENT
            in_indent = self.INDENT*2
            rename = self.info.rename or self.enum.name
            full_name = self.enum.FullName()
            if rename == "$_0" or rename == '._0':
                full_name = "int"
                rename = "unnamed"
            code = indent + namespaces.python
            code += 'enum_< %s >("%s")\n' % (full_name, rename)
            for name in self.enum.values:         
                rename = self.info[name].rename or name
                value_fullname = self.enum.ValueFullName(name)
                code += in_indent + '.value("%s", %s)\n' % (rename, value_fullname)
            code += indent + ';\n\n'
            codeunit.Write('module', code)
            exported_names[self.Name()] = 1


    def Name(self):
        return self.info.name
