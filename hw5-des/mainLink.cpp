# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;

extern int tabChk(char tFile[]);
extern int DESencrypt(string k,char tabFile[],char inpFile[]);
extern int DESdecrypt(string k,char tabFile[],char inpFile[]);

int main ( int argc, char *argv[] )
{
	if(argc<=2) // if in sufficient arguments are provided
	{
		fputs("Provide Appropriate Arguments", stderr); cout<<endl;
		return 0;
	}
	
	if(strcmp(argv[0],"./hw5")==0)
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
			//cout<<tFile<<endl;
			return 1;
		}

		else if(strcmp(argv[1],"encrypt")==0) // encrypt option
		{
			//cout<<argc<<endl;
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
			
			if(argc==5)
			{	
				string ifl=argv[4];
				char *iFile = const_cast<char*>(ifl.c_str());
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				DESencrypt(key,tFile,iFile);
				
				// call encrypt
			}
			else if(argc==4)
			{
				char iFile[]="desInp.in";
				ofstream tempFile2;
				string ipStrFile="";
				std::getline(std::cin,ipStrFile);
				tempFile2.open(iFile);
				tempFile2 << ipStrFile;
				tempFile2.close();
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				DESencrypt(key,tFile,iFile);
				remove(iFile);
				// call enrypt
			}
			
			return 1;
			
		}
		
		else if(strcmp(argv[1],"decrypt")==0) // decrypt option
		{
			//cout<<argc<<endl;
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
			
			if(argc==5)
			{	
				string ifl=argv[4];
				char *iFile = const_cast<char*>(ifl.c_str());
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				DESdecrypt(key,tFile,iFile);
				
				// call encrypt
			}
			else if(argc==4)
			{
				char iFile[]="desInp.in";
				ofstream tempFile2;
				string ipStrFile="";
				std::getline(std::cin,ipStrFile);
				tempFile2.open(iFile);
				tempFile2 << ipStrFile;
				tempFile2.close();
				//cout<<"Key : "<<key<<endl<<"TableFile : "<<tFile<<endl<<"Input File : "<<iFile<<endl;
				DESdecrypt(key,tFile,iFile);
				remove(iFile);
				// call enrypt
			}
			
			return 1;
			
		}
		
		else if(strcmp(argv[1],"decrypt3")==0 || strcmp(argv[1],"encrypt3")==0)
		{
			string kr=argv[2];
			string key = kr.substr(3,kr.length());
			if (key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) { cerr<<"Invalid Key"<<endl; return 0; }
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Key Option", stderr); cout<<endl; return 0; }
			if(key.length()<48) { fputs("Key Too Short", stderr); cout<<endl; return 0; }
			if((key.compare(""))==0) { fputs("Key Not Specified", stderr); cout<<endl; return 0; }
			
			string tr=argv[3];
			string tfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Table Option", stderr); cout<<endl; return 0; }
			if((tfile.compare(""))==0) { fputs("Table File Not Specified", stderr); cout<<endl; return 0; }
			char *tFile = const_cast<char*>(tfile.c_str());
		
			ifstream tabFile;
			tabFile.open(tFile,ios::binary);
			if ( !tabFile ) // open the table file
			{
			fputs("Cannot Open Table File\n", stderr); 
			return 0; 
			}
		
		
		}
		
		else { fputs("Malformed Command\n", stderr); return 0; }
		
	}
	return 1;
}
