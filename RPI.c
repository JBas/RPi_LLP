#include "RPI.h"

bcm2835_peripheral gpio = {GPIO_BASE};

int map_peripheral(bcm2835_peripheral *p) {
	
	// Open /dev/mem
	if ((p->mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
		printf("Failed to open /dev/mem; try checking permissions.\n");
		return -1;
	}

	// https://goo.gl/WfFdAZ
	p->map = mmap(
		NULL,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		p->mem_fd,	// file descriptor to physical memory virtual file '/dev/mem'
		p->addr_p	// Address in physical map that we want this memory block to expose
		);

	if (p->map == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	// https://goo.gl/6hm81K
	p->adrr = (volatile unsigned int *)p->map;

	return 0;
}

void unmap_peripheral(bcm2835_peripheral *p) {
	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}