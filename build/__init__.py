# Dummy file actually to be included by Jam when the python headers
# can't be found

if ! $(gNO_PYTHON_INSTALL)
{
    ECHO "Couldn't find Python $(PYTHON_VERSION) installation in $(PYTHON_ROOT)" ;
    ECHO skipping Boost.Python library build ;
    ECHO You can configure the location of your python installation, by setting: ;
    ECHO PYTHON_ROOT - currently \"$(PYTHON_ROOT)\" ;
    ECHO PYTHON_VERSION - currently \"$(PYTHON_VERSION)\" ;
    ECHO ;
    ECHO "The following are automatically configured from PYTHON_ROOT if not otherwise set" ;
    ECHO "    PYTHON_INCLUDES    - path to Python #include directories; currently" \"$(PYTHON_INCLUDES)\" ;
    ECHO "    PYTHON_LIB_PATH    - path to Python library; currently" \"$(PYTHON_LIB_PATH)\" ;
    ECHO "    PYTHON_STDLIB_PATH - path to Python standard library modules; currently" \"$(PYTHON_STDLIB_PATH)\" ;
}
gNO_PYTHON_INSTALL ?= true ;
