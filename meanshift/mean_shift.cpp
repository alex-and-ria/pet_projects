#include<iostream>
#include<math.h>
#include<string.h>
#include<vector>
#include<fstream>

#define fname "./ppms/shapes1.ppm"
#define Nchs 3//RGB;
#define BSZ 3//should be greater or equal to 3;
#define num_BSZ 8
#define sigma_c 19//2//19
#define sigma_s 16//2//16
#define N_iter 10
#define max_h_size 64

using namespace std;

typedef unsigned short int usi;

class img_point{
	public:
		usi r;
		usi g;
		usi b;
		unsigned int x;
		unsigned int y;
		vector<unsigned int> ids;
		void fnd_nbhd(img_point& img_pnt,vector<img_point>& prev_points,vector<img_point>& nbrs){
			double dist_c=0, dist_s=0;
			for(unsigned int i=0;i<prev_points.size();i++){
				dist_c=sqrt((img_pnt.r-prev_points.at(i).r)*(img_pnt.r-prev_points.at(i).r)+(img_pnt.g-prev_points.at(i).g)*(img_pnt.g-prev_points.at(i).g)+(img_pnt.b-prev_points.at(i).b)*(img_pnt.b-prev_points.at(i).b)+0.0);
				dist_s=sqrt((img_pnt.x-prev_points.at(i).x)*(img_pnt.x-prev_points.at(i).x)+(img_pnt.y-prev_points.at(i).y)*(img_pnt.y-prev_points.at(i).y)+0.0);
				/*cout<<"\ndist_c="<<dist_c<<" dist_s="<<dist_s//<<" 3*sigma_c="<<3*sigma_c<<" 3*sigma_s="<<3*sigma_s
					;
				vector<img_point> tmp_pnt; tmp_pnt.push_back(img_pnt); tmp_pnt.push_back(prev_points.at(i));
				cout<<"\n------i="<<i<<"--------------";
				show(tmp_pnt,2);
				cout<<"\n---------------------";*/
				if((dist_c<=(3*sigma_c))&&(dist_s<=(3*sigma_s))&&(dist_s!=0)){
					nbrs.push_back(prev_points.at(i));
				}
			}
		}
		bool img_pnts_eqlt(img_point img_p1,img_point img_p2){
			if((img_p1.r==img_p2.r)&&(img_p1.g==img_p2.g)&&(img_p1.b==img_p2.b)&&(img_p1.x==img_p2.x)&&(img_p1.y==img_p2.y))
				return 1;
			else return 0;
		
		}
		void conc_dubl(vector<img_point>& img_points){
			for(unsigned int i=0;i<img_points.size();i++){
				for(unsigned int j=i+1;j<img_points.size();j++){
					if(img_pnts_eqlt(img_points.at(i),img_points.at(j))){
						for(unsigned int k=0;k<img_points.at(j).ids.size();k++){
							img_points.at(i).ids.push_back(img_points.at(j).ids.at(k));
						}
						/*//usi usi_tmp;
						cout<<"\nimg_points.at("<<i<<" ).ids=";
						for(usi k=0;k<img_points.at(i).ids.size();k++){
							cout<<img_points.at(i).ids.at(k);
							if(k!=img_points.at(i).ids.size()-1)
								cout<<' ';
						}
						//cin>>usi_tmp;
						*/
						img_points.erase(img_points.begin()+j);
						j--;
					}
				}
			}
		}
		void show(vector<img_point>& img_points,usi n_v){
			for(usi i=0;i<n_v;i++){
				cout<<"\ni="<<i<<": "<<img_points.at(i).r<<' '<<img_points.at(i).g<<' '<<img_points.at(i).b<<' '<<img_points.at(i).x<<' '<<img_points.at(i).y<<";\n\tids: ";
				for(unsigned int j=0;j<ids.size()&&j<n_v;j++){
					cout<<img_points.at(i).ids.at(j);
					if(j!=ids.size()-1) cout<<' ';
				}
			}
		}
};

bool is_delim(unsigned char ch,unsigned char* delims,usi d_sz){
	for(usi i=0;i<d_sz;i++){
		if(ch==delims[i])
			return 1;
	}
	return 0;
}

unsigned int ch_int(unsigned char* num_buf, usi sz){
	unsigned int res_val=0;
	for(usi i=0;i<sz;i++){
		res_val+=(num_buf[i]-'0')*pow(10,(sz-i-1));
	}
	//cout<<"\nres_val="<<res_val;
	return res_val;
}

