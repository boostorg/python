'''
Pyste version %s

Usage:
    pyste [options] interface-files

where options are:
    --module=<name>     the name of the module that will be generated.
                        Defaults to the first interface filename, without
                        the extension.
    -I <path>           add an include path    
    -D <symbol>         define symbol    
    --multiple          create various cpps, instead of only one 
                        (useful during development)                        
    --out               specify output filename (default: <module>.cpp)
                        in --multiple mode, this will be a directory
    --no-using          do not declare "using namespace boost";
                        use explicit declarations instead
    --pyste-ns=<name>   set the namespace where new types will be declared;
                        default is the empty namespace
    --debug             writes the xml for each file parsed in the current
                        directory
    -h, --help          print this help and exit
    -v, --version       print version information                         
'''

import sys
import os
import getopt
import exporters
import SingleCodeUnit
import MultipleCodeUnit
import infos
import exporterutils
import settings
import gc
import sys
from policies import *
from CppParser import CppParser, CppParserError
import time

__VERSION__ = '0.9.4'

def RecursiveIncludes(include):
    'Return a list containg the include dir and all its subdirectories'
    dirs = [include]
    def visit(arg, dir, names):
        # ignore CVS dirs
        if os.path.split(dir)[1] != 'CVS':
            dirs.append(dir)
    os.path.walk(include, visit, None)
    return dirs

    
def GetDefaultIncludes():
    if 'INCLUDE' in os.environ:
        include = os.environ['INCLUDE']
        return include.split(os.pathsep)
    else:
        return []


def ParseArguments():

    def Usage():
        print __doc__ % __VERSION__
        sys.exit(1)
        
    try:
        options, files = getopt.getopt(
            sys.argv[1:], 
            'R:I:D:vh', 
            ['module=', 'multiple', 'out=', 'no-using', 'pyste-ns=', 'debug', 'version', 'help'])
    except getopt.GetoptError, e:
        print
        print 'ERROR:', e
        Usage()
    includes = GetDefaultIncludes()
    defines = []
    module = None
    out = None
    multiple = False
    for opt, value in options:
        if opt == '-I':
            includes.append(value)
        elif opt == '-D':
            defines.append(value)
        elif opt == '-R':
            includes.extend(RecursiveIncludes(value))
        elif opt == '--module':
            module = value
        elif opt == '--out':
            out = value 
        elif opt == '--no-using':
            settings.namespaces.python = 'boost::python::'
            settings.USING_BOOST_NS = False
        elif opt == '--pyste-ns':
            settings.namespaces.pyste = value + '::'
        elif opt == '--debug':
            settings.DEBUG = True
        elif opt == '--multiple':
            multiple = True
        elif opt in ['-h', '--help']:
            Usage()
        elif opt in ['-v', '--version']:
            print 'Pyste version %s' % __VERSION__
            sys.exit(2)
        else:
            print 'Unknown option:', opt
            Usage()

    if not files:
        Usage() 
    if not module:
        module = os.path.splitext(files[0])[0]
    if not out:
        out = module
        if not multiple:
            out += '.cpp'
    return includes, defines, module, out, files, multiple

    
def CreateContext():
    'create the context where a interface file will be executed'
    context = {}
    # infos
    context['Function'] = infos.FunctionInfo
    context['Class'] = infos.ClassInfo
    context['Include'] = infos.IncludeInfo
    context['Template'] = infos.ClassTemplateInfo
    context['Enum'] = infos.EnumInfo
    context['AllFromHeader'] = infos.HeaderInfo
    context['Var'] = infos.VarInfo
    # functions
    context['rename'] = infos.rename
    context['set_policy'] = infos.set_policy
    context['exclude'] = infos.exclude
    context['set_wrapper'] = infos.set_wrapper
    context['use_shared_ptr'] = infos.use_shared_ptr
    context['use_auto_ptr'] = infos.use_auto_ptr
    context['add_method'] = infos.add_method
    context['no_override'] = infos.no_override
    # policies
    context['return_internal_reference'] = return_internal_reference
    context['with_custodian_and_ward'] = with_custodian_and_ward
    context['return_value_policy'] = return_value_policy
    context['reference_existing_object'] = reference_existing_object
    context['copy_const_reference'] = copy_const_reference
    context['copy_non_const_reference'] = copy_non_const_reference
    context['return_opaque_pointer'] = return_opaque_pointer
    context['manage_new_object'] = manage_new_object
    # utils
    context['Wrapper'] = exporterutils.FunctionWrapper
    return context                                        

    
def Main():
    includes, defines, module, out, interfaces, multiple = ParseArguments()
    # execute the interface files
    for interface in interfaces:
        context = CreateContext()
        execfile(interface, context)        
    # create the parser
    parser = CppParser(includes, defines) 
    # prepare to generate the wrapper code
    if multiple:
        codeunit = MultipleCodeUnit.MultipleCodeUnit(module, out)
    else:
        codeunit = SingleCodeUnit.SingleCodeUnit(module, out) 
    # group exporters by header files    
    groups = {}
    for export in exporters.exporters:
        header = export.Header()
        if header in groups:
            groups[header].append(export)
        else:
            groups[header] = [export] 
    # stop referencing the exporters here
    exporters.exporters = None 
    # export all the exporters in each group, releasing memory as doing so
    while len(groups) > 0:
        # get the first group
        header = groups.keys()[0]
        exports = groups[header]
        del groups[header]
        # gather all tails into one
        all_tails = []
        for export in exports:
            if export.Tail():
                all_tails.append(export.Tail())
        all_tails = '\n'.join(all_tails)
        # parse header (if there's one)
        if header:
            try:
                declarations, parsed_header = parser.parse(header, all_tails)
            except CppParserError, e:            
                print>>sys.stderr, '\n\n***', e, ': exitting'
                return 2
        else:
            declarations = []
            parsed_header = None
        # first set the declarations and parsed_header for all the exporters
        for export in exports:
            export.SetDeclarations(declarations)
            export.SetParsedHeader(parsed_header)
        # sort the exporters by their order
        exports = [(x.Order(), x) for x in exports]
        exports.sort()
        exports = [x for _, x in exports]
        # maintain a dict of exported_names for this group
        exported_names = {}
        for export in exports:
            if multiple:
                codeunit.SetCurrent(export.Unit())
            export.GenerateCode(codeunit, exported_names)
            exported_names[export.Name()] = 1
        # force collect of cyclic references
        gc.collect()
    # finally save the code unit
    codeunit.Save()                
    print 'Module %s generated' % module
    return 0


def UsePsyco():
    'Tries to use psyco if possible'
    try:
        import psyco
        psyco.profile()
    except: pass         

    
if __name__ == '__main__':
    start = time.clock()
    UsePsyco()
    status = Main()
    print '%0.2f seconds' % (time.clock()-start)
    sys.exit(status)
