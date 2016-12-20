/*
目的：在/proc下產生一個slam目錄後,在slam目錄下產成xinu檔案和stxinu的link檔

執行範例： 
# sudo /sbin/insmod ./sample.ko 
# ls -l /proc/slam
# cat /proc/slam/xinu
# echo 1 > /proc/slam/xinu
# cat /proc/slam/stxinu
# echo 0 > /proc/slam/stxinu
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

struct proc_dir_entry * slam_dir = NULL;
struct proc_dir_entry * slam_entry = NULL;

static char * dir_name = "slam";
static char * entry_name = "xinu";
static char * symlink_name = "stxinu";

static ssize_t xinu_proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
        char *str = "My name is xinu.\n";
        int len = strlen(str);
        copy_to_user(buf, str, len);
        if (*ppos == 0)
                *ppos += len;
        else
                len = 0;
        return len;
}

static ssize_t xinu_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
        char str[128];
        if (count > PAGE_SIZE) //procfs write and read has PAGE_SIZE limit
        count = 128;

        if (copy_from_user(str, buf, count))
        {
                printk("copy_from_user failed!\n");
                return -EFAULT;
        }

        str[count-1] = '\0';
        printk("Your enter :\n%s\n", str);
        return count;
}

static const struct file_operations slam_fops =
{
        .owner = THIS_MODULE,
        .read = xinu_proc_read,
        .write = xinu_proc_write,
};

static __init int procfs_example_init(void)
{
                slam_dir = proc_mkdir(dir_name, NULL);
                if (!slam_dir)
                {
                        printk("Create directory \"%s\" failed.\n", dir_name);
                        return -1;
                }

                slam_entry = proc_create(entry_name, 0666, slam_dir, &slam_fops);
                if (!slam_entry)
                {
                        printk("Create file \"%s\" and symlink \"%s\" failed.\n", entry_name, symlink_name);
                        return -1;
                }

                proc_symlink(symlink_name, slam_dir, entry_name);

        return 0;
}

static __exit void procfs_example_exit(void)
{
                   proc_remove(slam_entry);
     		     proc_remove(slam_dir);
		     remove_proc_subtree(dir_name,slam_entry);
}

MODULE_LICENSE("GPL");
module_init(procfs_example_init);
module_exit(procfs_example_exit);