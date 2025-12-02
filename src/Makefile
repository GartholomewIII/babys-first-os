# Cross-compiler
CC=i686-elf-gcc
AS=i686-elf-as
LD=i686-elf-ld
CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-builtin
ASFLAGS=-32
LDFLAGS=-m32 -T linker.ld

# Files
OBJS=boot.o gdt_flush.o gdt.o kernel.o
TARGET=myos.bin


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)


gdt.o: gdt.c gdt.h
	$(CC) $(CFLAGS) -c gdt.c -o gdt.o

kernel.o: kernel.c gdt.h
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o


gdt_flush.o: gdt_flush.s
	$(AS) $(ASFLAGS) gdt_flush.s -o gdt_flush.o

boot.o: boot.s
	$(AS) $(ASFLAGS) boot.s -o boot.o


run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)