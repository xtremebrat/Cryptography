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

int returnIndex(char ach) // return alphabetic index
{
	int ind=0,p=0;
	string lk="abcdefghijklmnopqrstuvwxyz";
	for(p=0;p<26;p++) if(ach==lk[p]) ind=p;
	return ind;
}

int encryptCode(int argcc, char** argvv)
{
int i=0,k=0,index=0,count=0,keyrow=0;
char *ipfile=argvv[3]; // obtain filenames
string arg1=argvv[2];
string ipStrFile="";
int limit=0;
char **key;
string kfile = arg1.substr(3,arg1.length());
char *keyfile = new char [kfile.length()+1];
strcpy (keyfile, kfile.c_str());
int period=0;

//cout<<"Key File is : "<<keyfile<<endl;
//cout<<"Input File is : "<<ipfile<<endl;

ifstream input_file,key_file;

key_file.open (keyfile, ios::in);
if ( !key_file ) // keyfine open
	{
    fputs("Cannot Open Keyfile !!!\n", stderr);
    return 0; 
	}
	
while(!key_file.eof()) // obtain period
{
	string fullLine="";
	getline(key_file,fullLine, '\n'); 
	period++;
}
key_file.close();
//cout<<"Period Is : "<<(--period)<<endl;
--period;
key_file.open (keyfile, ios::binary);

key= (char**)malloc((period) * sizeof(char*));
for(i=0;i<period;i++) key[i] = (char*)malloc((26) * sizeof(char));

k=0;
bool mfrm=false;
while(k<period)
{
	string fullLine=""; 
	getline(key_file,fullLine,'\n'); 
	for(i=0;i<26;i++) { key[k][i]=fullLine[i]; if(fullLine[i]<97 || fullLine[i]>122) mfrm=true; }
	k++;
}
key_file.close();

if(mfrm)
{
	fputs("Malformed Keyfile\n", stderr);
    return 0; 
}

if(argcc==4) // if specified, text file open
{	
input_file.open(ipfile, ios::in);
if ( !input_file ) 
	{
    fputs("Cannot Open Plain Text File\n", stderr);
    return 0; 
	}

std::string xStr((std::istreambuf_iterator<char>(input_file)),
                 std::istreambuf_iterator<char>()); // convert file to string and start manipulations
ipStrFile=xStr;
limit=ipStrFile.length();
input_file.close();
}

else if(argcc==3) // if no file specified, stdin 
{
	std::getline(std::cin,ipStrFile);
	limit=ipStrFile.length();
	
}	

count=0,index=0,keyrow=0;
for(i=0;i<limit;i++) // crypting
{
	if((unsigned)ipStrFile[i]==10) continue; 
	if((unsigned)ipStrFile[i] >= 32 && (unsigned)ipStrFile[i] <=126)
	{
	if(ipStrFile[i] >= 'a' && ipStrFile[i] <= 'z')
	{
		//cout<<ipStrFile[i]<<endl;
		char tch=ipStrFile[i]; //cout<<tch<<endl;
		index=returnIndex(tch); //cout<<index<<endl;
		keyrow=count%period;
		ipStrFile[i]=key[keyrow][index];
		index=0,keyrow=0;
		count++;
		//if(count==25) count=0; // chk
	}
	else { count++; index=0,keyrow=0; }
	}
	else { fputs("Improper Format\n", stderr); return 1; } // bad input
}

if((unsigned)ipStrFile[limit-1]!=10) ipStrFile+="\n";
cout<<ipStrFile;
return 1;
}
