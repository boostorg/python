import dvect
print dvect.dvect.__converters__
dv = dvect.dvect((1,2,3,4,5))
print dv
print dv.as_tuple()
iv = dv.as_ivect()
print iv
print iv.as_tuple()
print dvect.ivect_as_tuple(iv)
aiv = dv.auto_ptr_ivect()
print aiv
siv = dv.shared_ptr_ivect()
print dvect.auto_ptr_ivect_as_tuple(aiv)
print dvect.ivect_as_tuple(aiv)
print dvect.shared_ptr_ivect_as_tuple(siv)
print dvect.ivect_as_tuple(siv)
