# Revision history:
#   12 Apr 01 use os.path, shutil
#   Initial version: R.W. Grosse-Kunstleve

bpl_src = "/libs/python/src"
bpl_tst = "/libs/python/test"
bpl_exa = "/libs/python/example"
files = (
bpl_src + "/classes.cpp",
bpl_src + "/conversions.cpp",
bpl_src + "/extension_class.cpp",
bpl_src + "/functions.cpp",
bpl_src + "/init_function.cpp",
bpl_src + "/module_builder.cpp",
bpl_src + "/objects.cpp",
bpl_src + "/types.cpp",
bpl_src + "/cross_module.cpp",
bpl_tst + "/comprehensive.cpp",
bpl_tst + "/comprehensive.hpp",
bpl_tst + "/comprehensive.py",
bpl_tst + "/doctest.py",
bpl_exa + "/abstract.cpp",
bpl_exa + "/getting_started1.cpp",
bpl_exa + "/getting_started2.cpp",
bpl_exa + "/simple_vector.cpp",
bpl_exa + "/do_it_yourself_convts.cpp",
bpl_exa + "/nested.cpp",
bpl_exa + "/pickle1.cpp",
bpl_exa + "/pickle2.cpp",
bpl_exa + "/pickle3.cpp",
bpl_exa + "/test_abstract.py",
bpl_exa + "/test_getting_started1.py",
bpl_exa + "/test_getting_started2.py",
bpl_exa + "/test_simple_vector.py",
bpl_exa + "/test_do_it_yourself_convts.py",
bpl_exa + "/test_nested.py",
bpl_exa + "/test_pickle1.py",
bpl_exa + "/test_pickle2.py",
bpl_exa + "/test_pickle3.py",
bpl_exa + "/noncopyable.h",
bpl_exa + "/noncopyable_export.cpp",
bpl_exa + "/noncopyable_import.cpp",
bpl_exa + "/dvect.h",
bpl_exa + "/dvect.cpp",
bpl_exa + "/dvect_conversions.cpp",
bpl_exa + "/dvect_defs.cpp",
bpl_exa + "/ivect.h",
bpl_exa + "/ivect.cpp",
bpl_exa + "/ivect_conversions.cpp",
bpl_exa + "/ivect_defs.cpp",
bpl_exa + "/tst_noncopyable.py",
bpl_exa + "/tst_dvect1.py",
bpl_exa + "/tst_dvect2.py",
bpl_exa + "/tst_ivect1.py",
bpl_exa + "/tst_ivect2.py",
bpl_exa + "/test_cross_module.py",
bpl_exa + "/vector_wrapper.h",
bpl_exa + "/richcmp1.cpp",
bpl_exa + "/richcmp2.cpp",
bpl_exa + "/richcmp3.cpp",
bpl_exa + "/test_richcmp1.py",
bpl_exa + "/test_richcmp2.py",
bpl_exa + "/test_richcmp3.py",
)

defs = (
"boost_python_test",
"abstract",
"getting_started1",
"getting_started2",
"simple_vector",
"do_it_yourself_convts",
"nested",
"pickle1",
"pickle2",
"pickle3",
"noncopyable_export",
"noncopyable_import",
"ivect",
"dvect",
"richcmp1",
"richcmp2",
"richcmp3",
)

if (__name__ == "__main__"):

  import sys, os, shutil

  path = sys.argv[1]
  mode = sys.argv[2]
  if (not mode in ("softlinks", "unlink", "cp", "rm", "copy", "del")):
    raise RuntimeError, \
      "usage: python filemgr.py path <softlinks|unlink|cp|rm|copy|del>"

  if (mode in ("cp", "copy")):
    for fn in files:
      f = os.path.basename(fn)
      print "Copying: " + f
      shutil.copy(path + fn, ".")

  elif (mode == "softlinks"):
    for fn in files:
      f = os.path.basename(fn)
      if (os.path.exists(f)):
        print "File exists: " + f
      else:
        print "Linking: " + f
        os.symlink(path + fn, f)

  elif (mode in ("rm", "del")):
    for fn in files:
      f = os.path.basename(fn)
      if (os.path.exists(f)):
        print "Removing: " + f
        try: os.unlink(f)
        except: pass

  elif (mode == "unlink"):
    for fn in files:
      f = os.path.basename(fn)
      if (os.path.exists(f)):
        if (os.path.islink(f)):
          print "Unlinking: " + f
          try: os.unlink(f)
          except: pass
        else:
          print "Not a softlink: " + f

  if (mode in ("softlinks", "cp", "copy")):
    for d in defs:
      fn = d + ".def"
      print "Creating: " + fn
      f = open(fn, "w")
      f.write("EXPORTS\n")
      f.write("\tinit" + d + "\n")
      f.close()

  if (mode in ("unlink", "rm", "del")):
    for d in defs:
      fn = d + ".def"
      if (os.path.exists(fn)):
        print "Removing: " + fn
        try: os.unlink(fn)
        except: pass
