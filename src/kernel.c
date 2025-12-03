#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include terminal.h

#if defined(__linux__)
#error "YOU ARE NOT USING A CROSS COMPILER"
#endif

#if !defined(__i386__)
#error "YOU NEED A ix86-elf compiler"
#endif


void kernel_main(void)
{   
    gdt_install();

    terminal_initialize();

    terminal_writestring("ELLO GOVNA \n");
}