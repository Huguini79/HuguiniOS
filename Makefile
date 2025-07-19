FILES = ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/memory/memory.o ./build/io/io.asm.o ./build/memory/heap/heap.o ./build/memory/heap/kheap.o ./build/disk/disk.o ./build/string/string.o ./build/memory/paging/paging.o ./build/memory/paging/paging.asm.o ./build/disk/streamer.o ./build/gdt/gdt.o ./build/programs/calculator.o ./build/programs/hola.o ./build/keyboard/keyboard.o ./build/programs/guibonita.o ./build/programs/editordetexto.o ./build/games/menu.o ./build/games/tickdown.o ./build/graphics/graphics.o ./build/pci/pci.o

INCLUDES = -I./src

FLAGS = -g -ffreestanding -fno-pic -fno-pie -no-pie \
        -falign-jumps -falign-functions -falign-labels \
        -falign-loops -fstrength-reduce -fomit-frame-pointer \
        -finline-functions -Wno-unused-function -Wno-cpp \
        -Wno-unused-parameter -nostdlib -nostartfiles \
        -nodefaultlibs -Wall -Os -Iinc

DIRS = ./build ./bin ./build/io ./build/idt ./build/memory ./build/memory/heap ./build/disk ./build/string ./build/memory/paging./build/gdt./build/programs ./build/keyboard ./build/games ./build/graphics ./build/pci

$(shell mkdir -p $(DIRS))


all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/HuguiniOS.img
	rm -rf ./bin/HuguiniOS.iso
	rm -rf ./bin/os.bin
	dd if=/dev/zero of=./bin/HuguiniOS.img bs=512 count=400
	dd if=./bin/boot.bin of=./bin/HuguiniOS.img bs=512 count=1 conv=notrunc
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/HuguiniOS.iso
	dd if=./bin/kernel.bin of=./bin/HuguiniOS.img bs=512 seek=1 conv=notrunc
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/HuguiniOS.iso
	dd if=hola.txt of=./bin/HuguiniOS.img bs=512 seek=50 conv=notrunc
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/HuguiniOS.iso
	
./bin/kernel.bin: $(FILES)
	i686-elf-ld -g --relocatable $(FILES) -o ./bin/kernelfull.o
	i686-elf-gcc -w -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O2 -nostdlib -fno-use-linker-plugin ./bin/kernelfull.o
    
	i686-elf-ld -g -T ./src/linker.ld -o ./bin/kernel.elf ./bin/kernelfull.o


  
./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin
	
./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o
	
./build/kernel.o: ./src/kernel.c
	i686-elf-gcc -w $(INCLUDES) $(FLAGS) -fno-pic -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o
	
./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o: ./src/idt/idt.c
	i686-elf-gcc -w $(INCLUDES) -I./src/idt $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/memory/memory.o: ./src/memory/memory.c
	i686-elf-gcc -w $(INCLUDES) -I./src/memory $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o
	
./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o
	
./build/memory/heap/heap.o: ./src/memory/heap/heap.c
	i686-elf-gcc -w $(INCLUDES) $(FLAGS) -std=gnu99 -c $< -o $@
	
./build/memory/heap/kheap.o: ./src/memory/heap/kheap.c
	i686-elf-gcc -w $(INCLUDES) -I./src/memory/heap $(FLAGS) -std=gnu99 -c ./src/memory/heap/kheap.c -o ./build/memory/heap/kheap.o
	
./build/memory/paging/paging.o: ./src/memory/paging/paging.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/memory/paging $(FLAGS) -std=gnu99 -c ./src/memory/paging/paging.c -o ./build/memory/paging/paging.o
	
./build/memory/paging/paging.asm.o: ./src/memory/paging/paging.asm
	nasm -f elf -g ./src/memory/paging/paging.asm -o ./build/memory/paging/paging.asm.o
	
./build/disk/disk.o: ./src/disk/disk.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/disk/ $(FLAGS) -std=gnu99 -c ./src/disk/disk.c -o ./build/disk/disk.o
	
./build/string/string.o: ./src/string/string.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/string $(FLAGS) -std=gnu99 -c ./src/string/string.c -o ./build/string/string.o
	
./build/disk/streamer.o: ./src/disk/streamer.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/disk/ $(FLAGS) -std=gnu99 -c ./src/disk/streamer.c -o ./build/disk/streamer.o

./build/gdt/gdt.o: ./src/gdt/gdt.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/gdt/ $(FLAGS) -std=gnu99 -c ./src/gdt/gdt.c -o ./build/gdt/gdt.o
	
./build/programs/calculator.o: ./src/programs/calculator.c
	i686-elf-gcc -w $(INCLUDES) -I ./src/programs/ $(FLAGS) -std=gnu99 -c ./src/programs/calculator.c -o ./build/programs/calculator.o
	
./build/programs/hola.o: ./src/programs/hola.c
	i686-elf-gcc -w $(INCLUDES) -I./src/programs $(FLAGS) -std=gnu99 -c ./src/programs/hola.c -o ./build/programs/hola.o
	
./build/keyboard/keyboard.o: ./src/keyboard/keyboard.c
	i686-elf-gcc -w $(INCLUDES) -I./src/keyboard $(FLAGS) -std=gnu99 -c ./src/keyboard/keyboard.c -o ./build/keyboard/keyboard.o
	
./build/programs/guibonita.o: ./src/programs/guibonita.c
	i686-elf-gcc -w $(INCLUDES) -I./src/programs $(FLAGS) -std=gnu99 -c ./src/programs/guibonita.c -o ./build/programs/guibonita.o
	
./build/programs/editordetexto.o: ./src/programs/editordetexto.c
	i686-elf-gcc -w $(INCLUDES) -I./src/programs $(FLAGS) -std=gnu99 -c ./src/programs/editordetexto.c -o ./build/programs/editordetexto.o
	
./build/games/menu.o: ./src/games/menu.c
	i686-elf-gcc -w $(INCLUDES) -I./src/games $(FLAGS) -std=gnu99 -c ./src/games/menu.c -o ./build/games/menu.o
	
./build/games/tickdown.o: ./src/games/tickdown.c
	i686-elf-gcc -w $(INCLUDES) -I./src/games $(FLAGS) -std=gnu99 -c ./src/games/tickdown.c -o ./build/games/tickdown.o
	
./build/graphics/graphics.o: ./src/graphics/graphics.c
	i686-elf-gcc -w $(INCLUDES) -I./src/graphics $(FLAGS) -std=gnu99 -c ./src/graphics/graphics.c -o ./build/graphics/graphics.o
	
./build/pci/pci.o: ./src/pci/pci.c
	i686-elf-gcc -w $(INCLUDES) -I./src/pci $(FLAGS) -std=gnu99 -c ./src/pci/pci.c -o ./build/pci/pci.o
	
 clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/HuguiniOS.img
	rm -rf ./bin/os.bin
	rm -rf ./bin/HuguiniOS.iso
	rm -rf ${FILES}
	rm -rf ./build/kernelfull.o
