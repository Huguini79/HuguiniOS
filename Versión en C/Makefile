FILES = ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/memory/memory.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -fno-pic -fno-pie -no-pie \
        -falign-jumps -falign-functions -falign-labels \
        -falign-loops -fstrength-reduce -fomit-frame-pointer \
        -finline-functions -Wno-unused-function -Wno-cpp \
        -Wno-unused-parameter -nostdlib -nostartfiles \
        -nodefaultlibs -Wall -O2 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/HuguiniOS.img
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/HuguiniOS.img
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/HuguiniOS.img
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/HuguiniOS.img
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin
	
./bin/kernel.bin: $(FILES)
	i686-linux-gnu-ld -g --relocatable $(FILES) -o ./bin/kernelfull.o
	i686-linux-gnu-gcc -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O2 -nostdlib ./bin/kernelfull.o
  
./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin
	
./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o
	
./build/kernel.o: ./src/kernel.c
	i686-linux-gnu-gcc $(INCLUDES) $(FLAGS) -fno-pic -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o
	
./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o: ./src/idt/idt.c
	i686-linux-gnu-gcc $(INCLUDES) -I./src/idt $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/memory/memory.o: ./src/memory/memory.c
	i686-linux-gnu-gcc $(INCLUDES) -I./src/memory $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o
	
 clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/HuguiniOS.img
	rm -rf ./bin/os.bin
	rm -rf ${FILES}
	rm -rf ./build/kernelfull.o
