import numpy as np
f = open("/Users/mne081069/Desktop/POSCAR/111/POSCAR",'r',encoding="utf-8")
line = f.readlines()
lc = float(line[1].strip('\n'))
v1 = np.asarray(list(map(float,line[2].split())))
v2 = np.asarray(list(map(float,line[3].split())))
v3 = np.asarray(list(map(float,line[4].split())))
print("how many times x want to add?")
vx = int(input())
print("how many times y want to add?")
vy = int(input())
print("how many times z want to add?")
vz = int(input())
ctmp = list(line[6].split())
coef = [0]*len(ctmp)
for i in range(len(ctmp)):
    coef[i]=int(ctmp[i])

coef=coef*vx*vy*vz
line[6]=' '.join(str(v) for v in coef) +'\n'

pos = np.zeros([sum(coef),3])

for j in range(1,vx+1):
    for i in range(9,len(line)):
        str1 = line[i].split()
        pos[i*j-9]=list(map(float,str1[0:3]))
        pos[i*j-9][0]=pos[i-9][0]/j


for j in range(1,vy+1):
    for i in range(9,len(line)):
        str1 = line[i].split()
        pos[i*j-9]=list(map(float,str1[0:3]))
        pos[i*j-9][1]=pos[i-9][1]/j


v1=v1*vx
v2=v2*vy
v3=v3*vz
line[2]= ' '.join(str(v) for v in v1) +'\n'
line[3]= ' '.join(str(v) for v in v2) +'\n'
line[4]= ' '.join(str(v) for v in v3) +'\n'

fout = open("/Users/mne081069/Desktop/POSCAR/111/POSCAR_123",'w')


for i in range(len(pos)):
    str1 = line[9+i].split()
    line[9+i] = ' '.join('%10.8f'%v for v in pos[i]) +' '+ str1[3]+' ' + str1[4]+' ' + str1[5] + '\n'

for i in range(len(line)):
    fout.write(line[i])

f.close()
fout.close()