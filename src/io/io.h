#ifndef IO_H
#define IO_H

#include <stdint.h>

unsigned char insb(unsigned short port);
unsigned short insw(unsigned short port);

void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);
void outl(uint16_t port, uint32_t value);

#endif
