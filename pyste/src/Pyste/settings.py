
#==============================================================================
# Global information
#==============================================================================

DEBUG = False
USING_BOOST_NS = True

class namespaces:
    boost = 'boost::'
    pyste = ''
    python = '' # default is to not use boost::python namespace explicitly, so
                # use the "using namespace" statement instead
