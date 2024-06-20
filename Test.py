import os

f1=open(os.path.abspath('serialTest.txt'), 'r')
f2=open(os.path.abspath('parallelTest.txt'), 'r')

line1 = f1.read()
line2 = f2.read()

print(line1==line2)

