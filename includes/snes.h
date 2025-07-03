#ifndef __SNES_H__
#define __SNES_H__

#include <stdint.h>

#define RAM_SIZE	1 << 7

enum reg_name {X = 0, Y = 1, A = 2, P = 3};

uint8_t		*lorom_mapper(uint16_t addr, uint8_t bank);

int		ram_writter(uint16_t addr, uint8_t bank, uint16_t data, uint8_t*(*mapper)(uint16_t, uint8_t));
int		is_mad1();

void		*rom_reader(uint16_t addr, uint8_t bank);
void		*sram_reader(uint16_t addr, uint8_t bank);
void		write_register(enum reg_name reg, uint8_t data);
void		write_carry(int carry);

uint8_t		read_register(enum reg_name reg);
uint8_t		read_carry(); 

#endif
