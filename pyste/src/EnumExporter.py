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
        self.enum = self.GetDeclaration(self.info.name)


    def Export(self, codeunit, expoted_names):
        if not self.info.exclude:
            indent = self.INDENT
            in_indent = self.INDENT*2
            rename = self.info.rename or self.enum._name
            full_name = self.enum._FullName()
            if rename == "$_0" or rename == '._0':
                full_name = "int"
                rename = "unnamed"
            code = indent + namespaces.python
            code += 'enum_< %s >("%s")\n' % (full_name, rename)
            for name in self.enum._values:         
                rename = self.info[name].rename or name
                value_fullname = self.enum._ValueFullName(name)
                code += in_indent + '.value("%s", %s)\n' % (rename, value_fullname)
            code += indent + ';\n\n'
            codeunit.Write('module', code)


    def Unit(self):
        return utils.makeid(self.info.include)


    def Order(self):
        return self.info.name
