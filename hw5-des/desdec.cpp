#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<bitset>
#include<vector>
#include<sys/types.h>
#include<time.h>

using namespace std;

string retSValD(int tc)
{
	string result="";
	switch(tc)
    {
        case 0: result="0000"; break;
        case 1: result="0001"; break;
        case 2: result="0010"; break;
        case 3: result="0011"; break;
        case 4: result="0100"; break;
        case 5: result="0101"; break;
        case 6: result="0110"; break;
        case 7: result="0111"; break;
        case 8: result="1000"; break;
        case 9: result="1001"; break;
        case 10: result="1010"; break;
        case 11: result="1011"; break;
        case 12: result="1100"; break;
        case 13: result="1101"; break;
        case 14: result="1110"; break;
        case 15: result="1111"; break;
    }
	return result;
}

string retHexBin(string tc)
{
	string result="";
	int i=0;
	for(i=0;i<tc.length();i++)
	{
	
        if(tc[i]=='0') result+="0000";
        if(tc[i]=='1') result+="0001";
        if(tc[i]=='2') result+="0010";
        if(tc[i]=='3') result+="0011";
        if(tc[i]=='4') result+="0100";
        if(tc[i]=='5') result+="0101";
        if(tc[i]=='6') result+="0110";
        if(tc[i]=='7') result+="0111";
        if(tc[i]=='8') result+="1000";
        if(tc[i]=='9') result+="1001";
        if(tc[i]=='a') result+="1010";
        if(tc[i]=='b') result+="1011";
        if(tc[i]=='c') result+="1100";
        if(tc[i]=='d') result+="1101";
        if(tc[i]=='e') result+="1110";
        if(tc[i]=='f') result+="1111";
    
	}
	return result;
}

string retRowD(string trow)
{
	string result="";
	if(trow=="00") result="0";
	if(trow=="01") result="1";
	if(trow=="10") result="2";
	if(trow=="11") result="3";
	return result;
}

string retColD(string tcol)
{
	string result="";
	if(tcol=="0000") result="0";
	if(tcol=="0001") result="1";
	if(tcol=="0010") result="2";
	if(tcol=="0011") result="3";
	if(tcol=="0100") result="4";
	if(tcol=="0101") result="5";
	if(tcol=="0110") result="6";
	if(tcol=="0111") result="7";
	if(tcol=="1000") result="8";
	if(tcol=="1001") result="9";
	if(tcol=="1010") result="10";
	if(tcol=="1011") result="11";
	if(tcol=="1100") result="12";
	if(tcol=="1101") result="13";
	if(tcol=="1110") result="14";
	if(tcol=="1111") result="15";
	return result;
}


string retHexD(string binStr)
{
int x=0;
string result="";
for(x=0;x<binStr.length();x+=4)
{
	string mid="";
	mid=binStr[x];
	mid+=binStr[x+1];
	mid+=binStr[x+2];
	mid+=binStr[x+3];
	//cout<<mid<<" ";
	if(mid=="0000") result+="0";
	if(mid=="0001") result+="1";
	if(mid=="0010") result+="2";
	if(mid=="0011") result+="3";
	if(mid=="0100") result+="4";
	if(mid=="0101") result+="5";
	if(mid=="0110") result+="6";
	if(mid=="0111") result+="7";
	if(mid=="1000") result+="8";
	if(mid=="1001") result+="9";
	if(mid=="1010") result+="a";
	if(mid=="1011") result+="b";
	if(mid=="1100") result+="c";
	if(mid=="1101") result+="d";
	if(mid=="1110") result+="e";
	if(mid=="1111") result+="f";
}
return result;
}

int DESdecrypt(string key,char tFile[],char inpFile[])
{
ifstream tabFile;
ifstream ipFile;
string hexKey="", keywoPar="";
string keys[16]="",keysBin[16]="";
int i=0,j=0,k=0,x=0,y=0;
tabFile.open(tFile,ios::binary);
if ( !tabFile ) // open the table file
{
	fputs("Cannot Open Table File\n", stderr); 
	return 0; 
}

ipFile.open(inpFile,ios::binary);
if ( !ipFile ) // open the plain text file
{
	fputs("Cannot Open Table File\n", stderr); 
	return 0; 
}
std::string ipStr((std::istreambuf_iterator<char>(ipFile)),
                 std::istreambuf_iterator<char>());
				 
string allBin=retHexBin(ipStr);

int nc[14]={0};
int IP[64]={0};
int IPinv[64]={0};
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
	nl++;
	k++;
}
tabFile.close();

