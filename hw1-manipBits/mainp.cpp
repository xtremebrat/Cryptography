# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;
extern void enc64 ( char file_in_name[] );
extern void dec64 ( char file_in_name[] );
extern void hdump ( char file_in_name[] );

int main ( int argc, char *argv[] )
{
  char tFileName[]="tempp.txt";
  string ch1="hexdump",ch2="enc-base64",ch3="dec-base64",choice="";
  string contents;
  ofstream tempFile;
  int i;
//
//  If the input file was not specified, get it now from stdin
//
  if(argc <= 1)
  {
	  fputs("Provide Arguments ( hexdump / enc-base64 / dec-base64 )", stderr); cout<<endl;
	  return 0;
  }
  
  else if ( argc ==2 ) //call Appropriate function with std input
  {
	  choice=argv[1];
	  if(choice==ch1) {cin>>contents;
	  tempFile.open (tFileName);
	  tempFile << contents;
	  tempFile.close(); hdump(tFileName);getchar(); remove(tFileName);return 0; }
	  else if(choice==ch2) {cin>>contents;
	  tempFile.open (tFileName);
	  tempFile << contents;
	  tempFile.close(); enc64(tFileName);getchar();remove(tFileName); return 0; }
	  else if(choice==ch3) {cin>>contents;
	  tempFile.open (tFileName);
	  tempFile << contents;
	  tempFile.close(); dec64(tFileName);getchar(); remove(tFileName);return 0; }
	  else {remove(tFileName); fputs("Invalid Input\n",stderr); return 0; } 
  }
 
//
//  Call the Appropriate Function with file
//
  else 
  {
	choice=argv[1];
    for ( i = 2 ; i < argc ; ++i ) 
    {
		if(choice==ch1) { hdump(argv[i]);getchar(); return 0; }
		else if(choice==ch2) { enc64(argv[i]);getchar(); return 0; }
		else if(choice==ch3) { dec64(argv[i]);getchar(); return 0; }
	  else { fputs("Invalid Input\n",stderr); getchar(); return 0; }
    } 
  return 0;
}
}
