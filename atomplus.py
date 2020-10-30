import numpy as np
f = open("/Users/User/Desktop/CeO2/CeO2(100)/O/pristine/POSCAR",'r')
fadd = open("/Users/User/Desktop/CeO2/H2O2/POSCAR",'r')
line = fadd.readlines()
line2 = f.readlines()
lc = float(line[1].strip('\n'))
lc2 = float(line2[1].strip('\n'))
v1 = np.asarray(list(map(float,line[2].split())))
v2 = np.asarray(list(map(float,line[3].split())))
v3 = np.asarray(list(map(float,line[4].split())))
v12 = np.asarray(list(map(float,line2[2].split())))
v22 = np.asarray(list(map(float,line2[3].split())))
v32 = np.asarray(list(map(float,line2[4].split())))
pos = np.zeros([len(line)-8,3])
pos2 = np.zeros([len(line2)-8,3])
R=np.transpose([lc2*v12,lc2*v22,lc2*v32])
Rinv=np.linalg.inv(R)

for i in range(8,len(line)):
    str1 = line[i].split()
    pos[i-8]=list(map(float,str1))
    pos[i-8]=pos[i-8][0]*v1+pos[i-8][1]*v2+pos[i-8][2]*v3
    
for i in range(8,len(line2)):
    str1 = line2[i].split()
    pos2[i-8]=list(map(float,str1[0:3]))

pos = pos - (pos[1]+pos[0])/2
posr = np.transpose(np.dot([[0,1,0],[-1,0,0],[0,0,1]],np.transpose(pos)))

print('a positions:')
kx=float(input())
print('b positions:')
ky=float(input())
print('c positions:')
kz=float(input())/(v32[2]*lc2)
kz=max(pos2[:,2])+kz

post=np.transpose(np.dot(Rinv,np.transpose(pos)))+[kx,ky,kz]
postr=np.transpose(np.dot(Rinv,np.transpose(posr)))+[kx,ky,kz]


for i in range(len(post)):
    line[8+i] =' '.join('%10.8f'%v for v in post[i])
    print(line[8+i],'T T T')

for i in range(len(post)):
    line[8+i] =' '.join('%10.8f'%v for v in postr[i])
    print(line[8+i],'T T T')

f.close()
fadd.close()

