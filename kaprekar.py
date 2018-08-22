import matplotlib.pyplot as plt
from matplotlib import colors
import numpy as np

def KaprekarsConstant(num:int,width:int=4): 
    intermediates=[num]
    while(intermediates.count(intermediates[-1])==1):
        num_ascending=sorted(list(str(intermediates[-1]).rjust(width,'0')))
        num_descending=sorted(num_ascending.copy(),reverse=True)
        intermediates.append(int("".join(num_descending))-int("".join(num_ascending)))
    return len(intermediates)-1, intermediates[-1]

outfile=open("res.txt","w")
maxiters=0
ending_numbers={}

maxdigits=5
print("Doing max=",10**maxdigits)


for i in range(10000,10**maxdigits):
    niters, lastval=KaprekarsConstant(i,maxdigits)
    if niters>maxiters: maxiter=niters
    if lastval in ending_numbers.keys():
        ending_numbers[lastval]+=1
    else:
        ending_numbers[lastval]=1
    if (i/(10**maxdigits)*100)%1==0: print(i)
print(maxdigits)
print(ending_numbers.keys())
print(ending_numbers.values())
plt.bar(ending_numbers.keys(), ending_numbers.values(),width=20, color='g')
plt.show()