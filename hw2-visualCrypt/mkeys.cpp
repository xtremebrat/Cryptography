#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include <iomanip.h>
#include<math.h>
#include <sys/types.h>
#include <openssl/md5.h>

using namespace std;

void mdkeys(char pphrase[],int leng)
{

char *p1;
ofstream fp;
int counter=0;
int i=0;
p1=new char[30];
strcpy(p1,pphrase);
int length=leng;

fp.open ("md5Keys.txt");
unsigned char md5_buf[MD5_DIGEST_LENGTH];
int len=strlen(p1)+2+MD5_DIGEST_LENGTH;
char *s=new char[len+1];

MD5((unsigned char*)p1, strlen(p1), md5_buf);
 while(counter<(length/64)) {
sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p1);
memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
MD5((unsigned char*)s, len, md5_buf);
//fwrite(md5_buf, 1, sizeof(md5_buf)>>1,fp);
//fp.write((char *)md5_buf,sizeof(md5_buf));
fp<<(char *)md5_buf;
//cout<<hex<<(char*)md5_buf;
 if (++i == 100) i = 0;
 counter++;
    }
    free(s);
fp.close();

return ;
}
