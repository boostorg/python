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

def _gen_common_key(key, n, args):
    if len(key) > 0 and key in '123456789':
        return str(args[int(key) - 1])
    elif key == 'x':
        return str(n)
    else:
        return key

def _gen_arg(template, n, args, delimiter = '%'):
    result = ''
    i = 0
    while i < len(template): # until the template is consumed
        # consume everything up to the first delimiter
        delimiter_pos = _find(template, delimiter, i)
        result = result + template[i:delimiter_pos]
        
        # The start position of whatever comes after the delimiter+key
        start = delimiter_pos + 2
        key = template[start - 1 : start] # the key character. If there were no
                                          # delimiters left, key will be empty

        if key == 'n':
            result = result + `n`
        elif key == 'N':
            result = result + `n-1`
        else:
            result = result + _gen_common_key(key, n, args)

        i = start
        
    return result

def gen_function(template, n, *args, **keywords):
    r"""gen_function(template, n, [args...] ) -> string
    
    Generate a function declaration based on the given template.
    
    Sections of the template between '%(', '%)' pairs are repeated n times. If '%:'
    appears in the middle, it denotes the beginning of a delimiter.
    
    Sections of the template between '%{', '%}' pairs are ommitted if n == 0.
    
    %n is transformed into the string representation of 1..n for each repetition
    of n.

    %N is transformed into the string representation of 0..(n-1) for each repetition
    of n.

    %i, where i is a digit, is transformed into the corresponding additional
    argument.
    
    %x is transformed into the number of the current repetition

    for example,
    
    >>> gen_function('%1 abc(%(int a%n%:, %));%{ // all args are ints%}', 2, 'void')
    'void abc(int a1, int a2); // all args are ints'
    >>> gen_function('%1 abc(%(int a%n%:, %));%{ // all args are ints%}', 0, 'x')
    'x abc();'
        

    >>> template = '''    template <class T%(, class A%n%)>
    ...     static PyObject* call( %1(T::*pmf)(%(A%n%:, %))%2, PyObject* args, PyObject* /* keywords */ ) {
    ...         PyObject* self;
    ... %(        PyObject* a%n;
    ... %)        if (!PyArg_ParseTuple(args, const_cast<char*>("O%(O%)"), &self%(, &a%n%)))
    ...             return 0;
    ...         T& target = from_python(self, type<T&>());
    ...         %3to_python((target.*pmf)(%(
    ...                 from_python(a%n, type<A%n>())%:,%)
    ...                 ));%4
    ...     }'''
    
    >>> print gen_function(template, 0, 'R ', '', 'return ', '')
        template <class T>
        static PyObject* call( R (T::*pmf)(), PyObject* args, PyObject* /* keywords */ ) {
            PyObject* self;
            if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
                return 0;
            T& target = from_python(self, type<T&>());
            return to_python((target.*pmf)(
                    ));
        }
    
    >>> print gen_function(template, 2, 'R ', '', 'return ', '')    
        template <class T, class A1, class A2>
        static PyObject* call( R (T::*pmf)(A1, A2), PyObject* args, PyObject* /* keywords */ ) {
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
        static PyObject* call( void (T::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* /* keywords */ ) {
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
    delimiter = keywords.get('delimiter', '%')
    result = ''
    i = 0
    while i < len(template): # until the template is consumed
        # consume everything up to the first delimiter
        delimiter_pos = _find(template, delimiter, i)
        result = result + template[i:delimiter_pos]
        
        # The start position of whatever comes after the delimiter+key            
        start = delimiter_pos + 2
        key = template[start - 1 : start] # the key character. If there were no
                                          # delimiters left, key will be empty

        pairs = { '(':')', '{':'}' }
        
        if key in pairs.keys():
            end = string.find(template, delimiter + pairs[key], start)
            assert end >= 0, "Matching '" + delimiter + pairs[key] +"' not found!"
            delimiter_pos = end

            if key == '{':
                if n > 0:
                    result = result + gen_function(template[start:end], n, args, delimiter)
            else:
                separator_pos = _find(template, delimiter + ':', start, end)
                separator = template[separator_pos+2 : end]

                for x in range(1, n + 1):
                    result = result + _gen_arg(template[start:separator_pos], x, args,
                                               delimiter)
                    if x != n:
                        result = result + separator
                
        else:
            result = result + _gen_common_key(key, n, args)
            
        i = delimiter_pos + 2
        
    return result

def gen_functions(template, n, *args):
    r"""gen_functions(template, n, [args...]) -> string

    Call gen_function repeatedly with from 0..n and the given optional
    arguments.

    >>> print gen_functions('%1 abc(%(int a%n%:, %));%{ // all args are ints%}\n', 2, 'void'),
    void abc();
    void abc(int a1); // all args are ints
    void abc(int a1, int a2); // all args are ints
    
    """
    result = ''
    for x in range(n + 1):
        result = result + apply(gen_function, (template, x) + args)
    return result

if __name__ == '__main__':
    import doctest
    doctest.testmod()
