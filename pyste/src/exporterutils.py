'''
Various helpers for interface files.
'''

from settings import *
from policies import *
from declarations import *

#==============================================================================
# FunctionWrapper
#==============================================================================
class FunctionWrapper(object): 
    '''Holds information about a wrapper for a function or a method. It is in 2
    parts: the name of the Wrapper, and its code.  The code is placed in the
    declaration section of the module, while the name is used to def' the
    function or method (with the pyste namespace prepend to it). If code is None,
    the name is left unchanged.
    '''

    def __init__(self, name, code=None):
        self.name = name
        self.code = code

    def FullName(self):
        if self.code:
            return namespaces.pyste + self.name
        else:
            return self.name


_printed_warnings = {} # used to avoid double-prints of warnings

#==============================================================================
# HandlePolicy
#==============================================================================
def HandlePolicy(function, policy):
    '''Show a warning to the user if the function needs a policy and doesn't
    have one. Return a policy to the function, which is the given policy itself
    if it is not None, or a default policy for this method.
    '''
    
    def IsString(type):
        'Return True if the Type instance can be considered a string'
        return type.const and type.name == 'char' and isinstance(type, PointerType)

    def IsPyObject(type):
        return type.FullName() == '_object *' # internal name of PyObject
    
    result = function.result
    # basic test if the result type demands a policy
    needs_policy = isinstance(result, (ReferenceType, PointerType))
    # if the function returns const char*, a policy is not needed
    if IsString(result) or IsPyObject(result):
        needs_policy = False
    # if returns a const T&, set the default policy
    if policy is None and result.const and isinstance(result, ReferenceType):
        policy = return_value_policy(copy_const_reference)
    # show a warning to the user, if needed
    if needs_policy and policy is None:
        global _printed_warnings
        warning = '---> Error: %s returns a pointer or a reference, ' \
                  'but no policy was specified.' % function.FullName()
        if warning not in _printed_warnings:
            print warning
            print 
            # avoid double prints of the same warning
            _printed_warnings[warning] = 1
    return policy
            


#==============================================================================
# WarnForwardDeclarations
#==============================================================================
def WarnForwardDeclarations(function):
    '''Checks if any of the parameters or the result of the function are
    incomplete types.'''

    types = [function.result] + function.parameters
    types = [x for x in types if x]
    for type in types:
        if type.incomplete:
            msg = '---> Error: %s is forward declared. Please include the ' \
                'appropriate header with its definition' % type.name
            # disable this for now... it was reporting too many false 
            # forward declarations to be useful
            if 0 and msg not in _printed_warnings:
                print msg
                print 
                _printed_warnings[msg] = 1
    
