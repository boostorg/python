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
    
    result = function.result
    # basic test if the result type demands a policy
    needs_policy = isinstance(result, (ReferenceType, PointerType))
    # if the function returns const char*, a policy is not needed
    if IsString(result):
        needs_policy = False
    # if returns a const T&, set the default policy
    if policy is None and result.const and isinstance(result, ReferenceType):
        policy = return_value_policy(copy_const_reference)
    # show a warning to the user, if needed
    if needs_policy and policy is None:
        global _printed_warnings
        warning = '---> Error: Method "%s" needs a policy.' % m.FullName()
        if warning not in _printed_warnings:
            print warning
            print 
            # avoid double prints of the same warning
            _printed_warnings[warning] = 1
    return policy
            
_printed_warnings = {} # used to avoid double-prints in HandlePolicy
