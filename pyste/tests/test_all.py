#!/usr/bin/python

import os
import glob
import shutil
import sys

# 3 functions are needed for each plataform:
# build_pyste(multiple, module)
# compile_single(module)
# compile_multiple(module)
#
if sys.platform == 'win32':
    
    includes = '-ID:/programming/libraries/boost-cvs/boost -IC:/Python/include'
    lib_dirs = '/libpath:D:/programming/libraries/boost-cvs/lib /libpath:C:/Python/libs' 
    libs = 'boost_python.lib python22.lib'
    
    def build_pyste(multiple, module): 
        cmd = 'python ../src/pyste.py %s %s --module=%s %s.pyste'
        execute(cmd % (multiple, includes, '_' + module, module))


    def compile_single(module):
        start_building(module)
        cmd = 'icl /nologo /GR /GX -c %s -I.' % includes
        cmd += ' %s'
        module_obj = ''
        if os.path.isfile(module+'.cpp'):
            execute(cmd % (module+'.cpp'))
            module_obj = module + '.obj'
        execute(cmd % '_%s.cpp' % module)
        execute('link /nologo /DLL /out:_%s.dll %s %s %s %s' % \
            (module, lib_dirs, '_%s.obj' % module, module_obj, libs)) 
        end_building(module)


    def compile_multiple(module):
        start_building(module)
        cmd = 'icl /nologo /GR /GX -c %s -I.' % includes
        cmd += ' %s'
        module_obj = ''
        if os.path.isfile(module+'.cpp'):
            execute(cmd % (module+'.cpp'))
            module_obj = module + '.obj' 
        files = glob.glob('_%s/*.cpp' % module)
        for f in files:
            execute(cmd % f)
        objs = [os.path.split(os.path.splitext(x)[0])[1] + '.obj' for x in files]
        objs.append(module_obj)
        execute('link /nologo /DLL /out:_%s.dll %s %s %s' % \
            (module, lib_dirs, ' '.join(objs), libs))
        end_building(module)
        

    def start_building(module):
        #print 'Building module %s...' % module,  
        pass


    def end_building(module):
        pass
        #if os.path.isfile('_%s.dll' % module):
        #    print ' done.'
        #else:
        #    print 'FAILED!'
        #print 

        
elif sys.platform == 'posix':
    
    def build_pyste(multiple, module): 
        cmd = 'python ../src/pyste.py %s --module=%s %s.pyste'
        execute(cmd % (multiple, module))
        
    
def execute(cmd):
    #output = os.popen(cmd).read()
    #f = file('build.log', 'a')
    #f.write(output)
    #f.close()
    os.system(cmd)
    



def compile_pyste_files(multiple):
    pass    
    #if not multiple:
    #    ## compile each cpp into a shared library 
    #    #for cpp in glob.glob('*.cpp'):          
    #    #    print
    #    #    print 'compiling', cpp
    #    #    out = os.path.splitext(cpp)[0] + '.so'
    #    #    cmdline = 'g++ -shared -o %s -I../example ' \
    #    #        '-I/usr/include/python2.2 -lboost_python %s' % (out, cpp)
    #    #    os.system(cmdline)
    #    
    #else:
    #    modules = get_modules() 
    #    # list cpp files in each module directory
    #    print
    #    for module in modules:
    #        # compile each
    #        for file in glob.glob(module+'/*.cpp'):
    #            print 'compiling', file
    #            out = os.path.splitext(file)[0] + '.obj'
    #            cmdline = 'g++ -shared -c -o %s -I../example ' \
    #                '-I/usr/include/python2.2 %s' % (out, file)
    #            os.system(cmdline)
    #        # generate a dynamic library
    #        print 'linking'
    #        objs = ' '.join([x for x in glob.glob(module+'/*.obj')])
    #        out = module + '.so'
    #        cmdline = 'g++ -shared -o %s -lboost_python %s' % (out, objs)
    #        os.system(cmdline)
                
        
def compile_file_posix(filename, outfilename):
    cmdline = 'g++ -shared -o %s -I../example ' \
                '-I/usr/include/python2.2 -lboost_python %s' % (outfilename, filename)
    execute(cmdline)     
    

def run_tests():
    if os.system('python runtests.py') != 0:
        raise RuntimeError, 'tests failed'


def cleanup():
    modules = get_modules()
    extensions = '*.dll *.pyc *.obj *.exp *.lib'
    files = []
    for module in modules:
        files.append('_' + module + '.cpp')
    for ext in extensions.split():
        files += glob.glob(ext)
    files.append('build.log')
    for file in files:
        try:
            os.remove(file)
        except OSError: pass

    for module in modules:
        try:
            shutil.rmtree('_' + module)
        except OSError: pass

    
def main(multiple, module=None):
    if module is None:
        modules = get_modules()
    else:
        modules = [module]
    for module in modules:    
        build_pyste(multiple, module) 
        if multiple:
            compile_multiple(module)
        else:
            compile_single(module) 
    if len(modules) == 1:
        os.system('python %sUT.py' % modules[0])
    else:
        run_tests()
    cleanup() 

    
def get_modules():
    def getname(file):
        return os.path.splitext(os.path.basename(file))[0]
    return [getname(x) for x in glob.glob('*.pyste')]

if __name__ == '__main__':
    if len(sys.argv) > 1:
        module = sys.argv[1]
    else:
        module = None
    try:
        #main('--multiple', module)
        main('', module)
    except RuntimeError, e:
        print e        
