#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdint.h>
#include<iomanip>
#include<math.h>
#include<vector>
#include<sys/types.h>
#include<time.h>

using namespace std;

string toHex1(string str)
{
	//cout<<"str : "<<str<<endl;
	string h1="",result="";
	int i=0;
	for(i=0;i<(int)str.length();i+=4)
	{
	h1+=str[i]; h1+=str[i+1]; h1+=str[i+2]; h1+=str[i+3];
	
	if(h1=="0000") result+="0";
	if(h1=="0001") result+="1";
	if(h1=="0010") result+="2";
	if(h1=="0011") result+="3";
	if(h1=="0100") result+="4";
	if(h1=="0101") result+="5";
	if(h1=="0110") result+="6";
	if(h1=="0111") result+="7";
	if(h1=="1000") result+="8";
	if(h1=="1001") result+="9";
	if(h1=="1010") result+="a";
	if(h1=="1011") result+="b";
	if(h1=="1100") result+="c";
	if(h1=="1101") result+="d";
	if(h1=="1110") result+="e";
	if(h1=="1111") result+="f";
	h1="";
	}
	
	//cout<<"Res hex : "<<result<<endl;
	return result ;
}

string xorb(string x1, string x2)
{
	int k=0;
	//cout<<"x1 : "<<toHex1(x1)<<"\nx2 : "<<toHex1(x2)<<endl;
	string t1="";
	
	for(k=0;k<(int)x1.length(); k++)
			{
				if(x1[k]=='1' && x2[k]=='1') { t1+='0'; }
				else if(x1[k]=='0' && x2[k]=='1') { t1+='1'; }
				else if(x1[k]=='1' && x2[k]=='0') { t1+='1'; } 
				else if(x1[k]=='0' && x2[k]=='0') { t1+='0'; }
			}
			//cout<<"t1 : "<<t1<<endl;
	return t1;


}

string toBin1(string str)
{
	string res="";
	int i=0;
	for(i=0;i<(int)str.length();i++)
	{
	switch(str[i])
    {
        case '0': res+="0000"; break;
        case '1': res+="0001"; break;
        case '2': res+="0010"; break;
        case '3': res+="0011"; break;
        case '4': res+="0100"; break;
        case '5': res+="0101"; break;
        case '6': res+="0110"; break;
        case '7': res+="0111"; break;
        case '8': res+="1000"; break;
        case '9': res+="1001"; break;
        case 'a': res+="1010"; break;
        case 'b': res+="1011"; break;
        case 'c': res+="1100"; break;
        case 'd': res+="1101"; break;
        case 'e': res+="1110"; break;
        case 'f': res+="1111"; break;
    }
	}
	//cout<<"Res bin : "<<res<<endl;
	return res;
}

int getIndex(string val)
{
	string r="",c="";
	r=val[0]; c=val[1];
	int index=0;
	if(r>="a" && r<="f") { if(r=="a") index=16*10; if(r=="b") index=16*11; if(r=="c") index=16*12; if(r=="d") index=16*13; if(r=="e") index=16*14; if(r=="f") index=16*15; }
	else index=16*atoi(r.c_str());
	
	if(c>="a" && c<="f") { if(c=="a") index+=10; if(c=="b") index+=11; if(c=="c") index+=12; if(c=="d") index+=13; if(c=="e") index+=14; if(c=="f") index+=15; }
	else index+=atoi(c.c_str());
	
	return index;

}

