import richcmp3,sys
global iv,dv
iv = richcmp3.ivect((1,2,3,4,5))
print iv.as_tuple()
dv = richcmp3.dvect((2,-2,3,8,-5))
print dv.as_tuple()

print (iv+dv).as_tuple()
print (iv+3).as_tuple()
print (3+iv).as_tuple()

def python_2_1():
  print "\nvect vs. vect Comparisons:"
  print (iv < dv).as_tuple()
  print (iv <= dv).as_tuple()
  print (iv == dv).as_tuple()
  print (iv != dv).as_tuple()
  print (iv > dv).as_tuple()
  print (iv >= dv).as_tuple()

  print "\nvect vs. scalar Comparisons:"
  print (iv < 3).as_tuple()
  print (iv <= 3).as_tuple()
  print (iv == 3).as_tuple()
  print (iv != 3).as_tuple()
  print (iv > 3).as_tuple()
  print (iv >= 3).as_tuple()

  print "\nscalar  vs. vect Comparisons:"
  print (3 < iv).as_tuple()
  print (3 <= iv).as_tuple()
  print (3 == iv).as_tuple()
  print (3 != iv).as_tuple()
  print (3 > iv).as_tuple()
  print (3 >= iv).as_tuple()

def python_pre_2_1():
  print "\nvect vs. vect Comparisons:"
  print (iv.__lt__(dv)).as_tuple()
  print (iv.__le__(dv)).as_tuple()
  print (iv.__eq__(dv)).as_tuple()
  print (iv.__ne__(dv)).as_tuple()
  print (iv.__gt__(dv)).as_tuple()
  print (iv.__ge__(dv)).as_tuple()

  print "\nvect vs. scalar Comparisons:"
  print (iv.__lt__(3)).as_tuple()
  print (iv.__le__(3)).as_tuple()
  print (iv.__eq__(3)).as_tuple()
  print (iv.__ne__(3)).as_tuple()
  print (iv.__gt__(3)).as_tuple()
  print (iv.__ge__(3)).as_tuple()

  print "\nscalar  vs. vect Comparisons:"

if __name__=='__main__':
  if sys.version_info[0]>=2 and sys.version_info[1]>=1:
    python_2_1()
  else:
    python_pre_2_1()
