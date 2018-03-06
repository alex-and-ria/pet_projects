#include "snfr_d.h"

/*void sps(){
	printf( "\npak...");
	getchar();
}*/
 
int main(int argc, char** argv){
	pid_t process_id = 0; pid_t sid = 0;
	if(argc!=2 || strcmp(argv[1],"strt")){
		process_id = fork(); // Create child process
		if (process_id < 0){ printf( "fork failed!\n"); return 1;}
		if (process_id > 0){// PARENT PROCESS. Need to kill it.
			printf("process_id of child process %d \n", process_id); 
			//printf( "here0.01\n");
			return 0;
		}
	}
	umask(0); //unmask the file mode
	sid = setsid(); //set new session
	if(sid < 0) return 1;
	close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);// Close stdin, stdout and stderr;
	chdir("/"); // Change the current working directory to root.;
	
	
	FILE *logfile,*outlog; bool flread=0; unsigned int itr=0,f_ret=0;
	int saddr_size, data_size, cli_sock, msgsock, rval, sock_raw, fd; int dcnt=flines_max;
    struct sockaddr saddr; struct sockaddr_un server; struct ifreq ifr; struct sockaddr_ll sock_address;
	char cli_comm[kb_sz],cli_snd[kb_sz]; char if_name[10]; char fname[strlen("log")+10+strlen(".txt")];
	memcpy(if_name,"wlan0\0",strlen("wlan0")+1);//let's default interface is wlan0;
	sprintf(fname,"log%s.txt",if_name);
    unsigned char *buffer = (unsigned char *) malloc(buf_sz);
    unsigned int argc_sock; unsigned char argv_sock[2][kb_sz];

	if(f_ret=open_fls(&logfile,&outlog,fname)){
		printf("\nopen_fls err: check %s file", (f_ret==1)?fname:"outlog");
		return 1;
	}
	if(f_ret=sock_conf(&sock_raw,&fd,&cli_sock,&ifr,if_name,&sock_address,&server)) return 1;
    
	listen(cli_sock, 3);
	fcntl(cli_sock, F_SETFL, O_NONBLOCK);//nonblocking socket;
    
    while(1){
    	msgsock = accept(cli_sock, 0, 0);
		fcntl(msgsock, F_SETFL, O_NONBLOCK);
		if(dcnt>=0&&msgsock==-1&&(!flread)){
		    saddr_size = sizeof(saddr);
		    data_size = recvfrom(sock_raw , buffer , buf_sz , 0 , &saddr , (socklen_t*)&saddr_size);//Receive a packet;
		    if(data_size <0 ){
		        printf( "Recvfrom error , failed to get packets\n");
		        return 1;
		    }
		    pprocess(buffer,data_size,ifr,logfile,flread);//Now process the packet;
		    dcnt--;
		}
		else if(msgsock!=-1){
			if ((rval = read(msgsock, cli_comm, kb_sz)) < 0)
                perror("reading stream message");
            else if (rval == 0)
                printf( "Ending connection\n");
            else{
            	//handle request;
            	printf( "\n-->%s\n", cli_comm);
            	prs_cli(cli_comm,rval,&argc_sock,argv_sock);
            	if(argc_sock==1){
            		if(strcmp(argv_sock[0],"start")==0){
		        		fprintf(outlog, "\nstrt fnd"); dcnt=flines_max; flread=0;
		        		fclose(logfile);
		        		logfile=fopen(fname,"wb+");//clear existing file;
		        		if(logfile==NULL){
		        			fprintf(outlog, "Unable to create log[iface].txt file.");
		        			char* tmp_msg="start: Unable to create log[iface].txt file\0";
		        			memcpy(cli_snd,tmp_msg,strlen(tmp_msg)+1);
		        		}
		        		else{
		        			char* tmp_msg="started log\0";
		        			memcpy(cli_snd,tmp_msg,strlen(tmp_msg)+1);
		        		}
		        	}
		        	else if(strcmp(argv_sock[0],"stop")==0){
		        		fprintf(outlog, "\nstop fnd");
		        		fclose(logfile);
		        		logfile=fopen(fname,"rb");//open for reading existing file;
		        		if(logfile==NULL){
		        			fprintf(outlog, "Unable to read log[iface].txt file.");
		        			char* tmp_msg="stop: Unable to read log[iface].txt file\0";
		        			memcpy(cli_snd,tmp_msg,strlen(tmp_msg)+1);
		        		}
		        		else{
		        			flread=1;
		        			char* tmp_msg="stopped log\0";
		        			memcpy(cli_snd,tmp_msg,strlen(tmp_msg)+1);
		        		}
		        	}
		        	else if(strcmp(argv_sock[0],"q")==0){
		        		fprintf(outlog, "\nq");
		        		memcpy(cli_snd,"q\0",2);
		        		break;
		        	}
		        	else{
		        		cli_snd[0]='\0';
		        		fprintf(outlog, "\ndefault");
		        	}
            	}
            	else{
            		if(strcmp(argv_sock[0],"show")==0){
		        		fprintf(outlog, "\nshow %s",argv_sock[1]);
		        		struct sockaddr_in iptf; int fip_res;
		        		if(inet_aton(argv_sock[1],&(iptf.sin_addr))){
		        			if((fip_res=ffindip(iptf,logfile,1))<0){
		        				if(fip_res==-2){
									fprintf(outlog, "\nip_nfnd\n");
									memcpy(cli_snd,"ip not found\0",strlen("ip not found")+1);
								}
								else if(fip_res==-3){
									fprintf(outlog, "\nread_err!\n");
									memcpy(cli_snd,"read_err!\0",strlen("read_err!")+1);
								}
		        			}
		        			else{
		        				printf( "\nfnd_cnt=%d\n",fip_res);
		        				unsigned char str_num_res[12];//enough for 4 byte number;
		        				sprintf(str_num_res,"%d",fip_res);
								memcpy(cli_snd,"fip_res=",strlen("fip_res="));
								memcpy(cli_snd+strlen("fip_res="),str_num_res,strlen(str_num_res)+1);
		        			}
		        		}
		        		else{
	        				perror("\nip_convertion");
	        				memcpy(cli_snd,"check ip\0",strlen("check ip")+1);
	        			}
		        	}
		        	else if(strcmp(argv_sock[0],"select")==0){
		        		printf( "\nselect %s",argv_sock[1]);
		        		int isifname;
		        		if((isifname=checkifnm(argv_sock[1]))<0){//no such interface;
		        			printf( "\niface not found");
		        			memcpy(cli_snd,"iface not found\0",strlen("iface not found")+1);
		        		}
		        		else{
		        			fclose(logfile);//finishing write to previous log file;
		        			memcpy(if_name,argv_sock[1],strlen(argv_sock[1])+1);//new file's name;
							memcpy(fname,"log",strlen("log"));
							memcpy(fname+strlen("log"),if_name,strlen(if_name));
							memcpy(fname+strlen("log")+strlen(if_name),".txt\0",strlen(".txt\0")+1); printf( "%s",fname);
		        			logfile=fopen(fname,"rb+");
							if(logfile==NULL){
								logfile=fopen(fname,"wb+");//if file not exist, create it;
								if(logfile==NULL){
									printf( "Unable to create new log.txt file.");
									memcpy(cli_snd,"file_err\0",strlen("file_err")+1);
								}
							}
							if(logfile!=NULL){
								memcpy(cli_snd,fname,strlen(fname));
								memcpy(cli_snd+strlen(fname)," selected\0",strlen(" selected")+1);
							}
		        		}
		        	}
		        	else if(strcmp(argv_sock[0],"stat")==0){//shoud be rewriten (probably with changes in cli_cnfr.c code);
		        		if(strcmp(argv_sock[1],"all")==0){
		        			printf( "\nstat: full");
		        			showstall(cli_snd,msgsock);
		        		}
		        		else{
		        			printf( "\nstat %s",argv_sock[1]);
		        			int chck_stat,flns=0; unsigned char tpm_msg[kb_sz/2];
		        			if((chck_stat=checkifnm(argv_sock[1]))<0){//no such iface;
		        				sprintf(tpm_msg,"%d",-1);
		        				memcpy(cli_snd,tpm_msg,strlen(tpm_msg)+1);
		        				if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
									perror("writing stream message");
								}
								sprintf(tpm_msg,"select another iface");
								printf( "\nselect another iface");
		        				memcpy(cli_snd,tpm_msg,strlen(tpm_msg)+1);
		        			}
		        			else if(chck_stat==0){
		        				showstt(cli_snd,msgsock,argv_sock[1]);
		        			}
		        		}
		        	}
		        	else{
		        		cli_snd[0]='\0';
		        		printf( "\ndefault");
		        	}
            	}
				sleep(1);
            	printf( "\nsnd_msg=%s",cli_snd); int wrtsz=0;
            	printf("\n wrtsz=%d, srtlen=%d",wrtsz=write(msgsock,cli_snd,strlen(cli_snd)+1),(int)strlen(cli_snd));
            	if(wrtsz<0){
            		perror("writing stream message");
            	}
            	printf("\n q");
            }
            close(msgsock);
		}
		sleep(1);
		fclose(outlog);//keep outlog's size by reopening each iteration;
		outlog=fopen("outlog","w+");
		if(outlog==NULL){
			printf( "\noutlg");
		 	return 1;
		}
    }
    free(buffer);
    close(sock_raw);
    close(cli_sock);
    unlink(NAME);
    printf( "Finished");
    fclose(logfile);
    fclose(outlog);
    return 0;
}

//files "log%interface_name%.txt will be saved at '/' (perhaps place them in separate directory: '/%dir_name%/%files%');
//communication between cli and daemon implemented through file (AF_UNIX socket); may d-bus be used;
//because of lines' shifts complexity is approximately O(N*log N) for insert operation and O(log N) for search operation;
//because of close(STDOUT_FILENO);, close(STDERR_FILENO);, fork() and setsid() printf's and perror's not printing data, but they stayed here for debug pupposes;
