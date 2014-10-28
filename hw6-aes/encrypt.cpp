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

extern string modprod(string poly1, string poly2, int status);
extern string* keyexp(string key, char tfile[],int status);

string xorb2(string x1, string x2)
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

string toBin2(string str)
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

int getIndex2(string val)
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


string toHex2(string str)
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

string getHex(long int num)   // Function Definition
{
long int rem[50],i=0,length=0;
char qw[5];
string str="";

while(num>0)
   {
      rem[i]=num%16;
      num=num/16;
      i++;
      length++;
   }
for(i=length-1;i>=0;i--)
  {
     switch(rem[i])
    {
      case 10:
          //cout<<"a";
		  str+="a";
          break;
      case 11:
          //cout<<"b";
		  str+="b";
          break;
      case 12:
          //cout<<"c";
		  str+="c";
          break;
      case 13:
          //cout<<"d";
		  str+="d";
          break;
      case 14:
          //cout<<"e";
		  str+="e";
          break;
      case 15:
          //cout<<"f";
		  str+="f";
          break;
      default :
		 qw[0] = rem[i] + '0';
		 str+=qw[0];
    }
  }
	return str;
}

string hdump ( char file_in_name[] )
{
  string fullHex="";
  string fname=file_in_name,ext;
  unsigned char buffer[20];
  string hexAddr="",bStr="";
  long int cnt;
  long int cnt2;
  ifstream file_in;
  long n;
//
//  Open the file.
//

  file_in.open ( file_in_name,ios::binary );

  if ( !file_in ) 
  {
    fputs("Cannot Open The File\n", stderr);
    exit(EXIT_FAILURE);
  }
  
  while ( ! file_in.eof ( ) )
  {
    file_in.read ( ( char * ) buffer, 16 );
    cnt = file_in.gcount();
    if ( cnt <= 0 )
    {
      break;
    }
	
    cnt2 = 0;
    for ( n = 0; n < 16; n++ )
    {
      cnt2 = cnt2 + 1;
	  bStr="";
      if ( cnt2 <= cnt )
      {
		bStr = getHex((int)buffer[n]);
		if(bStr.length()==1) bStr.insert(0,"0");
		if(bStr.length()==0) bStr.insert(0,"00");
		fullHex+=bStr;
      }
    }
  }
  file_in.close ( );
  return fullHex;
}

