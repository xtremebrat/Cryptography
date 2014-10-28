# include <netinet/in.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <string>
# include <math.h>

using namespace std;

// hw7 millerrabin -n=number -t=maxitr -p=primesfile
extern unsigned long int getLongValue(unsigned long int tp);

// obtain the modulo
static uint64_t getTheModulo(uint64_t aaa, uint64_t xxx, uint64_t nnn) 
{
uint64_t rrr=1;
while (xxx) 
{
    if((xxx & 1) == 1) rrr = aaa*rrr % nnn;
	xxx>>= 1;
    aaa=aaa*aaa%nnn;
}
return rrr;
}

int combine(int a, int b) {
   int times = 1;
   while (times <= b)
      times *= 10;
   return a*times + b;
} 

// millerabin
int mrabin(unsigned long long int n,int t, char pfile[],int status)
{

FILE *fpf; // open the primesfile
fpf=fopen(pfile,"rb");
uint64_t NN=n;
uint64_t mmm=0;
int ss=0;
int res=0;
for (mmm = NN-1; !(mmm & 1); ++ss, mmm >>= 1 );
uint64_t RR = (NN-1) / (1<<ss);

unsigned long int *calc_buff;
calc_buff = new unsigned long int;

res=fread(calc_buff,sizeof(unsigned long int),1,fpf);
	if(res==0) {
		fputs("Error in reading primesfile\n",stderr);
		exit(1);
	}
	// output in the required format
	if(status==0) cout<<"n = "<<NN<<endl<<"  n-1 = "<<NN-1<<endl<<"  s = "<<ss<<endl<<"  r = "<<RR<<endl;
	else if(status>=100) cout<<"    n-1 = "<<NN-1<<endl<<"    s = "<<ss<<endl<<"    r = "<<RR<<endl;
	
for(int i=1;i<=t;i++) 
{
	res=fread(calc_buff,sizeof(unsigned long int),1,fpf);
	if(res==0) 
	{
	cerr<<"Error in reading primesfile\n"<<endl;
	exit(1);
	}
	unsigned long int aa;
	aa = getLongValue(*calc_buff); // obtain the long int value
	if(aa>(NN-1)) 
	{
		cout<<"maxitr is too large or not enough primes"<<endl;
		return 2;
	}
	
	uint64_t AA = (unsigned long long int)aa;
	uint64_t yy = getTheModulo(AA,RR,NN);
	
	if(status==0) cout<<"  Itr "<<i<<" of "<<t<<", a = "<<AA<<", y = "<<yy;
	else cout<<"    Itr "<<i<<" of "<<t<<", a = "<<AA<<", y = "<<yy;
	
	if(yy==NN-1) cout<<" (which is n-1)"<<endl; 
	else cout<<endl; 

	if(yy!=1 && yy!=NN-1) 
	{
		for(int jjj=1;(jjj<=ss-1 && yy!=NN-1);jjj++) 
		{
			yy = getTheModulo(yy,2,NN); // obtain modulo
			cout<<"    j = "<<jjj<<" of "<<ss-1<<", y = "<<yy;
			if(yy==NN-1) cout<<" (which is n-1)"<<endl; 
			else cout<<endl;
			if(yy==1) 
			{
				if(status==0) cout<<"  Miller-Rabin found a strong witness "<<AA<<endl;
				else cout<<"  Miller-Rabin found a strong witness "<<AA<<endl;
				return 0;
			}
		}
		
		if(yy!=NN-1) 
		{
			if(status==0) cout<<"Miller-Rabin found a strong witness "<<AA<<endl;
			else cout<<"  Miller-Rabin found a strong witness "<<AA<<endl;
			return 0;
		}
	}
}

if(status==0) cout<<"Miller-Rabin declares n to be a prime number"<<endl;
else cout<<"  Miller-Rabin declares n to be a prime number"<<endl;
return 1;

}
