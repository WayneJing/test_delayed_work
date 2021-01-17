#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

static struct delayed_work dwork;
static unsigned long intervals;
static int update_version;

static void update_work_item(struct work_struct *work)
{
    int i;
    
    for (i = 0; i < 30; i++) {
        printk(KERN_INFO"update_version%5d update work item!!!    %3d\n", update_version, i);
        msleep(1);
    }
    schedule_delayed_work(&dwork, intervals);
};

static int my_init(void)
{
    intervals = HZ * 5;
    update_version = 0;
    INIT_DELAYED_WORK(&dwork, update_work_item);
    schedule_delayed_work(&dwork, intervals);
    printk(KERN_ALERT"work_queue init!!!!!\n");
    return 0;
}

static void my_exit(void) 
{
    printk(KERN_ALERT"work_queue begin fini!!!!\n");
    cancel_delayed_work_sync(&dwork);
    printk(KERN_ALERT"work_queue canceled!!!!\n");
    //flush_delayed_work(&dwork);
    //printk(KERN_ALERT"work_queue flushed!!!!\n");
    
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("Dual BSD/GPL");


