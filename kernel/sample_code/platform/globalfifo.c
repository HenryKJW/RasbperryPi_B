#include <linux/module.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Brook");
MODULE_DESCRIPTION("Kernel module for demo");
MODULE_LICENSE("GPL");

#define DEVNAME "brook"

#define DYN_ALLOC	 1

static struct platform_device brook_device = {
    .name = DEVNAME,
};

static int brook_probe(struct platform_device *pdev)
{
    pr_info("%s(#%d)\n", __func__, __LINE__);
    return 0;
}

static int brook_remove(struct platform_device *pdev)
{
    pr_info("%s(#%d)\n", __func__, __LINE__);
    return 0;
}

static struct platform_driver brook_driver = {
    .driver = {
        .name  = DEVNAME,
        .owner = THIS_MODULE,
    },
    .probe  = brook_probe,
    .remove = brook_remove,
};

static int __init brook_init(void)
{
    int err;
    pr_info("%s(#%d)\n", __func__, __LINE__);

    err = platform_device_register(&brook_device);
    if (err) {
        pr_err("%s(#%d): platform_device_register failed(%d)\n",
                __func__, __LINE__, err);
        return err;
    }

    err = platform_driver_register(&brook_driver);
    if (err) {
        dev_err(&(brook_device.dev), "%s(#%d): platform_driver_register fail(%d)\n",
                __func__, __LINE__, err);
        goto dev_reg_failed;
    }
    return err;

dev_reg_failed:
    platform_device_unregister(&brook_device);

    return err;
}
module_init(brook_init);

static void __exit brook_exit(void)
{
    dev_info(&(brook_device.dev), "%s(#%d)\n", __func__, __LINE__);
    platform_device_unregister(&brook_device);
    platform_driver_unregister(&brook_driver);
}
module_exit(brook_exit);