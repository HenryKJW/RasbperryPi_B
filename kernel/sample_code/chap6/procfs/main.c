/* 
目的：在/proc下產生一個test目錄後,在test目錄下產成sample檔案
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");
#define PROCNAME1	"test"
#define PROCNAME2	"sample"

struct proc_dir_entry *entry,*entry1;

//#define DUMMY_BUFSIZ 4096
//static char dummy[DUMMY_BUFSIZ];

struct file_operations smaple_fops;

static int sample_init(void)
{
	int i;

	/* add /proc */
	entry=proc_mkdir(PROCNAME1,NULL);
	entry1 = proc_create(PROCNAME2, S_IRUGO | S_IWUGO, entry, &smaple_fops);
	if (entry == NULL) {
		printk(KERN_WARNING "sample: unable to create /proc entry\n");
	}
/*
	for (i = 0 ; i < DUMMY_BUFSIZ ; i++) {
		dummy[i] = 'A' + (i % 26);
	}
*/
	printk("driver loaded\n");
		
	return 0;
}

static void sample_exit(void)
{
//	remove_proc_entry(PROCNAME1,entry);
//	remove_proc_entry(PROCNAME1,entry1);
	proc_remove(entry1);
	proc_remove(entry);
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);

