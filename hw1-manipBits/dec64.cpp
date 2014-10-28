# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;
string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

int getDec(long int n) 
{
	int dec = 0;
	for(int i=0; n > 0; i++) 
	{
		if(n % 10 == 1) dec += (1 << i);
        n /= 10;
    }
	//cout<<dec<<" ";
	return dec;
}

string getBin(int num)   // Function Definition
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
	if(binStr.length() == 5) binStr.insert(0,"0"); else if(binStr.length() == 4) binStr.insert(0,"00"); else if(binStr.length() == 3) binStr.insert(0,"000"); else if(binStr.length() == 2) binStr.insert(0,"0000"); else if(binStr.length() == 1) binStr.insert(0,"00000"); //insert the leading 0s
	//cout<<binStr<<endl; // 6 bit binary 
	return binStr;
}

void dec64 ( char file_in_name[] )
{
  long int addr,cnt=0,d[8],rema=0;
  int i=0,j=0,k=0,b64No,fileLen=0,fileCharCount=0,WOnlLen=0,z=0,y=0;
  unsigned char eq = '=';
  bool badInput=false;
  char bufb[8],strFileBuffer[4];
  string vStr,bStr,arStr[100],decStr,encFinal,fileWOnl;
  ifstream file_in;
  ifstream binFile;
//
//  Open the file.
//
  //binFile.open(file_in_name,ios::binary);
  file_in.open ( file_in_name, ios::binary );

  if ( !file_in ) 
  {
    fputs("Cannot Open The File\n", stderr);
    return;
  }

  std::ifstream ifs(file_in_name, ios::binary);
   std::string fullFile( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

   fileLen = fullFile.length();

   for(fileCharCount=0;fileCharCount<fileLen;fileCharCount++)
   {
	   if((int)fullFile[fileCharCount]==10 || (int)fullFile[fileCharCount]==13 ) fileWOnl += "";
	   else { fileWOnl += fullFile[fileCharCount]; }

   }
   WOnlLen = fileWOnl.length();

   for(y=0;y<WOnlLen;y++)
   {
	   for(z=0;z<=42;z++)  { if((int)fileWOnl[y]==z) badInput=true; }
	   for(z=44;z<=46;z++) { if((int)fileWOnl[y]==z) badInput=true; }
	   for(z=58;z<=64;z++) { if((int)fileWOnl[y]==z) badInput=true; }
	   for(z=91;z<=96;z++) { if((int)fileWOnl[y]==z) badInput=true; }
	   for(z=123;z<=127;z++) { if((int)fileWOnl[y]==z) badInput=true; }

   }

   if(WOnlLen %4 !=0) { fputs("Invalid Input", stderr); cout<<endl;  return; }
   else if(badInput) {  fputs("Bad Input", stderr); cout<<endl;  return; }
   else
   {
     
  cnt=0;
  while ( cnt<WOnlLen )
  {
    fileWOnl.copy(strFileBuffer,4,cnt); //4 chars at a time
	cnt += 4; 
	rema=WOnlLen-cnt;
	// 4 chars at a time
	//cout<<strFileBuffer[0]<<strFileBuffer[1]<<strFileBuffer[2]<<strFileBuffer[3]<<endl;
	bStr="";
	if(cnt!=0)
	{
	for(i=0;i<4;i++) //group of 4 base 64 index nos
		{
			if(strFileBuffer[i]==eq && rema==0) { bStr += "000000";} //cout<<"equals = here "<<endl;
			else 
			{
				for(j=0;j<64;j++)
				{
					if(strFileBuffer[i]==base64_chars[j]) b64No=j;
				}
				vStr="";
				vStr = getBin(b64No); //bin no of base 64 index value
				//cout<<vStr<<" "; //6 bit binary 
				bStr += vStr;
			}
			  
		}
	//cout<<endl<<bStr<<endl<<endl; //Full Binary converted string
	
	//decStr="";
	string tStr="";
	for(unsigned int pos=0;pos<bStr.length();pos+=8,i++)
	{
		arStr[i]=bStr.substr(pos,8);
		//cout<<arStr[i]<<endl; //8 bit binary string array
		tStr=arStr[i];
		//cout<<tStr<<endl; //8 bit binary string 

		tStr.copy(bufb,8,0);
		//cout<<bufb[0]<<bufb[1]<<bufb[2]<<bufb[3]<<bufb[4]<<bufb[5]<<bufb[6]<<bufb[7]<<endl; //8 bt binary char array
		if(tStr=="00000000" && rema==0) decStr+="";
		else
		{
		for(j=0;j<8;j++) d[j] = bufb[j] - '0'; //bin char to int array of 1 n 0
		//cout<<d[0]<<d[1]<<d[2]<<d[3]<<d[4]<<d[5]<<d[6]<<d[7]<<endl; //8 bit binary int array , 8 bit 0s not considered

		addr = 0;
		for(j=7,k=0;j>=0;j--,k++) addr += d[k] * pow((double)10,j); 
		//cout<<"Int No : "<<addr<<endl; //int array to single integer !

		int tdec=getDec(addr);
		cout<<(char)tdec;
		//decStr+=(char)tdec;
		
		}		
	}
		  
  }

  }

	//cout<<"Decoded Data : "<<endl;
	//cout<<decStr;

  file_in.close ( );

  return;
}
}
