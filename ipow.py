def ipow(x,n,a):
    print x,n,a
    if n == 0:
        return a
    elif n%2==0:
        return ipow(x*x,n/2,a)
    else:
        return ipow(x,n-1,x*a)

print ipow(4,7,1)
