#include <stdint.h>

#ifndef QLUX_TRAPS_H
#define QLUX_TRAPS_H

struct qlux_trap {
    uint32_t trap_pc;
    void (*trap_ptr)(int);
};

extern struct qlux_trap qlux_traps[];

enum {
    QLUX_TRAP_FSTART = 0,
};

#endif /* QLUX_TRAPS_H */
