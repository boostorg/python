import richcmp,sys
global dv,dv2
dv = richcmp.ivect((1,2,3,4,5))
print dv.as_tuple()
dv2 = richcmp.dvect((2,-2,3,8,-5))
print dv2.as_tuple()

print (dv+dv2).as_tuple()
print (dv+3).as_tuple()
print (3+dv).as_tuple()

def python_2_1():
  print "\nvect vs. vect Comparisons:"
  print (dv < dv2).as_tuple()
  print (dv <= dv2).as_tuple()
  print (dv == dv2).as_tuple()
  print (dv != dv2).as_tuple()
  print (dv > dv2).as_tuple()
  print (dv >= dv2).as_tuple()

  print "\nvect vs. scalar Comparisons:"
  print (dv < 3).as_tuple()
  print (dv <= 3).as_tuple()
  print (dv == 3).as_tuple()
  print (dv != 3).as_tuple()
  print (dv > 3).as_tuple()
  print (dv >= 3).as_tuple()

  print "\nscalar  vs. vect Comparisons:"
  print (3 < dv).as_tuple()
  print (3 <= dv).as_tuple()
  print (3 == dv).as_tuple()
  print (3 != dv).as_tuple()
  print (3 > dv).as_tuple()
  print (3 >= dv).as_tuple()

def python_pre_2_1():
  print "\nvect vs. vect Comparisons:"
  print (dv.__lt__(dv2)).as_tuple()
  print (dv.__le__(dv2)).as_tuple()
  print (dv.__eq__(dv2)).as_tuple()
  print (dv.__ne__(dv2)).as_tuple()
  print (dv.__gt__(dv2)).as_tuple()
  print (dv.__ge__(dv2)).as_tuple()

  print "\nvect vs. scalar Comparisons:"
  print (dv.__lt__(3)).as_tuple()
  print (dv.__le__(3)).as_tuple()
  print (dv.__eq__(3)).as_tuple()
  print (dv.__ne__(3)).as_tuple()
  print (dv.__gt__(3)).as_tuple()
  print (dv.__ge__(3)).as_tuple()

  print "\nscalar  vs. vect Comparisons:"

if __name__=='__main__':
  try:
    if sys.version_info[0]>=2 and sys.version_info[1]>=1:
      python_2_1()
    else:
      python_pre_2_1()
  except:
    python_pre_2_1()
