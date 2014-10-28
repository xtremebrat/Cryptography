# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <stdlib.h>
# include <fstream>
# include <string>
# include <math.h>
#include <sys/types.h>
#include <openssl/md5.h>
#define MD5_DIGEST_LENGTH 16
#define p "yesnomaybe"

using namespace std;

extern string hdump ( char file_in_name[] );
extern string toBin(int num);
extern void pbdump ( char file_in_name[], string keyString );
extern void merge(char file_in_name1[],char file_in_name2[]);

int main ( int argc, char *argv[] )
{
  char tFileName[]="tempp.txt";
  //string fname;
  string ch1="stream",ch2="encrypt",ch3="merge",ch4="decrypt",choice="";
  char fname[30],pbmname[30];
  //string ch1="keydump",ch2="pbdump",choice="";
  string contents,keyStr;
  ofstream tempFile,fp;
  int i,k,j;

  if(argc <= 1)
  {
	  fputs("Provide Arguments ( stream / encrypt / merge/ decrypt )", stderr); cout<<endl;
	  return 0;
  }

  else if ( argc ==2 ) //call Appropriate function with std input
  {
	  choice=argv[1];
	  if(choice==ch1) // stream
	  {
		  if(argc == 4)
		  {
			  string pp="",ll="";
			  pp=argv[2];
			  ll=argv[3];
			  pp.erase(0,3);
			  char *ppr;
			  for(int z=0;z<pp.length();z++) ppr[z]=pp[z];
			  ll.erase(0,3);
			  int leng = atoi(ll.c_str());
			  
			  unsigned char md5_buf[MD5_DIGEST_LENGTH];
				int len=strlen(p)+2+MD5_DIGEST_LENGTH;
				char *s=new char[len+1];
				int i=0;

				MD5((unsigned char*)p, strlen(p), md5_buf);
				for (;;) {
				sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
				memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
				MD5((unsigned char*)s, len, md5_buf);
				//fwrite(md5_buf, 1, sizeof(md5_buf)>>1, stdout);
				fp<<(char *)md5_buf;
				//puts((char*)md5_buf);
				if (++i == 100) i = 0;
					}
				free(s);

			  keyStr = hdump("md5keys.txt");
		  int *arrayBinKey = new int[keyStr.length()]; //integer array of the key string bits !
		  for(k=0;k<keyStr.length();k++)
			{
				arrayBinKey[k]=(int)keyStr[k]-48;
				//cout<<arrayBinKey[k];
			}
		  }
		  else fputs("Bad Commandline", stderr); cout<<endl;
	  return 0;
	  }

	  if(choice==ch2)
	  {
		  if(argc == 4)
		  {
		  string pp="",pbname="";
		  pp=argv[2];
		  pbname=argv[3];
		  pp.erase(0,3); 
		  pbname.erase(0,3);
		  char *file=new char[50];
		  for(int x=0;x<pbname.length();x++) file[x]=pbname[x];

		  // insert function call to keys
		  fp.open("md5keys.txt");
		  
		  keyStr = hdump("md5keys.txt");
		  int *arrayBinKey = new int[keyStr.length()]; //integer array of the key string bits !
		  for(k=0;k<keyStr.length();k++)
			{
				arrayBinKey[k]=(int)keyStr[k]-48;
				//cout<<arrayBinKey[k];
			}

		  pbdump(file,keyStr);
		  }
		  
		  else fputs("Bad Commandline", stderr); cout<<endl;
			return 0;
	  }
	  if(choice==ch3)
	  {
		  if(argc == 4)
		  { string m1="",m2="";
			m1=argv[2];
			m2=argv[3];
			char *file1=new char[50], *file2=new char[50];
			merge(file1,file2);

		  }
		  else fputs("Bad Commandline", stderr); cout<<endl;
				return 0;
	  }
	
	if(choice==ch4)
{
fputs("Bad Commandline", stderr); cout<<endl;
				return 0;
}	
  }

	rm("md5keys.txt");
	return 0;

}
