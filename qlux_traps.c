#include <stddef.h>

#include "m68k.h"
#include "QLtraps.h"
#include "qlux_traps.h"
#include "QL68000.h"
#include "xcodes.h"

struct qlux_trap qlux_traps[] = {
    {
	.trap_ptr = FastStartup,
    },
    {
	.trap_pc = 0xDEADBEEF,
    }};

int qlux_illg_hook(int opcode)
{
	printf("OPCODE: %x\n", opcode);
	switch (opcode) {
	case FSTART_CMD_CODE:
		FastStartup(m68k_get_reg(NULL, M68K_REG_PC));
		return 1;
	default:
		printf("Unknown Illegal Instruction Trap\n");
		exit(0);
	}
	return 0;
}

void qlux_pc_hook(int pc)
{
	int trap_idx;

	printf("PC: %x\n", pc);

	if (pc > 65536)
		printf("ERROR\n");

	while (qlux_traps[trap_idx].trap_pc != 0xDEADBEEF)
	{

		if (pc == qlux_traps[trap_idx].trap_pc)
		{
			qlux_traps[trap_idx].trap_ptr(pc);
		}

		trap_idx++;
	}
}
