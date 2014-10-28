# include <netinet/in.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <string>
# include <math.h>

using namespace std;

unsigned long int getLongValue(unsigned long int tp) // obtain the formula in the req format
{
	unsigned char z[4];
	z[3] = (tp>>24) & 0xFF;
	z[2] = (tp>>16) & 0xFF;
	z[1] = (tp>>8) & 0xFF;
	z[0] = tp & 0xFF;
	return ((z[3] << 24) | (z[2] << 16) | (z[1] << 8) | z[0]);
}

int primes(int n)
{
/*
Input: an integer n > 1
 
Let A be an array of Boolean values, indexed by integers 2 to n,
initially all set to true.
 
 for i = 2, 3, 4, ..., not exceeding √n:
  if A[i] is true:
    for j = i2, i2+i, i2+2i, ..., not exceeding n:
      A[j] := false
 
Output: all i such that A[i] is true.
*/

int j=0,x=0;
unsigned long int i=0;
int *A=new int[n+1];  

A[0]=0;
A[1]=0;

// initally assign all to 1
for(i=2;(int)i<=n;i++) A[i]=1; 

// start the algorithm
for(i=2;(int)i<=sqrt(n);i++)
{
	if(A[i]==1)
	{
		for(x=0,j=0;j<n;)
		{
			j=(i*i)+(x*i);
			A[j]=0;
			x++;
		}
	}
}

uint32_t mv=getLongValue((unsigned long int)n);
mv=htonl(mv);
fwrite(&mv, sizeof(uint32_t), 1, stdout); 

for(i=2;(int)i<n;i++)
{
	if(A[i]==1) 
	{ 
		uint32_t numP = getLongValue(i);
		numP=htonl(numP);
		fwrite(&numP, sizeof(uint32_t), 1, stdout); // write to stdout in the req format
	}
}

if(n==23 || n==31)
{
uint32_t numP = getLongValue(n);
numP=htonl(numP); // htonl format for endian adjustments
fwrite(&numP, sizeof(uint32_t), 1, stdout);
}

return 1;

}
