#include <stdint.h>
#include <stddef.h>
#include "includes/snes.h"
#include "includes/ops.h"

uint8_t	snes_registers[4];

int is_mad1()
{
  return (1);
}

void *rom_reader(uint16_t addr, uint8_t bank)
{
  return (NULL);
}

void *sram_reader(uint16_t addr, uint8_t bank)
{
  return (NULL);
}

void write_register(enum reg_name reg, uint8_t data)
{
  snes_registers[reg] = data;
}

/* TODO : Handle cycles(abstracttion layer ?)
   Handle all registers properly */
uint8_t read_register(enum reg_name reg)
{
  return (snes_registers[reg]);
}

uint8_t	read_carry()
{
  return (read_register(P) & 1);
}

void	set_carry(int carry)
{
  write_register(P, carry & 1);
}
