#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<sys/types.h>
#include<time.h>

using namespace std;

int invkey(char file_in_name[])
{
char **ik;
char **ak;
string lk="abcdefghijklmnopqrstuvwxyz";
ifstream file_in;
int i=0,k=0,j=0;
int period=0;

file_in.open (file_in_name, ios::binary);

if ( !file_in ) 
	{
    fputs("Cannot Open File\n", stderr); 
	return 0; 
	}

while(!file_in.eof()) // obtain period
{
	string fullLine="";
	getline(file_in,fullLine, '\n'); 
	period++;
}
file_in.close();
period--;
ak= (char**)malloc((period) * sizeof(char*));
for(i=0;i<period;i++) ak[i] = (char*)malloc((26) * sizeof(char));

file_in.open (file_in_name, ios::binary);
k=0;

while(k<period) // store full key
{
	string fullLine=""; 
	getline(file_in,fullLine,'\n'); 
	for(i=0;i<26;i++) { ak[k][i]=fullLine[i]; if(fullLine[i]<97 || fullLine[i]>122) { fputs("Malformed File\n", stderr); return 0; }}
	k++;
}

ik= (char**)malloc((period) * sizeof(char*));
for(i=0;i<period;i++) ik[i] = (char*)malloc((26) * sizeof(char));

int index=0;

for(i=0;i<period;i++) // inverse the key
{
	for(j=0;j<26;j++)
	{
		index=0;
		for(k=0;k<26;k++) if(ak[i][j]==lk[k]) { index=k; } // cout<<index<<" "; }
		char tchar=lk[j]; //cout<<lk[j]<<" ";
		ik[i][index]=tchar;
	}
}

for(i=0;i<period;i++) // output the key stdout
{
	for(j=0;j<26;j++)
	{
	cout<<ik[i][j];
	}
if(i!=period-1) cout<<endl;
}
cout<<endl;
return 1;
}
