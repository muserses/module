#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

/**
 * Macro to set SCCR
 * value: value to set
 * processor: processor to use
 * op1: operation code 1
 * crn: register n
 * crm: register m
 * op2: operation code 2
 */
#define WRITE_SCCR(value, processor, op1, crn, crm, op2) \
asm volatile ("mcr " #processor "," #op1 ", %0," #crn "," #crm "," #op2 "" :: "r" (value))

/**
 * Macro to get SCCR
 * value: value to set
 * processor: processor to use
 * op1: operation code 1
 * crn: register n
 * crm: register m
 * op2: operation code 2
 */
#define READ_SCCR(value, processor, op1, crn, crm, op2)	 \
asm volatile ("mrc " #processor "," #op1 ", %0," #crn "," #crm "," #op2 "" : "=r" (value))


/*! \def WRITE_AVCR(value)
    Macro to set ACVR register
    value is used to read/write value
 */
#define WRITE_AVCR(value)               WRITE_SCCR(value, p15, 0, c15, c9, 0)

/*! \def WRITE_AVCR(value)
    Macro to get PMCR register
    value is used to read/write value
 */
#define READ_AVCR(value)                READ_SCCR(value,  p15, 0, c15, c9, 0)


/**
 * int perf_monitor_init(void)
 * @initialize performance counter
 * @return execution result
 */
static int perf_monitor_init(void)
{
        /** enable user-mode access to the performance counter */
        WRITE_AVCR(0x1);

        printk(KERN_INFO "enable user-mode access to the performance counter!\n");

        return 0;
}

/**
 * void perf_monitor_exit(void)
 * @exit performance counter
 */
static void perf_monitor_exit(void)
{
        /** disable user-mode access to the performance counter */
        WRITE_AVCR(0x0);

        printk(KERN_INFO "disable user-mode access to the performance counter!\n");
}


module_init(perf_monitor_init);

module_exit(perf_monitor_exit);

//MODULE_LICENSE("GPL");
