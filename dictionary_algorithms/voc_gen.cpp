#include<iostream>
#include<time.h>
#include<string>
#include<fstream>
#define strvoc "strvoc.txt"
#define wordSZ 10
#define transSZ 15
#define alphSZ 26
#define vocSZ 500

using namespace std;
typedef unsigned short int usi;

int main(){
	srand(time(NULL));
	ofstream fpo(strvoc,ios::trunc);
	if(!fpo.is_open()){cout<<"\nerr: ptf no output file;"; system("pause"); return 0;}
	usi wlen,tlen; string ln;
	for(unsigned int i=0; i<vocSZ;i++){
		wlen=rand()%wordSZ+1; tlen=rand()%transSZ+1; ln.clear(); 
		for(usi j=0;j<wlen+transSZ+2;j++){
			if(j==wlen){
				ln+=' ';
			}
			else{
				unsigned char letter=rand()%(alphSZ*2)+'A';
				if(letter>90) letter='a'+(letter-'A'-alphSZ);
				ln+=letter;
			}
		}
		ln+="\n";
		fpo<<ln;
	}
	fpo.close();
	cout<<strvoc;
	return 0;
}
