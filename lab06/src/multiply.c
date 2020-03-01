#include <linux/module.h>   // Needed by all modules
#include <linux/kernel.h>   // Needed for KERN_* and printk
#include <linux/init.h>     // Needed for __init and __exit macros
#include <asm/io.h>         // Needed for IO reads and writes
#include "xparameters.h"    // Needed for IO reads and writes
#include <linux/ioport.h>   // Used for io memory allocation
//Kernel sources: /home/ugrads/p/philipsmith/new/ecen449/lab05/local_kern/linux-3.14
// From xparameters.h, physical address of multiplier
#define PHY_ADDR XPAR_MULTIPLY_0_S00_AXI_BASEADDR 
// Size of physical address range for multiply
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
    
    int bytes_read = 0;
    int* kernelBuffer = (int*)kmalloc(length * sizeof(int), GFP_KERNEL);
    
    kernelBuffer[0] = ioread32(virt_addr + REG_A_OFFSET);
    kernelBuffer[1] = ioread32(virt_addr + REG_B_OFFSET);
    kernelBuffer[2] = ioread32(virt_addr + REG_O_OFFSET);
    
    char* kbuff = (char*)kernelBuffer;
    
    int i;
    for (i = 0; i < length; i++) {
        put_user(*(kbuff++), buffer++);
        bytes_read++;
    }
    
    kfree(kbuff);
    return bytes_read;
}

static ssize_t device_write(struct file *filp, 
                            const char *buff, 
                            size_t len, 
                            loff_t * off)
{
    char* kbuf = (char*)kmalloc((len + 1) * sizeof(char), GFP_KERNEL);
    
    int i;
    
    for (i = 0; i < len; i++){
        get_user(kbuff[i], buff++);
    }
    
    kernelBuffer[len] = '\0';
    
    int* intBuffer = (int*)kernelBuffer; 
    
    iowrite32(intBuffer[0], virt_addr + REG_A_OFFSET);
    iowrite32(intBuffer[0], virt_addr + REG_B_OFFSET);
    
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