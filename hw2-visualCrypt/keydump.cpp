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

string toBin(int num)   // Function Definition
{
	string binStr="",fullBin="";
	int keys[1024];
	int i=1,k=0;
	long int bin=0;
	int rem;
	binStr="";
	do
    {
        rem=num%2; if(rem==0) binStr+='0' ; else binStr += '1';
        bin=bin + (i*rem);
		keys[k]=(i*rem);
		k++;
        num=num/2;
        i=i*10;
    }while(num>0);

	binStr = string ( binStr.rbegin(), binStr.rend() );
	
	if(binStr.length() == 7) binStr.insert(0,"0"); else if(binStr.length()==6) binStr.insert(0,"00"); else if(binStr.length()==5) binStr.insert(0,"000"); else if(binStr.length()==4) binStr.insert(0,"0000"); else if(binStr.length()==3) binStr.insert(0,"00000"); else if(binStr.length()==2) binStr.insert(0,"000000"); else if(binStr.length()==1) binStr.insert(0,"0000000");  //insert the leading 0s 
	return binStr;
}

string getHex(long int num)   // converting decimal to hexadecimal value
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
		  str+="a";
          break;
      case 11:
		  str+="b";
          break;
      case 12:
		  str+="c";
          break;
      case 13:
		  str+="d";
          break;
      case 14:
		  str+="e";
          break;
      case 15:
		  str+="f";
          break;
      default :
		 qw[0] = rem[i] + '0';
		 str+=qw[0];
    }
  } //cout<<endl;
	if (str.length()==2) return str;
	else { str.insert(0,"0"); return str; } 
}

string hdump ( char file_in_name[] )
{
  long int addr;
  int i=0,k=0,nl=0;
  bool lLine=false;
  unsigned char buffer[20];
  string hexAddr="",bStr="",kStr="";
  long int cnt;
  long int cnt2;
  ifstream file_in;
  long n;

  file_in.open ( file_in_name,ios::binary ); // opening file in binary mode

  if ( !file_in ) 
  {
    fputs("Cannot Open The File - Error\n", stderr);
    return 0 ;
  }

  while ( ! file_in.eof ( ) )
  {
    file_in.read ( ( char * ) buffer, 16 ); // reading 16 characters at a time per iteration

    cnt = file_in.gcount();

    if ( cnt <= 0 )
    {
      break;
    }

    cnt2 = 0;
    for ( n = 0; n < 8; n++ ) // 8 data items printed in pairs of hexAdecimal
    {  
      cnt2 = cnt2 + 1; 
      if ( cnt2 <= cnt )
      {
		nl++;
		int tmpchar=(unsigned)(buffer[i] & 0xff);
		string dbn=toBin(tmpchar);
		bStr += getHex((int)buffer[n]);  //converting to hexadecimal
		kStr += dbn;	 //converting to binary
      }
      
    }
	
  }
	
  file_in.close ( ); //file closed
  //cout<<bStr<<endl;
  //cout<<endl<<kStr<<endl;
  return kStr;
}

