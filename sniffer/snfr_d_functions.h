typedef union uint_u{
	unsigned int u_val;
	unsigned char u_byte[4];
} uint_f;

unsigned int getln(unsigned char* strff,unsigned char* g_ip, uint_f* g_ipcnt,FILE *logfile){
	unsigned int cpcnt=0,i=0;
	fread(strff,sizeof(unsigned char),line_len,logfile);
	for(i=0;i<m_ip_len;i++){
		if(strff[i]!=' '){
			memcpy(g_ip+cpcnt,strff+i,1);
			cpcnt++;
		}
	}
	memcpy(g_ip+cpcnt,"\0",1);
	g_ipcnt->u_byte[0]=strff[16]; g_ipcnt->u_byte[1]=strff[17]; g_ipcnt->u_byte[2]=strff[18]; g_ipcnt->u_byte[3]=strff[19];
	return cpcnt;
}

int ffindip(struct sockaddr_in src,FILE *logfile,bool flread){//it would be easier to work with data loaded to RAM (with list or so) but as collected information may become too big to handle it, there used file to save data;
	unsigned char str_to_file[line_len],strff[line_len],g_ip[m_ip_len+1];
	uint_f curr_ipcnt,g_ipcnt; curr_ipcnt.u_val=1;
	unsigned int i; int cmpres; unsigned long int n_lines=0,sln=0,eln=0,curr_dif,curr_line; long int i_signed;
	for(i=0;i<line_len;i++)
		str_to_file[i]=' ';
	memcpy(str_to_file+15-strlen(inet_ntoa(src.sin_addr)),inet_ntoa(src.sin_addr),strlen(inet_ntoa(src.sin_addr)));
	memcpy(str_to_file+15," ",1);
	memcpy(str_to_file+16,curr_ipcnt.u_byte,sizeof(curr_ipcnt.u_val));
	memcpy(str_to_file+20,"\n",strlen("\n"));
	
	rewind(logfile);//find start of the file;
	unsigned long int sstrt=ftell(logfile);
	if(fseek(logfile,0L,SEEK_END)){
		printf( "\nfseek_err: %s",strerror(errno)); return -1;
	}
	unsigned long int send=ftell(logfile);
	rewind(logfile);// unsigned char ufchar;
	if((send-sstrt)==0){//file is empty;
		if(flread) return -2;
		rewind(logfile);//to be sure;
		fwrite(str_to_file,sizeof(unsigned char),line_len,logfile);
		return 0;
	}
	n_lines=(send-sstrt)/line_len; sln=0;eln=n_lines-1;
	
	rewind(logfile);
	while((eln-sln)>1){
		//sps();
		curr_dif=(unsigned int)((eln-sln)/2.+0.5); curr_line=sln+curr_dif;
		fseek(logfile, curr_line*line_len,SEEK_SET);//find line position;
		unsigned int f_ip_len=getln(strff,g_ip,&g_ipcnt,logfile);
		if((cmpres=strcmp(g_ip,inet_ntoa(src.sin_addr)))==0){//equal
			if(flread){
				return g_ipcnt.u_val;
			}
			g_ipcnt.u_val++;
			memcpy(strff+16,g_ipcnt.u_byte,sizeof(g_ipcnt.u_val));
			fseek(logfile, curr_line*line_len,SEEK_SET);//find line position;
			fwrite(strff,sizeof(unsigned char),line_len,logfile);
			return 0;
		}
		else if(cmpres<0){
			sln=curr_line;
		}
		else{
			eln=curr_line;
		}
	}//we have src.sin_addr, sln, eln;
	fseek(logfile, sln*line_len,SEEK_SET);//find start line position;
	getln(strff,g_ip,&g_ipcnt,logfile);
	cmpres=strcmp(g_ip,inet_ntoa(src.sin_addr));
	if((cmpres=strcmp(g_ip,inet_ntoa(src.sin_addr)))==0){
		if(flread) return g_ipcnt.u_val;
		g_ipcnt.u_val++;
		memcpy(strff+16,g_ipcnt.u_byte,sizeof(g_ipcnt.u_val));
		fseek(logfile, sln*line_len,SEEK_SET);//find line position;
		fwrite(strff,sizeof(unsigned char),line_len,logfile);
		return 0;
	}
	if(cmpres>0){//insert line before sln;
		if(flread) return -2;
		for(i_signed=n_lines-1;i_signed>=(long int)sln;i_signed--){//shift lines;
			fseek(logfile, i_signed*line_len,SEEK_SET);//find line position;
			getln(strff,g_ip,&g_ipcnt,logfile);
			fwrite(strff,sizeof(unsigned char),line_len,logfile);
		}
		fseek(logfile, sln*line_len,SEEK_SET);
		fwrite(str_to_file,sizeof(unsigned char),line_len,logfile);
		return 0;
	}
	else{
		fseek(logfile, eln*line_len,SEEK_SET);
		getln(strff,g_ip,&g_ipcnt,logfile);
		if((cmpres=strcmp(g_ip,inet_ntoa(src.sin_addr)))==0){
			if(flread) return g_ipcnt.u_val;
			g_ipcnt.u_val++;
			memcpy(strff+16,g_ipcnt.u_byte,sizeof(g_ipcnt.u_val));
			fseek(logfile, eln*line_len,SEEK_SET);
			fwrite(strff,sizeof(unsigned char),line_len,logfile);
			return 0;
		}
		if(cmpres>0){//insert line between sln and eln;
			if(flread) return -2;
			for(i_signed=n_lines-1;i_signed>=(long int)eln;i_signed--){
				fseek(logfile, i_signed*line_len,SEEK_SET);//find line position;
				getln(strff,g_ip,&g_ipcnt,logfile);
				fwrite(strff,sizeof(unsigned char),line_len,logfile);
			}
			fseek(logfile, eln*line_len,SEEK_SET);
			fwrite(str_to_file,sizeof(unsigned char),line_len,logfile);
			return 0;
		}
		else{//insert line after eln;
			if(flread) return -2;
			for(i_signed=n_lines-1;i_signed>(long int)eln;i_signed--){
				fseek(logfile, i_signed*line_len,SEEK_SET);//find line position;
				getln(strff,g_ip,&g_ipcnt,logfile);
				fwrite(strff,sizeof(unsigned char),line_len,logfile);
			}
			fseek(logfile, (eln+1)*line_len,SEEK_SET);
			fwrite(str_to_file,sizeof(unsigned char),line_len,logfile);
			return 0;
		}
	}
	if(flread) return -3;
	return -1;
}

