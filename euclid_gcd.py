def gcd(a,b):
    print a, b
    if b == 0:return a
    else:return gcd(b, a%b)


print gcd(412,260)
