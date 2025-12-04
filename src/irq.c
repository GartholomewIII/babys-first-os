/*
=========================================================================================================
Author : Quinn Olney

Purpose: impliments PIC which routes interrupts to the CPU
=========================================================================================================
*/



#include "idt.h"
#include "irq.h"
#include "terminal.h"

extern void irq1();

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

static inline void outb(uint16_t port, uint8_t value )
{
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void irq_install(void)
{

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);


    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);

    outb(PIC1_DATA, 0xFD);  
    outb(PIC2_DATA, 0xFF);  
}

