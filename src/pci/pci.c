#include "../kernel.h"
#include "pci.h"
#include "keyboard/keyboard.h"
#include "io/io.h"
#include "idt/idt.h"

#include <stdint.h>

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;
  
    // Create configuration address as per Figure 1
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
  
    // Write out the address
    outl(0xCF8, address);
    // Read in the data
    // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
    tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}          
              
uint16_t pciCheckVendor(uint8_t bus, uint8_t slot) {
    uint16_t vendor, device;
    /* Try and read the first configuration register. Since there are no
     * vendors that == 0xFFFF, it must be a non-existent device. */
    if ((vendor = pciConfigReadWord(bus, slot, 0, 0)) != 0xFFFF) {
       device = pciConfigReadWord(bus, slot, 0, 2);
       
    } return (vendor);
}

 void checkDevice(uint8_t bus, uint8_t device) {
     uint8_t function = 0;
     uint16_t vendorID;
     uint16_t headerType;

     vendorID = getVendorID(bus, device, function);
     if (vendorID == 0xFFFF) return; // Device doesn't exist
     checkFunction(bus, device, function);
     headerType = getHeaderType(bus, device, function);
     if( (headerType & 0x80) != 0) {
         // It's a multi-function device, so check remaining functions
         for (function = 1; function < 8; function++) {
             if (getVendorID(bus, device, function) != 0xFFFF) {
                 checkFunction(bus, device, function);
             }
         }
     }
 }
   void checkAllBuses(void) {
     uint8_t function;
     uint8_t bus;
     uint16_t headerType;

     headerType = getHeaderType(0, 0, 0);
     if ((headerType & 0x80) == 0) {
         // Single PCI host controller
         checkBus(0);
     } else {
         // Multiple PCI host controllers
         for (function = 0; function < 8; function++) {
             if (getVendorID(0, 0, function) != 0xFFFF) break;
             bus = function;
             checkBus(bus);
         }
     }
 }
 
 void checkBus(uint8_t bus) {
     uint8_t device;

     for (device = 0; device < 32; device++) {
         checkDevice(bus, device);
     }
 }
 
  void checkFunction(uint8_t bus, uint8_t device, uint8_t function) {
     uint8_t baseClass;
     uint8_t subClass;
     uint8_t secondaryBus;

     baseClass = getBaseClass(bus, device, function);
     subClass = getSubClass(bus, device, function);
     if ((baseClass == 0x6) && (subClass == 0x4)) {
         secondaryBus = getSecondaryBus(bus, device, function);
         checkBus(secondaryBus);
     }
 }
 
 uint8_t pciConfigReadByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000;
    outl(0xCF8, address);
    return (uint8_t)((inl(0xCFC) >> ((offset & 3) * 8)) & 0xFF);
}

uint8_t getHeaderType(uint8_t bus, uint8_t device, uint8_t function) {
    return pciConfigReadByte(bus, device, function, 0x0E);
}

uint8_t getBaseClass(uint8_t bus, uint8_t device, uint8_t function) {
    return pciConfigReadByte(bus, device, function, 0x0B);
}

uint8_t getSubClass(uint8_t bus, uint8_t device, uint8_t function) {
    return pciConfigReadByte(bus, device, function, 0x0A);
}

uint8_t getSecondaryBus(uint8_t bus, uint8_t device, uint8_t function) {
    return pciConfigReadByte(bus, device, function, 0x19);
}

uint8_t getVendorID(uint8_t bus, uint8_t device, uint8_t function) {
    return pciConfigReadWord(bus, device, function, 0x00);
}
