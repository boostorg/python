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
bpl_exa + "/getting_started3.cpp",
bpl_exa + "/getting_started4.cpp",
bpl_exa + "/getting_started5.cpp",
bpl_exa + "/pickle1.cpp",
bpl_exa + "/pickle2.cpp",
bpl_exa + "/pickle3.cpp",
bpl_exa + "/test_abstract.py",
bpl_exa + "/test_getting_started1.py",
bpl_exa + "/test_getting_started2.py",
bpl_exa + "/test_getting_started3.py",
bpl_exa + "/test_getting_started4.py",
bpl_exa + "/test_getting_started5.py",
bpl_exa + "/test_pickle1.py",
bpl_exa + "/test_pickle2.py",
bpl_exa + "/test_pickle3.py",
bpl_exa + "/noncopyable.h",
bpl_exa + "/noncopyable_export.cpp",
bpl_exa + "/noncopyable_import.cpp",
bpl_exa + "/tst_noncopyable.py",
bpl_exa + "/dvect.h",
bpl_exa + "/dvect.cpp",
bpl_exa + "/dvect_conversions.cpp",
bpl_exa + "/dvect_defs.cpp",
bpl_exa + "/ivect.h",
bpl_exa + "/ivect.cpp",
bpl_exa + "/ivect_conversions.cpp",
bpl_exa + "/ivect_defs.cpp",
bpl_exa + "/tst_dvect1.py",
bpl_exa + "/tst_dvect2.py",
bpl_exa + "/tst_ivect1.py",
bpl_exa + "/tst_ivect2.py",
)

defs = (
"boost_python_test",
"abstract",
"getting_started1",
"getting_started2",
"getting_started3",
"getting_started4",
"getting_started5",
"pickle1",
"pickle2",
"pickle3",
"noncopyable_export",
"noncopyable_import",
"ivect",
"dvect",
)

if (__name__ == "__main__"):

  import sys, os, string

  path = sys.argv[1]
  mode = sys.argv[2]
  if (not mode in ("softlinks", "unlink", "cp", "rm", "copy", "del")):
    raise RuntimeError, \
      "usage: python filemgr.py path <softlinks|unlink|cp|rm|copy|del>"

  translation_table = string.maketrans("/", "\\")

  if (mode == "copy"):
    for fn in files:
      fn = string.translate(fn, translation_table)
      os.system("copy " + path + fn + " .")

  elif (mode == "cp"):
    for fn in files:
      os.system("cp " + path + fn + " .")

  elif (mode == "softlinks"):
    for fn in files:
      f = string.split(fn, "/")[-1]
      if (os.access(f, os.F_OK)):
        print "File exists: " + f
      else:
        print "Linking: " + f
        os.system("ln -s " + path + os.sep + fn + " .")

  elif (mode in ("rm", "del")):
    for fn in files:
      flds = string.split(fn, "/")
      try: os.unlink(flds[-1])
      except: pass

  elif (mode == "unlink"):
    for fn in files:
      f = string.split(fn, "/")[-1]
      if (os.system("test -e " + f) == 0):
        if (os.system("test -L " + f) == 0):
          try: os.unlink(f)
          except: pass
        else:
          print "Not a softlink: " + f

  if (mode in ("softlinks", "cp", "copy")):
    for d in defs:
      fn = d + ".def"
      f = open(fn, "w")
      f.write("EXPORTS\n")
      f.write("\tinit" + d + "\n")
      f.close()

  if (mode in ("unlink", "rm", "del")):
    for d in defs:
      fn = d + ".def"
      try: os.unlink(fn)
      except: pass
