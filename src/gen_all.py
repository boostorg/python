from gen_callback import *
from gen_caller import *
from gen_init_function import *
from gen_signatures import *
from gen_singleton import *
from gen_extclass import *

def gen_all(args):
    open('callback.hpp', 'w').write(gen_callback(args))
    open('caller.hpp', 'w').write(gen_caller(args))
    open('init_function.hpp', 'w').write(gen_init_function(args))
    open('signatures.hpp', 'w').write(gen_signatures(args))
    open('instance.hpp', 'w').write(gen_singleton(args))
    open('extension_class.hpp', 'w').write(gen_extclass(args))

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 10
    else:
        args = int(sys.argv[1])

    print gen_all(args)

    
