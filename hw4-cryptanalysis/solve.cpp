#include<iostream>
#include<cctype>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<limits>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<sys/types.h>
#include<time.h>

using namespace std;

int solve(char ctfile[], int maxlen)
{
int offset=1,hits=0,totchar=0; 
double n=(double)26;
double IC=0,EIC=0,kp=0.0658,kr=0; 
kr=(double)((double)1/(double)n);
string lkup="abcdefghijklmnopqrstuvwxyz";
int freqs[26]={0};
int i=0,j=0,k=0;
int ctLen=0;
string ctStrBuf="";

ifstream cipher_tfile;
cipher_tfile.open(ctfile,ios::in);
if ( !cipher_tfile ) // open the cipher text file
	{
    fputs("Cannot Open File\n", stderr); 
	return 0; 
	}
std::string ctStr((std::istreambuf_iterator<char>(cipher_tfile)),
                 std::istreambuf_iterator<char>());

ctLen = ctStr.length() - 1;	
for(i=0;i<ctLen;i++) ctStrBuf+=ctStr[i];// newline at the end omitted

string compStr="";
//start kasiski method
cout<<"Kasiski Method\n==============\n";
int counter=1,k1=0,c1=0,c11=0,c2=0,strmat=0,match=0,len=4,clen=0;
while(counter!=0)
{
	counter=0;
	i=0;
	while(i+(len-1)<ctLen)
	{
		strmat=i+len;
		while(strmat+(len-1)<ctLen)
		{
			match=0,k1=0;
			c1=i;
			c2=strmat;
			clen=0;
			while(clen<len)
			{
				if(ctStrBuf[c1]==ctStrBuf[c2])
				{
					if((unsigned)ctStrBuf[c1]>=97 && (unsigned)ctStrBuf[c1]<=122) match++; // mactch valid characters
				}
				c1++; c2++; clen++;
			}
			
		if(match==len)
			{
				//len=4, i=41, j=131, j-i=90, zstv, 
				//format of output required
				counter=1;
				c11=i;
				int diff = strmat-i;
				cout<<"len="<<len<<", i="<<i<<", j="<<strmat<<", j-i="<<diff<<", ";
				for(int x=0;x<len;x++) { cout<<ctStrBuf[c11]; c11++; }
				cout<<endl;
			}	
			strmat++;
		}
		i++;
	}
	if(counter == 0) cout<<"len="<<len<<", no more matches\n\n"; // stop when no more matches
	len++;
}

// start average index of coincidence method
cout<<"Average Index of Coincidence\n============================\n";
for(i=0;i<ctLen;i++)
{
	if((unsigned)(ctStr[i])>=97 && (unsigned)(ctStr)[i]<=122)  // total valid characters
	{	
		totchar++;
		for(j=0;j<26;j++) if(ctStr[i]==lkup[j]) freqs[j]++;
	}
}

cout<<"L="<<totchar<<endl; // print total
for(k=0;k<26;k++) { cout<<"f('"<<lkup[k]<<"')="<<freqs[k]<<endl; IC+=(double)((freqs[k])*(freqs[k]-1)); } // corresponding letter frequencies
IC =(double)(IC/(totchar*(totchar-1))); // IC value
cout.setf(ios::fixed, ios::floatfield);
cout.precision(9); // precision maintained upto 9 decimals
cout<<"IC="<<IC<<endl;
for(i=1;i<=maxlen;i++)
{
	//EIC=0; compute EIC value
	EIC=(double)((((double)1/(double)i)*(((double)totchar-(double)i)/((double)totchar-(double)1))*kp) + ((((double)i-(double)1)/(double)i)*((double)totchar/((double)totchar-(double)1))*kr)) ;
	if(i==1)
	{
		cout<<"t="<<i<<", E(IC)="<<setprecision(4)<<EIC<<endl;	// stdout EIC value for period
	}
	else
	{
	cout<<"t="<<i<<", E(IC)="<<setprecision(9)<<EIC<<endl;
	}
}

// start auto correlation method
cout<<"\nAuto-correlation Method\n=======================\n";
hits=0;
while(offset<=maxlen)
{
	hits=0;
	for(i=offset,j=0;i<ctLen;i++,j++)
		{
			if((unsigned)(ctStr[i])>=97 && (unsigned)(ctStr)[i]<=122) if(ctStr[i]==ctStrBuf[j]) hits++;
		}
	cout<<"t="<<offset<<", "<<"count="<<hits<<endl;	
	offset++;
}

return 1;
}
