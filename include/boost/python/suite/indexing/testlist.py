#!/usr/bin/python
# -*- mode:python -*-
#
# Python module testlist.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this material for any purpose is hereby
# granted without fee, provided the above notices are retained on all
# copies.  Permission to modify the material and to distribute modified
# versions is granted, provided the above notices are retained, and a
# notice that the material was modified is included with the above
# copyright notice.
#
# History
# =======
# 2003/ 8/20	rmg	File creation
#
# $Id$
#

from types import SliceType

class ListIter:
    def __init__(self, l):
        self.myList = l
        self.myIndex = 0

    def next(self):
        print "next(ListIter)",
        try:
            result = self.myList[self.myIndex]
            self.myIndex += 1
            print "ok"
            return result

        except IndexError:
            print "StopIteration"
            raise StopIteration

class MyList:
    def __init__(self, l = None):
        print "__init__(MyList)"

        if l == None:
            self.myList = list()
        else:
            self.myList = l

    def __setitem__(self, key, value):
        print "__setitem__(MyList, %s, %s)" % (key, value)
        if isinstance (key, SliceType):
            if key.step != None:
                raise TypeError ("Invalid slice for list")
            self.myList.__setslice__ (key.start, key.stop, value)

        else:
            self.myList.__setitem__(key, value)

    def __iter__(self):
        print "__iter__(MyList)"
        return ListIter(self.myList)

    def __getitem__(self, key):
        print "__getitem__(MyList, %s)" % key
        if isinstance (key, SliceType):
            if key.step != None:
                raise TypeError ("Invalid slice for list")
            return self.myList.__getslice__ (key.start, key.stop)
        return self.myList.__getitem__(key)

    def __delitem__(self, key):
        print "__delitem__(MyList, %s)" % key
        if isinstance (key, SliceType):
            if key.step != None:
                raise TypeError ("Invalid slice for list")
            self.myList.__delslice__ (key.start, key.stop)

        else:
            self.myList.__delitem__(key)

    def __len__(self):
        print "__len__(MyList)"
        return self.myList.__len__()

    def __add__(self, value):
        print "__add__(MyList, %s)" % value
        return MyList(self.myList.__add__(value))

    def __mul__(self, value):
        print "__mul__(MyList, %s)" % value
        return MyList(self.myList.__mul__(value))

#    def __imul__(self, value):
#        print "__imul__(MyList, %s)" % value
#        self.myList.__imul__(value)

#     def __contains__(self, value):
#         print "__contains__(MyList, %s)" % value
#         return self.myList.__contains__(value)

    def append(self, value):
        print "append(MyList, %s)" % value
        self.myList.append(value)

    def __insert__(self, key, value):
        print "__insert__(MyList, %s, %s)" % (key, value)
        self.myList.__insert__(key, value)

#     def __setslice__(self, start, end, value):
#         print "__setslice__(MyList, %s, %s, %s)" % (start, end, value)
#         self.myList.__setslice__(start, end, value)

#     def __getslice__(self, start, end):
#         print "__getslice__(MyList, %s, %s)" % (start, end)
#         self.myList.__getslice__(start, end)

#     def __delslice__(self, start, end):
#         print "__delslice__(MyList, %s, %s)" % (start, end)
#         self.myList.__delslice__(start, end)

    def __repr__(self):
        return self.myList.__repr__()

x = MyList()

x.append(4)
x.append(5)
x.append(6)

print 4 in x
print 7 in x

x[1] = 0
x[2:3]=[7, 8, 9]
print x + [10]
print x[2:]

del x[2:3]
del x[0]

print x

x[1:2] = []

print x

x *= 2

print x

x[0:3][0:1] = [1]

print x

