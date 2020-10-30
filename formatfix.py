import numpy as np
f = open("/Users/User/Desktop/CeO2/CeO2(100)/POSCAR",'r')
line = f.readlines()
lc = float(line[1].strip('\n'))
v1 = np.asarray(list(map(float,line[2].split())))
v2 = np.asarray(list(map(float,line[3].split())))
v3 = np.asarray(list(map(float,line[4].split())))
pos = np.zeros([len(line)-8,3])
xl = v1[0]
v1 = v1/xl
v2 = v2/xl
v3 = v3/xl
for i in range(8,len(line)):
    str1 = line[i].split()
    pos[i-8]=list(map(float,str1))

line[1]=str(xl)+'\n'
line[2]= ' '.join('%10.8f'%v for v in v1) +'\n'
line[3]= ' '.join('%10.8f'%v for v in v2) +'\n'
line[4]= ' '.join('%10.8f'%v for v in v3) +'\n'

ctmp = list(line[6].split())
coef = [0]*len(ctmp)
for i in range(len(ctmp)):
    coef[i]=int(ctmp[i])

fout = open("/Users/User/Desktop/CeO2/CeO2(100)/POSCAR_456",'w')

for i in range(len(pos)):
    line[8+i] = ' '.join('%10.8f'%v for v in pos[i]) +'\n'

for i in range(len(line)):
    fout.write(line[i])

f.close()
fout.close()

