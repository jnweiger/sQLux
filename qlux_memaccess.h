/*
 * (c) UQLX - see COPYRIGHT
 */

#ifndef QLUX_MEMACCESS_H
#define QLUX_MEMACCESS_H

unsigned int m68k_read_memory_8(unsigned int addr);
unsigned int m68k_read_memory_16(unsigned int addr);
unsigned int m68k_read_memory_32(unsigned int addr);
void m68k_write_memory_8(unsigned int addr, unsigned int val);
void m68k_write_memory_16(unsigned int addr, unsigned int val);
void m68k_write_memory_32(unsigned int addr, unsigned int val);
void m68k_write_memory_16_direct(unsigned int addr, unsigned int val);
void m68k_write_memory_32_direct(unsigned int addr, unsigned int val);

#endif /* QLUX_MEMACCESS_H */

