.section .text
.global irq1
irq1:
    cli                 # disable interrupts
    pushl $33           # push interrupt number (IRQ1)
    jmp isr_common_stub # jump to common C handler