if(nl!=14) { fputs("Invalid Table File\n", stderr); return 0; }

for(i = 0; i < 64; i++) IP[i] = tempVect[i];
int tempIndex=0,tempArray=0;
for (i = 0; i < 64; i++ ) 
{
		tempIndex = i+1;
		tempArray = IP[i]-1;
		IPinv[tempArray] = tempIndex;
}
for(i = 64,j=0; i < 112; i++,j++) E[j] = tempVect[i];
for(i = 112,j=0; i < 144; i++,j++) P[j] = tempVect[i];
for(i = 144,j=0; i < 208; i++,j++) S1[j] = tempVect[i]; // s1
for(i = 208,j=0; i < 272; i++,j++) S2[j] = tempVect[i];
for(i = 272,j=0; i < 336; i++,j++) S3[j] = tempVect[i];
for(i = 336,j=0; i < 400; i++,j++) S4[j] = tempVect[i];
for(i = 400,j=0; i < 464; i++,j++) S5[j] = tempVect[i];
for(i = 464,j=0; i < 528; i++,j++) S6[j] = tempVect[i];
for(i = 528,j=0; i < 592; i++,j++) S7[j] = tempVect[i];
for(i = 592,j=0; i < 656; i++,j++) S8[j] = tempVect[i]; // s8
for(i = 656,j=0; i < 672; i++,j++) V[j] = tempVect[i];
for(i = 672,j=0; i < 728; i++,j++) PC1[j] = tempVect[i];
for(i = 728,j=0; i < 776; i++,j++) PC2[j] = tempVect[i];

// convert to binary
for(i=0;i<16;i++)
{
switch(key[i])
    {
        case '0': hexKey+="0000"; break;
        case '1': hexKey+="0001"; break;
        case '2': hexKey+="0010"; break;
        case '3': hexKey+="0011"; break;
        case '4': hexKey+="0100"; break;
        case '5': hexKey+="0101"; break;
        case '6': hexKey+="0110"; break;
        case '7': hexKey+="0111"; break;
        case '8': hexKey+="1000"; break;
        case '9': hexKey+="1001"; break;
        case 'a': hexKey+="1010"; break;
        case 'b': hexKey+="1011"; break;
        case 'c': hexKey+="1100"; break;
        case 'd': hexKey+="1101"; break;
        case 'e': hexKey+="1110"; break;
        case 'f': hexKey+="1111"; break;
    }
}
// remove parity bits
for(i=0;i<56;i++)
{
	int a=PC1[i]-1;
	keywoPar+=hexKey[a];
}
//(C0,D0)=f0ccaa0aaccf00
string r1=retHexD(keywoPar);
cerr<<"(C0,D0)="<<r1<<endl;

string c="",d="",kt="",kk="",cd="",cd1="";
int shift=0;
for(j=0;j<16;j++)
{
kt="",kk="",cd="",cd1="";
if(j==0)
{
for(i=0;i<28;i++) c+=keywoPar[i];
for(i=28;i<56;i++) d+=keywoPar[i];
}
//left shift
shift=V[j];
std::rotate(c.begin(), c.begin() + shift, c.end());
std::rotate(d.begin(), d.begin() + shift, d.end());
for(i=0;i<28;i++) cd+=c[i];
for(i=0;i<28;i++) cd+=d[i];
cd1=retHexD(cd);
cerr<<"(C"<<j+1<<",D"<<j+1<<")="<<cd1<<endl;
for(i=0;i<48;i++)
{
	int b=PC2[i]-1;
	kt+=cd[b];
}
keysBin[j]=kt;
keys[j]=retHexD(kt);
cerr<<"k"<<j+1<<"="<<keys[j]<<endl;
}

// all keys inside keys[] array. 

//cout<<ipStr<<endl;

string binIpStr;
// convert input to binary
for (i = 0; i < ipStr.size(); i++)
	{
		std::bitset<8> b(ipStr.c_str()[i]);
		binIpStr+= b.to_string();
	}

//cout<<binIpStr<<endl;
// start encryption
//apply IP
string binIP="",bIp="";
for(i=0;i<64;i++)
{
	int c=IP[i]-1;
	binIP+=allBin[c];
}
bIp=retHexD(binIP);
//cout<<binIP<<" "<<binIP.length()<<endl;
cerr<<"(L0,R0)="<<bIp<<endl;
//cout<<keys[0]<<endl;
string L[17]="",R[17]="";
string nL[16]="",nR[16]="",LR[16]="";
string Ev[16]="",ekx[16]="";
string xr[16]="";
string fBuf="";

