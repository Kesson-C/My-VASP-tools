#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
class poscar{
	public:
		char dynamic[3];
		double position[3];
};
void readfile(const char* filename,vector<poscar> &atom, 
vector<string> &head), 
scale(vector<poscar> &atom, 
vector<string> &head, vector<string> &atomtype, 
vector<int> &atomnum), atominf(vector<string> head, vector<string> &atomtype, vector<int> &atomnum), 
dadsop(),
adsop(vector<poscar> &atom, vector<string> &head, vector<string> &atomtype,vector<int> &atomnum),
rotate(),
inverseM(double &xtmp[3],double &ytmp[3],double &ztmp[3]);

int main()
{
	const char* filename= new char;
	char type;
	vector<string> head, atomtype;
	vector<int> atomnum;
	vector<poscar> atom;
	filename = "POSCAR";
	readfile(filename, atom, head);
	atominf(head,atomtype,atomnum);
	cout<<"You have "<<atomtype.size()<<" type of atom, list as follow"<<endl;
	for(int i=0;i<atomtype.size();i++){
		cout<<atomtype[i]<<" "<<atomnum[i]<<endl;
	}
	while(1){
	cout<<"Select function(s,d,a,r,e):"<<endl;
	cin>>type;
	if(type=='s'){
		scale(atom,head,atomtype,atomnum);
	}
	else if(type=='a'){
		adsop(atom,head,atomtype,atomnum);
	}
	else if(type=='e'){
		break;
	}
	cout<<"=================================================="<<endl;
	}
	filename = "CONTCAR";
	ofstream fout;
	fout.open(filename);
	for(int i=0; i<head.size();i++){
	if(i==5){
	for(int j=0; j<atomtype.size();j++)fout<<atomtype[j]<<" ";
	fout<<endl;
	}
	else if(i==6){
	for(int j=0; j<atomtype.size();j++)fout<<atomnum[j]<<" ";
	fout<<endl;
	}
	else{
	fout<<head[i]<<endl;}}
	for(int i=0; i<atom.size();i++){
	for(int j=0; j<3; j++){
	fout<< setprecision(9)<<atom[i].position[j]<<' ';}
	for(int j=0; j<3; j++){
	fout<<atom[i].dynamic[j]<<' ';}
	fout<<endl;
	}
	return 0;
}
void readfile(const char* filename,vector<poscar> &atom, vector<string> &head){	
	char line[1000];
	int k=0;
	poscar temp;
	fstream fin;
	fin.open(filename,ios::in);
	while(fin.getline(line,sizeof(line))){
		if(k==1){
		sscanf(line,"%lf %lf %lf %c %c %c",&temp.position[0],&temp.position[1],&temp.position[2],&temp.dynamic[0],&temp.dynamic[1],&temp.dynamic[2]);
		atom.push_back(temp);
		}
		if(k==0){
		head.push_back(line);
		}
		if(line[0]=='D'){
			k=1;}
}
}
void atominf(vector<string> head, vector<string> &atomtype, vector<int> &atomnum){
	vector<string> stmp,ntmp;
	string temp,tmpat,tempn;
	tempn=head[6];
	temp=head[5];
	for(int i=0;i<temp.size();i++){
		if((temp[i]>='A' && temp[i]<='Z')||(temp[i]>='a' && temp[i]<='z')){
			tmpat.push_back(temp[i]);
		if(!(temp[i+1]>='A' && temp[i+1]<='Z')&&!(temp[i+1]>='a' && temp[i+1]<='z')){
			stmp.push_back(tmpat);
			tmpat.clear();
			}
	}
	}
	for(int i=0;i<tempn.size();i++){
		if(tempn[i]>='0' && tempn[i]<='9'){
			tmpat.push_back(tempn[i]);
		if(!(tempn[i+1]>='0' && tempn[i+1]<='9')){
			ntmp.push_back(tmpat);
			tmpat.clear();
			}
	}
	}
	atomtype=stmp;
	for(int i=0;i<ntmp.size();i++)atomnum.push_back(stoi(ntmp[i]));
	
}
void inverseM(double &xtmp[3],double &ytmp[3],double &ztmp[3]){
	det=xtmp[0]*ytmp[1]*ztmp[2]+xtmp[1]*ytmp[2]*ztmp[0]+xtmp[2]*ytmp[0]*ztmp[1]-xtmp[2]*ytmp[1]*ztmp[0]-xtmp[0]*ytmp[2]*ztmp[1]-xtmp[1]*ytmp[0]*ztmp[2];
	double tx[3],ty[3],tz[3];
	tx[0]= (ytmp[1]*ztmp[2]-ztmp[1]*ytmp[2])/det;//a22a33-a23a32
	tx[1]= (-xtmp[1]*ztmp[2]+ztmp[1]*xtmp[2])/det;//-a21a33+a31a23
	tx[2]= (xtmp[1]*ytmp[2]-ytmp[1]*xtmp[2])/det;//a21a32-a31a22
	ty[0]= (-ytmp[0]*ztmp[2]+ztmp[0]*ytmp[2])/det;//-a12a33+a13a32
	ty[1]= (xtmp[0]*ztmp[2]-ztmp[0]*xtmp[2])/det;//a11a33-a31a13
	ty[2]= (-xtmp[0]*ytmp[2]+ytmp[0]*xtmp[2])/det;//-a11a32+a31a12
	tz[0]= (ytmp[0]*ztmp[1]-ztmp[0]*ytmp[1])/det;//a12a23-a22a13
	tz[1]= (-xtmp[0]*ztmp[1]+xtmp[1]*ztmp[0])/det;//-a11a23+a21a13
	tz[2]= (xtmp[0]*ytmp[1]-xtmp[1]*ytmp[0])/det;//a11a22-a21a12
	xtmp=tx;
	ytmp=ty;
	ztmp=tz;
}
void scale(vector<poscar> &atom, vector<string> &head, vector<string> &atomtype, vector<int> &atomnum){	
	cout<<"=================================================="<<endl;
	char dir;int scale; double tmp[3];
	cout<<"Which direction you wanna scale?"<<endl;
	cin>>dir;
	cout<<"Scale size?"<<endl;
	cin>>scale;
	if(dir=='x'){
		const char* temp=head[2].c_str();
		sscanf(temp,"%lf %lf %lf",&tmp[0],&tmp[1],&tmp[2]);
		tmp[0]=tmp[0]*scale;
		tmp[1]=tmp[1]*scale;
		tmp[2]=tmp[2]*scale;
		stringstream ss;
		for(int i=0; i<3;i++){
		ss << fixed << setprecision(9) << tmp[i]<<" ";
		}
		head[2]=ss.str();
		int len=atomtype.size();
		poscar ptemp;
		vector<poscar> vptmp;
		int itmp=0,m;
		for(int i=0;i<len;i++){
			cout<<atomtype[i]<<" ";
		for(int j=0; j<scale;j++){
			float k=(float)j/(float)scale;
		for(int m=0;m<atomnum[i];m++){
			ptemp.dynamic[0]=atom[m+itmp].dynamic[0];
			ptemp.dynamic[1]=atom[m+itmp].dynamic[1];
			ptemp.dynamic[2]=atom[m+itmp].dynamic[2];
			ptemp.position[0]=atom[m+itmp].position[0]/scale+k;
			ptemp.position[1]=atom[m+itmp].position[1];
			ptemp.position[2]=atom[m+itmp].position[2];
			vptmp.push_back(ptemp);}
		}
		itmp=atomnum[i];
		cout<<"done!"<<endl;
	}
		atom.clear();
		atom=vptmp;
	}
	else if(dir=='y'){
		const char* temp=head[3].c_str();
		sscanf(temp,"%lf %lf %lf",&tmp[0],&tmp[1],&tmp[2]);
		tmp[0]=tmp[0]*scale;
		tmp[1]=tmp[1]*scale;
		tmp[2]=tmp[2]*scale;
		stringstream ss;
		for(int i=0; i<3;i++){
		ss << fixed << setprecision(9) << tmp[i]<<" ";
		}
		head[3]=ss.str();
		int len=atomtype.size();
		poscar ptemp;
		vector<poscar> vptmp;
		int itmp=0,m;
		for(int i=0;i<len;i++){
			cout<<atomtype[i]<<" ";
		for(int j=0; j<scale;j++){
			float k=(float)j/(float)scale;
		for(int m=0;m<atomnum[i];m++){
			ptemp.dynamic[0]=atom[m+itmp].dynamic[0];
			ptemp.dynamic[1]=atom[m+itmp].dynamic[1];
			ptemp.dynamic[2]=atom[m+itmp].dynamic[2];
			ptemp.position[0]=atom[m+itmp].position[0];
			ptemp.position[1]=atom[m+itmp].position[1]/scale+k;
			ptemp.position[2]=atom[m+itmp].position[2];
			vptmp.push_back(ptemp);}
		}
		itmp=atomnum[i];
		cout<<"done!"<<endl;
	}
		atom.clear();
		atom=vptmp;
}
	else if(dir=='z'){
		const char* temp=head[4].c_str();
		sscanf(temp,"%lf %lf %lf",&tmp[0],&tmp[1],&tmp[2]);
		tmp[0]=tmp[0]*scale;
		tmp[1]=tmp[1]*scale;
		tmp[2]=tmp[2]*scale;
		stringstream ss;
		for(int i=0; i<3;i++){
		ss << fixed << setprecision(9) << tmp[i]<<" ";
		}
		head[4]=ss.str();
		int len=atomtype.size();
		poscar ptemp;
		vector<poscar> vptmp;
		int itmp=0,m;
		for(int i=0;i<len;i++){
			cout<<atomtype[i]<<" ";
		for(int j=0; j<scale;j++){
			float k=(float)j/(float)scale;
		for(int m=0;m<atomnum[i];m++){
			ptemp.dynamic[0]=atom[m+itmp].dynamic[0];
			ptemp.dynamic[1]=atom[m+itmp].dynamic[1];
			ptemp.dynamic[2]=atom[m+itmp].dynamic[2];
			ptemp.position[0]=atom[m+itmp].position[0];
			ptemp.position[1]=atom[m+itmp].position[1];
			ptemp.position[2]=atom[m+itmp].position[2]/scale+k;
			vptmp.push_back(ptemp);}
		}
		itmp=atomnum[i];
		cout<<"done!"<<endl;
	}
		atom.clear();
		atom=vptmp;	
}
	for(int i=0;i<atomnum.size();i++)
	{atomnum[i]=atomnum[i]*scale;}
}
void dadsop(){
	
}
void adsop(vector<poscar> &atom, vector<string> &head, vector<string> &atomtype,vector<int> &atomnum){
	string s;
	double x,y,z;
	cout<<"=================================================="<<endl;
	cout<<"adsope file:";
	cin>>s;
	cout<<endl<<"position in model:";
	cin>>x>>y>>z;
	const char* filename=s.c_str();
	vector<string> a_head, a_type;
	vector<poscar> a_atom;
	vector<int> a_num,a_tmp;
	int c,jtmp;
	readfile(filename, a_atom, a_head);
	atominf(a_head, a_type, a_num);
/////////////////////////////////////////////////////
	double tmp,atmp,xtmp[3],ytmp[3],ztmp[3],axtmp[3],aytmp[3],aztmp[3];
	const char* temp=head[1].c_str();
	//Target basis
	sscanf(temp,"%lf %lf %lf",&tmp);
	temp=head[2].c_str();
	sscanf(temp,"%lf %lf %lf",&xtmp[0],&xtmp[1],&xtmp[2]);
	temp=head[3].c_str();
	sscanf(temp,"%lf %lf %lf",&ytmp[0],&ytmp[1],&ytmp[2]);
	temp=head[4].c_str();
	sscanf(temp,"%lf %lf %lf",&ztmp[0],&ztmp[1],&ztmp[2]);
	inverseM(xtmp[3],ytmp[3],ztmp[3]);
	//adsop basis
	temp=a_head[1].c_str();
	sscanf(temp,"%lf %lf %lf",&atmp);
	temp=a_head[2].c_str();
	sscanf(temp,"%lf %lf %lf",&axtmp[0],&axtmp[1],&axtmp[2]);
	temp=a_head[3].c_str();
	sscanf(temp,"%lf %lf %lf",&aytmp[0],&aytmp[1],&aytmp[2]);
	temp=a_head[4].c_str();
	sscanf(temp,"%lf %lf %lf",&aztmp[0],&aztmp[1],&aztmp[2]);
	vector<double> ttmp;
	vector<vector<double>> stmp;
	for(int i=0;i<a_atom.size();i++){
		for(int j=0;j<3;j++){
		ttmp.push_back(a_atom[i].position[j]-a_atom[0].position[j]);}
		
		ttmp[0]=ttmp[0]+x;ttmp[1]=ttmp[1]+y;ttmp[2]=ttmp[2]+z;
		stmp.push_back(ttmp);
		ttmp.clear();
	}
/////////////////////////////////////////////////////////////
	for(int i=0; i<stmp.size();i++){
		a_atom[i].position[0]=stmp[i][0];
		a_atom[i].position[1]=stmp[i][1];
		a_atom[i].position[2]=stmp[i][2];
		a_atom[i].dynamic[0]='T';
		a_atom[i].dynamic[1]='T';
		a_atom[i].dynamic[2]='T';
		}
	
	for(int i=0;i<a_type.size();i++){
		c=0;jtmp=0;
		for(int j=0;j<atomtype.size();j++){
			if(a_type[i].compare(atomtype[j])==0){
				c=1;jtmp=j;
			}
		}
		if(c==0){
			a_tmp.push_back(i);
		}
		else{
			int start=0,ls=0; 
			atomnum[jtmp]=atomnum[jtmp]+a_num[i];
			for(int l=0;l<jtmp;l++){
			start+=atomnum[l];
			}
			for(int l=0;l<i;l++){
			ls+=a_num[l];
			}
			for(int l=0;l<a_num[i];l++){
			atom.insert(atom.begin()+start,a_atom[ls+l]);
			}
		}
	}
	for(int i=0;i<a_tmp.size();i++){
		int k = a_tmp[i],start=0;
		atomtype.push_back(a_type[k]);
		atomnum.push_back(a_num[k]);
		for(int j=0;j<k;j++){
			start+=a_num[j];
	}	
		for(int i=start;i<start+a_num[k];i++){
		atom.push_back(a_atom[i]);} 
}
}
void rotate(){
	
}
