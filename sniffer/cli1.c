#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>

#define NAME "sock_file"
#define info_str "The​ ​ cli​ ​ should​ ​ support​ ​ command:\
			\na. start​​ ​ (packets​ ​ are​ ​ being​ ​ sniffed​ ​ from​ ​ now​ ​ on​ ​ from​ ​ default​ ​ iface(eth0))\
			\nb. stop​​ ​ (packets​ ​ are​ ​ not​ ​ sniffed)\
			\nc. show​ ​ [ip]​ ​ count​ ​ (print​ ​ number​ ​ of​ ​ packets​ ​ received​ ​ from​ ​ ip​ ​ address)\
			\nd. select​ ​ iface​ ​ [iface]​ ​ (select​ ​ interface​ ​ for​ ​ sniffing​ ​ eth0,​ ​ wlan0,​ ​ ethN, wlanN...)\
			\ne. stat​​ ​ [iface]​​ ​ show​ ​ all​ ​ collected​ ​ statistics​ ​ for​ ​ particular​ ​ interface,​ ​ if​ ​ iface\
			omitted​ ​ - ​ ​ for​ ​ all​ ​ interfaces.\
			\nf. ​ ​ --help​ ​ (show​ ​ usage​ ​ information)\n"
#define buff_len 128

int is_startted(unsigned char* srch_nm){
	DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[buff_len];
    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }
    while((ent = readdir(dir)) != NULL) {//if endptr is not a null character, the directory is not entirely numeric, so ignore it
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }
        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);//try to open the cmdline file
        FILE* fp = fopen(buf, "r");
        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
				char* first = strtok(buf, " ");//check the first token in the file, the program name
                if (!strcmp(first, srch_nm)) {
                    fclose(fp);
                    closedir(dir);
                    return 1;
                }
            }
            fclose(fp);
        }
    }
    closedir(dir);
    return 0;
}

/*void sps(){
	printf( "\npak...");
	getchar();
}*/

