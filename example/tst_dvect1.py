def f():
  import dvect
  print dvect.dvect.__converters__
  dv = dvect.dvect((1,2,3,4,5))
  print dv
  print dv.as_tuple()
  iv = dv.as_ivect()
  print iv
  print iv.as_tuple()
  print dvect.const_ivect_reference_as_tuple(iv)
  aiv = dvect.ivect_as_auto_ptr(iv)
  print dvect.const_ivect_reference_as_tuple(aiv)
  siv = dvect.ivect_as_shared_ptr(iv)
  print dvect.const_ivect_reference_as_tuple(siv)
  print aiv.as_tuple()
  print siv.as_tuple()

if (__name__ == "__main__"):
  import sys, string
  n = 1
  if (len(sys.argv) > 1): n = string.atoi(sys.argv[1])
  for i in xrange(n):
    f()
