# Dummy file actually to be included by Jam when the python headers
# can't be found

if ! $(gNO_PYTHON_INSTALL)
{
    ECHO "---------------------------------------------------------------------" ;
    ECHO skipping Boost.Python library build ;
    ECHO You can configure the location of your python installation, by setting: ;
    ECHO "PYTHON_ROOT    - currently" \"$(PYTHON_ROOT:J=" ")\" ;
    ECHO "PYTHON_VERSION - The 2-part python Major.Minor version number (e.g." ;
    ECHO "                 \"2.2\", NOT \"2.2.1\")  - currently" \"$(PYTHON_VERSION)\" ;
    ECHO ;
    ECHO "The following are automatically configured from PYTHON_ROOT if not" ;
    ECHO "otherwise set:" ;
    ECHO "    PYTHON_INCLUDES    - path to Python #include directories; currently" \"$(PYTHON_INCLUDES:J=" ")\" ;
    ECHO "    PYTHON_LIB_PATH    - path to Python library; currently" ;
    ECHO "                         " \"$(PYTHON_LIB_PATH:J=" ")\" ;
    ECHO "    PYTHON_STDLIB_PATH - path to Python standard library modules; currently" ;
    ECHO "                         " \"$(PYTHON_STDLIB_PATH:J=" ")\" ;
    ECHO "---------------------------------------------------------------------" ;
}
gNO_PYTHON_INSTALL ?= true ;
