.section .text
.extern isr_handler_c      # same C handler

.global irq1
irq1:
    cli
    pusha

    # PIC remapped to 0x20; IRQ1 = 0x20 + 1 = 33
    pushl $33
    call isr_handler_c
    add $4, %esp

    popa
    iret
