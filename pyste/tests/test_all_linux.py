#!/usr/bin/python

import os
import glob
import shutil

def build_pyste_files(multiple):
    # list all pyste files in the example directory
    examples = glob.glob('../example/*.pyste')
    # generate the cpp file for each example
    for example in examples:    
        path, filename = os.path.split(example)
        module = os.path.splitext(filename)[0]
        os.system('python ../src/pyste.py %s -I%s --module=%s %s' % \
            (multiple, path, module, example))
    

def compile_pyste_files(multiple):
    if not multiple:
        # compile each cpp into a shared library 
        for cpp in glob.glob('*.cpp'):          
            print
            print 'compiling', cpp
            out = os.path.splitext(cpp)[0] + '.so'
            cmdline = 'g++ -shared -o %s -I../example ' \
                '-I/usr/include/python2.2 -lboost_python %s' % (out, cpp)
            os.system(cmdline)
    else:
        modules = get_modules() 
        # list cpp files in each module directory
        print
        for module in modules:
            # compile each
            for file in glob.glob(module+'/*.cpp'):
                print 'compiling', file
                out = os.path.splitext(file)[0] + '.obj'
                cmdline = 'g++ -shared -c -o %s -I../example ' \
                    '-I/usr/include/python2.2 %s' % (out, file)
                os.system(cmdline)
            # generate a dynamic library
            print 'linking'
            objs = ' '.join([x for x in glob.glob(module+'/*.obj')])
            out = module + '.so'
            cmdline = 'g++ -shared -o %s -lboost_python %s' % (out, objs)
            os.system(cmdline)
                
        
        

def run_tests():
    if os.system('python runtests.py') != 0:
        raise RuntimeError, 'tests failed'


def cleanup():
    extensions = '*.cpp *.so *.pyc'
    files = []
    for ext in extensions.split():
        files += glob.glob(ext)
    for file in files:
        try:
            os.remove(file)
        except OSError: pass

    modules = get_modules()
    for module in modules:
        try:
            shutil.rmtree(module)
        except OSError: pass

    
def main(multiple):
    build_pyste_files(multiple)
    compile_pyste_files(multiple)
    run_tests()
    cleanup()

def get_modules():
    def getname(file):
        return os.path.splitext(os.path.basename(file))[0]
    return [getname(x) for x in glob.glob('../example/*.pyste')]

if __name__ == '__main__':
    try:
        main('--multiple')
        main('')
    except RuntimeError, e:
        print e        
