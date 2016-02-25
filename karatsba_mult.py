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
        e = multiply(a,c)
        f = multiply(b,d)
        g = multiply(a+b, c+d)
        return e * pow(10,n) + (g-e-f)*pow(10,n/2) + f

a = 23422
b = 2346
print multiply(a, b)
print a * b
