#include "gdt.h"
#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct gdt_entry gdt_entries[3];
static struct gdt_ptr gdt_descriptor;

extern void gdt_flush(uint32_t gdt_ptr_addr);

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].limit_low = (uint16_t)(limit & 0xFFFF);
    gdt_entries[num].base_low = (uint16_t)(base & 0xFFFF);

    gdt_entries[num].base_middle = (uint8_t)((base >> 16) & 0xFF);
    gdt_entries[num].access = access;

    gdt_entries[num].granularity = (uint8_t)(((limit >> 16) & 0x0F) | (gran & 0xF0));
    gdt_entries[num].base_high = (uint8_t)((base >> 24) & 0xFF);
}

void gdt_install(void)
{   
    /*Null Descriptor*/
    gdt_set_gate(0,0,0,0,0);

    gdt_set_gate(1, 0x00000000, 0x000FFFFF, 0x9A, 0xCF);

    gdt_set_gate(2, 0x00000000, 0x000FFFFF, 0x92, 0xCF);

    gdt_descriptor.limit = (uint16_t)(sizeof(gdt_entries) - 1);
    gdt_descriptor.base = (uint32_t)(uint32_t)&gdt_entries;

    gdt_flush((uint32_t)& gdt_descriptor);
    
}