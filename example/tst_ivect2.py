def f():
  import ivect
  import dvect
  #
  iv = ivect.ivect((1,2,3,4,5))
  dv = iv.as_dvect()
  #
  adv = ivect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_value_dvect_as_tuple'
  print dvect.auto_ptr_value_dvect_as_tuple(adv)
  print '2. auto_ptr_value_dvect_as_tuple'
  print dvect.auto_ptr_value_dvect_as_tuple(adv)
  #
  aiv = ivect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_value_ivect_as_tuple'
  print dvect.auto_ptr_value_ivect_as_tuple(aiv)
  print '2. auto_ptr_value_ivect_as_tuple'
  print dvect.auto_ptr_value_ivect_as_tuple(aiv)
  #
  sdv = ivect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_value_dvect_as_tuple'
  print dvect.shared_ptr_value_dvect_as_tuple(sdv)
  print '2. shared_ptr_value_dvect_as_tuple'
  print dvect.shared_ptr_value_dvect_as_tuple(sdv)
  #
  siv = ivect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_value_ivect_as_tuple'
  print dvect.shared_ptr_value_ivect_as_tuple(siv)
  print '2. shared_ptr_value_ivect_as_tuple'
  print dvect.shared_ptr_value_ivect_as_tuple(siv)
  #
  adv = ivect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_reference_dvect_as_tuple'
  print dvect.auto_ptr_reference_dvect_as_tuple(adv)
  print '2. auto_ptr_reference_dvect_as_tuple'
  print dvect.auto_ptr_reference_dvect_as_tuple(adv)
  #
  aiv = ivect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_reference_ivect_as_tuple'
  print dvect.auto_ptr_reference_ivect_as_tuple(aiv)
  print '2. auto_ptr_reference_ivect_as_tuple'
  print dvect.auto_ptr_reference_ivect_as_tuple(aiv)
  #
  sdv = ivect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_reference_dvect_as_tuple'
  print dvect.shared_ptr_reference_dvect_as_tuple(sdv)
  print '2. shared_ptr_reference_dvect_as_tuple'
  print dvect.shared_ptr_reference_dvect_as_tuple(sdv)
  #
  siv = ivect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_reference_ivect_as_tuple'
  print dvect.shared_ptr_reference_ivect_as_tuple(siv)
  print '2. shared_ptr_reference_ivect_as_tuple'
  print dvect.shared_ptr_reference_ivect_as_tuple(siv)
  #
  adv = ivect.dvect_as_auto_ptr(dv)
  print '1. auto_ptr_const_reference_dvect_as_tuple'
  print dvect.auto_ptr_const_reference_dvect_as_tuple(adv)
  print '2. auto_ptr_const_reference_dvect_as_tuple'
  print dvect.auto_ptr_const_reference_dvect_as_tuple(adv)
  #
  aiv = ivect.ivect_as_auto_ptr(iv)
  print '1. auto_ptr_const_reference_ivect_as_tuple'
  print dvect.auto_ptr_const_reference_ivect_as_tuple(aiv)
  print '2. auto_ptr_const_reference_ivect_as_tuple'
  print dvect.auto_ptr_const_reference_ivect_as_tuple(aiv)
  #
  sdv = ivect.dvect_as_shared_ptr(dv)
  print '1. shared_ptr_const_reference_dvect_as_tuple'
  print dvect.shared_ptr_const_reference_dvect_as_tuple(sdv)
  print '2. shared_ptr_const_reference_dvect_as_tuple'
  print dvect.shared_ptr_const_reference_dvect_as_tuple(sdv)
  #
  siv = ivect.ivect_as_shared_ptr(iv)
  print '1. shared_ptr_const_reference_ivect_as_tuple'
  print dvect.shared_ptr_const_reference_ivect_as_tuple(siv)
  print '2. shared_ptr_const_reference_ivect_as_tuple'
  print dvect.shared_ptr_const_reference_ivect_as_tuple(siv)

if (__name__ == "__main__"):
  import sys, string
  n = 1
  if (len(sys.argv) > 1): n = string.atoi(sys.argv[1])
  for i in xrange(n):
    f()
