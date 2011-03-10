#include <linux/init.h>
#include <linux/module.h>
 
//模块许可证
//WARNING: modpost: missing MODULE_LICENSE() in /home/ecy/module/helloworld/hello.o
MODULE_LICENSE("Dual BSD/GPL");
 
static DEFINE_PER_CPU(int, count);
 
//尽量使用static声明函数，不要污染全局名字空间
static int hello_init(void)
{
	printk(KERN_ALERT "[%d]Hello World enter\n", smp_processor_id());
 
	int* p;
 
	p = &(get_cpu_var(count));
 
	while (*p < 10)
	{
		++(*p);
	}
 
	return 0;
}
 
static void hello_exit(void)
{
	int* p;
 
	p = &(get_cpu_var(count));
 
	printk(KERN_ALERT "===count = %d\n", *p);
 
	printk(KERN_ALERT "[%d]Hello World exit\n", smp_processor_id());
}
 
//模块加载函数和卸载函数
module_init(hello_init);
module_exit(hello_exit);
 
//使用modinfo可以看到这些信息
MODULE_AUTHOR("Zhijie Fu");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("A simplest module");
