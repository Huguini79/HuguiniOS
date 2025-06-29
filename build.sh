clear
make clean && make all
qemu-system-i386 -drive format=raw,file=./bin/HuguiniOS.img
