#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<sys/types.h>
#include<time.h>

using namespace std;

int returnIndex2(char ach) // obtain alphabetic index
{
	int ind=0,p=0;
	string lkp="abcdefghijklmnopqrstuvwxyz";
	
	for(p=0;p<26;p++) if(ach==lkp[p]) ind=p;
	return ind;
}

int histo(int period,int ival,char cfile[])
{
int i=0,j=0,temp=0;
int total=0,cind=0;
int hcal[26]={0};
int limit=0;
string lkup="abcdefghijklmnopqrstuvwxyz";
string cStr="";

ifstream cipher_file;
cipher_file.open(cfile,ios::in);
if ( !cipher_file ) // open the cipher text file
	{
    fputs("Cannot Open File\n", stderr);
    return 0; 
	}

std::string mStr((std::istreambuf_iterator<char>(cipher_file)),
                 std::istreambuf_iterator<char>()); // converted to string
cStr=mStr;
cipher_file.close();
limit=cStr.length()-1;

i=0;
for(i=ival-1;i<limit;i+=period)
{
	cind=0;
	if(cStr[i] >= 'a' && cStr[i] <= 'z') // obtain total valid chars
	{
		total++;
		char tc=cStr[i];
		cind=returnIndex2(tc);
		hcal[cind]++;
	}
	else continue;
}
// output the values in descending order, handle clashes with alphabetic order
for(i=0;i<26;i++)
for(j=0;j<25;j++)
{
	if(hcal[j]<hcal[j+1])
		{
			temp=hcal[j+1];
			hcal[j+1]=hcal[j];
			hcal[j]=temp;
			char ts=lkup[j+1];
			lkup[j+1]=lkup[j];
			lkup[j]=ts;
		}
}

cout<<"L="<<total<<endl; // output total
float pval=0;
cout.setf(ios::fixed, ios::floatfield);
cout.precision(2);
for(j=0;j<26;j++) 
{
	pval=(float)(((float)(hcal[j])/(float)(total))*100);
	cout<<lkup[j]<<": "<<hcal[j]<<" ("<<pval<<"%)"; // output in the required format
	cout<<endl;
}
	
return 1;	
}