void pprocess(unsigned char* buffer, int data_sz, struct ifreq ifr,FILE *logfile,bool flread){
	struct sockaddr_in source,dest; int fip_res;
	struct iphdr *iph = (struct iphdr *)(buffer  + sizeof(struct ethhdr));
	source.sin_addr.s_addr = iph->saddr; dest.sin_addr.s_addr = iph->daddr;
	if(source.sin_addr.s_addr!=((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr){//skip packets which were sent, collect only received packets;
		if((fip_res=ffindip(source,logfile,flread))){
			if(!flread){
				if(fip_res==-1){
					printf( "\nwrite_err!\n");
				}
			}
			else{
				if(fip_res==-2){
					printf( "\nip_nfnd\n");
				}
				else if(fip_res==-3){
					printf( "\nread_err!\n");
				}
			}
		}
	}
}

void prs_cli(char* cli_comm,int rval,int* argc_sock, unsigned char argv_sock[2][kb_sz]){
	unsigned int i=0,ln_cnt=0; *argc_sock=1;
	for(i=0;i<rval;i++){
		if(cli_comm[i]!=' '){
			argv_sock[(*argc_sock)-1][ln_cnt]=cli_comm[i];
			ln_cnt++;
		}
		else{
			argv_sock[(*argc_sock)-1][ln_cnt]='\0';
			(*argc_sock=2); ln_cnt=0;
		}
	}
	argv_sock[(*argc_sock)-1][ln_cnt]='\0';
	if((*argc_sock)==1){
		argv_sock[1][0]='\0';
	}
	printf( "\n*argc_sock=%d argv_sock[0]=%s argv_sock[1]=%s",*argc_sock,argv_sock[0],argv_sock[1]);
}

int checkifnm(char* ifname){
	struct ifaddrs *ifaddr,*ifa; int i,cmpres,family;
	if (getifaddrs(&ifaddr) == -1) {
       perror("getifaddrs");
       return -1;
   	}
   	for (ifa = ifaddr, i = 0; ifa != NULL; ifa = ifa->ifa_next, i++){
   		family = ifa->ifa_addr->sa_family;
   		if (ifa->ifa_addr == NULL||family != AF_PACKET)
			continue;
   		cmpres=strcmp(ifname,ifa->ifa_name);
   		printf( "\ni=%d, ifa_name=%s cmpres=%d",i,ifa->ifa_name,cmpres);
   		if(cmpres==0){
   			printf( "\nif_fnd");
   			return 0;
   		}
   	}
   	return -1;
}

void showstt(unsigned char* cli_snd,int msgsock, unsigned char* ifacenm){
	unsigned char flnm[strlen("log")+strlen(ifacenm)+strlen(".txt")+1], strff[line_len], g_ip[m_ip_len+1];
	uint_f g_ipcnt;	unsigned long i,sstrt,send,n_lines;
	sprintf(flnm,"log%s.txt",ifacenm);
	if(access(flnm,F_OK)!=-1){
		FILE* ftsw=fopen(flnm,"r");
		if(ftsw==NULL){
			sprintf(cli_snd,"%d",-1);
			if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
				perror("writing stream message");
			}
			sprintf(cli_snd,"file log%s.txt nopn",ifacenm);
		}
		else{
			rewind(ftsw);
			sstrt=ftell(ftsw);
			if(fseek(ftsw,0L,SEEK_END)){
				printf( "\nfseek_err: %s",strerror(errno)); return;
			}
			send=ftell(ftsw);
			if((send-sstrt)==0){//file is empty;
				sprintf(cli_snd,"%d",-1);
				if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
					perror("writing stream message");
				}
				sprintf(cli_snd,"file log%s.txt is empty",ifacenm);
			}
			else{
				n_lines=(send-sstrt)/line_len;
				sprintf(cli_snd,"%ld",n_lines); printf("\nn_lines=%ld",n_lines);
				if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
					perror("writing stream message");
				}
				rewind(ftsw);
				for(i=0;i<n_lines;i++){
					getln(strff,g_ip,&g_ipcnt,ftsw);
					sprintf(cli_snd,"%s %d",g_ip,g_ipcnt.u_val);
					printf("\nsnd=%s",cli_snd);
					sleep(1);//TODO: replace sleep() with write/read pairs;
					if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
						perror("writing stream message");
					}
				}
				sprintf(cli_snd,"ok");
			}
		}
	}
	else{
		sprintf(cli_snd,"%d",-1);
		if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
    		perror("writing stream message");
    	}
    	sprintf(cli_snd,"file log%s.txt nfnd",ifacenm);
	}
}

