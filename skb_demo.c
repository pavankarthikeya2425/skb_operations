#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>

MODULE_LICENSE("GPL");

// Module initialization function
static int __init skb_demo_init(void)
{
    struct sk_buff *skb;

    // Allocate an sk_buff with 128 bytes
    skb = alloc_skb(128, GFP_KERNEL);
    if (!skb) {
        pr_err("Failed to allocate skb\n");
        return -ENOMEM;
    }

    // Print available tailroom
    pr_info("Allocated skb with tailroom: %u bytes\n", skb_tailroom(skb));

    // Reserve 64 bytes at tail (simulate adding data)
    skb_put(skb, 64);
    pr_info("After skb_put(64), len=%u\n", skb->len);

    // Push 16 bytes at head (simulate adding protocol header)
    skb_push(skb, 16);
    pr_info("After skb_push(16), data=%p\n", skb->data);

    // Pull 32 bytes from head (simulate removing header)
    skb_pull(skb, 32);
    pr_info("After skb_pull(32), len=%u\n", skb->len);

    // Free the sk_buff
    kfree_skb(skb);
    return 0;
}

// Module cleanup function
static void __exit skb_demo_exit(void)
{
    pr_info("skb demo module unloaded\n");
}

module_init(skb_demo_init);
module_exit(skb_demo_exit);

