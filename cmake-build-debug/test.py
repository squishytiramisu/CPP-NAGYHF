be=open("kimenet.txt")
ki=open("bemenet.txt")
x=[y for y in be]
z=[y for y in ki]

for i in range(len(x)):
    if x[i]!=z[i]:
        print(list(x[i]),list(z[i]))
be.close()
ki.close()

