from __future__ import generators

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
def makeid(name):
    'Returns the name as a valid identifier'
    for invalidchar in ('::', '<', '>', ' ', ',', '.', '#'):
        name = name.replace(invalidchar, '_') 
    # avoid duplications of '_' chars
    names = [x for x in name.split('_') if x]
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
