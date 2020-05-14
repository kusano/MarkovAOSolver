from fractions import *

for l in range(2, 16):
  for a in range(1, l):
    b = l-a
    print "o"*a+"|"+"o"*b+":"+"o"*gcd(a, b)
