#include <stdio.h>
 
#include <pthread.h>
 
#include<sched.h> 
#include<stdlib.h>
#include<unistd.h>
 
#include <errno.h>
 

pthread_mutex_t mutex;
 
pthread_attr_t attr[3];
 
static int get_thread_info( pthread_attr_t *attr )
{
	int policy;
	int scope;
	struct sched_param param;
 
	pthread_attr_getschedpolicy( attr, &policy );
 
	pthread_attr_getscope(attr, &scope);
 
	switch ( policy )
	{
		case SCHED_FIFO:
			printf( "policy = SCHED_FIFO\n" );
			break;
		case SCHED_RR:
			printf( "policy = SCHED_RR\n" );
			break;
		case SCHED_OTHER:
			printf( "policy = SCHED_OTHER\n" );
			break;
		default:
			printf( "policy = UNKNOWN\n" );
			break;
	}
 
	switch (scope)
	{
		case PTHREAD_SCOPE_SYSTEM:
			printf("scope = PTHREAD_SCOPE_SYSTEM\n");
			break;
 
		case PTHREAD_SCOPE_PROCESS:
			printf("scope = PTHREAD_SCOPE_PROCESS\n");
			break;
 
		default:
			printf("scope = UNKNOWN\n");
			break;
	}
 
	pthread_attr_getschedparam( attr, &param );
 
	printf ("pority = %d\n", param.sched_priority);
 
	return policy;
}
 
void* callback(void* num)
{
	int n = (int)num;
 
	int ret;
 
	get_thread_info(&attr[n]);
 
	if (n == 0)
	{
		int i;
 
		int a = 1234;
		int b = 4321;
 
		int sum;
 
		ret = pthread_mutex_lock(&mutex); 
 
		printf("thread 0 lock the mutex\n", n);
 
		//阻塞高优先级线程
		for (i = 0; i < 2000000000; ++i)
		{
			if (i % 100000000 == 0)
			{
				printf("thread 0 running on cpu [%d]\n", sched_getcpu());
			}
 
			sum += a * b;
			sum -= a * b;
		}
 
		printf("thread 0 ready to unlock the mutex\n");
 
		pthread_mutex_unlock(&mutex);
	}
	else if(n == 1)
	{
		int i;
 
		int sum;
 
		int a = 1234;
		int b = 4321;
 
		for (i = 0; i < 2000000000; ++i)
		{
			if (i % 100000000 == 0)
			{
				printf("thread 1 running on cpu [%d]\n", sched_getcpu());
			}
 
			sum += a * b;
			sum -= a * b;
		}
 
		printf("thread 1 exit\n");
	}
	else
	{
		sleep(2);
 
		//等待0号线程释放锁
		ret = pthread_mutex_lock(&mutex); 
 
		printf("thread 2 got the mutex\n");
 
		pthread_mutex_unlock(&mutex);
	}
}
 
int main()
{
	cpu_set_t mask;  
 
	int ret;
 
	int i;
 
	pthread_t thread[3];
 
	struct sched_param param;
 
	int protocol;
 
	/*pthread_mutexattr_getprotocol(..., &protocol);
 
	switch (protocol)
	{
	case PTHREAD_PRIO_NONE:
		printf("PTHREAD_PRIO_NONE\n");
		break;
 
	case PTHREAD_PRIO_INHERIT:
		printf("PTHREAD_PRIO_INHERIT\n");
		break;
 
	case:
		printf("PTHREAD_PRIO_PROTECT\n");
		break;
 
	default:
		printf("error!\n");
	}*/
 
	CPU_ZERO(&mask);  
 
	CPU_SET(0, &mask);  
 
	//设置CPU亲和性，让线程只运行在0号核上
	//多核CPU会对线程优先级产生干扰，比如有两个线程，一个优先级高，一个优先级低
	//在单核CPU上，会先运行高优先级线程，再运行低优先级线程
	//在多核CPU上，两个线程可能就会在不同的CPU上并行执行
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1)  
	{  
		printf("warning: could not set CPU affinity, continuing\n");  
	}
 
	//初始化互斥体
	ret = pthread_mutex_init(&mutex, NULL);
 
	//创建子线程
	for (i = 0; i < 3; ++i)
	{
		pthread_attr_init(&attr[i]);
 
		//get_thread_policy(&attr[i]);
 
		//设置线程优先级
		//线程优先级从0-99，0最低，99最高
		//第一个线程优先级是1
		//第二个线程优先级是49
		//第三个线程优先级是99
		if (i == 0)	
			param.sched_priority = 1;
		else if (i == 1)
			param.sched_priority = 49;
		else
			param.sched_priority = 99;
 
		//必须首先将调度策略设置为SCHED_FIFO或SCHED_RR
		//否则后面设置线程优先级不会成功
		pthread_attr_setschedpolicy(&attr[i], SCHED_FIFO);
 
                //将scope设置成PTHREAD_SCOPE_PROCESS
                //返回值会是ENOTSUP，也就是说"not support"
		ret = pthread_attr_setscope(&attr[i], PTHREAD_SCOPE_PROCESS);
 
		switch (ret)
		{
		case ENOSYS:
				printf("===ENOSYS\n");
				break;
 
		case EINVAL:
				printf("===EINVAL\n");
				break;
 
		case ENOTSUP:
				printf("===ENOTSUP\n");
				break;
 
		default:
				printf("successfully\n");
		}
 
		pthread_attr_setschedparam(&attr[i], &param);
 
		#ifdef HAS
			pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
		#endif
 
		//创建线程
		ret = pthread_create(
				&thread[i], 
				&attr[i],
				callback,
				(void *)(i)
				);
 
	}
 
	//等待子线程退出
	for (i = 0; i < 3; ++i)
	{
		pthread_join(thread[i], NULL);
	}
 
	//释放资源
	pthread_mutex_destroy(&mutex);
 
	for (i = 0; i < 3; ++i)
	{
		pthread_attr_destroy(&attr[i]);
	}
 
	return 0;
}