void data_ftch(ifstream& data_img,vector<img_point>& img_points,unsigned int width,unsigned int height){
	unsigned char rbuf[Nchs];
	for(unsigned int i=0;i<(width*height);i++){
		data_img.read((char*)rbuf,BSZ);
		img_points.at(i).r=rbuf[0];
		img_points.at(i).g=rbuf[1];
		img_points.at(i).b=rbuf[2];
		img_points.at(i).x=i%height;
		img_points.at(i).y=i/width;
		img_points.at(i).ids.push_back(i);
	}
	//img_points.at(0).show(img_points,10);
}

bool P6_255_img_read(const char* file_name,vector<img_point>& org_img_points,unsigned char* h_buf,unsigned int& h_sz,unsigned int& width,unsigned int& height){
	ifstream data_img(file_name,ios::binary);
	if(data_img.is_open()){
		char rbuf[Nchs];
		unsigned char delims[]={0x0a,0x20,0x0d,0x09}, num_buf[8];//NL, space, CR, TAB;
		cout<<"\nsizeof(delims)="<<sizeof(delims);
		unsigned char uch_byte=0;
		data_img.read(rbuf,BSZ); strncpy((char*)h_buf,(const char*)rbuf,BSZ); h_sz+=BSZ;
		if(rbuf[0]!='P'||rbuf[1]!='6'||!is_delim((unsigned char)rbuf[2],delims,BSZ)){
			cout<<"\ninput file should be of .ppm format with pix_max_val equal to 255";
			data_img.close();
			return 0;
		}
		else{
			cout<<"\nrbuf="<<hex<<rbuf<<dec; unsigned int pix_max_val; usi fl=0;
			for(usi j=0;j<3;j++){
				for(usi i=0;i<num_BSZ;i++) num_buf[i]=0;
				for(usi i=0;i<num_BSZ;i++){
					//data_img>>uch_byte; 
					data_img.read((char*)&uch_byte,1); h_buf[h_sz]=uch_byte; h_sz++;
					//cout<<"\ni="<<i<<"; uch_byte="<<(unsigned int)uch_byte<<" (hex): "<<hex<<(unsigned int)uch_byte<<dec;
					if(!is_delim(uch_byte,delims,sizeof(delims)/sizeof(delims[0]))){
						num_buf[i]=uch_byte;
					}
					else{
						if(fl==0){
							//cout<<"\nnum_buf="<<hex<<num_buf<<dec;
							width=ch_int(num_buf,i);
							fl=1;
						}
						else if(fl==1){
							//cout<<"\nnum_buf="<<hex<<num_buf<<dec;	
							height=ch_int(num_buf,i);
							fl=2;
						}
						else{
							//cout<<"\nnum_buf="<<hex<<num_buf<<dec;
							pix_max_val=ch_int(num_buf,i);
							
							if(pix_max_val!=255){
								cout<<"\ninput file should be of .ppm format with pix_max_val equal to 255";
								data_img.close();
								return 0;
							}
						}
						break;
					}
				}
			}
			cout<<dec<<"\nwidth="<<width<<" height="<<height<<" pix_max_val="<<pix_max_val;
			//fetch the data;
			vector<img_point> img_points(width*height);
			data_ftch(data_img,img_points,width,height);
			org_img_points=img_points;
			data_img.close();
		}
	}
	return 1;
}

bool P6_255_img_write(const char* inpt_file_name,vector<img_point>& img_points,unsigned char* h_buf,unsigned int& h_sz,unsigned int& width,unsigned int& height){
	char oupt_file_name[strlen("oupt_")+strlen(inpt_file_name)+1]; strncpy(oupt_file_name,inpt_file_name,strlen(inpt_file_name)-4); strcat(oupt_file_name,"_oupt"); strcat(oupt_file_name,inpt_file_name+strlen(inpt_file_name)-4);
	cout<<"\noupt_file_name="<<oupt_file_name;
	ofstream outp_img(oupt_file_name,ios::binary|ios::trunc);
	if(outp_img.is_open()){
		outp_img.write((char*)h_buf,h_sz); unsigned char wbuf[Nchs]; bool pix_fnd_fl=0;
		for(unsigned int i=0;i<width*height;i++){
			pix_fnd_fl=0;
			for(unsigned int j=0;j<img_points.size();j++){
				for(unsigned int k=0;k<img_points.at(j).ids.size();k++){
					if(img_points.at(j).ids.at(k)==i){
						wbuf[0]=img_points.at(j).r; wbuf[1]=img_points.at(j).g; wbuf[2]=img_points.at(j).b;
						outp_img.write((char*)wbuf,Nchs);
						pix_fnd_fl=1;
						break;
					}
				}
				if(pix_fnd_fl==1)
					break;
			}
		}
	}
	else{
		cout<<"\n!data_img.is_open()";
		outp_img.close();
		return 0;
	}
	outp_img.close();
	return 1;
}

