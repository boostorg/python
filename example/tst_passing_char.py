import passing_char
print passing_char.get_char()
print passing_char.get_signed_char()
print passing_char.get_unsigned_char()
for arg in (-97, 97, -140, 140, "a", "ab", ""):
  try:
    print 'char', arg, ':'
    passing_char.use_char(arg)
  except (TypeError, ValueError), e:
    print e.args[0]
  try:
    print 'signed char', arg, ':'
    passing_char.use_signed_char(arg)
  except (TypeError, ValueError), e:
    print e.args[0]
  try:
    print 'unsigned char', arg, ':'
    passing_char.use_unsigned_char(arg)
  except (TypeError, ValueError), e:
    print e.args[0]