int encrypt(string key, char tFile[], char iFile[])
{
// ./hw6 encrypt -k=000102030405060708090a0b0c0d0e0f -t=aes.in testvec.in
ifstream tabFile;
tabFile.open(tFile,ios::binary);
int nl=0;
int i=0,k=0,j=0;
string ts="",Sbox[256];
string P="",PP="";

while(!tabFile.eof())
{
	string line="";
	getline(tabFile,line);
	unsigned pos = line.find("=");	
	if(nl==0) ts=line.substr(pos+1,line.length());
	if(nl==1) PP=line.substr(pos+1,line.length());
	nl++;
}
//cout<<"P : "<<P<<endl;
P+=PP[6]; P+=PP[7]; P+=PP[4]; P+=PP[5]; P+=PP[2]; P+=PP[3]; P+=PP[0]; P+=PP[1];
//cout<<"P : "<<P<<endl;
for(i=0,j=0;i<256;i++)
{
Sbox[i]=ts[j];j++;
Sbox[i]+=ts[j];j++;
}
//cout<<"SBox = \n";
//for(i=0;i<256;i++) cout<<Sbox[i];

string fullIp="";
string ipMat[4][4];
string *roundKeys = new string[44];

//cout<<"Key :   "<<key<<endl;
fullIp = hdump(iFile);
//cout<<"Input : "<<fullIp<<endl;

for(i=0,j=0,k=0;i<32;i+=2,j++)
{
	
	ipMat[k][j]=fullIp[i];
	ipMat[k][j]+=fullIp[i+1];
	if(j==4) { k++; j=0; }
	
}

//for(i=0;i<4;i++)
//{
//for(j=0;j<4;j++) cout<<ipMat[j][i]<<" ";
//cout<<endl;
//}
//cout<<endl;

cout<<"round[ 0].input    "<<fullIp<<endl;
cout<<"round[ 0].k_sch    "<<key<<endl;


roundKeys = keyexp(key,tFile,10);
//for(i=0;i<44;i++)
//cout<<roundKeys[i]<<endl;

// round 0
// xor with w0,w1,w2,w3
// rc = toHex1(xorb(toBin1(tcol2),toBin1(rcon[rcnt])));
string ipCol1="",ipCol2="",ipCol3="",ipCol4=""; 
string at1="",at2="",at3="",at4="";
string x1="",x2="",x3="",x4="",x="",mp1="",mp2="",mp3="",mp4="";
string n1="",n2="",n3="",n4="",tmp1[4][4],tmp2[4][4],tmp="";
string SboxStep[9],Sbox10="";
int index=0;
ipCol1+=ipMat[0][0]; ipCol1+=ipMat[0][1]; ipCol1+=ipMat[0][2]; ipCol1+=ipMat[0][3];
ipCol2+=ipMat[1][0]; ipCol2+=ipMat[1][1]; ipCol2+=ipMat[1][2]; ipCol2+=ipMat[1][3];
ipCol3+=ipMat[2][0]; ipCol3+=ipMat[2][1]; ipCol3+=ipMat[2][2]; ipCol3+=ipMat[2][3];
ipCol4+=ipMat[3][0]; ipCol4+=ipMat[3][1]; ipCol4+=ipMat[3][2]; ipCol4+=ipMat[3][3];       

//cout<<ipCol1<<" "<<ipCol2<<" "<<ipCol3<<" "<<ipCol4<<endl;

x1 = toHex2(xorb2(toBin2(ipCol1),toBin2(roundKeys[0])));
x2 = toHex2(xorb2(toBin2(ipCol2),toBin2(roundKeys[1])));
x3 = toHex2(xorb2(toBin2(ipCol3),toBin2(roundKeys[2])));
x4 = toHex2(xorb2(toBin2(ipCol4),toBin2(roundKeys[3])));
x+=x1; x+=x2; x+=x3; x+=x4;
int q=0;

//round[ 1].start    00102030405060708090a0b0c0d0e0f0
//round[ 1].s_box    63cab7040953d051cd60e0e7ba70e18c
//round[ 1].s_row    6353e08c0960e104cd70b751bacad0e7
//round[ 1].m_col    5f72641557f5bc92f7be3b291db9f91a
//round[ 1].k_sch    d6aa74fdd2af72fadaa678f1d6ab76fe
// start round 1-9
int round_key_count=4;
for(i=0;i<9;i++) // < 10
{
cout<<"round[ "<<i+1<<"].start    "<<x<<endl;
// sbox
for(j=0;j<(int)x.length();j+=2)
	{
		tmp=x[j]; tmp+=x[j+1];
		index = getIndex2(tmp);
		SboxStep[i]+=Sbox[index];
		tmp=""; index=0;
	}
	
for(q=0,j=0,k=0;q<32;q+=2,j++)
	{
		tmp1[k][j]=SboxStep[i][q];
		tmp1[k][j]+=SboxStep[i][q+1];
		if(j==4) { k++; j=0; }
	}

for(q=0;q<4;q++)
{
for(j=0;j<4;j++) { tmp2[q][j] = tmp1[j][q]; }
}

// tmp has matrix rep data

cout<<"round[ "<<i+1<<"].s_box    "<<SboxStep[i]<<endl;
cout<<"round[ "<<i+1<<"].s_row    ";

// row shift
n1=tmp2[1][0]; n2=tmp2[1][1]; n3=tmp2[1][2]; n4=tmp2[1][3]; 
tmp2[1][0]=n2; tmp2[1][1]=n3; tmp2[1][2]=n4; tmp2[1][3]=n1;
n1=""; n2=""; n3=""; n4="";

n1=tmp2[2][0]; n2=tmp2[2][1]; n3=tmp2[2][2]; n4=tmp2[2][3]; 
tmp2[2][0]=n3; tmp2[2][1]=n4; tmp2[2][2]=n1; tmp2[2][3]=n2;
n1=""; n2=""; n3=""; n4="";

n1=tmp2[3][0]; n2=tmp2[3][1]; n3=tmp2[3][2]; n4=tmp2[3][3]; 
tmp2[3][0]=n4; tmp2[3][1]=n1; tmp2[3][2]=n2; tmp2[3][3]=n3;
n1=""; n2=""; n3=""; n4="";

for(q=0;q<4;q++)
for(j=0;j<4;j++) cout<<tmp2[j][q];
cout<<endl;

//for(q=0;q<4;q++)
//{
//for(j=0;j<4;j++) cout<<tmp2[j][q]<<" ";
//cout<<endl;
//}
//cout<<endl;

// mix cols
n1=tmp2[0][0]; n1+=tmp2[1][0]; n1+=tmp2[2][0]; n1+=tmp2[3][0];
n2=tmp2[0][1]; n2+=tmp2[1][1]; n2+=tmp2[2][1]; n2+=tmp2[3][1]; 
n3=tmp2[0][2]; n3+=tmp2[1][2]; n3+=tmp2[2][2]; n3+=tmp2[3][2];
n4=tmp2[0][3]; n4+=tmp2[1][3]; n4+=tmp2[2][3]; n4+=tmp2[3][3];

//cout<<n1<<" "<<n2<<" "<<n3<<" "<<n4<<endl;

mp1=modprod(n1,P,10);
mp2=modprod(n2,P,10);
mp3=modprod(n3,P,10);
mp4=modprod(n4,P,10);

//cout<<mp1<<" "<<mp2<<" "<<mp3<<" "<<mp4<<endl;
//  5f726415 57f5bc92 f7be3b29 1db9f91a
tmp2[0][0]=mp1[2]; tmp2[0][0]+=mp1[3]; tmp2[1][0]=mp1[4]; tmp2[1][0]+=mp1[5]; tmp2[2][0]=mp1[6]; tmp2[2][0]+=mp1[7]; tmp2[3][0]=mp1[0]; tmp2[3][0]+=mp1[1];
tmp2[0][1]=mp2[2]; tmp2[0][1]+=mp2[3]; tmp2[1][1]=mp2[4]; tmp2[1][1]+=mp2[5]; tmp2[2][1]=mp2[6]; tmp2[2][1]+=mp2[7]; tmp2[3][1]=mp2[0]; tmp2[3][1]+=mp2[1];
tmp2[0][2]=mp3[2]; tmp2[0][2]+=mp3[3]; tmp2[1][2]=mp3[4]; tmp2[1][2]+=mp3[5]; tmp2[2][2]=mp3[6]; tmp2[2][2]+=mp3[7]; tmp2[3][2]=mp3[0]; tmp2[3][2]+=mp3[1];
tmp2[0][3]=mp4[2]; tmp2[0][3]+=mp4[3]; tmp2[1][3]=mp4[4]; tmp2[1][3]+=mp4[5]; tmp2[2][3]=mp4[6]; tmp2[2][3]+=mp4[7]; tmp2[3][3]=mp4[0]; tmp2[3][3]+=mp4[1];

cout<<"round[ "<<i+1<<"].m_col    ";
for(q=0;q<4;q++)
for(j=0;j<4;j++) cout<<tmp2[j][q];
cout<<endl;

// xor with round key
at1="",at2="",at3="",at4="";
at1=mp1[2]; at1+=mp1[3]; at1+=mp1[4]; at1+=mp1[5]; at1+=mp1[6]; at1+=mp1[7]; at1+=mp1[0]; at1+=mp1[1];
at2=mp2[2]; at2+=mp2[3]; at2+=mp2[4]; at2+=mp2[5]; at2+=mp2[6]; at2+=mp2[7]; at2+=mp2[0]; at2+=mp2[1];
at3=mp3[2]; at3+=mp3[3]; at3+=mp3[4]; at3+=mp3[5]; at3+=mp3[6]; at3+=mp3[7]; at3+=mp3[0]; at3+=mp3[1];
at4=mp4[2]; at4+=mp4[3]; at4+=mp4[4]; at4+=mp4[5]; at4+=mp4[6]; at4+=mp4[7]; at4+=mp4[0]; at4+=mp4[1];
//cout<<at1<<" "<<at2<<" "<<at3<<" "<<at4<<endl;
//cout<<ipCol1<<" "<<ipCol2<<" "<<ipCol3<<" "<<ipCol4<<endl;
x1 = toHex2(xorb2(toBin2(at1),toBin2(roundKeys[round_key_count++])));
x2 = toHex2(xorb2(toBin2(at2),toBin2(roundKeys[round_key_count++])));
x3 = toHex2(xorb2(toBin2(at3),toBin2(roundKeys[round_key_count++])));
x4 = toHex2(xorb2(toBin2(at4),toBin2(roundKeys[round_key_count++])));

x=x1; x+=x2; x+=x3; x+=x4;

cout<<"round[ "<<i+1<<"].k_sch    "<<roundKeys[round_key_count-4]<<roundKeys[round_key_count-3]<<roundKeys[round_key_count-2]<<roundKeys[round_key_count-1]<<endl;
}

//round[10].start    bd6e7c3df2b5779e0b61216e8b10b689
//round[10].s_box    7a9f102789d5f50b2beffd9f3dca4ea7
//round[10].s_row    7ad5fda789ef4e272bca100b3d9ff59f
//round[10].k_sch    13111d7fe3944a17f307a78b4d2b30c5
//round[10].output   69c4e0d86a7b0430d8cdb78070b4c55a

cout<<"round[10].start    "<<x<<endl;
//sbox
for(j=0;j<(int)x.length();j+=2)
	{
		tmp=x[j]; tmp+=x[j+1];
		index = getIndex2(tmp);
		Sbox10+=Sbox[index];
		tmp=""; index=0;
	}
	
for(q=0,j=0,k=0;q<32;q+=2,j++)
	{
		tmp1[k][j]=Sbox10[q];
		tmp1[k][j]+=Sbox10[q+1];
		if(j==4) { k++; j=0; }
	}
	
for(q=0;q<4;q++)
	{
		for(j=0;j<4;j++) { tmp2[q][j] = tmp1[j][q]; }
	}
cout<<"round[10].s_box    "<<Sbox10<<endl;
cout<<"round[10].s_row    ";

// row shift
n1=tmp2[1][0]; n2=tmp2[1][1]; n3=tmp2[1][2]; n4=tmp2[1][3]; 
tmp2[1][0]=n2; tmp2[1][1]=n3; tmp2[1][2]=n4; tmp2[1][3]=n1;
n1=""; n2=""; n3=""; n4="";

n1=tmp2[2][0]; n2=tmp2[2][1]; n3=tmp2[2][2]; n4=tmp2[2][3]; 
tmp2[2][0]=n3; tmp2[2][1]=n4; tmp2[2][2]=n1; tmp2[2][3]=n2;
n1=""; n2=""; n3=""; n4="";

n1=tmp2[3][0]; n2=tmp2[3][1]; n3=tmp2[3][2]; n4=tmp2[3][3]; 
tmp2[3][0]=n4; tmp2[3][1]=n1; tmp2[3][2]=n2; tmp2[3][3]=n3;
n1=""; n2=""; n3=""; n4="";
string tmp3[4][4];
for(q=0;q<4;q++)
for(j=0;j<4;j++) { cout<<tmp2[j][q]; tmp3[q][j]=tmp2[j][q]; }
cout<<endl;

cout<<"round[10].k_sch    "<<roundKeys[round_key_count+0]<<roundKeys[round_key_count+1]<<roundKeys[round_key_count+2]<<roundKeys[round_key_count+3]<<endl;

at1=tmp3[0][0]; at1+=tmp3[0][1]; at1+=tmp3[0][2]; at1+=tmp3[0][3]; 
at2=tmp3[1][0]; at2+=tmp3[1][1]; at2+=tmp3[1][2]; at2+=tmp3[1][3];
at3=tmp3[2][0]; at3+=tmp3[2][1]; at3+=tmp3[2][2]; at3+=tmp3[2][3];
at4=tmp3[3][0]; at4+=tmp3[3][1]; at4+=tmp3[3][2]; at4+=tmp3[3][3];

//cout<<at1<<" "<<at2<<" "<<at3<<" "<<at4<<endl;
//cout<<ipCol1<<" "<<ipCol2<<" "<<ipCol3<<" "<<ipCol4<<endl;
x1 = toHex2(xorb2(toBin2(at1),toBin2(roundKeys[round_key_count++])));
x2 = toHex2(xorb2(toBin2(at2),toBin2(roundKeys[round_key_count++])));
x3 = toHex2(xorb2(toBin2(at3),toBin2(roundKeys[round_key_count++])));
x4 = toHex2(xorb2(toBin2(at4),toBin2(roundKeys[round_key_count+0])));

x=x1; x+=x2; x+=x3; x+=x4;
cout<<"round[10].output   "<<x<<endl;


return 1;
}
