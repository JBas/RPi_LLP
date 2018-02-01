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

// IO Access
struct bcm2835_peripheral_header {
    unsigned ling addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
}; typedef bcm2835_peripheral

bcm2835_peripheral gpio = {GPIO_BASE};

extern bcm2835_peripheral gpio; // for files that need gpio variable
