# Dummy file actually to be included by Jam when the python headers
# can't be found

if ! $(gNO_PYTHON_INSTALL)
{
    ECHO Couldn't find Python $(PYTHON_VERSION) installation in $(PYTHON_ROOT) ;
    ECHO skipping Boost.Python library build ;
    ECHO You can configure the location of your python installation, by setting: ;
    ECHO PYTHON_ROOT - currently \"$(PYTHON_ROOT)\" ;
    ECHO PYTHON_VERSION - currently \"$(PYTHON_VERSION)\" ;
    ECHO PYTHON_INCLUDES - configured from PYTHON_ROOT, currently \"$(PYTHON_INCLUDES)\" ;
    ECHO PYTHON_LIB_PATH - configured from PYTHON_ROOT, currently \"$(PYTHON_LIB_PATH)\" ;
}
gNO_PYTHON_INSTALL ?= true ;
