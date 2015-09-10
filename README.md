# Boost.NumPy

Boost.NumPy is an extension for Boost.Python that adds NumPy support.

It is intended as a replacement for the old numeric support in
Boost.Python proper, which is now out-of-date and does not support
C/C++ pointer access to the data.  Because it builds against the NumPy
headers and hence has a dependency that Boost.Python does not, it is
intended to be built as a separate library.  This is also not intended
to be a high-level C++ array library; it would be more accurate to
consider it a C++ NumPy API, with the intent of making the NumPy C-API
available in a form that is safer and more convenient for C++ users
(and particularly those using Boost.Python, of course).

*THIS IS NOT AN OFFICIAL BOOST LIBRARY*

...we're just calling it Boost.NumPy right now because that clearly
indicates that it's for Boost.Python and NumPy.  We may
propose it for inclusion in Boost eventually, but that's not high
on the priority list for any of the original authors.


## INSTALLATION

We have provided three build systems: Boost.Build, SCons, and CMake
build system.  At the moment, we recommend using SCons or CMake on
Linux and CMake on Windows.

Building with SCons should be as simple as running `scons` and `scons
install`, but you may need to use the `--with-boost*` options (see
`scons --help`) to specify where to find Boost.  The Python that is
used by SCons will be the one built against. Additionally, the
SConsChecks submodule must be initialized by git before building
by running

    git submodule update --init

Please see `libs/numpy/doc/cmakeBuild.rst` for more information on
building with CMake.


## DOCUMENTATION

More documentation on how to use the library can be found in
libs/numpy/doc, but it may be most useful to start with the
examples in libs/numpy/examples.  The headers files are also
well documented and are intended to serve as a reference.


## ISSUES AND NEW FEATURES

Please create an issue on the GitHub site at:

https://github.com/ndarray/Boost.NumPy/issues

Patches and detailed debugging are greatly appreciated; the authors don't have much time to devote to this project on a regular basis, but we do try to fix critical bugs.


## CONTACT

Please post questions, bug reports, and feature requests to
the GitHub issues list (see above).


## MULTI-PLATFORM SUPPORT

The vast majority of development has happened on Linux/g++, and while
we have taken some steps to support MacOS/clang, there hasn't been
much testing.  There has been very little testing on Windows, though there
has been some work contributed to get it working there.

In short, we'd really love to have some testing on additional platforms,
especially from people who know their way around SCons, NumPy, or
Boost.Python.


## HISTORY/AUTHORS

Boost.NumPy was originally written by Jim Bosch as part of the
"ndarray" C++ library, then reorganized into a standalone component,
cleaned up, and documented as part of a Boost-sponsored
Google Summer of Code by Ankit Daftery, mentored by Stefan Seefeld.
Philip Miller contributed the CMake build system.

An older version of this project is hosted on the Boost Sandbox:

https://svn.boost.org/svn/boost/sandbox/numpy

but the latest version is on GitHub:

https://github.com/ndarray/Boost.NumPy
