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

extern string dotprod(string p1, string p2);
extern string toHex(string str);
extern string toBin(string str);

string to2bHex2(int i)
{
std::stringstream sstream;
sstream << std::hex << i;
std::string result = sstream.str();
return result;
}

int inverse(string polyb)
{
// ./hw6 inverse -p=03010102
//cout<<"Polynomial Is : "<<polyb<<endl<<endl;
int i=0,j=0;
string Sbox[256][256];
string polya="0100000001";
string hexi="",hexj="",dpval="";

for(i=0;i<256;i++)
{
	hexi=to2bHex2(i);
	if((int)hexi.length()==1) hexi.insert(0,"0");
	for(j=0;j<256;j++)
	{
		hexj=to2bHex2(j);
		if((int)hexj.length()==1) hexj.insert(0,"0");
		dpval=toHex(dotprod(toBin(hexi),toBin(hexj)));
		Sbox[i][j]=dpval;
		dpval="",hexj="";
	}
	hexi="";
}
string rem[6],quo[6],aux[6],x="";
// i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}
// i=2, rem[i]={03}{01}{01}{02}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{01}
// i=3, rem[i]={00}{a4}{a5}{a5}, quo[i]={00}{00}{f6}{52}, aux[i]={00}{00}{f6}{52}
// i=4, rem[i]={00}{00}{4f}{c5}, quo[i]={00}{00}{8a}{4f}, aux[i]={00}{8f}{40}{45}
// i=5, rem[i]={00}{00}{00}{9a}, quo[i]={00}{00}{f3}{ca}, aux[i]={09}{78}{26}{cd}
// i=6, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{a8}{05}, aux[i]={0b}{0d}{09}{0e}
// Multiplicative inverse of {03}{01}{01}{02} is {0b}{0d}{09}{0e}

rem[0]="00000001"; quo[0]="00000000"; aux[0]="00000000"; quo[1]="00000000";
rem[1]=polyb[0]; rem[1]+=polyb[1]; rem[1]+=polyb[2]; rem[1]+=polyb[3]; rem[1]+=polyb[4]; rem[1]+=polyb[5]; rem[1]+=polyb[6]; rem[1]+=polyb[7];        
string e1="",d1="",q1="";
for(i=0;i<2;i++) // 6 rounds begin
{
	if(i==0)
	{
		// print in required format
		cout<<"i="<<i+1<<", rem[i]={"<<rem[0][0]<<rem[0][1]<<"}"<<"{"<<rem[0][2]<<rem[0][3]<<"}"<<"{"<<rem[0][4]<<rem[0][5]<<"}"<<"{"<<rem[0][6]<<rem[0][7]<<"}, quo[i]=";
		cout<<"{"<<quo[0][0]<<quo[0][1]<<"}"<<"{"<<quo[0][2]<<quo[0][3]<<"}"<<"{"<<quo[0][4]<<quo[0][5]<<"}"<<"{"<<quo[0][6]<<quo[0][7]<<"}, aux[i]=";
		cout<<"{"<<aux[0][0]<<aux[0][1]<<"}"<<"{"<<aux[0][2]<<aux[0][3]<<"}"<<"{"<<aux[0][4]<<aux[0][5]<<"}"<<"{"<<aux[0][6]<<aux[0][7]<<"}"<<endl;
	}
	if(i==1)
	{
		cout<<"i="<<i+1<<", rem[i]={"<<rem[1][0]<<rem[1][1]<<"}"<<"{"<<rem[1][2]<<rem[1][3]<<"}"<<"{"<<rem[1][4]<<rem[1][5]<<"}"<<"{"<<rem[1][6]<<rem[1][7]<<"}, quo[i]=";
		cout<<"{"<<quo[1][0]<<quo[1][1]<<"}"<<"{"<<quo[1][2]<<quo[1][3]<<"}"<<"{"<<quo[1][4]<<quo[1][5]<<"}"<<"{"<<quo[1][6]<<quo[1][7]<<"}, ";
		cout<<endl;
		
		
	}
	


}




return 1;
}
