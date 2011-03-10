#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("dual BSD/GPL");
char * who="world";
static int hello_init(void){
	printk(KERN_ALERT "hello ,%s!\n",who);
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye,%s!\n",who);
}

module_init(hello_init);
module_exit(hello_exit);
