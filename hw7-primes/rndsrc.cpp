#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <openssl/bn.h>

using namespace std;
extern int mrabin(unsigned long long int n,int t, char pfile[], int status);
extern int trialdiv(int n, char pfile[], int status);


// init the bignum type for rndsearch
BIGNUM* RndOddNum(int k, FILE *rf) {
	int zxz= ceil((double)k/8);
	unsigned char *calc_buff;
	calc_buff=new unsigned char[zxz];
	int res=0;
	res=fread(calc_buff,zxz,1,rf);
	if(res==0) return NULL;
	BIGNUM *bn_n=NULL;
	bn_n = BN_new();
	BN_zero(bn_n);
	BN_bin2bn(calc_buff, zxz, bn_n);
	BN_set_bit(bn_n, 0);
	BN_set_bit(bn_n, k-1);
	for(int i=k;i<zxz*8;i++) BN_clear_bit(bn_n, i);
	return bn_n;
}

// hw7 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile

int rndsrc(int k, int t, char pfile[], char rfile[])
{

FILE *fpf; // open primesfile
fpf=fopen(pfile,"rb");

FILE *frf; // open rnd file
frf=fopen(rfile,"rb");

int i=1;
int x=100;

for( ; ; ) 
{
	printf("RANDOM-SEARCH: iteration %d\n",i); // being the random iterarion
	BIGNUM *bn_n=NULL; // decl bignum
	//bn_n = BN_new();
	bn_n = RndOddNum(k,frf); // obtain the random odd number
	if(bn_n==NULL) break;	
	unsigned long long int n=(unsigned long long int)strtoull(BN_bn2dec(bn_n),NULL,0);	
	int res=trialdiv(n,pfile,x); // call trial div
	if(res==2) break;
	if(res==0) 
	{
		i++;
		rewind(fpf); // set back to start of file
		continue;
	}
	rewind(fpf); // set back to start of file
	if(mrabin(n,t,pfile,x)) // call millerabin
	{
		return 1;
		i++;
	}
	x++;
}

return 1;

}
