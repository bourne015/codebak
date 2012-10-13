#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/kobject.h>
#include<linux/sysfs.h>
#include<linux/stat.h>
#include<linux/string.h>

#define myk_name "fantao"

struct kobject kobj;
//struct attribute *myk_attrs;
struct attribute myk_attr = {
    .name = myk_name,
//    .owner = THIS_MODULE,
    .mode = S_IWUSR,
};


struct attribute *myk_attrs[] = {
    &myk_attr,
    NULL,
};

static ssize_t myk_show(struct kobject *kobj, struct attribute *attr,
                       char *buffer)
{
    printk(KERN_ALERT "myk_show is working next is empty print\n");
    printk("test printk with empty\n");
    //strcpy()    
    //printk("%s\n",myk_attrs.name);
    return 0;
}

static ssize_t myk_store(struct kobject *kobj, struct attribute *attr,
                         const char *buffer, size_t size)
{
    printk(KERN_ALERT "myk_store is working\n");
    printk("%s\n",buffer);
    return 0;
}
struct sysfs_ops myk_ops = {
    .show = myk_show,
    .store = myk_store,
};

void myk_release(struct kobject *kobj)
{
    printk(KERN_ALERT "myk_release is working\n");
}

struct kobj_type myk_type = {
    .release = myk_release,
    .sysfs_ops = &myk_ops,
    .default_attrs = myk_attrs,
};//*myk_type;

int kobjt_init(void)
{
    kobject_init(&kobj, &myk_type);
    kobject_add(&kobj, NULL, "parename");
    printk(KERN_INFO "INFO:kobject inited\n");
    printk(KERN_ALERT "ALERT:kobject inited\n");
    return 0;
}

void kobjt_exit(void)
{
    kobject_del(&kobj);
}

module_init(kobjt_init);
module_exit(kobjt_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FANTAO");
