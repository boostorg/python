from gen_callback import *
from gen_caller import *
from gen_init_function import *
from gen_signatures import *
from gen_singleton import *
from gen_extclass import *

def gen_all(args):
    open('callback.h', 'w').write(gen_callback(args))
    open('caller.h', 'w').write(gen_caller(args))
    open('init_function.h', 'w').write(gen_init_function(args))
    open('signatures.h', 'w').write(gen_signatures(args))
    open('singleton.h', 'w').write(gen_singleton(args))
    open('extclass.h', 'w').write(gen_extclass(args))

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_all(args)

    
