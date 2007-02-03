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

Boost.Python requires `Python 2.2`_ *or* |newer|__.

.. _Python 2.2: http://www.python.org/2.2
__ http://www.python.org

Background
==========

There are two basic models for combining C++ and Python:

- extending_, in which the end-user launches the Python
  interpreter executable and imports Python “extension modules”
  written in C++.  Think of providing libraries written in C++ for
  Python programmers to use.  From Python, these modules look just
  like regular Python modules.

- embedding_, in which the end-user launches a program written
  in C++ that in turn invokes the Python interpreter as a library
  subroutine.  Think of adding scriptability to an existing
  application.

.. _extending: http://www.python.org/doc/current/ext/intro.html
.. _embedding: http://www.python.org/doc/current/ext/embedding.html

The key distinction between extending and embedding is the location
of C++' ``main()`` function: in the Python interpreter executable,
or in some other program, respectively.  Note that even when
embedding Python in another program, `extension modules are often the best
way to give Python code access to C/C++ functionality`__, so the use
of extension modules is really at the heart of both models.

__ http://www.python.org/doc/current/ext/extending-with-embedding.html

Except in rare cases, extension modules are built as
dynamically-loaded libraries with a single entry point, which means
you can change them without recompiling either the other extension
modules or the executable containing ``main()``.

Choosing a Boost.Python Library Binary
======================================

Boost.Python extension modules draw on the services of the
Boost.Python library binary.  Since Boost.Python is a
separately-compiled (as opposed to `header-only`_) library, it
comes in both static and dynamic flavors.  Take care to choose the
right flavor for your application.  The dynamic library is the
safest and most-versatile choice:

- A single copy of the library code is used by all extension
  modules built with a given toolset.

- The library contains a type conversion registry.  Because one
  registry is shared among all extension modules, a instances of a
  class exposed to Python in one dynamically-loaded extension
  module can be passed to functions exposed in another such module.

It is appropriate to use the static Boost.Python library in any of
the following cases:

- You are extending_ python and the types exposed in your
  dynamically-loaded extension module don't need to be used by any
  other Boost.Python extension modules, and you don't care if the
  core library code is duplicated among them.

- You are embedding_ python in your application and either:

  - You are targeting a Unix variant OS, where the
    dynamically-loaded extension modules can “see” the Boost.Python
    library symbols that are part of the executable.

  - You have statically linked some Boost.Python extension modules
    into your application and you don't care if any
    dynamically-loaded Boost.Python extension modules can use the
    types exposed by your statically-linked extension modules (and
    vice-versa).

.. _header-only: ../../../more/getting_started.html#header-only-libraries

Although they are supported under Boost.Python, we're not going to
cover the esoteric case of statically-linked extension modules here
in detail.