void pbdump ( char file_in_name[], string keyString )
{
  int i=0,j=0,k=0,wd=0,ht=0,newwd=0,newht=0;
  
  string fullbin="",fullHex="";
  bool lLine=false;
  char *buffer;
  string arStr[1024];
//  unsigned char buffer[20];
  char tFileName[]="tempp20.txt";
  int nlcount=0,space=0,fileLen=0;
  int tchar=0;
  ofstream tempFile;
  string head1="",head2="",head11="",head22="",wid="",het="";
  ifstream file_in;
  long n;

  int *arrayBinKey = new int[keyString.length()]; //integer array of the key string bits !
		for(k=0;k<keyString.length();k++)
			{
				arrayBinKey[k]=(int)keyString[k]-48;
				//cout<<arrayBinKey[k];
			}
		//cout<<endl<<"Key Length : "<<keyString.length()<<endl;
		int totalKey=keyString.length();

  std::ifstream ifs(file_in_name, ios::binary); // opening file in binary mode

  if ( !file_in ) 
  {
    fputs("Cannot Open The File - Error\n", stderr);
    return ;
  }

  ifs.seekg (0, ios::end);
  fileLen = ifs.tellg();
  ifs.seekg (0, ios::beg);
  buffer = new char[fileLen];
  ifs.read (buffer,fileLen);
  string newbn="",fullbn="";

  for(i=0;i<fileLen;i++)
  {
	  newbn="";
	  tchar=(unsigned)(buffer[i] & 0xff);
	  newbn=toBin(tchar);

	  if(tchar==10) { nlcount++; continue; }

	  if(nlcount==0) { head1+=newbn; head11+=buffer[i]; }
	  else if(nlcount==1) { head2+=newbn; head22+=buffer[i]; }
	  else { fullbn+=newbn; }

  }

	cout<<head11<<endl<<"Orig : "<<head22<<endl;
	//cout<<fullbn<<endl;
	for(j=0;j<head22.length();j++)
	{
		if(head22[j]==' ') { space=1; continue ; }
		if(space==0) { wid+=head22[j]; }
		if(space==1) { het+=head22[j]; }

	}
	
	for(j=wid.length()-1;j>=0;j--)
	{
		wd+= ((int)wid[j]-48)*pow((double)10,((int)wid.length()-1-j));
	}


	for(j=het.length()-1;j>=0;j--)
	{
		ht+= ((int)het[j]-48)*pow((double)10,((int)het.length()-1-j));
	}

	int orgwidadj=0;
	if(wd%8 !=0) orgwidadj = 8 - (wd%8);

	int *arrayBinPbm = new int[fullbn.length()]; //integer array of the pbm file bits !
  for(k=0;k<fullbn.length();k++)
  {
	arrayBinPbm[k]=(int)fullbn[k]-48;
	//if(k%(wd+orgwidadj)==0) cout<<endl; // only for printin
	//cout<<arrayBinPbm[k]; 
  }	
  int totalPbm=fullbn.length();

	newwd=wd*2;
	newht=ht*2;
	string head22new="";
	std::stringstream wth;
	wth << newwd;
	head22new+=wth.str();
	head22new+=" ";
	std::stringstream hth;
	hth << newht;
	head22new+=hth.str();
	head22new+="\n";

	
	int newwidadj=0;

	// newwd is new width, newht is new height, widadj is no of padding 0s in the new pbms, header P4 is stored in head11 as string. new w*h haeder should be made.
	// P4\n w h\n pbm bits

	string share11="",share22="",r1="",r2="",r3="",r4="";
	int binFileCount=0,keyCount=0,bitcnt=0;

	if(newwd%8 !=0) newwidadj = 8 - (newwd%8); //no of 0s to be padded
	int rowlimit=newwd+newwidadj;
	cout<<endl<<"New : "<<newwd<<" "<<newht<<endl<<"Adj bits : "<<newwidadj<<endl<<endl;

	int** share1 = new int*[newht];
	for(i = 0; i < newht; ++i)	share1[i] = new int[(newwd+newwidadj)];

	int** share2 = new int*[newht];
	for(i = 0; i < newht; ++i)	share2[i] = new int[(newwd+newwidadj)];

	binFileCount=0;

	while(binFileCount<totalPbm)
	{
		if(bitcnt==newwd) 
		{
			//cout<<"here 1";
			bitcnt=0; //track of row
			binFileCount+=orgwidadj;
			for(k=0;k<newwidadj;k++) { r1+="0"; r2+="0"; r3+="0"; r4+="0"; }
			r1+=r2;
			//cout<<r1<<endl;
			share11+=r1;
			//cout<<share11<<endl;
			r3+=r4;
			share22+=r3;
			r1=""; r2=""; r3=""; r4="";
		}
		
		else if(arrayBinPbm[binFileCount]==0 && arrayBinKey[keyCount]==0 )
			{
				//cout<<arrayBinPbm[binFileCount]<<" - "<<arrayBinKey[keyCount]<<endl;
				//cout<<"here 2";
				r1+="10"; r3+="10";
				r2+="01"; r4+="01";
				binFileCount++;
				keyCount++;
				bitcnt+=2;
			}
		else if(arrayBinPbm[binFileCount]==0 && arrayBinKey[keyCount]==1)
			{
				//cout<<arrayBinPbm[binFileCount]<<" - "<<arrayBinKey[keyCount]<<endl;
				//cout<<"here 3";
				r1+="01"; r3+="01";
				r2+="10"; r4+="10";
				binFileCount++;
				keyCount++;
				bitcnt+=2;
			}
		else if(arrayBinPbm[binFileCount]==1 && arrayBinKey[keyCount]==0)
			{
				//cout<<arrayBinPbm[binFileCount]<<" - "<<arrayBinKey[keyCount]<<endl;
				//cout<<"here 4";
				r1+="10"; r3+="01";
				r2+="01"; r4+="10";
				binFileCount++;
				keyCount++;
				bitcnt+=2;
			}
		else if(arrayBinPbm[binFileCount]==1 && arrayBinKey[keyCount]==1 )
			{
				//cout<<arrayBinPbm[binFileCount]<<" - "<<arrayBinKey[keyCount]<<endl;
				//cout<<"here 5";
				r1+="01"; r3+="10";
				r2+="10"; r4+="01";
				binFileCount++;
				keyCount++;
				bitcnt+=2;
			}

		
	}

	//cout<<endl<<share11.length()<<endl<<share22.length()<<endl<<endl;

	char s1[]="share.1.pbm";
	char s2[]="share.2.pbm";
	string nl="\n";

	long tempVar=0;
	ofstream myfile;
	myfile.open (s1, ios::binary);
	myfile << head11;
	myfile <<nl;
	myfile << head22new; 
	string arStr1="";
	for(i=0;i<share11.length();i+=8)
	{
		arStr1=share11.substr(i,8);
		int b=0;
		for( j=0; j<arStr1.length(); j++ ) b = 2*b + arStr1[j] - '0';
		myfile<<(char)b;
	}

	myfile.close();

	ofstream myfile2;
	myfile2.open (s2, ios::binary);
	myfile2 << head11;
	myfile2 <<nl;
	myfile2 << head22new; 
	arStr1="";
	for(i=0;i<share22.length();i+=8)
	{
		arStr1=share22.substr(i,8);
		int b=0;
		for( j=0; j<arStr1.length(); j++ ) b = 2*b + arStr1[j] - '0';
		myfile2<<(char)b;
	}
	
	getchar();
    return ;
	
}
