r"""
>>> template = '''    template <class T%(, class A%+%)>
...     static PyObject* call( %1(T::*pmf)(%(A%+%:, %))%2, PyObject* args, PyObject* ) {
...         PyObject* self;
... %(        PyObject* a%+;
... %)        if (!PyArg_ParseTuple(args, const_cast<char*>("O%(O%)"), &self%(, &a%+%)))
...             return 0;
...         T& target = from_python(self, type<T&>());
...         %3to_python((target.*pmf)(%(
...                 from_python(a%+, type<A%+>())%:,%)
...                 ));%4
...     }'''

>>> print gen_function(template, 0, 'R ', '', 'return ', '')
    template <class T>
    static PyObject* call( R (T::*pmf)(), PyObject* args, PyObject* ) {
        PyObject* self;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(
                ));
    }

>>> print gen_function(template, 2, 'R ', '', 'return ', '')    
    template <class T, class A1, class A2>
    static PyObject* call( R (T::*pmf)(A1, A2), PyObject* args, PyObject* ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &self, &a1, &a2))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(
                from_python(a1, type<A1>()),
                from_python(a2, type<A2>())
                ));
    }

>>> print gen_function(template, 3, 'void ', ' const', '', '\n'+8*' ' + 'return none();')
    template <class T, class A1, class A2, class A3>
    static PyObject* call( void (T::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &self, &a1, &a2, &a3))
            return 0;
        T& target = from_python(self, type<T&>());
        to_python((target.*pmf)(
                from_python(a1, type<A1>()),
                from_python(a2, type<A2>()),
                from_python(a3, type<A3>())
                ));
        return none();
    }
"""
import string

def _find(s, sub, start=0, end=None):
    """Just like string.find, except it returns end or len(s) when not found.
    """
    if end == None:
        end = len(s)
        
    pos = string.find(s, sub, start, end)
    if pos < 0:
        return end
    else:
        return pos

def _raise_no_argument(key, n, args):
    raise IndexError(str(key) + " extra arg(s) not passed to gen_function")
    
def _gen_common_key(key, n, args, fill = _raise_no_argument):
    # import sys
    # print >> sys.stderr, "_gen_common_key(", repr(key), ",", repr(n), ',', repr(args), ',', fill, ')'
    # sys.stderr.flush()
    if len(key) > 0 and key in '123456789':
        index = int(key) - 1;
        
        if index >= len(args):
            return fill(key, n, args)

        arg = args[index]
        if callable(arg):
            return str(arg(key, n, args))
        else:
            return str(arg)
    elif key in ('x','n','-','+'):
        return str(n + {'-':-1,'+':+1,'x':0,'n':0}[key])
    else:
        return key

def _gen_arg(template, n, args, fill = _raise_no_argument):
    
    result = ''
    i = 0
    while i < len(template): # until the template is consumed
        # consume everything up to the first '%'
        delimiter_pos = _find(template, '%', i)
        result = result + template[i:delimiter_pos]
        
        # The start position of whatever comes after the '%'+key
        start = delimiter_pos + 2
        key = template[start - 1 : start] # the key character. If there were no
                                          # '%'s left, key will be empty

        if 0 and key == 'n':
            result = result + `n`
        else: 
            result = result + _gen_common_key(key, n, args, fill)

        i = start

    return result

def gen_function(template, n, *args, **keywords):
    r"""gen_function(template, n, [args...] ) -> string
    
    Generate a function declaration based on the given template.
    
    Sections of the template between '%(', '%)' pairs are repeated n times. If '%:'
    appears in the middle, it denotes the beginning of a '%'.
    
    Sections of the template between '%{', '%}' pairs are ommitted if n == 0.
    
    %n is transformed into the string representation of 1..n for each
    repetition within %(...%). Elsewhere, %n is transformed into the
    string representation of n

    %- is transformed into the string representation of 0..n-1 for
    each repetition within %(...%). Elsewhere, %- is transformed into the
    string representation of n-1.

    %+ is transformed into the string representation of 2..n+1 for
    each repetition within %(...%). Elsewhere, %- is transformed into the
    string representation of n+1.

    %x is always transformed into the string representation of n

    %z, where z is a digit, selects the corresponding additional
    argument. If that argument is callable, it is called with three
    arguments:
        key  - the string representation of 'z'
        n    - the iteration number
        args - a tuple consisting of all the additional arguments to
               this function
    otherwise, the selected argument is converted to a string representation


    for example,
    
    >>> gen_function('%1 abc%x(%(int a%n%:, %));%{ // all args are ints%}', 2, 'void')
    'void abc2(int a0, int a1); // all args are ints'
    
    >>> gen_function('%1 abc(%(int a%n%:, %));%{ // all args are ints%}', 0, 'x')
    'x abc();'
        
    >>> gen_function('%1 abc(%(int a%n%:, %));%{ // all args are ints%}', 0, lambda key, n, args: 'abcd'[n])
    'a abc();'
        
    >>> gen_function('%2 %1 abc(%(int a%n%:, %));%{ // all args are ints%}', 0, 'x', fill = lambda key, n, args: 'const')
    'const x abc();'

    >>> gen_function('abc%[k%:v%]', 0, fill = lambda key, n, args, value = None: '<' + key + ',' + value + '>')
    'abc<k,v>'

"""
    expand = (lambda s, n = n:
              apply(gen_function, (s, n) + args, keywords))
    
    fill = keywords.get('fill', _raise_no_argument);
    result = ''
    i = 0
    while i < len(template): # until the template is consumed
        # consume everything up to the first '%'
        delimiter_pos = _find(template, '%', i)
        result = result + template[i:delimiter_pos]
        
        # The start position of whatever comes after the '%'+key            
        start = delimiter_pos + 2
        key = template[start - 1 : start] # the key character. If there were no
                                          # '%'s left, key will be empty

        pairs = { '(':')', '{':'}', '[':']' }
        
        if key in pairs.keys():
            end = string.find(template, '%' + pairs[key], start)
            assert end >= 0, "Matching '" + '%' + pairs[key] +"' not found!"
            delimiter_pos = end

            if key == '{':
                if n > 0:
                    result = result + expand(template[start:end])
            else:
                separator_pos = _find(template, '%:', start, end)
                remainder = template[separator_pos+2 : end]
                
                if key == '(':
                    for x in range(n):
                        
                        iteration = expand(
                            template[start:separator_pos], x)
                        
                        result = result + expand(iteration, x)

                        if x != n - 1:
                            result = result + expand(remainder, x)
                else:
                    function_result = fill(
                        template[start:separator_pos], n, args, value = remainder)
                    result = result + expand(function_result)
                
        else:
            result = result + expand(_gen_common_key(key, n, args, fill))
            
        i = delimiter_pos + 2
        
    return result

def gen_functions(template, n, *args, **keywords):
    r"""gen_functions(template, n, [args...]) -> string

    Call gen_function repeatedly with from 0..n and the given optional
    arguments.

    >>> print gen_functions('%1 abc(%(int a%n%:, %));%{ // all args are ints%}\n', 2, 'void'),
    void abc();
    void abc(int a0); // all args are ints
    void abc(int a0, int a1); // all args are ints
    
    """
    fill = keywords.get('fill', _raise_no_argument);
    result = ''
    for x in range(n + 1):
        result = result + apply(gen_function, (template, x) + args, keywords)
    return result

if __name__ == '__main__':
    import doctest
    import sys
    doctest.testmod(sys.modules.get(__name__))
