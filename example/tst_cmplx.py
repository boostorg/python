import cmplx
c = cmplx.dpolar(1, 1)
print c
print cmplx.dreal(c)
print cmplx.dimag(c)

c = cmplx.fpolar(1, 1)
print c
print cmplx.freal(c)
print cmplx.fimag(c)

print cmplx.dreal(c)
print cmplx.dimag(c)

try:
  cmplx.freal("")
except TypeError:
  pass
else:
  raise SystemError
