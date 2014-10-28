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
extern string modprod(string poly1, string poly2,int status);

int tabChk(char tFile[])
{
ifstream tabFile;
//int i=0,j=0,k=0,x=0,y=0;
tabFile.open(tFile,ios::binary);
string S="",P="",INVP="";

if ( !tabFile ) // open the cipher text file
{
	fputs("Cannot Open File\n", stderr); 
	return 0; 
}

vector<int> tempVect;

int nl=0,i=0,j=0;
while(!tabFile.eof())
{
	string line="";
	getline(tabFile,line);
	unsigned pos = line.find("=");
	if(line=="") break;	
	if(nl==0) S=line.substr(pos+1,line.length());
	if(nl==1) P=line.substr(pos+1,line.length());
	if(nl==2) INVP=line.substr(pos+1,line.length());
	nl++;
}

if(nl>3) { cerr<<"Invalid Table File"<<endl; exit (EXIT_FAILURE); }

if((int)S.length()!=512) { cerr<<"Invalid SBox - Invalid Number Of Characters"<<endl; return 0; }
if(S.find_first_not_of("abcdef0123456789") != std::string::npos) { cerr<<"Invalid SBox - Contains Invalid Characters"<<endl; return 0; }


string tempSB1="",tempSB2="";
for(i=0;i<512;i+=2)
{
	tempSB1=S[i]; tempSB1+=S[i+1];
	for(j=i+2;j<512;j+=2)
	{
		tempSB2=S[j]; tempSB2+=S[j+1];
		if(tempSB1==tempSB2) { cerr<<"Invalid SBox - Repeated Entries"<<endl; return 0; } 
	}
}

if(P.find_first_not_of("abcdef0123456789") != std::string::npos) { cerr<<"Invalid P - Contains Invalid Characters"<<endl; return 0; }
if(INVP.find_first_not_of("abcdef0123456789") != std::string::npos) { cerr<<"Invalid INVP - Contains Invalid Characters"<<endl; return 0; }

if(P.length() != 8 ) { cerr<<"Not A Valid P, Invalid # Of Characters !"<<endl; return 0; }
if(INVP.length() != 8 ) { cerr<<"Not A Valid INVP, Invalid # Of Characters !"<<endl; return 0; }

if(nl!=3) { fputs("Invalid Table File\n", stderr); return 0; }
string mpRes="";
mpRes = modprod(P,INVP,100);

if(mpRes != "00000001") { cerr<<"Not The Inverses !"<<endl; return 0; }

return 1;
}
