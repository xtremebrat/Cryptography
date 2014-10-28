# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <math.h>

using namespace std;

extern int primes(int n);
extern int trialdiv(int n, char pfile[], int status);
extern int mrabin(unsigned long long int n,int t, char pfile[], int status);
extern int rndsrc(int k, int t, char pfile[], char rfile[]);

#define maxNval 16777216

int main ( int argc, char *argv[] )
{
	if(argc<=2) // if insufficient arguments are provided
	{
		fputs("Provide Appropriate Arguments", stderr); cout<<endl;
		return 0;
	}
	
	if(strcmp(argv[0],"./hw7")==0)
	{
		if(strcmp(argv[1],"primes")==0) // primes option
		{
			//hw7 primes -n=maxval
			string ar=argv[2];
			if((int)ar.length()<4) { fputs("Invalid N argument", stderr); cout<<endl; return 0; } 
			string nval = ar.substr(3,ar.length()); // splitting arguments
			string opt = ar.substr(0,3);
			if((opt.compare("-n=")) !=0) { fputs("Invalid Primes Option", stderr); cout<<endl; return 0; }
			if((nval.compare(""))==0) { fputs("N Value Not Specified", stderr); cout<<endl; return 0; }
			int n=atoi(nval.c_str()); // integer n 
			if(n==0) { fputs("Invalid N", stderr); cout<<endl; return 0; }
			if(n>maxNval) { fputs("N too large", stderr); cout<<endl; return 0; }
			//cout<<"N Is :"<<n<<endl;
			primes(n);
			
			return 1;
		}
		
		else if(strcmp(argv[1],"trialdiv")==0) // trialdiv option
		{
			if(argc<4) { fputs("Insufficient Arguments\n", stderr); return 0; }
			//hw7 trialdiv -n=number -p=primesfile
			string kr=argv[2];
			string nval = kr.substr(3,kr.length());
			//cout<<"NVAL : "<<nval<<endl;
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-n=")) !=0) { fputs("Invalid Option", stderr); cout<<endl; return 0; }
			if((nval.compare(""))==0) { fputs("N Value Specified", stderr); cout<<endl; return 0; }
			int n=atoi(nval.c_str()); // integer n
			if(n==0) { fputs("Invalid N", stderr); cout<<endl; return 0; }
			
			//cout<<"N Is :"<<n<<endl;
			
			string tr=argv[3];
			string pfile = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-p=")) !=0) { fputs("Invalid Primesfile Option", stderr); cout<<endl; return 0; }
			if((pfile.compare(""))==0) { fputs("Primesfile Not Specified", stderr); cout<<endl; return 0; }
			char *pFile = const_cast<char*>(pfile.c_str());
			//cout<<"Primesfile : "<<pFile<<endl;
			ifstream file_in;
			file_in.open ( pFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}

			trialdiv(n,pFile,0);
			
			return 1;
			
		}
		
		else if(strcmp(argv[1],"millerrabin")==0) // millerrabin option
		{
			if(argc<5) { fputs("Insufficient Arguments\n", stderr); return 0; }
			//hw7 millerrabin -n=number -t=maxitr -p=primesfile
			ifstream file_in;
			string kr=argv[2];
			string nval = kr.substr(3,kr.length());
			//cout<<"NVAL : "<<nval<<endl;
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-n=")) !=0) { fputs("Invalid Option", stderr); cout<<endl; return 0; }
			if((nval.compare(""))==0) { fputs("N Not Specified", stderr); cout<<endl; return 0; }
			string n1="",n2=""; n1=nval.substr(0,nval.length()/2); n2=nval.substr(nval.length()/2,nval.length()); 
			unsigned long long int n=atoi(nval.c_str()); // integer n
			if(n==0) { fputs("Invalid N", stderr); cout<<endl; return 0; }
			//cout<<"N Is : "<<n<<endl;
			
			string tr=argv[3];
			string titr = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Maxitr Option", stderr); cout<<endl; return 0; }
			if((titr.compare(""))==0) { fputs("Maxitr Not Specified", stderr); cout<<endl; return 0; }
			int t=atoi(titr.c_str()); // integer t
			if(t==0) { fputs("Invalid MaxITr", stderr); cout<<endl; return 0; }
			//cout<<"Maxitr Is : "<<t<<endl;
			
			string pr=argv[4];
			string pfile = pr.substr(3,pr.length());
			string opt3 = pr.substr(0,3);
			if((opt3.compare("-p=")) !=0) { fputs("Invalid Primesfile Option", stderr); cout<<endl; return 0; }
			if((pfile.compare(""))==0) { fputs("Primesfile Not Specified", stderr); cout<<endl; return 0; }
			char *pFile = const_cast<char*>(pfile.c_str());
			//cout<<"Primesfile : "<<pFile<<endl;
			
			file_in.open ( pFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			
			mrabin(n,t,pFile,0);
			
			return 1;
			
		}
	
		else if(strcmp(argv[1],"rndsearch")==0) // rndsearch option
		{
			if(argc<6) { fputs("Insufficient Arguments\n", stderr); return 0; }
			//hw7 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile
			ifstream file_in;
			string kr=argv[2];
			string kval = kr.substr(3,kr.length());
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Option", stderr); cout<<endl; return 0; }
			if((kval.compare(""))==0) { fputs("K Not Specified", stderr); cout<<endl; return 0; }
			int k=atoi(kval.c_str()); // integer k
			//cout<<"K Is : "<<k<<endl;
			
			string tr=argv[3];
			string titr = tr.substr(3,tr.length());
			string opt2 = tr.substr(0,3);
			if((opt2.compare("-t=")) !=0) { fputs("Invalid Maxitr Option", stderr); cout<<endl; return 0; }
			if((titr.compare(""))==0) { fputs("Maxitr Not Specified", stderr); cout<<endl; return 0; }
			int t=atoi(titr.c_str()); // integer n
			//cout<<"Maxitr Is : "<<t<<endl;
			
			string pr=argv[4];
			string pfile = pr.substr(3,pr.length());
			string opt3 = pr.substr(0,3);
			if((opt3.compare("-p=")) !=0) { fputs("Invalid Primesfile Option", stderr); cout<<endl; return 0; }
			if((pfile.compare(""))==0) { fputs("Primesfile Not Specified", stderr); cout<<endl; return 0; }
			char *pFile = const_cast<char*>(pfile.c_str());
			//cout<<"Primesfile : "<<pFile<<endl;
			file_in.open ( pFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			file_in.close();
			
			string zr=argv[5];
			string rfile = zr.substr(3,zr.length());
			string opt4 = zr.substr(0,3);
			if((opt4.compare("-r=")) !=0) { fputs("Invalid Rndfile Option", stderr); cout<<endl; return 0; }
			if((rfile.compare(""))==0) { fputs("Rndfile Not Specified", stderr); cout<<endl; return 0; }
			char *rFile = const_cast<char*>(rfile.c_str());
			//cout<<"Rndfile : "<<rFile<<endl;
			file_in.open ( rFile,ios::binary );

			if ( !file_in ) 
			{
				fputs("Cannot Open Rnd File\n", stderr);
				exit(EXIT_FAILURE);
			}
			file_in.close();
			
			rndsrc(k,t,pFile,rFile);
			
			return 1;
		}
		
		
		else if(strcmp(argv[1],"maurer")==0) // maurer option
		{
			if(argc<5) { fputs("Insufficient Arguments\n", stderr); return 0; }
			//hw7 maurer -k=numbits -p=primesfile -r=rndfile
			ifstream file_in;
			string kr=argv[2];
			string kval = kr.substr(3,kr.length());
			string opt1 = kr.substr(0,3);
			if((opt1.compare("-k=")) !=0) { fputs("Invalid Option", stderr); cout<<endl; return 0; }
			if((kval.compare(""))==0) { fputs("K Not Specified", stderr); cout<<endl; return 0; }
			//int k=atoi(kval.c_str()); // integer n
			//cout<<"K Is : "<<k<<endl;
			
			string pr=argv[3];
			string pfile = pr.substr(3,pr.length());
			string opt2 = pr.substr(0,3);
			if((opt2.compare("-p=")) !=0) { fputs("Invalid Primesfile Option", stderr); cout<<endl; return 0; }
			if((pfile.compare(""))==0) { fputs("Primesfile Not Specified", stderr); cout<<endl; return 0; }
			char *pFile = const_cast<char*>(pfile.c_str());
			//cout<<"Primesfile : "<<pFile<<endl;
			file_in.open ( pFile,ios::binary );
			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			
			string zr=argv[4];
			string rfile = zr.substr(3,zr.length());
			string opt3 = zr.substr(0,3);
			if((opt3.compare("-r=")) !=0) { fputs("Invalid Rndfile Option", stderr); cout<<endl; return 0; }
			if((rfile.compare(""))==0) { fputs("Rndfile Not Specified", stderr); cout<<endl; return 0; }
			char *rFile = const_cast<char*>(rfile.c_str());
			//cout<<"Rndfile : "<<rFile<<endl;	

			file_in.open ( rFile,ios::binary );
			if ( !file_in ) 
			{
				fputs("Cannot Open Table File\n", stderr);
				exit(EXIT_FAILURE);
			}
			
			return 1;
			
		}
		
		else { fputs("Malformed Commandline\n", stderr); return 0; }
		
	}
	return 1;
}
