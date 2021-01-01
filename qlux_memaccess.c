/*
 * (c) UQLX - see COPYRIGHT
 */


/* define memory access fns */
#include "QL68000.h"
#include "memaccess.h"
#include "general.h"
#include "qx_proto.h"
#include "SDL2screen.h"
#include <SDL_endian.h>

static void *m68k_calc_addr(unsigned int addr)
{
    return theROM + addr;
}

unsigned int m68k_read_memory_8(unsigned int addr)
{
    addr&=ADDR_MASK;

    if (addr > RTOP)
        return 0;

    if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        return ReadHWByte(addr);
    }

    return *(uint8_t *)m68k_calc_addr(addr);
}

unsigned int m68k_read_memory_16(unsigned int addr)
{
    addr &=ADDR_MASK;

    if (addr > RTOP)
        return 0;

    if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        return ((w16)ReadHWWord(addr));
    }

    return SDL_SwapBE16(*(uint16_t *)m68k_calc_addr(addr));
}

unsigned int m68k_read_memory_32(unsigned int addr)
{
    addr &= ADDR_MASK;

    if (addr > RTOP)
        return 0;

    if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        return ((w32)ReadWord(addr)<<16)|(uw16)ReadWord(addr+2);
    }

    return SDL_SwapBE32(*(uint32_t *)m68k_calc_addr(addr));
}

void m68k_write_memory_8(unsigned int addr, unsigned int val)
{
    addr &= ADDR_MASK;

    if (addr > RTOP)
        return;

    if ((addr >= qlscreen.qm_lo) && (addr <= qlscreen.qm_hi)) {
	    *((w8*)theROM+addr) = val;
        QLSDLUpdateScreenByte(addr-qlscreen.qm_lo, val);
    } else if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        WriteHWByte(addr, val);
    } else if (addr > QL_ROM_SIZE) {
        *(uint8_t *)m68k_calc_addr(addr) = val;
    }
}

void m68k_write_memory_16(unsigned int addr, unsigned int val)
{
    addr &= ADDR_MASK;

    if (addr > RTOP)
        return;

    if ((addr >= qlscreen.qm_lo) && (addr <= qlscreen.qm_hi)) {
        *(uint16_t *)m68k_calc_addr(addr) = SDL_SwapBE16(val);
        QLSDLUpdateScreenWord(addr-qlscreen.qm_lo, val);
    } else if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        WriteHWWord(addr, val);
    } else if (addr >= QL_ROM_SIZE) {
        *(uint16_t *)m68k_calc_addr(addr) = SDL_SwapBE16(val);
    }
}

void m68k_write_memory_32(unsigned int addr, unsigned int val)
{
    addr &= ADDR_MASK;

    if (addr > RTOP)
        return;

    if ((addr >= qlscreen.qm_lo) && (addr <= qlscreen.qm_hi)) {
        *(uint32_t *)m68k_calc_addr(addr) = SDL_SwapBE32(val);
        QLSDLUpdateScreenLong(addr-qlscreen.qm_lo, val);
    } else if ((addr >= QL_INTERNAL_IO_BASE) &&
                (addr < (QL_INTERNAL_IO_BASE + QL_INTERNAL_IO_SIZE))) {
        WriteHWWord(addr, val >> 16);
        WriteHWWord(addr + 2, val);
    } else if (addr >= QL_ROM_SIZE) {
        *(uint32_t *)m68k_calc_addr(addr) = SDL_SwapBE32(val);
    }
}