int main(int argc, char** argv){//it is good idea to use here getopt_long() for parsing command-line options bet here just limited number of possible options to one then parsing it;
	if(argc<2||argc>4||strcmp(argv[1],"--help")==0){
		printf(info_str);
		return 0;
	}
	int isstrt=is_startted("./snfr_d");
	if(isstrt<0){
		return 1;
	}
	else if(isstrt==0){
		printf("\nidstrt=%d\n",isstrt);
		int frk=fork();
		if(frk<0){
			perror("fork()<0");
			return 1;
		}
		else if(frk==0){//child process;
			char* argv1[]={"./snfr_d","strt",(char*)0};
			if(execve("./snfr_d",argv1, NULL)<0){
				printf("\n%d",errno);
				perror("\nexecve");
			}
			return 0;
		}
		else{
			sleep(2);//wait for ./snfr_d;
		}
	}
	chdir("/"); // Change the current working directory to root. (for socket names);
	int sock,rval; struct sockaddr_un server; char buf[1024]; 
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		return 1;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1) {//Allow the socket to be reused;
	  perror("setsockopt");
	  close(sock);
	  return 1;
	}
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, NAME);
	int err_num=0;
	if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
		perror("connect");
		close(sock);
		return 1;		
	}
    	
	if(strcmp(argv[1],"start")==0){
		unsigned char* data_snd="start";
		printf("data_snd=%s\n",data_snd);
		if (write(sock, data_snd, sizeof(data_snd)) < 0)
        	perror("writing on stream socket");
	}
	else if(strcmp(argv[1],"stop")==0){
		unsigned char* data_snd="stop";
		printf("data_snd=%s\n",data_snd);
		if (write(sock, data_snd, sizeof(data_snd)) < 0)
        	perror("writing on stream socket");
	}
	else if(strcmp(argv[1],"show")==0 && argc==4 && strcmp(argv[3],"count")==0){
		unsigned char data_snd[strlen("show")+strlen(argv[2])+2];
		memcpy(data_snd,"show",strlen("show"));
		memcpy(data_snd+strlen("show")," ",1);
		memcpy(data_snd+strlen("show")+1,argv[2],strlen(argv[2])+1);
		printf("data_snd=%s\n",data_snd);
		if (write(sock, data_snd, sizeof(data_snd)) < 0)
        	perror("writing on stream socket");
	}
	else if(strcmp(argv[1],"select")==0 && argc==4 && strcmp(argv[2],"iface")==0){
		unsigned char data_snd[strlen("select")+strlen(argv[3])+2];
		memcpy(data_snd,"select",strlen("select"));
		memcpy(data_snd+strlen("select")," ",1);
		memcpy(data_snd+strlen("select")+1,argv[3],strlen(argv[3])+1);
		printf("data_snd=%s\n",data_snd);
		if (write(sock, data_snd, sizeof(data_snd)) < 0)
        	perror("writing on stream socket");
	}
	else if(strcmp(argv[1],"stat")==0 && (argc==2 || argc==3)){
		unsigned char *data_snd1;
		if(argc==3){
			data_snd1=(unsigned char *) malloc(strlen("stat")+strlen(argv[2])+2);
			memcpy(data_snd1,"stat",strlen("stat"));
			memcpy(data_snd1+strlen("stat")," ",1);
			memcpy(data_snd1+strlen("stat")+1,argv[2],strlen(argv[2])+1);
		}
		else{
			data_snd1=(unsigned char *) malloc(strlen("stat")+strlen("all")+2);
			memcpy(data_snd1,"stat",strlen("stat"));
			memcpy(data_snd1+strlen("stat")," ",1);
			memcpy(data_snd1+strlen("stat")+1,"all",strlen("all")+1);
		}
		printf("data_snd1=%s\n",data_snd1);
		if (write(sock, data_snd1, strlen(data_snd1)) < 0)
        	perror("writing on stream socket");
        free(data_snd1);
        if ((rval = read(sock, buf, 1024)) < 0)
		    perror("reading stream message");
		else if (rval == 0)
		    printf("Ending connection\n");
		else{
			printf("\nrecv_msg=%s",buf);
			int nlines=atoi(buf); unsigned int i;
			if(nlines==-1){
				printf("\nerr: ");
			}
			else{
				if(argc==2){
					while(nlines!=0){
						int cnt;
						if ((rval = read(sock, buf, 1024)) < 0)
							perror("reading stream message");
						else if (rval == 0){
							printf("Ending connection1\n");
						}
						else{
							printf("\ncnt=%s",buf);
							cnt=atoi(buf);
							if(cnt==-1){
								printf("\nskip iface");
							}
							else{
								printf("\nall:");
								for(i=0;i<cnt;i++){
									if ((rval = read(sock, buf, 1024)) < 0)
										perror("reading stream message");
									else if (rval == 0)
										printf("Ending connection2\n");
									else{
										printf("\nln=%s",buf);
									}
								}
							}
							if ((rval = read(sock, buf, 1024)) < 0)
								perror("reading stream message");
							else if (rval == 0)
								printf("Ending connection3\n");
							else{
								printf("\nstat=%s",buf);
								nlines=atoi(buf);
							}
						}
					}
				}
				else{
					for(i=0;i<nlines;i++){
						if ((rval = read(sock, buf, 1024)) < 0)
							perror("reading stream message");
						else if (rval == 0)
							printf("Ending connection\n");
						else{
							printf("\nln=%s",buf);
						}
					}
				}
			}
		}
	}
	else{
		printf("default: %s\n",argv[1]);
	}
	if ((rval = read(sock, buf, 1024)) < 0)
	    perror("\nreading stream message");
	else if (rval == 0)
	    printf("\nEnding connection\n");
	else{
		printf("\nrecv_msg=%s\n",buf);
	}
	close(sock);
	
	return 0;
}