int showstall(unsigned char* cli_snd,int msgsock){
	struct ifaddrs *ifaddr,*ifa; int i,cmpres,family;
	if (getifaddrs(&ifaddr) == -1) {
       perror("getifaddrs");
       return -1;
   	}
   	for (ifa = ifaddr, i = 0; ifa != NULL; ifa = ifa->ifa_next, i++){
   		family = ifa->ifa_addr->sa_family;
   		if (ifa->ifa_addr == NULL||family != AF_PACKET)
			continue;
		sleep(1);
		sprintf(cli_snd,"%d",1);
		if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
			perror("writing stream message");
		}
		printf("\nifn=%s",ifa->ifa_name);
		sleep(1);
   		showstt(cli_snd,msgsock,ifa->ifa_name);
   	}
   	sprintf(cli_snd,"%d",0);
   	if(write(msgsock,cli_snd,strlen(cli_snd)+1)<0){
		perror("writing stream message");
	}
	sprintf(cli_snd,"ok");
}

int open_fls(FILE** logfile,FILE** outlog,char* fname){//as we modifying FILE*, FILE** should be passed in function; another possible approach, use 2 functions with each one returning its own FILE*;
	*logfile=fopen(fname,"rb+");
    if(*logfile==NULL){
    	*logfile=fopen(fname,"wb+");//if file not exist, create it;
    	if(*logfile==NULL){
    		printf( "Unable to create log.txt file."); return 1;
    	}
    }
    *outlog=fopen("outlog","w+");
	if(*outlog==NULL){
		printf("outlog==NULL\n");
	 	return 2;
	}
	return 0;
}

int sock_conf(int* sock_raw,int* fd, int* cli_sock,struct ifreq* ifr,char* if_name,struct sockaddr_ll* sock_address, struct sockaddr_un* server){//create and configure socet for sniffing; (sock_raw -- for sniffing; fd -- to get NIC's IPv4 address;)
    *sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    if(*sock_raw < 0){ perror("Socket Error"); return 1;}
	ioctl(*sock_raw, SIOCGIFFLAGS, &(*ifr));//Set interface to promiscuous mode for sniffing all received packets;
	ifr->ifr_flags |= IFF_PROMISC;
	ioctl(*sock_raw, SIOCSIFFLAGS, &(*ifr));
	if (setsockopt(*sock_raw, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1) {//Allow the socket to be reused;
	  perror("setsockopt");
	  close(*sock_raw);
	  return 1;
	}
	memset(sock_address, 0, sizeof(*sock_address));//bind socket to specific NIC (if_name); (SO_BINDTODEVICE  is not supported for packet sockets);
	sock_address->sll_family = AF_PACKET;
	sock_address->sll_protocol = htons(ETH_P_ALL);
	sock_address->sll_ifindex = if_nametoindex(if_name);
	if (bind(*sock_raw, (struct sockaddr*) sock_address, sizeof(*sock_address)) < 0) {
	  perror("bind failed\n");
	  close(*sock_raw);
	  return 1;
	}
	
	*fd= socket(AF_INET, SOCK_DGRAM, 0);//*fd -- temporary file descriptor; AF_INET addresses are accepted;
	ifr->ifr_addr.sa_family = AF_INET; /* I want to get an IPv4 IP address */
	strncpy(ifr->ifr_name, if_name, IFNAMSIZ-1); /* I want IP address attached to if_name */
	ioctl(*fd, SIOCGIFADDR, &(*ifr)); close(*fd);
	printf( "\nip(if_name)=%s\n", inet_ntoa(((struct sockaddr_in *)(&(ifr->ifr_addr)))->sin_addr));	
	
    *cli_sock = socket(AF_UNIX, SOCK_STREAM, 0);//create socket for cli communication;
    if (*cli_sock < 0) {
        perror("opening stream socket");
        return 1;
    }
	if (setsockopt(*cli_sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1) {//Allow the socket to be reused;
		perror("setsockopt");
		close(*sock_raw); close(*cli_sock);
		return 1;
	}
    server->sun_family = AF_UNIX;
    strcpy(server->sun_path, NAME);
    if (bind(*cli_sock, (struct sockaddr *) server, sizeof(struct sockaddr_un))) {
        perror("binding stream socket");
        return 1;
    }
	return 0;
}