string* keyexp(string key, char tfile[], int status)
{
// keyexpand -k=2b7e151628aed2a6abf7158809cf4f3c -t=aes.in
//cout<<"Key Is : "<<key<<endl;
//cout<<"File Is : "<<tfile<<endl;
string ts="",Sbox[256];
int i=0,j=0,k=0;
string firstc="",w4="",w0="",w1="",w2="",w3="";
ifstream tabFile;
tabFile.open(tfile,ios::binary);
if ( !tabFile ) // open the table file
{
	fputs("Cannot Open File\n", stderr); 
	return 0; 
}
int nl=0;
while(!tabFile.eof())
{
	string line="";
	getline(tabFile,line);
	unsigned pos = line.find("=");	
	if(nl==0) ts=line.substr(pos+1,line.length());
	nl++;
}
//cout<<"S = "<<ts<<endl<<ts.length()<<endl;

for(i=0,j=0;i<256;i++)
{
Sbox[i]=ts[j];j++;
Sbox[i]+=ts[j];j++;
}

//for(i=0;i<256;i++)
//cout<<Sbox[i]<<" ";
//cout<<endl;

string winit[4][4];

for(i=0,j=0,k=0;i<32;i+=2,j++)
{
	
	winit[k][j]=key[i];
	winit[k][j]+=key[i+1];
	if(j==4) { k++; j=0; }
	
}

w0=winit[0][0]; w0+=winit[0][1]; w0+=winit[0][2]; w0+=winit[0][3];
w1=winit[1][0]; w1+=winit[1][1]; w1+=winit[1][2]; w1+=winit[1][3];
w2=winit[2][0]; w2+=winit[2][1]; w2+=winit[2][2]; w2+=winit[2][3];
w3=winit[3][0]; w3+=winit[3][1]; w3+=winit[3][2]; w3+=winit[3][3];


//for(i=0;i<4;i++)
//{
//for(j=0;j<4;j++) cout<<winit[j][i]<<" ";
//cout<<endl;
//}
//cout<<endl;

// circular shift last column
string tmp1[4];
tmp1[0]=winit[3][0];
tmp1[1]=winit[3][1];
tmp1[2]=winit[3][2];
tmp1[3]=winit[3][3];

winit[3][0]=tmp1[1];
winit[3][1]=tmp1[2];
winit[3][2]=tmp1[3];
winit[3][3]=tmp1[0];

//for(i=0;i<4;i++)
//{
//for(j=0;j<4;j++) cout<<winit[j][i]<<" ";
//cout<<endl;
//}
//cout<<endl;

// s box !
//int ind=getIndex("aa");
//cout<<endl<<"index = "<<ind<<endl;

int s1=0,s2=0,s3=0,s4=0;
s1=getIndex(winit[3][0]);
s2=getIndex(winit[3][1]);
s3=getIndex(winit[3][2]);
s4=getIndex(winit[3][3]);

winit[3][0]=Sbox[s1];
winit[3][1]=Sbox[s2];
winit[3][2]=Sbox[s3];
winit[3][3]=Sbox[s4];

//for(i=0;i<4;i++)
//{
//for(j=0;j<4;j++) cout<<winit[j][i]<<" ";
//cout<<endl;
//}
///cout<<endl;

// rcon 
string rcon[10];
rcon[0]="01000000"; rcon[1]="02000000"; rcon[2]="04000000"; rcon[3]="08000000"; rcon[4]="10000000"; 
rcon[5]="20000000"; rcon[6]="40000000"; rcon[7]="80000000"; rcon[8]="1b000000"; rcon[9]="36000000";
string lastc="";
lastc=winit[3][0]; lastc+=winit[3][1]; lastc+=winit[3][2]; lastc+=winit[3][3];  
//cout<<lastc<<endl;
string rc="";
rc = toHex1(xorb(toBin1(lastc),toBin1(rcon[0])));
//cout<<rc1<<endl;

winit[3][0]=rc[0]; winit[3][0]+=rc[1];
winit[3][1]=rc[2]; winit[3][1]+=rc[3];
winit[3][2]=rc[4]; winit[3][2]+=rc[5];
winit[3][3]=rc[6]; winit[3][3]+=rc[7];

//for(i=0;i<4;i++)
//{
//for(j=0;j<4;j++) cout<<winit[j][i]<<" ";
//cout<<endl;
//}
//cout<<endl;

// w[ 0]: 2b7e1516

firstc=winit[0][0]; firstc+=winit[0][1]; firstc+=winit[0][2]; firstc+=winit[0][3];
//cout<<firstc<<endl;
w4 = toHex1(xorb(toBin1(firstc),toBin1(rc)));
//cout<<"w4 : "<<w4<<endl;
if(status<10)
{
cout<<"w[ 0]: "<<w0<<endl;
cout<<"w[ 1]: "<<w1<<endl;
cout<<"w[ 2]: "<<w2<<endl;
cout<<"w[ 3]: "<<w3<<endl;
cout<<"w[ 4]: "<<w4<<endl;
}

string *ww=new string[44];
ww[0]=w0;
ww[1]=w1;
ww[2]=w2;
ww[3]=w3;
ww[4]=w4;
string tm1="",tm2="",tm3="",tm4="";
int rcnt=1;

for(i=5;i<44;i++)
{
		if(i!=8 && i!=12 && i!=16 && i!=20 && i!=24 && i!=28 && i!=32 && i!=36 && i!=40 )        
		{
			//cout<<i<<endl;
			ww[i]=toHex1(xorb(toBin1(ww[i-1]),toBin1(ww[i-4])));
			if (i<10) { if(status<10) cout<<"w[ "<<i<<"]: "<<ww[i]<<endl; }
			else { if(status<10) cout<<"w["<<i<<"]: "<<ww[i]<<endl; }
		}
		
		else
		{
			//cout<<"HERE !!!"<<endl;
			s1=0,s2=0,s3=0,s4=0; rc="";
			tm1=ww[i-1][0]; tm1+=ww[i-1][1]; tm2=ww[i-1][2]; tm2+=ww[i-1][3]; tm3=ww[i-1][4]; tm3+=ww[i-1][5]; tm4=ww[i-1][6]; tm4+=ww[i-1][7]; 
			string tcol1="",tcol2="";
			//cout<<tm2<<" "<<tm3<<" "<<tm4<<" "<<tm1<<endl;
			//ww[i-1]="";
			// circ shift
			//ww[i-1]=tm2; ww[i-1]+=tm3; ww[i-1]+=tm4; ww[i-1]+=tm1;
			tcol1+=tm2; tcol1+=tm3; tcol1+=tm4; tcol1+=tm1;  
			// sbox
			s1=getIndex(tm2);
			s2=getIndex(tm3);
			s3=getIndex(tm4);
			s4=getIndex(tm1);
			tcol2=Sbox[s1];
			tcol2+=Sbox[s2];
			tcol2+=Sbox[s3];
			tcol2+=Sbox[s4];
			// rcon
			rc = toHex1(xorb(toBin1(tcol2),toBin1(rcon[rcnt]))); rcnt++;
			//ww[i-1]=rc;
			// xor
			ww[i] = toHex1(xorb(toBin1(ww[i-4]),toBin1(rc)));
		
			if(i<10) { if(status<10) cout<<"w[ "<<i<<"]: "<<ww[i]<<endl; }
			else { if(status<10) cout<<"w["<<i<<"]: "<<ww[i]<<endl; }
		}



}

return ww;
}
