/*
=========================================================================================================
Author : Quinn Olney

Purpose: kernal, self explainatory, initializes the OS
=========================================================================================================
*/


#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"

void kernel_main(void)
{
    terminal_initialize();
    gdt_install();
    idt_install();
    isr_install();
    irq_install();

    asm volatile("sti");  // enable interrupts


    while (1) { }
}