for(i=0;i<32;i++) L[0]+=binIP[i]; // L0
for(i=32;i<64;i++) R[0]+=binIP[i]; // R0
//START des
for(int z=0,y=15;z<=15;z++,y--)
{
if(z==0) nL[z]=R[z];
else
{
L[z]=R[z-1];
nL[z]=xr[z-1];
R[z]=nL[z];
}
//else R[z]=nL[z];
for(i=0;i<48;i++)
{
	int d=E[i]-1;
	Ev[z]+=R[z][d];
}

string tstr="";
//cout<<retHexD(keysBin[z])<<endl;
//cout<<retHexD(Ev[z])<<endl;
for(i=0;i<48;i++)
{
	tstr="";
	tstr+=Ev[z][i];
	tstr+=keysBin[y][i];
	//cout<<tstr<<" ";
	if(tstr=="10" || tstr=="01") ekx[z]+='1';
	else ekx[z]+='0';
}
//cout<<ekx[0]<<endl<<ekx[0].length()<<endl;
//cout<<retHexD(ekx[z])<<endl;
string sbit="",trw="",tcol="",r11="",r22="";

string f32="";
int tc=0;
int rw=0,rw1=0,rw2=0,cl=0;
// s box
for(i=0;i<48;i+=6)
{
	sbit="",trw="",tcol="";tc=0;
	sbit+=ekx[z][i]; sbit+=ekx[z][i+1]; sbit+=ekx[z][i+2]; sbit+=ekx[z][i+3]; sbit+=ekx[z][i+4]; sbit+=ekx[z][i+5];
	trw+=ekx[z][i]; trw+=ekx[z][i+5];
	r11=ekx[z][i]; r22=ekx[z][i+5];
	rw1=2*(atoi(r11.c_str()));
	rw2=rw1+(atoi(r22.c_str()));
	
	tcol+=ekx[z][i+1]; tcol+=ekx[z][i+2]; tcol+=ekx[z][i+3]; tcol+=ekx[z][i+4];	
	//cout<<sbit<<" ";
	trw=retRowD(trw); tcol=retColD(tcol);
	rw=(atoi(trw.c_str()));
	cl=atoi(tcol.c_str());
	//cout<<trw<<" "<<tcol<<endl;cout<<rw<<" "<<cl<<endl;
	if(i==0) tc=S1[(16*rw2)+cl];
	if(i==6) tc=S2[(16*rw2)+cl];
	if(i==12) tc=S3[(16*rw2)+cl];
	if(i==18) tc=S4[(16*rw2)+cl];
	if(i==24) tc=S5[(16*rw2)+cl];
	if(i==30) tc=S6[(16*rw2)+cl];
	if(i==36) tc=S7[(16*rw2)+cl];
	if(i==42) tc=S8[(16*rw2)+cl];
	f32+=retSValD(tc);
	//cout<<tc<<endl;
}
//cout<<retHexD(f32)<<endl;

for(i=0;i<32;i++)
{
	int e=P[i]-1;
	nR[z]+=f32[e];
}
//cout<<retHexD(nR[z])<<endl;
//cout<<retHexD(nR[z])<<" "<<retHexD(L[z])<<" "<<retHexD(nL[z])<<" "<<retHexD(nR[z])<<" "<<retHexD(R[z])<<endl;
// xor again
for(i=0;i<32;i++)
{	
	tstr="";
	tstr+=nR[z][i];
	
	tstr+=L[z][i];
	if(tstr=="10" || tstr=="01") xr[z]+='1';
	else xr[z]+='0';

}
//cout<<retHexD(nR[0])<<endl;
LR[z]+=nL[z];
LR[z]+=xr[z];
//cout<<nL[0]<<endl;
//cout<<nR[0]<<endl;
//cout<<LR[0]<<endl;
string tHex=retHexD(LR[z]);
if(z==15) fBuf+=LR[z];
cerr<<"(L"<<z+1<<",R"<<z+1<<")="<<tHex<<endl;
}
//cout<<fBuf<<endl;
string FinalOP="",DESec="";
for(i=32;i<64;i++) FinalOP+=fBuf[i];
for(i=0;i<32;i++) FinalOP+=fBuf[i];
//cout<<retHexD(FinalOP)<<endl;

//for(i=0;i<64;i++)
//{
//	if(IP[i]==64) IPinv[i]=IP[i];
//	else IPinv[i]=64-IP[i];
//}
for(i=0;i<64;i++)
{
	int f = IPinv[i]-1;
	DESec+=FinalOP[f];
}
cout<<retHexD(DESec)<<endl;

return 1;
}
