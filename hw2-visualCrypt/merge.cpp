# include <cstdlib>
# include <algorithm>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>
# include <sstream>
# include <bitset>

using namespace std;
extern string toBin(int num);

void merge(char file_in_name1[],char file_in_name2[])
{
	int fileLen1=0,fileLen2=0,nlcount1=0,nlcount2=0,space=0,wd=0,ht=0;
	std::ifstream ifs1(file_in_name1, ios::binary);
	std::ifstream ifs2(file_in_name2, ios::binary);
	char *buffer1,*buffer2;
	int tchar=0;

	if ( !ifs1 || !ifs2 ) 
  {
    fputs("Cannot Open The File - Error\n", stderr);
    return ;
  }
  ifs1.seekg (0, ios::end);
  fileLen1 = ifs1.tellg();
  ifs1.seekg (0, ios::beg);
  buffer1 = new char[fileLen1];
  ifs1.read (buffer1,fileLen1);
  string newbn1="",newbn2="",fullbn1="",fullbn2="";
  string head1="",head2="",head11="",head22="",wid="",het="";

  for(int i=0;i<fileLen1;i++)
  {
	  newbn1="";
	  tchar=(unsigned)(buffer1[i] & 0xff);
	  newbn1=toBin(tchar);

	  if(tchar==10) { nlcount1++; continue; }

	  if(nlcount1==0) { head1+=newbn1; head11+=buffer1[i]; }
	  else if(nlcount1==1) { head2+=newbn1; head22+=buffer1[i]; }
	  else { fullbn1+=newbn1; }

  }

  ifs2.seekg (0, ios::end);
  fileLen2 = ifs2.tellg();
  ifs2.seekg (0, ios::beg);
  buffer2 = new char[fileLen2];
  ifs2.read (buffer2,fileLen1);

  tchar=0;
  for(int i=0;i<fileLen2;i++)
  {
	  newbn2="";
	  tchar=(unsigned)(buffer2[i] & 0xff);
	  newbn2=toBin(tchar);

	  if(tchar==10) { nlcount2++; continue; }

	  
	  if(nlcount2>1) { fullbn2+=newbn2; }

  }




  	for(int j=0;j<head22.length();j++)
	{
		if(head22[j]==' ') { space=1; continue ; }
		if(space==0) { wid+=head22[j]; }
		if(space==1) { het+=head22[j]; }

	}
	
	for(int j=wid.length()-1;j>=0;j--)
	{
		wd+= ((int)wid[j]-48)*pow((double)10,((int)wid.length()-1-j));
	}


	for(int j=het.length()-1;j>=0;j--)
	{
		ht+= ((int)het[j]-48)*pow((double)10,((int)het.length()-1-j));
	}

	char s3[]="shared-merge.pbm";
	ofstream myfile3;
	myfile3.open (s3, ios::binary);
	myfile3 << "P4";
	myfile3 << "\n";
	myfile3 << head22;
	string merger="";
	string arStr1="";

	for(int x=0;x<fullbn1.length();x++)
	{
		if(fullbn1[x]==0 && fullbn2[x]==0) merger+="0";
		else merger+="1";
	}
	for(int i=0;i<merger.length();i+=8)
	{
		arStr1=merger.substr(i,8);
		int b=0;
		for( int j=0; j<arStr1.length(); j++ ) b = 2*b + arStr1[j] - '0';
		myfile3<<(char)b;
	}
	myfile3.close();
	ifs1.close();
	ifs2.close();

	getchar();
    return ;

}
