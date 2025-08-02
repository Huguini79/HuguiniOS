![HuguiniOS](https://github.com/user-attachments/assets/8626dd3d-c1d2-4648-8adf-29595efa4268)

HuguiniOS is an open source 32 bit protected mode operating system made by Huguini79 in 3 months, this operating system is from scratch.

The operating system(including IDT interrumptions, disk driver, gdt descriptor, kheap, string, pparser, paging, memory heap etc, I/O ports, A SHELL, ATA driver, my own bootloader without using GRUB, AND MY OWN INTERPRETER CALLED HUGUINILANGUAGE), it's wrote in C and Assembly, and it's being constantly updated.

The bin folder is where the compiled version of the operating system resides(you can emulate with QEMU the os.bin or HuguiniOS.img file), the build folder is where the object files of the HuguiniOS source code resides, and the src folder is where the HuguiniOS source code resides, you can see the files in Assembly or in C.

Note: The operating system only runs on newer versions of QEMU, if you run it on older versions or in specific real hardware, it might crash.

I don't know if in some hardware might run, or others repositories like "AssemblyDrivers" with that boot.bin might run on real hardware.

I hope you enjoy my operating system and if you want, you can do your own version of HuguiniOS. IT'S OPEN SOURCE!

For anyone who is interested, I learned how to make my own operating system using the book Developing a multi-thread kernel from scratch of Daniel McCarthy, he explains very well the process from creating a real mode bootloader to a multi-thread 32 bit kernel in protected mode.
