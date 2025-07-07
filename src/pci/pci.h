#ifndef PCI_H
#define PCI_H

#include <stdint.h>

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint8_t  pciConfigReadByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

uint16_t pciCheckVendor(uint8_t bus, uint8_t slot);
void checkDevice(uint8_t bus, uint8_t device);
void checkAllBuses(void);
void checkBus(uint8_t bus);
void checkFunction(uint8_t bus, uint8_t device, uint8_t function);

uint8_t getVendorID(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getBaseClass(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getSubClass(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getSecondaryBus(uint8_t bus, uint8_t device, uint8_t function);

#endif
