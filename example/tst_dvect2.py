def f(broken_auto_ptr):
  import dvect
  import ivect
  #
  dv = dvect.dvect((1,2,3,4,5))
  iv = dv.as_ivect()
  #
  aiv = dvect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_value_ivect_as_tuple'
  print ivect.auto_ptr_value_ivect_as_tuple(aiv)
  print '2. auto_ptr_value_ivect_as_tuple'
  if (not broken_auto_ptr):
    print ivect.auto_ptr_value_ivect_as_tuple(aiv)
  else:
    print None
  #
  adv = dvect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_value_dvect_as_tuple'
  print ivect.auto_ptr_value_dvect_as_tuple(adv)
  print '2. auto_ptr_value_dvect_as_tuple'
  if (not broken_auto_ptr):
    print ivect.auto_ptr_value_dvect_as_tuple(adv)
  else:
    print None
  #
  siv = dvect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_value_ivect_as_tuple'
  print ivect.shared_ptr_value_ivect_as_tuple(siv)
  print '2. shared_ptr_value_ivect_as_tuple'
  print ivect.shared_ptr_value_ivect_as_tuple(siv)
  #
  sdv = dvect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_value_dvect_as_tuple'
  print ivect.shared_ptr_value_dvect_as_tuple(sdv)
  print '2. shared_ptr_value_dvect_as_tuple'
  print ivect.shared_ptr_value_dvect_as_tuple(sdv)
  #
  aiv = dvect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_reference_ivect_as_tuple'
  print ivect.auto_ptr_reference_ivect_as_tuple(aiv)
  print '2. auto_ptr_reference_ivect_as_tuple'
  print ivect.auto_ptr_reference_ivect_as_tuple(aiv)
  #
  adv = dvect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_reference_dvect_as_tuple'
  print ivect.auto_ptr_reference_dvect_as_tuple(adv)
  print '2. auto_ptr_reference_dvect_as_tuple'
  print ivect.auto_ptr_reference_dvect_as_tuple(adv)
  #
  siv = dvect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_reference_ivect_as_tuple'
  print ivect.shared_ptr_reference_ivect_as_tuple(siv)
  print '2. shared_ptr_reference_ivect_as_tuple'
  print ivect.shared_ptr_reference_ivect_as_tuple(siv)
  #
  sdv = dvect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_reference_dvect_as_tuple'
  print ivect.shared_ptr_reference_dvect_as_tuple(sdv)
  print '2. shared_ptr_reference_dvect_as_tuple'
  print ivect.shared_ptr_reference_dvect_as_tuple(sdv)
  #
  aiv = dvect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_const_reference_ivect_as_tuple'
  print ivect.auto_ptr_const_reference_ivect_as_tuple(aiv)
  print '2. auto_ptr_const_reference_ivect_as_tuple'
  print ivect.auto_ptr_const_reference_ivect_as_tuple(aiv)
  #
  adv = dvect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_const_reference_dvect_as_tuple'
  print ivect.auto_ptr_const_reference_dvect_as_tuple(adv)
  print '2. auto_ptr_const_reference_dvect_as_tuple'
  print ivect.auto_ptr_const_reference_dvect_as_tuple(adv)
  #
  siv = dvect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_const_reference_ivect_as_tuple'
  print ivect.shared_ptr_const_reference_ivect_as_tuple(siv)
  print '2. shared_ptr_const_reference_ivect_as_tuple'
  print ivect.shared_ptr_const_reference_ivect_as_tuple(siv)
  #
  sdv = dvect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_const_reference_dvect_as_tuple'
  print ivect.shared_ptr_const_reference_dvect_as_tuple(sdv)
  print '2. shared_ptr_const_reference_dvect_as_tuple'
  print ivect.shared_ptr_const_reference_dvect_as_tuple(sdv)

if (__name__ == "__main__"):
  import sys, string
  broken_auto_ptr = 0
  n = 1
  
  if len(sys.argv) > 1:
      argv = []
      
      for x in sys.argv:
        if x != '--broken-auto-ptr':
          argv.append(x)
      broken_auto_ptr = argv != sys.argv
      sys.argv = argv

      if len(sys.argv) > 1:
        n = string.atoi(sys.argv[1])
        
  for i in xrange(n):
    f(broken_auto_ptr)
