from __future__ import generators
import string

#==============================================================================
# enumerate
#==============================================================================
def enumerate(seq):
    i = 0
    for x in seq:
        yield i, x
        i += 1  


#==============================================================================
# makeid
#==============================================================================
_valid_chars = string.ascii_letters + string.digits + '_'
_valid_chars = dict(zip(_valid_chars, _valid_chars))

def makeid(name):
    'Returns the name as a valid identifier'
    newname = []
    for char in name:
        if char not in _valid_chars:
            char = '_'
        newname.append(char)
    newname = ''.join(newname)
    # avoid duplications of '_' chars
    names = [x for x in newname.split('_') if x]
    return '_'.join(names)
 

#==============================================================================
# remove_duplicated_lines
#==============================================================================
def remove_duplicated_lines(text):
    includes = text.splitlines()
    d = dict([(include, 0) for include in includes])
    return '\n'.join(d.keys())


#==============================================================================
# left_equals
#==============================================================================
def left_equals(s):
        s = '// %s ' % s
        return s + ('='*(80-len(s))) + '\n'  
