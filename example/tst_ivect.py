import ivect
print ivect.ivect.__converters__
iv = ivect.ivect((1,2,3,4,5))
print iv
print iv.as_tuple()
dv = iv.as_dvect()
print dv
print dv.as_tuple()
print ivect.dvect_as_tuple(dv)
adv = iv.auto_ptr_dvect()
print adv
sdv = iv.shared_ptr_dvect()
print ivect.auto_ptr_dvect_as_tuple(adv)
print ivect.dvect_as_tuple(adv)
print ivect.shared_ptr_dvect_as_tuple(sdv)
print ivect.dvect_as_tuple(sdv)
