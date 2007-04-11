.. Copyright David Abrahams 2006. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at
.. http://www.boost.org/LICENSE_1_0.txt)

==============================================
 |(logo)|__ Boost.Python Build and Test HOWTO
==============================================

.. |(logo)| image:: ../boost.png
   :alt: Boost C++ Libraries:
   :class: boost-logo

__ ../index.htm


.. section-numbering::
   :depth: 2

.. contents:: Contents
   :depth: 2
   :class: sidebar small

.. |newer| replace:: *newer*

Requirements
============

Boost.Python requires `Python 2.2`_ [#2.2]_ *or* |newer|__.  

.. _Python 2.2: http://www.python.org/2.2
__ http://www.python.org

No-Install Quickstart
=====================

There is no need to install Boost in order to get started using
Boost.Python.  These instructions use Boost.Build_ projects,
which will build those binaries as soon as they're needed.  Your
first tests may take a little longer while you wait for
Boost.Python to build, but doing things this way will save you from
worrying about build intricacies like which library binaries to use
for a specific compiler configuration.

.. Note:: Of course it's possible to use other build systems to
   build Boost.Python and its extensions, but they are not
   officially supported by Boost.  Moreover **99% of all “I can't
   build Boost.Python” problems come from trying to use another
   build system**.

   If you want to use another system anyway, we suggest that you
   follow these instructions, and then invoke ``bjam`` with the
   ``-a -o``\ *filename* option to dump the build commands it executes
   to a file, so you can see what your build system needs to do.

1. Get Boost; see sections 1 and 2 of the Boost `Getting Started Guide`_.
2. Get the ``bjam`` build driver.  See sections 5.2.1-5.2.3 of the
   Boost `Getting Started Guide`_.
3. cd into the ``libs/python/test/example`` directory.   

.. _Getting Started Guide: ../../../more/getting_started/index.html


Background
==========

There are two basic models for combining C++ and Python:

- extending_, in which the end-user launches the Python interpreter
  executable and imports Python “extension modules” written in C++.
  Think of taking a library written in C++ and giving it a Python
  interface so Python programmers can use it.  From Python, these
  modules look just like regular Python modules.

- embedding_, in which the end-user launches a program written
  in C++ that in turn invokes the Python interpreter as a library
  subroutine.  Think of adding scriptability to an existing
  application.

.. _extending: http://www.python.org/doc/current/ext/intro.html
.. _embedding: http://www.python.org/doc/current/ext/embedding.html

The key distinction between extending and embedding is the location
of C++' ``main()`` function: in the Python interpreter executable,
or in some other program, respectively.  Note that even when
embedding Python in another program, `extension modules are often
the best way to make C/C++ functionality accessible to Python
code`__, so the use of extension modules is really at the heart of
both models.

__ http://www.python.org/doc/current/ext/extending-with-embedding.html

Except in rare cases, extension modules are built as
dynamically-loaded libraries with a single entry point, which means
you can change them without rebuilding either the other extension
modules or the executable containing ``main()``.

Getting Boost.Python Binaries
=============================

Since Boost.Python is a separately-compiled (as opposed to
`header-only`_) library, its user relies on the services of a
Boost.Python library binary.  

.. _header-only: ../../../more/getting_started/windows.html#header-only-libraries

Installing Boost.Python on your System
--------------------------------------

If you need a regular, installation of the Boost.Python library
binaries on your system, the Boost `Getting Started Guide`_ will
walk you through the steps of installing one.  If building binaries
from source, you might want to supply the ``--with-python``
argument to ``bjam`` (or the ``--with-libraries=python`` argument
to ``configure``), so only the Boost.Python binary will be built,
rather than all the Boost binaries.

Configuring Boost.Build
=======================

As described in the `Boost.Build reference manual`__, a file called
``user-config.jam`` in your home
directory [#home-dir]_ is used to
describe the build resources available to the build system.  You'll
need to tell it about your Python installation.

__ http://www.boost.orgdoc/html/bbv2/advanced.html#bbv2.advanced.configuration

.. Admonition:: Users of Unix-Variant OSes

   If you are using a unix-variant OS and you ran Boost's
   ``configure`` script, it may have generated a
   ``user-config.jam`` for you. [#overwrite]_ If your ``configure``\
   /\ ``make`` sequence was successful and Boost.Python binaries
   were built, your ``user-config.jam`` file is probably already
   correct.

If you have a fairly “standard” python installation for your
platform, there's very little you need to do to describe it.
Simply having ::

  
  import toolset : using ; 
  using python ;

in a ``user-config.jam`` file in your home directory [#home-dir]_ 
should be enough. [#user-config.jam]_  For more complicated setups,
see `Advanced Configuration`_.

.. Note:: You might want to pass the ``--debug-configuration``
   option to ``bjam`` the first few times you invoke it, to make
   sure that Boost.Build is correctly locating all the parts of
   your Python installation.  If it isn't, consider passing some of
   the optional `Python configuration parameters`_ detailed below.

Building an Extension Module
============================


Testing
=======


Advanced Configuration
======================

If you have several versions of Python installed, or Python is
installed in an unusual way, you may want to supply any or all of
the following optional parameters to ``using python``.

Python Configuration Parameters
-------------------------------

version
  the version of Python to use.  Should be in Major.Minor
  format, for example, ``2.3``.  Do not include the subminor
  version (i.e. *not* ``2.5.1``).  If you have multiple Python
  versions installed, the version will usually be the only
  additional argument required.

cmd-or-prefix
  preferably, a command that invokes a Python
  interpreter.  Alternatively, the installation prefix for Python
  libraries and header files.  Use the alternative formulation if
  there is no appropriate Python executable available.

includes
  the ``#include`` path for Python headers. 

libraries
  the path to Python library binaries.  On MacOS/Darwin,
  you can also pass the path of the Python framework.

condition
  if specified, should be a set of Boost.Build
  properties that are matched against the build configuration when
  Boost.Build selects a Python configuration to use.  

extension-suffix
  A string to append to the name of extension
  modules before the true filename extension.  You almost certainly
  don't need to use this.  Usually this suffix is only used when
  targeting a Windows debug build of Python, and will be set
  automatically for you based on the value of the
  ``<python-debugging>`` feature.  However, at least one Linux
  distribution (Ubuntu Feisty Fawn) has a specially configured
  `python-dbg`__ package that claims to use such a suffix.

__ https://wiki.ubuntu.com/PyDbgBuilds


Examples
--------

Note that in the examples below, case and *especially whitespace* are
significant.

- If you have both python 2.5 and python 2.4 installed,
  ``user-config.jam`` might contain::
  
    using python : 2.5 ;  # Make both versions of Python available 

    using python : 2.4 ;  # To build with python 2.4, add python=2.4 
                          # to your command line.

  The first version configured (2.5) becomes the default.  To build
  against python 2.4, add ``python=2.4`` to the ``bjam`` command line.

- If you have python installed in an unusual location, you might
  supply the path to the interpreter in the ``cmd-or-prefix``
  parameter::

    using python : : /usr/local/python-2.6-beta/bin/python ;

- If you have a separate build of Python for use with a particular
  toolset, you might supply that toolset in the ``condition``
  parameter::

    using python ;  # use for most toolsets
    
    # Use with Intel C++ toolset
    using python 
         : # version
         : c:\\Devel\\Python-2.5-IntelBuild\\PCBuild\\python # cmd-or-prefix
         : # includes
         : # libraries
         : <toolset>intel # condition
         ;

- You can set up your user-config.jam so a bjam built under Windows 
  can build/test both Windows and Cygwin_ python extensions.  Just pass
  ``<target-os>cygwin`` in the ``condition`` parameter
  for the cygwin python installation::

    # windows installation
    using python ;

    # cygwin installation
    using python : : c:\\cygwin\\bin\\python2.5 : : : <target-os>cygwin ;

  when you put target-os=cygwin in your build request, it should build
  with the cygwin version of python: [#flavor]_

    bjam target-os=cygwin toolset=gcc 

  This is supposed to work the other way, too (targeting windows
  python with a Cygwin_ bjam) but it seems as though the support in
  Boost.Build's toolsets for building that way is broken at the
  time of this writing.

- Note that because of `the way Boost.Build currently selects target
  alternatives`__, you might have be very explicit in your build
  requests.  For example, given::

    using python : 2.5 ; # a regular windows build
    using python : 2.4 : : : : <target-os>cygwin ;

  building with ::

    bjam target-os=cygwin

  will yield an error.  Instead, you'll need to write::

    bjam target-os=cygwin/python=2.4

.. _Cygwin: http://cygwin.com

__ http://zigzag.cs.msu.su/boost.build/wiki/AlternativeSelection

Choosing a Boost.Python Library Binary
======================================

If—instead of letting Boost.Build construct and link withthe right
libraries automatically—you choose to use a pre-built Boost.Python
library, you'll need to think about which one to link with.  The
Boost.Python binary comes in both static and dynamic flavors.  Take
care to choose the right flavor for your application. [#naming]_

The Dynamic Binary
------------------

The dynamic library is the safest and most-versatile choice:

- A single copy of the library code is used by all extension
  modules built with a given toolset. [#toolset-specific]_

- The library contains a type conversion registry.  Because one
  registry is shared among all extension modules, instances of a
  class exposed to Python in one dynamically-loaded extension
  module can be passed to functions exposed in another such module.

The Static Binary
-----------------

It might be appropriate to use the static Boost.Python library in
any of the following cases:

- You are extending_ python and the types exposed in your
  dynamically-loaded extension module don't need to be used by any
  other Boost.Python extension modules, and you don't care if the
  core library code is duplicated among them.

- You are embedding_ python in your application and either:

  - You are targeting a Unix variant OS other than MacOS or AIX,
    where the dynamically-loaded extension modules can “see” the
    Boost.Python library symbols that are part of the executable.

  - Or, you have statically linked some Boost.Python extension
    modules into your application and you don't care if any
    dynamically-loaded Boost.Python extension modules are able to
    use the types exposed by your statically-linked extension
    modules (and vice-versa).

Notes for MinGW (and Cygwin with -mno-cygwin) GCC Users
=======================================================

If you are using a version of Python prior to 2.4.1 with a MinGW
prior to 3.0.0 (with binutils-2.13.90-20030111-1), you will need to
create a MinGW-compatible version of the Python library; the one
shipped with Python will only work with a Microsoft-compatible
linker. Follow the instructions in the “Non-Microsoft” section of
the “Building Extensions: Tips And Tricks” chapter in `Installing
Python Modules`__ to create ``libpythonXX.a``, where ``XX``
corresponds to the major and minor version numbers of your Python
installation.

__ http://www.python.org/doc/current/inst/index.html

-----------------------------

.. [#2.2] Note that although we tested earlier versions of
   Boost.Python with Python 2.2, and we don't *think* we've done
   anything to break compatibility, this release of Boost.Python
   may not have been tested with versions of Python earlier than
   2.4, so we're not 100% sure that python 2.2 and 2.3 are
   supported.

.. [#naming] Information about how to identify the
   static and dynamic builds of Boost.Python:

   * `on Windows`__
   * `on Unix variants`__

   __ ../../../more/getting_started/windows.html#library-naming
   __ ../../../more/getting_started/unix-variants.html#library-naming

   Be sure to read this section even if your compiler supports
   auto-linking, as Boost.Python does not yet take advantage of
   that feature.

.. [#toolset-specific] Because of the way most \*nix platforms
   share symbols among dynamically-loaded objects, I'm not
   certainextension modules built with different compiler toolsets
   will always use different copies of the Boost.Python library
   when loaded into the same Python instance.  Not using different
   libraries could be a good thing if the compilers have compatible
   ABIs, because extension modules built with the two libraries
   would be interoperable.  Otherwise, it could spell disaster,
   since an extension module and the Boost.Python library would
   have different ideas of such things as class layout. I would
   appreciate someone doing the experiment to find out what
   happens.

.. [#overwrite] ``configure`` overwrites the existing
   ``user-config.jam`` in your home directory
   (if any) after making a backup of the old version.

.. [#flavor] Note that the ``<target-os>cygwin`` feature is
   different from the ``<flavor>cygwin`` subfeature of the ``gcc``
   toolset, and you might need handle both explicitly if you also
   have a MinGW GCC installed.

.. [#user-config.jam] Create the ``user-config.jam`` file if you don't
   already have one.  

.. [#home-dir] Windows users, your home directory can be
   found by typing::

     ECHO %HOMEDRIVE%%HOMEPATH%

   into a `Windows command prompt`__

__ ../../../more/getting_started/windows.html#or-build-from-the-command-prompt
