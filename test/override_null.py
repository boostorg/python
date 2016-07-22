import override_null_ext

foo = override_null_ext.foo()
foo.f()

class PyFoo(override_null_ext.foo):
    def __init__(self):
        super(override_null_ext.foo, self).__init__(self)

pyfoo = PyFoo()
try:
    thrown = False
    pyfoo.f()
except:
    thrown = True
assert thrown

class PyFooOverride(override_null_ext.foo):
    def __init__(self):
        super(override_null_ext.foo, self).__init__(self)

    def f(self):
        return None

pyfoo = PyFooOverride()
pyfoo.f()
