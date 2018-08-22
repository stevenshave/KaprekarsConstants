width=2
n_processors=5
min=1
max=10**width-1
print(max)
n=(int)(max/n_processors)+1
v_begin=[1]
v_end=[v_begin[0]+n]
while(v_end[-1]<max):
    v_begin.append(v_end[-1]+1)
    v_end.append(v_begin[-1]+n)
v_end[-1]=max

for i in range(n_processors):
    print("./kaprekar "+str(v_begin[i])+" "+str(v_end[i]))