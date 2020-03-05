#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>	
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "xparameters.h"
#define PHY_ADDR XPAR_MULTIPLY_0_S00_AXI_BASEADDR 
#define MEMSIZE XPAR_MULTIPLY_0_S00_AXI_HIGHADDR - XPAR_MULTIPLY_0_S00_AXI_BASEADDR + 1

//Program defines
#define REG_A_OFFSET 0
#define REG_B_OFFSET 4
#define REG_O_OFFSET 8
#define DEVICE_NAME "multiplier"
#define ERR_NO_MAJOR "Multiply device driver registration failed with code %d\n"
#define MAJOR_SCC "Multiply device driver registered with major number %d\n"

//Global variables
static int major;
void* virt_addr;

//Functions
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

static int __init my_init(void){
    major = register_chrdev(0, DEVICE_NAME, &fops);
    virt_addr = ioremap(PHY_ADDR, MEMSIZE); 
    if (major < 0){ 
        printk(KERN_ALERT ERR_NO_MAJOR, major); 
        return major; 
    }
    printk(KERN_INFO MAJOR_SCC, major);
    return 0;
}

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device file opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device file closed\n");
    return 0;
}

static ssize_t device_read(struct file *filp, 
                           char *buffer, 
                           size_t length, 
                           loff_t * offset)
{
    
    int bytes_read = 0; //Count how many bytes were read
    //Allocate space for 3 integers to operate on.
    int* kernelBuffer = (int*)kmalloc(3 * sizeof(int), GFP_KERNEL);
    
    //Directly copy all three integers to our buffer.
    kernelBuffer[0] = ioread32(virt_addr + REG_A_OFFSET);
    kernelBuffer[1] = ioread32(virt_addr + REG_B_OFFSET);
    kernelBuffer[2] = ioread32(virt_addr + REG_O_OFFSET);
    
    //Cast to characters
    char* kbuff = (char*)kernelBuffer;
    
    //Put characters onto the kernel segment buffer
    int i;
    for (i = 0; i < length; i++) {
        put_user(*(kbuff++), buffer++);
        bytes_read++;
    }
    //Free allocated space.
    kfree(kernelBuffer);
    return bytes_read;
}

static ssize_t device_write(struct file *filp, 
                            const char *buff, 
                            size_t len, 
                            loff_t * off)
{
    //Allocate space for user input, whatever it may be
    //This will be in the kernel so we can directly move
    //it to the device. 
    char* kbuf = (char*)kmalloc((len) * sizeof(char), GFP_KERNEL);
    
    //Copy that data to the kernel segment
    int i;
    for (i = 0; i < len; i++){
        get_user(kbuf[i], buff++);
    }
    
    //Cast to ints
    int* intBuffer = (int*)kbuf; 
    
    //Write ints directly to the device
    iowrite32(intBuffer[0], virt_addr + REG_A_OFFSET);
    iowrite32(intBuffer[1], virt_addr + REG_B_OFFSET);
    
    //Free up allocation!
    kfree(intBuffer);
    return i;
}

static void __exit my_exit(void){
    unregister_chrdev(major, DEVICE_NAME);
    iounmap((void*)virt_addr);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ECEN449 Student (and others)");
MODULE_DESCRIPTION("Multiply peripheral driver");

module_init(my_init);
module_exit(my_exit);

    //iowrite32(7, virt_addr + REG_A_OFFSET);
    //iowrite32(2, virt_addr + REG_B_OFFSET);
    //printk("Read %d from register 2\n", ioread32(virt_addr+8));
