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

string xorfour(string x1, string x2, string x3, string x4) // perform xor operation
{
	int k=0;
	//cout<<x1<<endl<<x2<<endl<<x3<<endl<<x4<<endl;
	string t1="",t2="",t3="";
	
	for(k=0;k<8; k++)
			{
				if(x1[k]=='1' && x2[k]=='1') { t1+='0'; }
				else if(x1[k]=='0' && x2[k]=='1') { t1+='1'; }
				else if(x1[k]=='1' && x2[k]=='0') { t1+='1'; } 
				else if(x1[k]=='0' && x2[k]=='0') { t1+='0'; }
			}
			//cout<<"t1 : "<<t1<<endl;
	for(k=0;k<8; k++)
			{
				if(t1[k]=='1' && x3[k]=='1') t2+='0';
				else if(t1[k]=='0' && x3[k]=='1') t2+='1';
				else if(t1[k]=='1' && x3[k]=='0') t2+='1';
				else if(t1[k]=='0' && x3[k]=='0') t2+='0';
			}
			//cout<<"t2 : "<<t2<<endl;
	for(k=0;k<8; k++)
			{
				if(t2[k]=='1' && x4[k]=='1') t3+='0';
				else if(t2[k]=='0' && x4[k]=='1') t3+='1';
				else if(t2[k]=='1' && x4[k]=='0') t3+='1';
				else if(t2[k]=='0' && x4[k]=='0') t3+='0';
			}
			//cout<<t3<<endl;
	return t3;


}

string toHex(string str) // convert to hexadecimal
{
	string h1="",h2="",result="";
	h1+=str[0]; h1+=str[1]; h1+=str[2]; h1+=str[3];
	h2+=str[4]; h2+=str[5]; h2+=str[6]; h2+=str[7];
	
	if(h1=="0000") result="0";
	if(h1=="0001") result="1";
	if(h1=="0010") result="2";
	if(h1=="0011") result="3";
	if(h1=="0100") result="4";
	if(h1=="0101") result="5";
	if(h1=="0110") result="6";
	if(h1=="0111") result="7";
	if(h1=="1000") result="8";
	if(h1=="1001") result="9";
	if(h1=="1010") result="a";
	if(h1=="1011") result="b";
	if(h1=="1100") result="c";
	if(h1=="1101") result="d";
	if(h1=="1110") result="e";
	if(h1=="1111") result="f";

	if(h2=="0000") result+="0";
	if(h2=="0001") result+="1";
	if(h2=="0010") result+="2";
	if(h2=="0011") result+="3";
	if(h2=="0100") result+="4";
	if(h2=="0101") result+="5";
	if(h2=="0110") result+="6";
	if(h2=="0111") result+="7";
	if(h2=="1000") result+="8";
	if(h2=="1001") result+="9";
	if(h2=="1010") result+="a";
	if(h2=="1011") result+="b";
	if(h2=="1100") result+="c";
	if(h2=="1101") result+="d";
	if(h2=="1110") result+="e";
	if(h2=="1111") result+="f";
		
	return result ;
}

string toBin(string str)
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
	return res;
}

