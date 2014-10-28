# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;

extern int tabChk(char tFile[]);
extern string modprod(string poly1, string poly2, int status);
extern string* keyexp(string key, char tfile[], int status);
extern int encrypt(string key, char tFile[], char iFile[]);
extern int decrypt(string key, char tFile[], char iFile[]);
extern int inverse(string poly);

int main ( int argc, char *argv[] )
{
	if(argc<=2) // if insufficient arguments are provided
	{
		fputs("Provide Appropriate Arguments", stderr); cout<<endl;
		return 0;
	}
	
	if(strcmp(argv[0],"./hw6")==0)
	{
		if(strcmp(argv[1],"tablecheck")==0) // tablecheck option
		{
			string ar=argv[2];
			string tabFile = ar.substr(3,ar.length()); // splitting arguments
			string opt = ar.substr(0,3);
			if((opt.compare("-t=")) !=0) { fputs("Invalid Tablecheck Option", stderr); cout<<endl; return 0; }
			if((tabFile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tabFile.c_str());
			tabChk(tFile);
			//cout<<"Table File Is :"<<tFile<<endl;
			return 1;
		}
		
		// hw6 modprod -p1=poly1 -p2=poly2
		else if(strcmp(argv[1],"modprod")==0) // modprod option
		{
			if(argc<4) { fputs("Insufficient Arguments\n", stderr); return 0; }
			
			string kr=argv[2];
			string poly1 = kr.substr(4,kr.length());
			string opt1 = kr.substr(0,4);
			if((opt1.compare("-p1=")) !=0) { fputs("Invalid Polynomial Option1", stderr); cout<<endl; return 0; }
			if((poly1.compare(""))==0) { fputs("Polynomial Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Poly1 : "<<poly1<<endl;
			
			string tr=argv[3];
			string poly2 = tr.substr(4,tr.length());
			string opt2 = tr.substr(0,4);
			if((opt2.compare("-p2=")) !=0) { fputs("Invalid Polynomial Option2", stderr); cout<<endl; return 0; }
			if((poly2.compare(""))==0) { fputs("Polynomial Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Poly2 : "<<poly2<<endl;
			string mpRes="";
			mpRes=modprod(poly1,poly2,1);
			
			return 1;
			
		}
		
		// hw6 keyexpand -k=key -t=tablefile
		else if(strcmp(argv[1],"keyexpand")==0) // keyexpand option
		{
			if(argc<4) { fputs("Insufficient Arguments\n", stderr); return 0; }
			
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			if((int)key.length()!=32) { cerr<<"Invalid Number Of Key Characters"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Key Is : "<<key<<endl;
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
			tabChk(tFile);
			string *keysptr = new string[44];
			//cout<<"Table File Is : "<<tFile<<endl;
			
			keysptr = keyexp(key,tFile,1);
			
			return 1;
			
		}
		// hw6 inverse -p=poly
		else if(strcmp(argv[1],"inverse")==0)
		{
			if(argc<3) { fputs("Insufficient Arguments\n", stderr); return 0; }
			string kr=argv[2];
			string poly = kr.substr(3,kr.length());
			if(poly.find_first_not_of("abcdef1234567890") != std::string::npos) { cerr<<"Invalid Polynomial"<<endl; return 0; }
			if((int)poly.length()!=8) { cerr<<"Invalid Polynomial Length"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-p=")) !=0) { fputs("Invalid Polynomial Option", stderr); cout<<endl; return 0; }
			if((poly.compare(""))==0) { fputs("Polynomial Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Polynomial Is : "<<poly<<endl;
			inverse(poly);
			
			return 1;
		}
		
		
		else if(strcmp(argv[1],"encrypt")==0) // encrypt option
		{
			if(argc<4) { fputs("Insufficient Arguments\n", stderr); return 0; }
			
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			if((int)key.length()!=32) { cerr<<"Invalid Number Of Key Characters"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Key Is : "<<key<<endl;
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
			ifstream file_in;
			file_in.open ( tFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			tabChk(tFile);
			//cout<<"TableFile Is : "<<tFile<<endl;
			
			if(argc==5)
			{	
				string ifl=argv[4];
				char *iFile = const_cast<char*>(ifl.c_str());
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				// call encrypt
				encrypt(key, tFile, iFile);
			}
			else if(argc==4)
			{
				char iFile[]="aesInp.in";
				ofstream tempFile2;
				string ipStrFile="";
				getline( cin, ipStrFile, '\0' );
				//cout<<"IP : "<<ipStrFile<<endl;
				tempFile2.open(iFile);
				tempFile2 << ipStrFile;
				tempFile2.close();
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				encrypt(key, tFile, iFile);
				remove(iFile);
				// call encrypt
			}
			
			return 1;
			
		}
		
		else if(strcmp(argv[1],"decrypt")==0) // decrypt option
		{
			if(argc<4) { fputs("Insufficient Arguments\n", stderr); return 0; }
			
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			if((int)key.length()!=32) { cerr<<"Invalid Number Of Key Characters"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			//cout<<"Key Is : "<<key<<endl;
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
			ifstream file_in;
			file_in.open ( tFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			//cout<<"TableFile Is : "<<tFile<<endl;
			
			tabChk(tFile);
			if(argc==5)
			{	
				string ifl=argv[4];
				char *iFile = const_cast<char*>(ifl.c_str());
				decrypt(key, tFile, iFile);
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
			}
			else if(argc==4)
			{
				char iFile[]="desInp.in";
				ofstream tempFile2;
				string ipStrFile="";
				getline( cin, ipStrFile, '\0' );
				tempFile2.open(iFile);
				tempFile2 << ipStrFile;
				tempFile2.close();
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				decrypt(key, tFile, iFile);
				remove(iFile);
			}
			
			return 1;
			
		}
		
		else { fputs("Malformed Command\n", stderr); return 0; }
		
	}
	return 1;
}
