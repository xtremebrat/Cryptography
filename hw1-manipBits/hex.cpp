# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;

string getHex(long int num)   // Function Definition
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
          //cout<<"a";
		  str+="a";
          break;
      case 11:
          //cout<<"b";
		  str+="b";
          break;
      case 12:
          //cout<<"c";
		  str+="c";
          break;
      case 13:
          //cout<<"d";
		  str+="d";
          break;
      case 14:
          //cout<<"e";
		  str+="e";
          break;
      case 15:
          //cout<<"f";
		  str+="f"; 
          break;
      default :
		 qw[0] = rem[i] + '0';
		 str+=qw[0];
    }
  }
	return str;
}

void hdump ( char file_in_name[] )
{
  long int addr;
  string fname=file_in_name,ext;
  unsigned char buffer[20];
  string hexAddr="",bStr="";
  long int cnt;
  long int cnt2;
  ifstream file_in;
  long n;
//
//  Open the file.
//

  file_in.open ( file_in_name,ios::binary );

  if ( !file_in ) 
  {
    fputs("Cannot Open The File\n", stderr);
    return;
  }
     
//
//  HexDump the file contents.
//
  addr = 0;

  while ( ! file_in.eof ( ) )
  {
    file_in.read ( ( char * ) buffer, 16 );

    cnt = file_in.gcount();

    if ( cnt <= 0 )
    {
      break;
    }
//
//  Print the address in decimal and hexadecimal.
//
	hexAddr = getHex(addr);
    cout << setw(7) << setfill ( '0' )<<hexAddr<< ": ";
	addr = addr + 16;
//
//  Print 16 data items, in pairs, in hexadecimal.
//
    cnt2 = 0;
    for ( n = 0; n < 16; n++ )
    {  
	  if(n==8) cout<<"  "; // 2 spaces at the middle
      cnt2 = cnt2 + 1;
	  bStr="";
      if ( cnt2 <= cnt )
      {
		bStr = getHex((int)buffer[n]);
        cout << setw(2) << setfill ( '0' ) << bStr;
      }
      else
      {
        cout << "--"; // Print double dashes if file ends before line is complete !
      }
      cout << " ";
    }

    cout << setfill ( ' ' );
//
//  Print the printable characters, or a period if unprintable.
//
    cout << " ";
    cnt2 = 0;
    for ( n = 0; n < 16; n++ )
    {
		
      cnt2 = cnt2 + 1;
      if ( cnt2 <= cnt )
      {
        if ( buffer[n] < 32 || buffer[n]==127 )
        {
          cout << '.';
        }
		else if( buffer[n]>=128) 
			cout<<'~';
        else
        {
          cout << buffer[n];
        }
      }
    }
    cout << "\n";
  }

  getchar();
  file_in.close ( );

  return;
}
