#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_performance.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/ 5    rmg     File creation
#
# $Id$
#

from time import clock
from testlinear import Vector

def fillByAppend (container, size):
    append = container.append
    for count in range (size):
        append (count)

def fillByExtend (container, size):
    extend = container.extend
    for count in range (size / 100):
        extend (range (count * 100, count * 100 + 100))

def search (container, item, iterations):
    index = container.index
    for count in range (iterations):
        index (item)

def reverse_part (container, start, end):
    end -= 1
    while start < end:
        temp = container[start]
        container[start] = container[end]
        container[end] = temp
        start += 1
        end -= 1

def reorder (container, block = 10):
    for count in range (len(container) / block):
        reverse_part (container, count * block, count * block + block)

def testPerformance (container):
    size = 1000000
    start = clock()
    fillByExtend (container, size)
    print "Fill:", clock() - start

    start = clock()
    search (container, container[size - 1], 10)
    print "Search:", clock() - start

    start = clock()
    reorder (container, 8)
    reorder (container, 16)
    reorder (container, 32)
    print "Reorder:", clock() - start

#    print container[:20]
#    print container[-20:]

    start = clock()
    container.sort()
    print "Sort:", clock() - start


print "list ====="
testPerformance ([])
v1 = Vector()
v1.reserve (1000000)
print "vector (with reserve) ====="
testPerformance (v1)

print "list ====="
testPerformance ([])
print "vector (no reserve) ====="
testPerformance (Vector())

