//
// ri/controller.h: RAM interface controller.
//
// CEN64: Cycle-Accurate Nintendo 64 Emulator.
// Copyright (C) 2015, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef __ri_controller_h__
#define __ri_controller_h__
#include "common.h"

#define MAX_RDRAM_SIZE 0x800000U
#define MAX_RDRAM_SIZE_MASK (MAX_RDRAM_SIZE - 1U)

enum rdram_register {
#define X(reg) reg,
#include "ri/rdram_registers.md"
#undef X
  NUM_RDRAM_REGISTERS
};

#ifdef DEBUG_MMIO_REGISTER_ACCESS
extern const char *rdram_register_mnemonics[NUM_RDRAM_REGISTERS];
#endif

enum ri_register {
#define X(reg) reg,
#include "ri/registers.md"
#undef X
  NUM_RI_REGISTERS
};

#ifdef DEBUG_MMIO_REGISTER_ACCESS
extern const char *ri_register_mnemonics[NUM_RI_REGISTERS];
#endif

struct ri_controller {
  struct bus_controller *bus;

  uint32_t rdram_regs[NUM_RDRAM_REGISTERS];
  uint32_t regs[NUM_RI_REGISTERS];

  uint64_t force_ram_alignment;
  uint8_t ram[MAX_RDRAM_SIZE];
};

cen64_cold int ri_init(struct ri_controller *ri, struct bus_controller *bus);

cen64_hot int read_rdram(void *opaque, uint32_t address, uint32_t *word);
cen64_hot int write_rdram(void *opaque, uint32_t address, uint32_t word, uint32_t dqm);

cen64_cold int read_rdram_regs(void *opaque, uint32_t address, uint32_t *word);
cen64_cold int read_ri_regs(void *opaque, uint32_t address, uint32_t *word);

cen64_cold int write_rdram_regs(void *opaque, uint32_t address, uint32_t word, uint32_t dqm);
cen64_cold int write_ri_regs(void *opaque, uint32_t address, uint32_t word, uint32_t dqm);

#endif

