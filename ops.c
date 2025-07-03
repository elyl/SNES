#include "includes/ops.h"
#include "includes/snes.h"

/* Prototype : void func(adressing_mode am, void *data); */

void ops_adc(uint8_t opcode, void *data)
{
  reg_name	reg;
  uint8_t	new_value;
  int		carry;

  reg = A;
  carry = read_carry();
  switch (opcode)
    {
    case 0x61:
      break;
    case 0x63:
      break;
    case 0x65:
      break;
    case 0x67:
      break;
    case 0x69:
      to_add = (uint8_t)*data;
      break;
    case 0x6D:
      break;
    case 0x6F:
      break;
    }
  new_value = carry + old_value + to_add;
  write_register(reg, new_value);
}