string dotprod(string p1, string p2) // perform the dot product
{
	//cout<<"p1 : "<<p1<<endl<<"p2 : "<<p2<<endl<<endl;
	string res="";
	string oneb="00011011";
	string tbuf[8]="";
	int i=0,k=0,c=0;
	tbuf[0]=p1;
	for(i=1; i<8; i++)
	{
		// left shift
		tbuf[i]+=tbuf[i-1][1]; tbuf[i]+=tbuf[i-1][2]; tbuf[i]+=tbuf[i-1][3]; tbuf[i]+=tbuf[i-1][4]; tbuf[i]+=tbuf[i-1][5]; tbuf[i]+=tbuf[i-1][6]; tbuf[i]+=tbuf[i-1][7]; tbuf[i]+='0';
		if(tbuf[i-1][0]=='1') // XOR with 1B
		{
			for(k=0;k<8; k++)
			{
				if(oneb[k]=='1' && tbuf[i][k]=='1') tbuf[i][k]='0';
				else if(oneb[k]=='0' && tbuf[i][k]=='1') tbuf[i][k]='1';
				else if(oneb[k]=='1' && tbuf[i][k]=='0') tbuf[i][k]='1';
				else if(oneb[k]=='0' && tbuf[i][k]=='0') tbuf[i][k]='0';
			}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		if(p2[i]=='1') 
		{ 
			if(c==0) { res=tbuf[7-i]; } 
			//cout<<7-i<<endl; 
			c++; 
			if(c>1) 
				{
					//cout<<tbuf[7-i]<<endl;
					for(k=0;k<8; k++)
					{
						
						if(res[k]=='1' && tbuf[7-i][k]=='1') res[k]='0';
						else if(res[k]=='0' && tbuf[7-i][k]=='1') res[k]='1';
						else if(res[k]=='1' && tbuf[7-i][k]=='0') res[k]='1';
						else if(res[k]=='0' && tbuf[7-i][k]=='0') res[k]='0';
					}
				} 
			//cout<<"Res : "<<res<<endl;
		}
			
	}
	

	return res;
}

string modprod(string poly1, string poly2, int status)
{
//cout<<"Poly1 : "<<poly1<<endl;
//cout<<"Poly2 : "<<poly2<<endl<<endl;
int i=0;
string pb1,pb2;
pb1=toBin(poly1);
pb2=toBin(poly2);

//cout<<"Poly1 : "<<pb1<<endl;
//cout<<"Poly2 : "<<pb2<<endl<<endl;

string aa0="",aa1="",aa2="",aa3="",bb0="",bb1="",bb2="",bb3="";
int a0=0,a1=0,a2=0,a3=0,b0=0,b1=0,b2=0,b3=0;
//int d0=0,d1=0,d2=0,d3=0;

for(i=0;i<(int)pb1.length();i++)
{
	if(i>=0 && i<=7) aa3+=pb1[i];
	if(i>=8 && i<=15) aa2+=pb1[i];
	if(i>=16 && i<=23) aa1+=pb1[i];
	if(i>=24 && i<=31) aa0+=pb1[i];
	
	if(i>=0 && i<=7) bb3+=pb2[i];
	if(i>=8 && i<=15) bb2+=pb2[i];
	if(i>=16 && i<=23) bb1+=pb2[i];
	if(i>=24 && i<=31) bb0+=pb2[i];
}

//cout<<"a0="<<aa0<<endl<<"a1="<<aa1<<endl<<"a2="<<aa2<<endl<<"a3="<<aa3<<endl;
//cout<<"b0="<<bb0<<endl<<"b1="<<bb1<<endl<<"b2="<<bb2<<endl<<"b3="<<bb3<<endl<<endl;

a0=atoi(aa0.c_str());
a1=atoi(aa1.c_str());
a2=atoi(aa2.c_str());
a3=atoi(aa3.c_str());
b0=atoi(bb0.c_str());
b1=atoi(bb1.c_str());
b2=atoi(bb2.c_str());
b3=atoi(bb3.c_str());

string res = dotprod(aa3,bb3);

string a0b0="",a3b1="",a2b2="",a1b3="";
string a1b0="",a0b1="",a3b2="",a2b3="";
string a2b0="",a1b1="",a0b2="",a3b3="";
string a3b0="",a2b1="",a1b2="",a0b3="";
string d0="",d1="",d2="",d3="";
string fd0="",fd1="",fd2="",fd3="";

if(bb0=="00000000") a0b0="00000000"; else a0b0=dotprod(aa0,bb0);
if(bb1=="00000000") a3b1="00000000"; else a3b1=dotprod(aa3,bb1);
if(bb2=="00000000") a2b2="00000000"; else a2b2=dotprod(aa2,bb2);
if(bb3=="00000000") a1b3="00000000"; else a1b3=dotprod(aa1,bb3); 
//cout<<"d0s args : "<<a2b2<<endl;
d0=xorfour(a0b0,a3b1,a2b2,a1b3);

if(bb0=="00000000") a1b0="00000000"; else a1b0=dotprod(aa1,bb0);
if(bb1=="00000000") a0b1="00000000"; else a0b1=dotprod(aa0,bb1);
if(bb2=="00000000") a3b2="00000000"; else a3b2=dotprod(aa3,bb2);
if(bb3=="00000000") a2b3="00000000"; else a2b3=dotprod(aa2,bb3);
//cout<<"d1s args : "<<a3b2<<endl;
d1=xorfour(a1b0,a0b1,a3b2,a2b3); 

if(bb0=="00000000") a2b0="00000000"; else a2b0=dotprod(aa2,bb0);
if(bb1=="00000000") a1b1="00000000"; else a1b1=dotprod(aa1,bb1);
if(bb2=="00000000") a0b2="00000000"; else a0b2=dotprod(aa0,bb2);
if(bb3=="00000000") a3b3="00000000"; else a3b3=dotprod(aa3,bb3);
//cout<<"d2s args : "<<a0b2<<endl;
d2=xorfour(a2b0,a1b1,a0b2,a3b3);

if(bb0=="00000000") a3b0="00000000"; else a3b0=dotprod(aa3,bb0);
if(bb1=="00000000") a2b1="00000000"; else a2b1=dotprod(aa2,bb1);
if(bb2=="00000000") a1b2="00000000"; else a1b2=dotprod(aa1,bb2);
if(bb3=="00000000") a0b3="00000000"; else a0b3=dotprod(aa0,bb3);
//cout<<"d3s args : "<<a1b2<<endl;
d3=xorfour(a3b0,a2b1,a1b2,a0b3);

//cout<<"Ds : "<<d0<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

fd0 = toHex(d0);
fd1 = toHex(d1);
fd2 = toHex(d2);
fd3 = toHex(d3);

// {f1}{83}{f2}{a4} CIRCLEX {0d}{5f}{e0}{7d} = {03}{90}{74}{7e}
if(status == 1)
{
cout<<"{"<<poly1[0]<<poly1[1]<<"}"<<"{"<<poly1[2]<<poly1[3]<<"}"<<"{"<<poly1[4]<<poly1[5]<<"}"<<"{"<<poly1[6]<<poly1[7]<<"} ";
cout<<"CIRCLEX ";
cout<<"{"<<poly2[0]<<poly2[1]<<"}"<<"{"<<poly2[2]<<poly2[3]<<"}"<<"{"<<poly2[4]<<poly2[5]<<"}"<<"{"<<poly2[6]<<poly2[7]<<"}";
cout<<" = {"<<fd3<<"}{"<<fd2<<"}{"<<fd1<<"}{"<<fd0<<"}"<<endl;
}
string mpRes="";
mpRes=fd3; mpRes+=fd2; mpRes+=fd1; mpRes+=fd0;

return mpRes;

}


