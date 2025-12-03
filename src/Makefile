# Cross-compiler
CC=i686-elf-gcc
AS=i686-elf-as
LD=i686-elf-ld

CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-builtin
ASFLAGS=
LDFLAGS=-T linker.ld

# Object files (added terminal.o)
OBJS = \
    boot.o \
    gdt.o gdt_flush.o \
    idt.o idt_flush.o \
    isr.o isr_stubs.o \
    irq.o irq_stubs.o \
    terminal.o \
    kernel.o

TARGET = myos.bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# C compilation rules
gdt.o: gdt.c gdt.h
	$(CC) $(CFLAGS) -c gdt.c -o gdt.o

idt.o: idt.c idt.h
	$(CC) $(CFLAGS) -c idt.c -o idt.o

isr.o: isr.c isr.h idt.h
	$(CC) $(CFLAGS) -c isr.c -o isr.o

irq.o: irq.c irq.h idt.h
	$(CC) $(CFLAGS) -c irq.c -o irq.o

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c -o terminal.o

kernel.o: kernel.c gdt.h idt.h isr.h irq.h terminal.h
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

# Assembly rules
boot.o: boot.s
	$(AS) boot.s -o boot.o

gdt_flush.o: gdt_flush.s
	$(AS) gdt_flush.s -o gdt_flush.o

idt_flush.o: idt_flush.s
	$(AS) idt_flush.s -o idt_flush.o

isr_stubs.o: isr_stubs.s
	$(AS) isr_stubs.s -o isr_stubs.o

irq_stubs.o: irq_stubs.s
	$(AS) irq_stubs.s -o irq_stubs.o

# Run with QEMU
run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
