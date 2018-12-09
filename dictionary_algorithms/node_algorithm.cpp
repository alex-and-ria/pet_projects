#include<iostream>
#include<chrono>
#include<string>
#include<fstream>
#include<map>
#include<unordered_map>
#include<assert.h>
#define alphSZ 26
#define strvoc "strvoc.txt"
#define private public

using namespace std;
typedef unsigned short int usi;
unsigned int mcnt_n=0, mcnt_m=0, mcnt_um=0;

class Ch_node{
	private:
		unsigned char ch;
		bool is_tr;
		string tr;
		Ch_node **nnodes;
	public:
		Ch_node(unsigned char letter): ch(letter), is_tr(0){
			nnodes=new Ch_node *[2*alphSZ];
			for(usi i=0;i<2*alphSZ;i++){
				nnodes[i]=NULL;
			}
		}
		Ch_node(unsigned char letter, string strtr): ch(letter), is_tr(1), tr(strtr){
			nnodes=new Ch_node *[2*alphSZ];
			for(usi i=0;i<2*alphSZ;i++){
				nnodes[i]=NULL;
			}
		}
		friend ostream& operator<<(ostream& out, Ch_node& nd){
			out<<"\nch="<<nd.ch<<" is_tr="<<nd.is_tr<<" tr="<<nd.tr<<' ';
			for(usi i=0;i<alphSZ*2;i++){
				if(nd.nnodes[i]!=NULL) out<<i<<' ';
			}
		}
	~Ch_node(){
		delete[] nnodes;
	}
};

bool bld_ff(ifstream& fpi, Ch_node& rootch, map<string,string>& vmap, unordered_map<string,string>& uvmap){
	if(!fpi.is_open()){cout<<"\nerr: gff no input file"; system("pause"); return 0;}
	else{
		string wrd,tr; Ch_node *curr_node=&rootch; usi pos=0; mcnt_n+=sizeof(rootch);
		while(1){
			fpi>>wrd>>tr;
			if(fpi.eof()) break;
			for(usi i=0;i<wrd.size();i++){
				pos=wrd.at(i)-'A'; 
				if(pos>25) pos=pos-('a'-'A')+alphSZ;// cout<<"\nwrd.at("<<i<<")="<<wrd.at(i)<<" pos="<<pos;
				if(curr_node->nnodes[pos]==NULL){
					curr_node->nnodes[pos]= (i==(wrd.size()-1))?(new Ch_node(wrd.at(i),tr)):(new Ch_node(wrd.at(i)));
				}
				else if(i==(wrd.size()-1)){
					if(!(curr_node->nnodes[pos]->is_tr)){//do not override translation;
						curr_node->nnodes[pos]->tr=tr;
						curr_node->nnodes[pos]->is_tr=1;
					}
				}
				curr_node=curr_node->nnodes[pos]; mcnt_n+=sizeof(*curr_node);
				//cout<<*curr_node;
			}
			curr_node=&rootch;
			vmap.insert(pair<string,string>(wrd,tr)); uvmap.insert(pair<string,string>(wrd,tr));
			mcnt_m+=wrd.size()+tr.size(); mcnt_um+=wrd.size()+tr.size();;
			//cout<<'\n'; system("pause");
		}
		
		
		
		
	}
	return 1;
}

int main(){
	ifstream fpi(strvoc); Ch_node rootch('\0'), *curr_node=&rootch; string wrd,tr; usi pos;
	map<string,string> vmap; unordered_map<string,string> uvmap;
	map<string,string>::iterator vmapit; unordered_map<string,string>::iterator uvmapit;
	mcnt_m=sizeof(vmap); mcnt_um=sizeof(uvmap);
	if(bld_ff(fpi,rootch,vmap,uvmap)){
		auto strt=chrono::high_resolution_clock::now();
		for(usi i=0;i<1000;i++){
			fpi.clear(); fpi.seekg(0,ios::beg);
			while(1){
				fpi>>wrd>>tr;
				if(fpi.eof()) break;
				for(usi i=0;i<wrd.size();i++){
					pos= (wrd.at(i)>'Z')?(wrd.at(i)-'a'+alphSZ):(wrd.at(i)-'A');
					if(curr_node->nnodes[pos]!=NULL) curr_node=curr_node->nnodes[pos];
					else break;
				}
				//vmapit=vmap.find(wrd);
				//uvmapit=uvmap.find(wrd);
				//assert(curr_node->is_tr); assert(curr_node->tr==vmapit->second); assert(curr_node->tr==uvmapit->second);
				curr_node=&rootch;
			}
		}
		auto res=chrono::high_resolution_clock::now();
		chrono::duration<double> diff=res-strt;
		cout<<"\ntn="<<diff.count()<<" mem_n="<<mcnt_n;
		//system("pause");
		
		strt=chrono::high_resolution_clock::now();
		for(usi i=0;i<1000;i++){
			fpi.clear(); fpi.seekg(0,ios::beg);
			while(1){
				fpi>>wrd>>tr;
				if(fpi.eof()) break;
				vmapit=vmap.find(wrd);
			}
		}
		res=chrono::high_resolution_clock::now();
		diff=res-strt;
		cout<<"\ntm="<<diff.count()<<" mem_m="<<mcnt_m;
			
		strt=chrono::high_resolution_clock::now();
		for(usi i=0;i<1000;i++){
			fpi.clear(); fpi.seekg(0,ios::beg);
			while(1){
				fpi>>wrd>>tr;
				if(fpi.eof()) break;
				uvmapit=uvmap.find(wrd);
			}
		}
		res=chrono::high_resolution_clock::now();
		diff=res-strt;
		cout<<"\ntum="<<diff.count()<<" mem_um="<<mcnt_um;
		
		
	}
	
	fpi.close();
	return 0;
}
