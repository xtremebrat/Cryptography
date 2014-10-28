#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<vector>
#include<sys/types.h>
#include<time.h>

using namespace std;

int tabChk(char tFile[])
{
ifstream tabFile;
int i=0,j=0,k=0,x=0,y=0;
tabFile.open(tFile,ios::binary);

if ( !tabFile ) // open the cipher text file
{
	fputs("Cannot Open File\n", stderr); 
	return 0; 
}
int nc[14]={0};
int IP[64]={0};
int E[48]={0};
int P[32]={0};
int S1[64]={0};
int S2[64]={0};
int S3[64]={0};
int S4[64]={0};
int S5[64]={0};
int S6[64]={0};
int S7[64]={0};
int S8[64]={0};
int V[16]={0};
int PC1[56]={0};
int PC2[48]={0};

vector<int> tempVect;

int nl=0;
int n=0;
k=0;
while(!tabFile.eof())
{
	string line="";
	getline(tabFile,line);
	if(line=="") break;
	n = 0;
	unsigned pos = line.find("=");
	string p1 = line.substr(0,pos+1);
	string p2 = line.substr(pos+1,line.length()); // requires check manips
	n = std::count(line.begin(), line.end(), ','); // no of commas + 1 = no of numbers
	nc[k]=n+1;
	std::stringstream ss(p2);
	int x;
	while (ss >> x)
	{
    tempVect.push_back(x);

    if (ss.peek() == ',')
        ss.ignore();
	}
	
	//cout<<p1<<endl<<p2<<endl<<n+1<<endl<<endl;
	
	
	nl++;
	k++;
}
//cout<<nl<<endl;
if(nl!=14) { fputs("Invalid Table File\n", stderr); return 0; }

//for(i=0;i<14;i++) cout<<nc[i]<<endl;

if(nc[0]<64) { fputs("(IP) too few values read\n", stderr); return 0; }
if(nc[1]<48) { fputs("(E) too few values read\n", stderr); return 0; }
if(nc[2]<32) { fputs("(P) too few values read\n", stderr); return 0; }
if(nc[3]<64) { fputs("(S1) too few values read\n", stderr); return 0; }
if(nc[4]<64) { fputs("(S2) too few values read\n", stderr); return 0; }
if(nc[5]<64) { fputs("(S3) too few values read\n", stderr); return 0; }
if(nc[6]<64) { fputs("(S4) too few values read\n", stderr); return 0; }
if(nc[7]<64) { fputs("(S5) too few values read\n", stderr); return 0; }
if(nc[8]<64) { fputs("(S6) too few values read\n", stderr); return 0; }
if(nc[9]<64) { fputs("(S7) too few values read\n", stderr); return 0; }
if(nc[10]<64) { fputs("(S8) too few values read\n", stderr); return 0; }
if(nc[11]<16) { fputs("(V) too few values read\n", stderr); return 0; }
if(nc[12]<56) { fputs("(PC1) too few values read\n", stderr); return 0; }
if(nc[13]<48) { fputs("(PC2) too few values read\n", stderr); return 0; }

//cout<<"Size Of Vector Is : "<<tempVect.size()<<endl;

if(tempVect.size()>776) { fputs("Extra Values Read\n", stderr); return 0; }

for(i = 0; i < 64; i++) IP[i] = tempVect[i]; 
for(y=0;y<64;y++) if(IP[y]<1 || IP[y]>64) { fputs("(IP) Value Not In Range \n", stderr); return 0; } 
for(x=0;x<63;x++) for(y=x+1;y<64;y++) if(IP[x]==IP[y]) { cerr<<"(IP) "<<IP[x]<<" Occurs Too Many Times\n"; return 0; }
//cout<<"IP="; for( k=0;k<64;k++) cout<<IP[k]<<" ";

for(i = 64,j=0; i < 112; i++,j++) E[j] = tempVect[i];
for(y=0;y<48;y++) if(E[y]<1 || E[y]>32) { fputs("(E) Value Not In Range \n", stderr); return 0; } 
int count=0;
for(x=0;x<48;x++){ count=0; for(y=0;y<48;y++) if(E[x]==E[y]) count++;  if(count>2) { cerr<<"(E) "<<E[x]<<" Occurs Too Many Times\n";return 0; } }
//cout<<endl<<"E="; for( k=0;k<48;k++) cout<<E[k]<<" ";

for(i = 112,j=0; i < 144; i++,j++) P[j] = tempVect[i];
for(y=0;y<32;y++) if(P[y]<1 || P[y]>32) { fputs("(P) Value Not In Range \n", stderr); return 0; } 
for(x=0;x<31;x++) for(y=x+1;y<32;y++) if(P[x]==P[y]) { cerr<<"(P) "<<P[x]<<" Occurs Too Many Times\n"; return 0; }
//cout<<endl<<"P="; for( k=0;k<32;k++) cout<<P[k]<<" ";

for(i = 144,j=0; i < 208; i++,j++) S1[j] = tempVect[i]; // s1
int c1=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S1[x]==S1[y]) { cerr<<"(S1) "<<S1[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S1[x]<0 || S1[x]>15) { cerr<<"(S1) "<<S1[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c1=0; for(y=16;y<64;y++) { if(S1[x]==S1[y]) c1++; } if(c1<3 || c1>3) { cerr<<"(S1) "<<S1[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S1="; for( k=0;k<64;k++) cout<<S1[k]<<" ";

for(i = 208,j=0; i < 272; i++,j++) S2[j] = tempVect[i];
int c2=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S2[x]==S2[y]) { cerr<<"(S2) "<<S2[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S2[x]<0 || S2[x]>15) { cerr<<"(S2) "<<S2[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c2=0; for(y=16;y<64;y++) { if(S2[x]==S2[y]) c2++; } if(c2<3 || c2>3) { cerr<<"(S2) "<<S2[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S2="; for( k=0;k<64;k++) cout<<S2[k]<<" ";

for(i = 272,j=0; i < 336; i++,j++) S3[j] = tempVect[i];
int c3=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S3[x]==S3[y]) { cerr<<"(S3) "<<S3[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S3[x]<0 || S3[x]>15) { cerr<<"(S3) "<<S3[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c3=0; for(y=16;y<64;y++) { if(S3[x]==S3[y]) c3++; } if(c3<3 || c3>3) { cerr<<"(S3) "<<S3[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S3="; for( k=0;k<64;k++) cout<<S3[k]<<" ";

for(i = 336,j=0; i < 400; i++,j++) S4[j] = tempVect[i];
int c4=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S4[x]==S4[y]) { cerr<<"(S4) "<<S4[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S4[x]<0 || S4[x]>15) { cerr<<"(S4) "<<S4[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c4=0; for(y=16;y<64;y++) { if(S4[x]==S4[y]) c4++; } if(c4<3 || c4>3) { cerr<<"(S4) "<<S4[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S4="; for( k=0;k<64;k++) cout<<S4[k]<<" ";

for(i = 400,j=0; i < 464; i++,j++) S5[j] = tempVect[i];
int c5=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S5[x]==S5[y]) { cerr<<"(S5) "<<S5[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S5[x]<0 || S5[x]>15) { cerr<<"(S5) "<<S5[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c5=0; for(y=16;y<64;y++) { if(S5[x]==S5[y]) c5++; } if(c5<3 || c5>3) { cerr<<"(S5) "<<S1[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S5="; for( k=0;k<64;k++) cout<<S5[k]<<" ";

for(i = 464,j=0; i < 528; i++,j++) S6[j] = tempVect[i];
int c6=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S6[x]==S6[y]) { cerr<<"(S6) "<<S6[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S6[x]<0 || S6[x]>15) { cerr<<"(S6) "<<S6[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c6=0; for(y=16;y<64;y++) { if(S6[x]==S6[y]) c6++; } if(c6<3 || c6>3)  { cerr<<"(S6) "<<S6[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S6="; for( k=0;k<64;k++) cout<<S6[k]<<" ";

for(i = 528,j=0; i < 592; i++,j++) S7[j] = tempVect[i];
int c7=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S7[x]==S7[y]) { cerr<<"(S7) "<<S7[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S7[x]<0 || S7[x]>15) { cerr<<"(S7) "<<S7[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c7=0; for(y=16;y<64;y++) { if(S7[x]==S7[y]) c7++; } if(c7<3 || c7>3) { cerr<<"(S7) "<<S7[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S7="; for( k=0;k<64;k++) cout<<S7[k]<<" ";

for(i = 592,j=0; i < 656; i++,j++) S8[j] = tempVect[i]; // s8
int c8=0;
for(x=0;x<15;x++) { for(y=x+1;y<16;y++) { if(S8[x]==S8[y]) { cerr<<"(S8) "<<S8[x]<<" Does Not Occur 4 Times\n"; return 0; } } }
for(x=0;x<64;x++) { if(S8[x]<0 || S8[x]>15) { cerr<<"(S8) "<<S8[x]<<" Invalid Value\n"; return 0; } }
for(x=0;x<16;x++) { c8=0; for(y=16;y<64;y++) { if(S8[x]==S8[y]) c8++; } if(c8<3 || c8>3) { cerr<<"(S8) "<<S8[x]<<" Does Not Occur 4 Times\n";return 0; } }
//cout<<endl<<"S8="; for( k=0;k<64;k++) cout<<S8[k]<<" ";

for(i = 656,j=0; i < 672; i++,j++) V[j] = tempVect[i];
//for(x=0;x<16;x++) { if(V[x]<1 || V[x]>2) { cerr<<"(V) "<<V[x]<<" Not Allowed\n";return 0; } }
int oc=0,tc=0;
for(x=0;x<16;x++) { if(V[x]==1) oc++; if(V[x]==2) tc++; } 
if(oc<4 || oc>4) { cerr<<"(V) Value 1 Did Not Occur 4 Times \n";return 0; }
if(tc<12 || tc>12) { cerr<<"(V) Value 2 Did Not Occur 12 Times \n";return 0; }
//cout<<endl<<"V="; for( k=0;k<16;k++) cout<<V[k]<<" ";

for(i = 672,j=0; i < 728; i++,j++) PC1[j] = tempVect[i];
for(x=0;x<56;x++) if(PC1[x]<1 || PC1[x]>64 || PC1[x]%8==0) { cerr<<"(PC1) "<<PC1[x]<<" Value Not Allowed\n";return 0; }
for(x=0;x<55;x++) for(y=x+1;y<56;y++) { if(PC1[x]==PC1[y]) { cerr<<"(PC1) "<<PC1[x]<<" Occurs Too Many Times\n";return 0;  } }
//cout<<endl<<"PC1="; for( k=0;k<56;k++) cout<<PC1[k]<<" ";

for(i = 728,j=0; i < 776; i++,j++) PC2[j] = tempVect[i];
for(x=0;x<48;x++) if(PC2[x]<1 || PC2[x]>56 ) { cerr<<"(PC2) "<<PC2[x]<<" Value Not Allowed\n";return 0; }
for(x=0;x<47;x++) for(y=x+1;y<48;y++) { if(PC2[x]==PC2[y]) { cerr<<"(PC2) "<<PC2[x]<<" Occurs Too Many Times\n";return 0; } } 
//cout<<endl<<"PC2="; for( k=0;k<48;k++) cout<<PC2[k]<<" ";

return 1;
}
