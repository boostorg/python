def f():
  import ivect
  iv = ivect.ivect((1,2,3,4,5))
  print iv.as_tuple()
  dv = iv.as_dvect()
  print dv.as_tuple()
  print ivect.const_dvect_reference_as_tuple(dv)
  adv = ivect.dvect_as_auto_ptr(dv)
  print ivect.const_dvect_reference_as_tuple(adv)
  sdv = ivect.dvect_as_shared_ptr(dv)
  print ivect.const_dvect_reference_as_tuple(sdv)
  print adv.as_tuple()
  print sdv.as_tuple()

if (__name__ == "__main__"):
  import sys, string
  n = 1
  if (len(sys.argv) > 1): n = string.atoi(sys.argv[1])
  for i in xrange(n):
    f()
