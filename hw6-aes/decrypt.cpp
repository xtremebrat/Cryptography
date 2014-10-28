#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<stdlib.h>
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

string to2bHex(int i)
{
std::stringstream sstream;
sstream << std::hex << i;
std::string result = sstream.str();
return result;
}

string toBin3(string str)
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

int getIndex3(string val)
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

string toHex3(string str)
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

	return result ;
}

string xorb3(string x1, string x2)
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


string getHex1(long int num)   // Function Definition
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


string hdump1 ( char file_in_name[] )
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
		bStr = getHex1((int)buffer[n]);
		if(bStr.length()==1) bStr.insert(0,"0");
		if(bStr.length()==0) bStr.insert(0,"00");
		fullHex+=bStr;
      }
    }
  }
  file_in.close ( );
  return fullHex;
}

int decrypt(string key, char tFile[], char iFile[])
{

// ./hw6 decrypt -k=000102030405060708090a0b0c0d0e0f -t=aes.in testvec.enc
ifstream tabFile;
tabFile.open(tFile,ios::binary);
int nl=0;
int i=0,k=0,j=0;
string ts="",Sbox[256],InvSbox[256];
string INVP="",PP="";

while(!tabFile.eof())
{
	string line="";
	getline(tabFile,line);
	unsigned pos = line.find("=");	
	if(nl==0) ts=line.substr(pos+1,line.length());
	if(nl==2) PP=line.substr(pos+1,line.length());
	nl++;
}

INVP+=PP[6]; INVP+=PP[7]; INVP+=PP[4]; INVP+=PP[5]; INVP+=PP[2]; INVP+=PP[3]; INVP+=PP[0]; INVP+=PP[1];
//cout<<"INVP1 : "<<PP<<endl;
//cout<<"INVP2 : "<<INVP<<endl;

string hexi="",hexj="";
for(i=0,j=0;i<256;i++)
{
Sbox[i]=ts[j];j++;
Sbox[i]+=ts[j];j++;
}
hexi="",hexj="";

//cout<<"SBox = "<<Sbox<<endl;
for(i=0;i<256;i++)
{
	hexi=to2bHex(i);
	if(hexi.length()==1) hexi.insert(0,"0");
	for(j=0;j<256;j++)
	{
		if(hexi.compare(Sbox[j])==0) { hexj=to2bHex(j); if(hexj.length()==1) hexj.insert(0,"0"); InvSbox[i]=hexj;  }
	}	
	
}

//cout<<"INV Sbox = \n";
//for(i=0;i<256;i++) cout<<InvSbox[i];

string fullIp="";
string ipMat[4][4];
string *roundKeys = new string[44];

//cout<<"Key :   "<<key<<endl;
fullIp = hdump1(iFile);
//cout<<"Input : "<<fullIp<<endl;

for(i=0,j=0,k=0;i<32;i+=2,j++)
{
	
	ipMat[k][j]=fullIp[i];
	ipMat[k][j]+=fullIp[i+1];
	if(j==4) { k++; j=0; }
	
}
roundKeys = keyexp(key,tFile,10);
//round 0
//round[ 0].iinput   69c4e0d86a7b0430d8cdb78070b4c55a
//round[ 0].ik_sch   13111d7fe3944a17f307a78b4d2b30c5

cout<<"round[ 0].iinput   "<<fullIp<<endl;
cout<<"round[ 0].ik_sch   "<<roundKeys[40]<<roundKeys[41]<<roundKeys[42]<<roundKeys[43]<<endl;

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

x1 = toHex3(xorb3(toBin3(ipCol1),toBin3(roundKeys[40])));
x2 = toHex3(xorb3(toBin3(ipCol2),toBin3(roundKeys[41])));
x3 = toHex3(xorb3(toBin3(ipCol3),toBin3(roundKeys[42])));
x4 = toHex3(xorb3(toBin3(ipCol4),toBin3(roundKeys[43])));
x+=x1; x+=x2; x+=x3; x+=x4;
x1=""; x2=""; x3=""; x4="";
int q=0;

//round[ 1].istart   7ad5fda789ef4e272bca100b3d9ff59f
//round[ 1].is_row   7a9f102789d5f50b2beffd9f3dca4ea7
//round[ 1].is_box   bd6e7c3df2b5779e0b61216e8b10b689
//round[ 1].ik_sch   549932d1f08557681093ed9cbe2c974e
//round[ 1].ik_add   e9f74eec023020f61bf2ccf2353c21c7

// start round 1-9

int round_key_count=39;
for(i=0;i<9;i++) // < 9
{
cout<<"round[ "<<i+1<<"].istart   "<<x<<endl;

// row manip 
for(q=0,j=0,k=0;q<32;q+=2,j++)
{
	
	ipMat[k][j]=x[q];
	ipMat[k][j]+=x[q+1];
	if(j==4) { k++; j=0; }
	
}

for(q=0;q<4;q++)
for(j=0;j<4;j++) { tmp1[q][j] = ipMat[j][q]; }

n1=tmp1[1][0]; n2=tmp1[1][1]; n3=tmp1[1][2]; n4=tmp1[1][3]; 
tmp1[1][0]=n4; tmp1[1][1]=n1; tmp1[1][2]=n2; tmp1[1][3]=n3;
n1=""; n2=""; n3=""; n4="";

n1=tmp1[2][0]; n2=tmp1[2][1]; n3=tmp1[2][2]; n4=tmp1[2][3]; 
tmp1[2][0]=n3; tmp1[2][1]=n4; tmp1[2][2]=n1; tmp1[2][3]=n2;
n1=""; n2=""; n3=""; n4="";

n1=tmp1[3][0]; n2=tmp1[3][1]; n3=tmp1[3][2]; n4=tmp1[3][3]; 
tmp1[3][0]=n2; tmp1[3][1]=n3; tmp1[3][2]=n4; tmp1[3][3]=n1;
n1=""; n2=""; n3=""; n4="";
x="";
cout<<"round[ "<<i+1<<"].is_row   ";
for(q=0;q<4;q++)
for(j=0;j<4;j++) { cout<<tmp1[j][q]; x+=tmp1[j][q]; }
cout<<endl;

// new s box
for(j=0;j<(int)x.length();j+=2)
	{
		tmp=x[j]; tmp+=x[j+1];
		index = getIndex3(tmp);
		SboxStep[i]+=InvSbox[index];
		tmp=""; index=0;
	}
	
for(q=0,j=0,k=0;q<32;q+=2,j++)
	{
		tmp1[k][j]=SboxStep[i][q];
		tmp1[k][j]+=SboxStep[i][q+1];
		if(j==4) { k++; j=0; }
	}

cout<<"round[ "<<i+1<<"].is_box   ";
x="";
for(q=0;q<4;q++)
for(j=0;j<4;j++) { cout<<tmp1[q][j]; x+=tmp1[q][j]; }
cout<<endl;

cout<<"round[ "<<i+1<<"].ik_sch   "<<roundKeys[round_key_count-3]<<roundKeys[round_key_count-2]<<roundKeys[round_key_count-1]<<roundKeys[round_key_count]<<endl;

// add round key
n1=x[0]; n1+=x[1]; n1+=x[2]; n1+=x[3]; n1+=x[4]; n1+=x[5]; n1+=x[6]; n1+=x[7];       
n2=x[8]; n2+=x[9]; n2+=x[10]; n2+=x[11]; n2+=x[12]; n2+=x[13]; n2+=x[14]; n2+=x[15];
n3=x[16]; n3+=x[17]; n3+=x[18]; n3+=x[19]; n3+=x[20]; n3+=x[21]; n3+=x[22]; n3+=x[23];
n4=x[24]; n4+=x[25]; n4+=x[26]; n4+=x[27]; n4+=x[28]; n4+=x[29]; n4+=x[30]; n4+=x[31];
//cout<<n1<<n2<<n3<<n4<<endl;

x1 = toHex3(xorb3(toBin3(n1),toBin3(roundKeys[round_key_count-3])));
x2 = toHex3(xorb3(toBin3(n2),toBin3(roundKeys[round_key_count-2])));
x3 = toHex3(xorb3(toBin3(n3),toBin3(roundKeys[round_key_count-1])));
x4 = toHex3(xorb3(toBin3(n4),toBin3(roundKeys[round_key_count])));
n1=""; n2=""; n3=""; n4="";

round_key_count=round_key_count-4;

x=x1; x+=x2; x+=x3; x+=x4;
cout<<"round[ "<<i+1<<"].ik_add   "<<x<<endl;

n1=x[0]; n1+=x[1]; n1+=x[2]; n1+=x[3]; n1+=x[4]; n1+=x[5]; n1+=x[6]; n1+=x[7];       
n2=x[8]; n2+=x[9]; n2+=x[10]; n2+=x[11]; n2+=x[12]; n2+=x[13]; n2+=x[14]; n2+=x[15];
n3=x[16]; n3+=x[17]; n3+=x[18]; n3+=x[19]; n3+=x[20]; n3+=x[21]; n3+=x[22]; n3+=x[23];
n4=x[24]; n4+=x[25]; n4+=x[26]; n4+=x[27]; n4+=x[28]; n4+=x[29]; n4+=x[30]; n4+=x[31];
//cout<<n1<<" "<<n2<<" "<<n3<<" "<<n4<<endl;

mp1=modprod(n1,INVP,10);
mp2=modprod(n2,INVP,10);
mp3=modprod(n3,INVP,10);
mp4=modprod(n4,INVP,10);

//cout<<mp1<<" "<<mp2<<" "<<mp3<<" "<<mp4<<endl;

tmp2[0][0]=mp1[2]; tmp2[0][0]+=mp1[3]; tmp2[1][0]=mp1[4]; tmp2[1][0]+=mp1[5]; tmp2[2][0]=mp1[6]; tmp2[2][0]+=mp1[7]; tmp2[3][0]=mp1[0]; tmp2[3][0]+=mp1[1];
tmp2[0][1]=mp2[2]; tmp2[0][1]+=mp2[3]; tmp2[1][1]=mp2[4]; tmp2[1][1]+=mp2[5]; tmp2[2][1]=mp2[6]; tmp2[2][1]+=mp2[7]; tmp2[3][1]=mp2[0]; tmp2[3][1]+=mp2[1];
tmp2[0][2]=mp3[2]; tmp2[0][2]+=mp3[3]; tmp2[1][2]=mp3[4]; tmp2[1][2]+=mp3[5]; tmp2[2][2]=mp3[6]; tmp2[2][2]+=mp3[7]; tmp2[3][2]=mp3[0]; tmp2[3][2]+=mp3[1];
tmp2[0][3]=mp4[2]; tmp2[0][3]+=mp4[3]; tmp2[1][3]=mp4[4]; tmp2[1][3]+=mp4[5]; tmp2[2][3]=mp4[6]; tmp2[2][3]+=mp4[7]; tmp2[3][3]=mp4[0]; tmp2[3][3]+=mp4[1];
x="";
for(q=0;q<4;q++)
for(j=0;j<4;j++) { x+=tmp2[j][q]; }
//cout<<"X : "<<x<<endl;
}

// round 10
//round[10].istart   6353e08c0960e104cd70b751bacad0e7
//round[10].is_row   63cab7040953d051cd60e0e7ba70e18c
//round[10].is_box   00102030405060708090a0b0c0d0e0f0
//round[10].ik_sch   000102030405060708090a0b0c0d0e0f
//round[10].ioutput  00112233445566778899aabbccddeeff

cout<<"round[10].istart   "<<x<<endl;

// row manip
for(q=0,j=0,k=0;q<32;q+=2,j++)
{
	
	ipMat[k][j]=x[q];
	ipMat[k][j]+=x[q+1];
	if(j==4) { k++; j=0; }
	
}

for(q=0;q<4;q++)
for(j=0;j<4;j++) { tmp1[q][j] = ipMat[j][q]; }

n1=tmp1[1][0]; n2=tmp1[1][1]; n3=tmp1[1][2]; n4=tmp1[1][3]; 
tmp1[1][0]=n4; tmp1[1][1]=n1; tmp1[1][2]=n2; tmp1[1][3]=n3;
n1=""; n2=""; n3=""; n4="";

n1=tmp1[2][0]; n2=tmp1[2][1]; n3=tmp1[2][2]; n4=tmp1[2][3]; 
tmp1[2][0]=n3; tmp1[2][1]=n4; tmp1[2][2]=n1; tmp1[2][3]=n2;
n1=""; n2=""; n3=""; n4="";

n1=tmp1[3][0]; n2=tmp1[3][1]; n3=tmp1[3][2]; n4=tmp1[3][3]; 
tmp1[3][0]=n2; tmp1[3][1]=n3; tmp1[3][2]=n4; tmp1[3][3]=n1;
n1=""; n2=""; n3=""; n4="";
x="";
cout<<"round[10].is_row   ";
for(q=0;q<4;q++)
for(j=0;j<4;j++) { cout<<tmp1[j][q]; x+=tmp1[j][q]; }
cout<<endl;

// inv sbox
Sbox10="";
for(j=0;j<(int)x.length();j+=2)
	{
		tmp=x[j]; tmp+=x[j+1];
		index = getIndex3(tmp);
		Sbox10+=InvSbox[index];
		tmp=""; index=0;
	}
	
for(q=0,j=0,k=0;q<32;q+=2,j++)
	{
		tmp1[k][j]=Sbox10[q];
		tmp1[k][j]+=Sbox10[q+1];
		if(j==4) { k++; j=0; }
	}

cout<<"round[10].is_box   ";
x="";
for(q=0;q<4;q++)
for(j=0;j<4;j++) { cout<<tmp1[q][j]; x+=tmp1[q][j]; }
cout<<endl;

//add round key
cout<<"round[10].ik_sch   "<<roundKeys[0]<<roundKeys[1]<<roundKeys[2]<<roundKeys[3]<<endl;

n1=x[0]; n1+=x[1]; n1+=x[2]; n1+=x[3]; n1+=x[4]; n1+=x[5]; n1+=x[6]; n1+=x[7];       
n2=x[8]; n2+=x[9]; n2+=x[10]; n2+=x[11]; n2+=x[12]; n2+=x[13]; n2+=x[14]; n2+=x[15];
n3=x[16]; n3+=x[17]; n3+=x[18]; n3+=x[19]; n3+=x[20]; n3+=x[21]; n3+=x[22]; n3+=x[23];
n4=x[24]; n4+=x[25]; n4+=x[26]; n4+=x[27]; n4+=x[28]; n4+=x[29]; n4+=x[30]; n4+=x[31];
//cout<<n1<<n2<<n3<<n4<<endl;

x1 = toHex3(xorb3(toBin3(n1),toBin3(roundKeys[0])));
x2 = toHex3(xorb3(toBin3(n2),toBin3(roundKeys[1])));
x3 = toHex3(xorb3(toBin3(n3),toBin3(roundKeys[2])));
x4 = toHex3(xorb3(toBin3(n4),toBin3(roundKeys[3])));
n1=""; n2=""; n3=""; n4="";

x=x1; x+=x2; x+=x3; x+=x4;
cout<<"round[10].ioutput  "<<x<<endl;

return 1;
}
