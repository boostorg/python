#!/usr/bin/python

import os
import glob

def build_pyste_files():
    # list all pyste files in the example directory
    examples = glob.glob('../example/*.pyste')
    # generate the cpp file for each example
    for example in examples:    
        path, filename = os.path.split(example)
        module = os.path.splitext(filename)[0]
        os.system('python ../src/pyste.py -I%s --module=%s %s' % (path, module, example))
    

def compile_pyste_files():
    # list all cpp files in this directory
    cpps = glob.glob('*.cpp')
    # compile each cpp into a shared library 
    for cpp in cpps:          
        print
        print 'compiling', cpp
        out = os.path.splitext(cpp)[0] + '.so'
        cmdline = 'g++ -shared -o %s -I../example ' \
            '-I/usr/include/python2.2 -lboost_python %s' % (out, cpp)
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
        os.remove(file)

    
def main():
    build_pyste_files()
    compile_pyste_files()
    run_tests()
    cleanup()

if __name__ == '__main__':
    try:
        main()
    except RuntimeError, e:
        print e        
