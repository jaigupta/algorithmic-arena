import math
allfunc = ["fact(n)",
        "sumOfDigits(n)",
        "ncr(a,b)",
        "computecnr()"]

def printall():
    for i in allfunc:
        print i

def fact(n):
    if n<=0:
        return 1
    return n*fact(n-1)

def sumOfDigits(n):
    vsum=0
    while n>0:
        vsum+=n%10
        n/=10
    return vsum

def ncr(a, b):
    return fact(a)/(fact(b)*fact(a-b))

ncr=[[0 for i in range(51)] for j in range(51)]
def computecnr():
    ncr[0][0] = 1
    for i in range(1, 51):
        ncr[i][0] = 1
        for j in range(1, i):
            ncr[i][j] = ncr[i-1][j-1]+ncr[i-1][j]
        ncr[i][i] = 1
