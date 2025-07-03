#include <stdlib.h>
#include <string.h>
#include "includes/snes.h"

/* TODO : Ajouter les cycles */
uint8_t *lorom_mapper(uint16_t addr, uint8_t bank)
{
  static uint8_t	ram[RAM_SIZE];

  if (bank <= 0x3f)
    {
      /* LowRAM */
      if (addr <= 0x1FFF)
	return (&ram[addr]);
      /* $2000 - $20ff : Unused */
      /* PPU1, APU, Hardware registers */
      if (addr >= 0X20FF && addr <= 0x21FF)
	return (0);
      /* $2200 - $2FFF : Unused */
      /* DSP, SuperFX */
      if (addr >= 0x2FFF && addr <= 0x2FFF)
	return (0);
      /* Joypad registers */
      if (addr >= 0x4000 && addr <= 0x40FF)
	return (0);
      /* $4100 - $41FF : Unused */
      /* DMA, PPU2, Hardware registers */
      if (addr >= 0x4200 && addr <= 0x44FF)
	return (0);
      /* $4500 - $5FFF : Unused */
      /* $6000 - $7FFF : enhancement chips memory */
      /* LoROM */
      if (addr >= 0x8000)
	return (rom_reader(addr, bank));
    }
  else if (bank <= 0x6F)
    {
      /* ROM if not MAD-1 */
      if (addr <= 0x7FFF && is_mad1())
	return (rom_reader(addr, bank));
      /* LoROM */
      if (addr >= 0x8000)
	return (rom_reader(bank, addr));
    }
  else if (bank <= 0x7D)
    {
      /* SRAM */
      if (addr  <= 0x7FFF)
	return (sram_reader(addr, bank));
      /* ROM */
      if (addr >= 0x8000)
	return (rom_reader(addr, bank));
    }
  else if (bank == 0x7E)
    {
      /* Low RAM */
      if (addr <= 0x1FFF)
	return (&ram[addr]);
      /* High RAM */
      else if (addr <= 0x7FFF)
	return (&ram[addr]);
      /* Extended RAM */
      else
	return (&ram[addr]);
    }
  else if (bank == 0x7F)
    {
      /* RAM */
      return (&ram[addr]);
    }
  else if (bank <= 0xBF)
    {
      /* ROM */
      return (rom_reader(addr, bank));
    }
  else if (bank <= 0xEF)
    {
      /* ROM */
      return (rom_reader(addr, bank));
    }
  else if (bank <= 0xfd)
    {
      /* ROM */
      return (rom_reader(addr, bank));
    }
  else
    {
      /* SRAM */
      if (addr <= 0x7FFF)
	return (sram_reader(addr, bank));      
      /* LoROM */
      else
	return (rom_reader(addr, bank));
    }
  return (NULL);
}

/* What should i do with 16 bits data ? */
int ram_writter(uint16_t addr, uint8_t bank, uint16_t data, uint8_t* (*mapper)(uint16_t, uint8_t))
{
  uint8_t	*ptr;

  ptr = mapper(addr, bank);
  if (ptr == NULL)
    return (1);
  *ptr = data;
  return (0);
}
