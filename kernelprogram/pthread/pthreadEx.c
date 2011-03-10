#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#define BUFFER 512
struct copy_file {
int infile;
int outfile;
};
void *copy(void *arg)
{
int infile,outfile;
int bytes_read,bytes_write,*bytes_copy_p;
char buffer[BUFFER],*buffer_p;
struct copy_file *file=(struct copy_file *)arg;
infile=file->infile;
outfile=file->outfile;
/* 因为线程退出时,所有的变量空间都要被释放,所以我们只好自己分配内存了 */
if((bytes_copy_p=(int *)malloc(sizeof(int)))==NULL) pthread_exit(NULL);
bytes_read=bytes_write=0;
*bytes_copy_p=0;
/* 还记得怎么拷贝文件吗 */
while((bytes_read=read(infile,buffer,BUFFER))!=0)
{
if((bytes_read==-1)&&(errno!=EINTR))break;
else if(bytes_read>0)
{
buffer_p=buffer;
while((bytes_write=write(outfile,buffer_p,bytes_read))!=0)
{
if((bytes_write==-1)&&(errno!=EINTR))break;
else if(bytes_write==bytes_read)break;
else if(bytes_write>0)
{
buffer_p+=bytes_write;
bytes_read-=bytes_write;
}
}
if(bytes_write==-1)break;
*bytes_copy_p+=bytes_read;
}
}
close(infile);
close(outfile);
pthread_exit(bytes_copy_p);
}
int main(int argc,char **argv)
{
pthread_t *thread;
struct copy_file *file;
int byte_copy,*byte_copy_p,num,i,j;
char filename[BUFFER];
struct dirent **namelist;
struct stat filestat;
/* 得到当前路径下面所有的文件(包含目录)的个数 */
if((num=scandir(".",&namelist,0,alphasort))<0)
{
fprintf(stderr,"Get File Num Error:%s\n\a",strerror(errno));
exit(1);
}
/* 给线程分配空间,其实没有必要这么多的 */
if(((thread=(pthread_t *)malloc(sizeof(pthread_t)*num))==NULL)||
((file=(struct copy_file *)malloc(sizeof(struct copy_file)*num))==NULL)
)
{
fprintf(stderr,"Out Of Memory!\n\a");
exit(1);
}
for(i=0,j=0;i<num;i++)
{
memset(filename,'\0',BUFFER);
strcpy(filename,*namelist->d_name);
if(stat(filename,&filestat)==-1)
{
fprintf(stderr,"Get File Information:%s\n\a",strerror(errno));
exit(1);
}
/* 我们忽略目录 */
if(!S_ISREG(filestat.st_mode))continue;
if((file[j].infile=open(filename,O_RDONLY))<0)
{
fprintf(stderr,"Open %s Error:%s\n\a",filename,strerror(errno));
continue;
}
strcat(filename,".bak");
if((file[j].outfile=open(filename,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))
<0)
{
fprintf(stderr,"Creat %s Error:%s\n\a",filename,strerror(errno
));
continue;
}
/* 创建线程,进行文件拷贝 */
if(pthread_create(&thread[j],NULL,copy,(void *)&file[j])!=0)
fprintf(stderr,"Create Thread[%d] Error:%s\n\a",i,strerror(errno));
j++;
}
byte_copy=0;
for(i=0;i<j;i++)
{
/* 等待线程结束 */
if(pthread_join(thread,(void **)&byte_copy_p)!=0)
fprintf(stderr,"Thread[%d] Join Error:%s\n\a",
i,strerror(errno));
else
{
if(byte_copy_p==NULL)
continue;
printf("Thread[%d] Copy %d bytes\n\a",i,*byte_copy_p);
byte_copy+=*byte_copy_p;
/* 释放我们在 copy 函数里面创建的内存 */
free(byte_copy_p);
}
}
printf("Total Copy Bytes %d\n\a",byte_copy);
free(thread);
free(file);
exit(0);
}

