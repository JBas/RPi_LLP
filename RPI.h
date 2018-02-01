#include <stdio.h>

// memory management library
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

#define BCM2708_PERI_BASE   0x20000000

// offset into the GPIO address space (pg. 90)
#define GPIO_BASE           (BCM2708_PERI_BASE + 0x200000)

// @TODO: figure out what this is for
#define BLOCK_SIZE          (4*1024)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
#define INP_GPIO(g)         *(gpio.addr + (g/10)) &= ~(7 << ((g%10) * 3))
#define OUT_GPIO(g)         *(gpio.addr + (g/10)) |= (1 << ((g%10) * 3))
#define SET_GPIO_ALT(g, a)  *(gpio.addr + (g/10)) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << (((g)%10) * 3))
#define GPIO_SET            *(gpio.addr + 7) // sets bits that are 1, ignores those that are 0
#define GPIO_CLR            *(gpio.addr + 10) // sets clears bits which are 1, ignore those that are 0

#define GPIO_READ(g)        *(gpio.addr + 13) &= (1 << g)

// IO Access
struct bcm2835_peripheral_header {
    unsigned ling addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
}; typedef bcm2835_peripheral

bcm2835_peripheral gpio = {GPIO_BASE};

extern bcm2835_peripheral gpio; // for files that need gpio variable
