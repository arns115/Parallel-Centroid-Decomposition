import matplotlib.pyplot as plt
import os

x=[]
y1=[]
y2=[]
y3=[]

sz=9999

#Opens files with runtime for each n value (size of tree) from 2 to sz+1.
f1=open(os.path.abspath('dataNormal.txt'), 'r')
f2=open(os.path.abspath('dataParallel.txt'), 'r')

line1 = f1.read()
line2 = f2.read()

a=line1.split(', ')
b=line2.split(', ')

for i in range(1, sz):
    x.append(i)

a=a[:len(a)-2]
b=b[:len(b)-2]

for s in a:
    y1.append(float(s))
    
for s in b:
    y2.append(float(s))

# Plots tree size to time it takes to execute Centroid decomposition 
# Plots serial and parallel implementation to compare
plt.plot(x, y1, label='Serial', color="green")
plt.plot(x, y2, label='ParallelNoTask', color="blue")
plt.legend(loc='best')
plt.title('Centroid Decomposition')
plt.xlabel('Number of nodes')
plt.ylabel('Time')
plt.show()

f1.close()
f2.close()