double G_kernel_k(img_point img_p1,img_point img_p2){
	return exp(-0.5*((((img_p1.r-img_p2.r)*(img_p1.r-img_p2.r)+(img_p1.g-img_p2.g)*(img_p1.g-img_p2.g)+(img_p1.b-img_p2.b)*(img_p1.b-img_p2.b)+0.)/((sigma_c)*(sigma_c+0.)))+(((img_p1.x-img_p2.x)*(img_p1.x-img_p2.x)+(img_p1.y-img_p2.y)*(img_p1.y-img_p2.y+0.))/((sigma_s)*(sigma_s+0.)))));
}

void mean_shift(vector<img_point>& org_img_points,vector<img_point>& curr_points){
	vector<img_point> prev_points=org_img_points;
	vector<img_point> nbrs; img_point tmp_img_pnt;
	for(usi j=0;j<N_iter;j++){
		//cout<<"\nb_prev_points.size()="<<prev_points.size()<<" curr_points.size()="<<curr_points.size();
		for(unsigned int i=0;i<prev_points.size();i++){
			nbrs.clear();
			prev_points.at(0).fnd_nbhd(prev_points.at(i),prev_points,nbrs);
			//cout<<"\n!i="<<i<<" nbrs.size()="<<nbrs.size();
			tmp_img_pnt.r=0; tmp_img_pnt.g=0; tmp_img_pnt.b=0; tmp_img_pnt.x=0; tmp_img_pnt.y=0;
			double G_koef=0., k_sum=0.;/////////
			for(unsigned int k=0;k<nbrs.size();k++){
				G_koef=G_kernel_k(nbrs.at(k),prev_points.at(i));//usi usi_tmp; cout<<"\nG_koef="<<G_koef; cin>>usi_tmp;
				tmp_img_pnt.r+=prev_points.at(i).r*G_koef; tmp_img_pnt.g+=prev_points.at(i).g*G_koef; tmp_img_pnt.b+=prev_points.at(i).b*G_koef;
				tmp_img_pnt.x+=prev_points.at(i).x*G_koef; tmp_img_pnt.y+=prev_points.at(i).y*G_koef;
				k_sum+=G_koef;
			}
			tmp_img_pnt.r=(tmp_img_pnt.r+0.)/k_sum; tmp_img_pnt.g=(tmp_img_pnt.g+0.)/k_sum; tmp_img_pnt.b=(tmp_img_pnt.b+0.)/k_sum;
			tmp_img_pnt.x=(tmp_img_pnt.x+0.)/k_sum; tmp_img_pnt.y=(tmp_img_pnt.y+0.)/k_sum;
			tmp_img_pnt.ids=prev_points.at(i).ids;
			curr_points.push_back(tmp_img_pnt);
		}
		//cout<<"\nm_prev_points.size()="<<prev_points.size()<<" curr_points.size()="<<curr_points.size();
		if(curr_points.size()!=0){
			curr_points.at(0).conc_dubl(curr_points);
		}
		cout<<"\na_prev_points.size()="<<prev_points.size()<<" curr_points.size()="<<curr_points.size();
		prev_points=curr_points; curr_points.clear();
	}
	curr_points=prev_points;
}

int main(){
	vector<img_point> org_img_points,oup_img_points;
	unsigned char h_buf[max_h_size]; unsigned int h_sz=0, width, height;
	if(P6_255_img_read(fname,org_img_points,h_buf,h_sz,width,height)==0){
		return 1;
	}
	mean_shift(org_img_points,oup_img_points);
	//oup_img_points=org_img_points;
	cout<<"\noup_img_points.size()="<<oup_img_points.size();
	if(P6_255_img_write(fname,oup_img_points,h_buf,h_sz,width,height)==0)
		return 1;
	
	
	return 0;
}
