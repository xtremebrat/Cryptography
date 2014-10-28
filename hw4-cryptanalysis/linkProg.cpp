# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;

extern int keygen(int period);
extern int invkey(char file_in_name[]);
extern int solve(char ctfile[],int maxlen);
extern int encryptCode(int count, char** argvv);
extern int histo(int tt,int ii, char cfile[]);

int main ( int argc, char *argv[] )
{
	if(argc<=2) // if in sufficient arguments are provided
	{
		fputs("Provide Appropriate Arguments", stderr); cout<<endl;
		return 0;
	}
	
	if(strcmp(argv[0],"hw4")==0)
	{
		if(strcmp(argv[1],"keygen")==0) // keygen option
		{
			int period = 0;
			string ar=argv[2];
			string ab = ar.substr(3,ar.length()); // splitting arguments
			string op = ar.substr(0,3);
			if((op.compare("-t=")) !=0) { fputs("Invalid Keygen Option", stderr); cout<<endl; return 0; }
			if((ab.compare(""))==0) { fputs("Period Not Specified", stderr); cout<<endl; return 0; }
			period=atoi(ab.c_str());
			keygen(period);
			return 1;
		}

		else if(strcmp(argv[1],"invkey")==0) // inverse key option
		{
			if(argc<3) { fputs("No Keyfile Provided\n", stderr); return 0; }
			char *kfile=argv[2];
			invkey(kfile);			
			
		}
		
		else if(strcmp(argv[1],"solve")==0)
		{
			if(argc<4) { fputs("Insufficient Arguments Provided\n", stderr); return 0; }
			int maxl=0;
			char *sfile=argv[3];
			string ar=argv[2];
			string ab = ar.substr(3,ar.length()); // maxlen
			string op = ar.substr(0,3);
			if((ab.compare(""))==0) { fputs("L Not Specified", stderr); cout<<endl; return 0; }
			if((op.compare("-l=")) !=0) { fputs("Invalid Solve Option\n", stderr); return 0; }
			maxl=atoi(ab.c_str());
			solve(sfile,maxl);
		}
		
		else if(strcmp(argv[1],"ecrypt")==0)
		{
			if(argc<3) { fputs("Insufficient Arguments Provided\n", stderr); return 0; }
			encryptCode(argc,argv);		// encrypt option
		}
		
		else if(strcmp(argv[1],"histo")==0) // histo option
		{
			if(argc<4) { fputs("Insufficient Arguments Provided\n", stderr); return 0; }
			int tt=0,ii=0;
			string ar=argv[2];
			string ab = ar.substr(3,ar.length());
			string op = ar.substr(0,3);
			tt=atoi(ab.c_str());
			if((ab.compare(""))==0) { fputs("Period Not Specified", stderr); cout<<endl; return 0; }
			if((op.compare("-t=")) !=0) { fputs("Invalid Keygen Option\n", stderr); return 0; }
			
			string aq=argv[3];
			string aw = aq.substr(3,aq.length());
			string oe = aq.substr(0,3);
			if((oe.compare("-i=")) !=0) { fputs("Invalid i Value Option\n", stderr); return 0; }
			if((aw.compare(""))==0) { fputs("i Value Not Specified", stderr); cout<<endl; return 0; }
			ii=atoi(aw.c_str());
			//cout<<ii<<endl;
			if((oe.compare("-i=")) !=0) { fputs("Invalid Keygen Option\n", stderr); return 0; }
		
			if(argc==5) // file provided
			{
				char *cttfile=argv[4];
				//cout<<cttfile<<endl;
				histo(tt,ii,cttfile);
			}
			
			if(argc==4) // file not provided, input from stdin
			{
				char tFileName2[]="tmp2.txt";
				ofstream tempFile2;
				string ipStrFile="";
				std::getline(std::cin,ipStrFile);
				ipStrFile+="\n";
				tempFile2.open (tFileName2);
				tempFile2 << ipStrFile;
				tempFile2.close();
				histo(tt,ii,tFileName2);
				remove(tFileName2);
			}
			
		}
		
		else { fputs("Malformed Command\n", stderr); return 0; }
		
	}
	return 1;
}
