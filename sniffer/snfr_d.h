#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include<string.h>    //strlen
#include <stdbool.h>//for bool;
 
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<netinet/if_ether.h>  //For ETH_P_ALL
#include<net/ethernet.h>  //For ether_header
#include <netpacket/packet.h>//for sockaddr_ll;
#include <net/if.h> //for ifreq
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include <fcntl.h>//for fcntl (nonblocking socket);
#include <sys/un.h>
#include <ifaddrs.h>
#include <syslog.h>

#define buf_sz 65536
#define kb_sz 1024
#define line_len 21//n(255.255.255.255)=15; n(' ')=1; n(unsigned int)=4; n('\n')=1;
#define m_ip_len 15
#define flines_max 500
#define NAME "sock_file"

#include "snfr_d_functions.h"
