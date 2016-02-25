import math
def multiply(x,y):
    n1 = len(str(x))
    n2 = len(str(y))
    n = n1 if n1 > n2 else n2
    if n % 2 != 0: n = n + 1 
    if n1 == 1 or n2 == 1:
        return x * y
    else:
        a = x / pow(10,n/2)
        b = x % pow(10, n/2)
        c = y / pow(10, n/2)
        d = y % pow(10, n/2)
        print a,b,c,d
        return multiply(a,c) * pow(10,n) + (multiply(a,d) + multiply(b,c))*pow(10,n/2) + multiply(b,d)

a = 23422
b = 2346
print multiply(a, b)
print a * b
