# include <netinet/in.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <string>
# include <math.h>

using namespace std;

extern unsigned long int getLongValue(unsigned long int tp);

int trialdiv(int n, char pfile[], int status)
{

/*
Trial division algorithm
That's it, we are ready to move on. First let's summarize our trial division algorithm in plain english:
Accept some input integer n
For each integer x from {2 ... sqrt(n)} check if x divides n
If you found a divisor then n is composite OR ELSE n is prime
*/

unsigned long long int nn = (unsigned long long int)n;
//cout<<"N is : "<<n<<endl;
//cout<<"File is : "<<pfile<<endl;

if(status>0)cout<<"  n = "<<n<<endl;

FILE *fpf;
fpf=fopen(pfile,"rb");
int res=0;
unsigned long int *calc_buff;
calc_buff = new unsigned long int;
res=fread(calc_buff,sizeof(unsigned long int),1,fpf);

if(res==0) 
{
	cerr<<"Error in reading primesfile"<<endl;
	exit(1);
}

unsigned long int maxval;
maxval = getLongValue(*calc_buff);

// start trial division algorithm
if(maxval<floor(sqrt(nn))) // run till square root of the number
{
	if(status==0) cout<<"n passes trial division test (not enough primes)"<<endl;
	else cout<<"  n passes trial division test (not enough primes)"<<endl;
	return 2;
}
	for( ; ; ) 
	{
		res=fread(calc_buff,sizeof(unsigned long int),1,fpf);
		if(res==0) 
		{
			break;
		}
		unsigned long int x;
		x = getLongValue(*calc_buff); 
		if((unsigned)x>=nn) break;
		
		if(nn%x==0) 
		{
			if(status==0) cout<<"n is composite by trial division (mod "<<x<<" = 0)"<<endl;
			else cout<<"  n is composite by trial division (mod "<<x<<" = 0)"<<endl;
			return 0;
		}
	}
	if(status==0) cout<<"n passes trial division test"<<endl;
	else cout<<"  n passes trial division test"<<endl;

return 1;

}
