# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;
string b64chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

int toDec(long int n) 
{

    int dec = 0;

    for(int i=0; n > 0; i++) 
	{

        if(n % 10 == 1) 
		{
            dec += (1 << i);
        }
        n /= 10;
    }

    return dec;
}

string toBin(int num)   // Function Definition
{
	string binStr="";
	int i=1;
	long int bin=0;
	int rem;
	
	do
    {
        rem=num%2; if(rem==0) binStr+='0' ; else binStr += '1';
        bin=bin + (i*rem);
        num=num/2;
        i=i*10;
    }while(num>0);

	binStr = string ( binStr.rbegin(), binStr.rend() );
	if(binStr.length() == 7) binStr.insert(0,"0"); else if(binStr.length()==6) binStr.insert(0,"00"); else if(binStr.length()==5) binStr.insert(0,"000"); else if(binStr.length()==4) binStr.insert(0,"0000"); //insert the leading 0s
	//cout<<binStr<<endl; // 8 bit binary 
	return binStr;
}

void enc64 ( char file_in_name[] )
{
  long int addr,cnt=0,d[6],fileLen=0;
  int i=0,j=0,k=0;
  unsigned char eq = '=';
  char bufb[6],strFileBuffer[3];
  string vStr,bStr,arStr[30],tStr,encStr="",encFinal,fileWOnl;
  ifstream file_in;
//
//  Open the file.
//
  file_in.open ( file_in_name,ios::binary );

  if ( !file_in ) 
  {
    fputs("Cannot Open The File\n", stderr);
    return;
  }

   std::ifstream ifs(file_in_name, ios::binary);
   std::string fullFile( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
   fileLen = fullFile.length();

   if(fileLen%3==1) { fullFile += "=="; fileLen += 2; }
   else if(fileLen%3==2) { fullFile += "="; fileLen += 1; }
  
  while ( cnt<fileLen )
  {
    //file_in.read ( ( char * ) buffer, 3 ); //read 64 chars at a time !
	//cnt = file_in.gcount(); //no of chars read from file
	fullFile.copy(strFileBuffer,3,cnt);
	cnt += 3;

	//cout<<strFileBuffer[0]<<strFileBuffer[1]<<strFileBuffer[2];
	//condtions of no of chars read. 1 or 2 will lead to the == or = cases

	if(cnt!=0)
	{

	bStr="";
	for(int i=0;i<3;i++)
	{
		    if(strFileBuffer[i]==eq) { bStr+="00000000"; }
			else
			{
			vStr = toBin(strFileBuffer[i]);
			//cout<<vStr<<endl<<endl;
			bStr += vStr;
			}
	}
	//cout<<endl<<cnt<<" - "<<bStr<<endl<<endl<<bStr.length()<<endl; //Full Binary converted string
	//encStr="";
	tStr="";
	
	//cout<<bStr;
	for(unsigned int pos=0,i=0;pos<bStr.length();pos+=6,i++)
	{
		arStr[i]=bStr.substr(pos,6);
		tStr=arStr[i];
		//cout<<tStr<<"  "; //6 bit binary 

		tStr.copy(bufb,6,0);
		//cout<<bufb[0]<<bufb[1]<<bufb[2]<<bufb[3]<<bufb[4]<<bufb[5]<<endl;
		if(tStr=="000000" && (fileLen-cnt)<=3 ) encStr += "=";
		else
		{
		for(j=0;j<6;j++) d[j] = bufb[j] - '0'; //bin char to int array of 1 n 0
		//cout<<d[0]<<d[1]<<d[2]<<d[3]<<d[4]<<d[5]<<endl;

		addr = 0;
		for(j=5,k=0;j>=0;j--,k++) addr += d[k] * pow((double)10,j); //int array to single integer !

		int tdec=toDec(addr);
		//cout<<tdec<<endl;
		//cout<<d[0]<<d[1]<<d[2]<<d[3]<<d[4]<<d[5]<< " = "<<addr<<" == "<<tdec<<" -> "<<b64chars[tdec]<<endl;
		encStr += b64chars[tdec];
		}
	 }
	
    }
  
   }
  int x = encStr.length();
  for(i=0;i<x;i++)
  {
	  if(i%64==0) cout<<endl; 
	  cout<<encStr[i];
  }

  getchar();
  file_in.close ( );

  return;
}
