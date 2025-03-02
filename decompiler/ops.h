#ifndef __OPS_H__
#define __OPS_H__

#include <stdint.h>

#define HEADER_SIZE   32
#define VECTORS_SIZE  12

#define MAX(x, y) (x > y) ? x : y;

enum addressing_mode {
  implied,
  immediate_memory,
  immediate_index,
  immediate,
  relative,
  relative_long,
  direct,
  direct_page_Xindexed,
  direct_page_Yindexed,
  direct_page_indirect,
  direct_page_indirect_indexed,
  direct_page_indirect_long,
  direct_page_indirect_indexed_long,
  absolute,
  absolute_Xindexed,
  absolute_Yindexed,
  absolute_long,
  absolute_indexed_long,
  stack_relative,
  stack_relative_indexed,
  absolute_indirect,
  absolute_indirect_long,
  absolute_indexed_indirect,
  implied_accumulator,
  block_move};

struct s_header
{
  char      title[21];
  uint8_t   rom_speed;
  uint8_t   chipset;
  uint8_t   rom_size;
  uint8_t   ram_size;
  uint8_t   country;
  uint8_t   dev_id;
  uint8_t   rom_version;
  uint16_t  checksum;
  uint16_t  checksum2;
};

struct s_vector
{
  uint16_t  cop;
  uint16_t  brk;
  uint16_t  abrt;
  uint16_t  nmi;
  uint16_t  reset;
  uint16_t  irq;
};

struct s_op
{
  uint8_t                 opcode;
  int                     size;
  enum addressing_mode    adm;
  int                     cycles;
  char                    name[32];
  void                    (*fn)(uint8_t*);
};

typedef union u_header
{
  uint8_t data[HEADER_SIZE];
  struct s_header fields;
} t_header;

typedef union u_vector
{
  uint8_t data[VECTORS_SIZE];
  struct s_vector fields;
} t_vector;

void parse_header(uint8_t *buffer, t_header *head, t_vector *vectors);
void display_header(t_header *head);
void decompile_function(uint8_t *buffer, int size);

void print_array(uint8_t *buffer, int size);

struct s_op ops[256] = {
  {0, 2, stack_relative, 7, "BRK", 0x00},
  {1, 3, direct_page_indirect_indexed, 7, "ORA", 0x00},
  {2, 2, stack_relative, 7, "COP", 0x00}, /* Stack.interupt */
  {3, 2, stack_relative, 4, "ORA", 0x00},
  {4, 2, direct_page, 5, "TSB", 0x00},
  {5, 2, direct_page, 3, "ORA", 0x00},
  {6, 2, direct, 5, "ASL", 0x00},
  {7, 2, direct_page_indirect_long, 6, "ORA", 0x00},
  {8, 1, stack_relative, 3, "PHP", 0x00}, /* Strange */
  {9, 2, immediate, 2, "ORA", 0x00},
  {10, 2, implied_accumulator, 2, "ASL", 0x00},
  {11, 1, stack_relative, 4, "PHD", 0x00}, /* Strange */
  {12, 3, absolute, 6, "TSB", 0x00},
  {13, 3, absolute, 4, "ORA", 0x00},
  {14, 3, absolute, 6, "ASL", 0x00},
  {15, 4, absolute_long, 5, "ORA", 0x00},
  {16, 2, relative, 2, "BPL", 0x00},
  {17, 2, direct_page_indexed_indirect, 5, "ORA", 0x00},
  {18, 2, direct_page_indirect, 5, "ORA", 0x00},
  {19, 2, stack_relative_indexed, 7, "ORA", 0x00},
  {20, 2, direct_page, 5, "TRB", 0x00},
  {21, 2, direct_page_Xindexed, 4, "ORA", 0x00},
  {22, 2, direct_page_Xindexed, 6, "ASL", 0x00},
  {23, 2, direct_page_indirect_indexed_long, 6, "ORA", 0x00},
  {24, 1, implied, 2, "CLC", 0x00},
  {25, 3, absolute_Yindexed, 4, "ORA", 0x00},
  {26, 1, implied_accumulator, 2, "INC", 0x00},
  {27, 1, implied, 2, "TCS", 0x00},
  {28, 3, absolute, 6, "TRB", 0x00},
  {29, 3, absolute_indirect, 4, "ORA", 0x00},
  {30, 3, absolute_Xindexed, 7, "ASL", 0x00},
  {31, 4, absolute_indexed_long, 5, "ORA", 0x00},
  {32, 3, absolute, 6, "JSR", 0x00},
  {33, 2, direct_page_indirect_indexed, 6, "AND", 0x00},
  {34, 4, absolute_long, 8, "JSR", 0x00},
  {35, 2, stack_relative, 4, "AND", 0x00},
  {36, 3, direct, 2, "BIT", 0x00},
  {37, 2, direct_page_Xindexed, 3, "AND", 0x00},
  {38, 2, direct_page, 5, "ROL", 0x00},
  {39, 2, direct_page_indirect_long, 6, "AND", 0x00},
  {40, 1, stack_relative, 5, "PLK", 0x00}, /* Strange */
  {41, 2, immediate, 2, "AND", 0x00},
  {42, 1, implied_accumulator, 2, "ROL", 0x00},
  {43, 1, stack_relative, 5, "PLD", 0x00}, /* Strange */
  {44, 3, absolute, 4, "BIT", 0x00},
  {45, 3, absolute, 4, "AND", 0x00},
  {46, 3, absolute, 6, "ROL", 0x00},
  {47, 4, absolute_long, 5, "AND", 0x00},
  {48, 2, relative, 2, "BIM", 0x00},
  {49, 2, direct_page_indirect_indexed, 5, "AND", 0x00},
  {50, 2, direct_page_indirect, 5, "AND", 0x00},
  {51, 2, stack_relative_indexed, 7, "AND", 0x00},
  {52, 2, direct_page_Xindexed, 4, "BIT", 0x00},
  {53, 2, direct_page_Xindexed, 4, "AND", 0x00},
  {54, 2, direct_page_Xindexed, 6, "ROL", 0x00},
  {55, 2, direct_page_indirect_indexed_long, 6, "AND", 0x00},
  {56, 1, implied, 2, "SEC", 0x00},
  {57, 3, absolute_Yindexed, 4, "AND", 0x00},
  {58, 1, implied_accumulator, 2, "DEC", 0x00},
  {59, 1, implied, 2, "TSC", 0x00},
  {60, 3, absolute_Xindexed, 4, "BIT", 0x00},
  {61, 3, absolute_Xindexed, 4, "AND", 0x00},
  {62, 3, absolute_Xindexed, 7, "ROL", 0x00},
  {63, 4, absolute_indexed_long, 5, "AND", 0x00},
  {64, 1, absolute, 6, "RTI", 0x00}, /* placeholder adressing */
  {65, 2, direct_page_indirect_indexed, 0, "EOR", 0x00},
  {66, 2, 0, 0, "WDM", 0x00},
  {67, 2, stack_relative, 4, "EOR", 0x00},
  {68, 3, block_move, 1, "MVP", 0x00},
  {69, 2, direct, 3, "EOR", 0x00},
  {70, 2, direct_page_Xindexed, 5, "LSR", 0x00},
  {71, 2, direct_page_indirect_long, 6, "EOR", 0x00},
  {72, 1, stack_relative, 3, "PHA", 0x00}, /* Stange */
  {73, 2, immediate, 2, "EOR", 0x00},
  {74, 2, implied_accumulator, 2, "LSR", 0x00},
  {75, 1, stack_relative, 3, "PHK", 0x00}, /* Strange */
  {76, 3, absolute, 3, "JMP", 0x00},
  {77, 3, absolute, 4, "EOR", 0x00},
  {78, 3, absolute, 6, "LSR", 0x00},
  {79, 4, absolute_long, 5, "EOR", 0x00},
  {80, 2, relative, 2, "BVC", 0x00},
  {81, 2, direct_page_indirect_indexed, 5, "EOR", 0x00},
  {82, 2, direct_page_indirect, 5, "EOR", 0x00},
  {83, 2, stack_relative_indexed, 7, "EOR", 0x00},
  {84, 3, block_move, 1, "MVN", 0x00},
  {85, 2, direct_page_Xindexed, 4, "EOR", 0x00},
  {86, 2, direct_page_Xindexed, 6, "LSR", 0x00},
  {87, 2, direct_page_indirect_indexed_long, 6, "EOR", 0x00},
  {88, 1, implied, 2, "CLI", 0x00},
  {89, 3, absolute_Yindexed, 4, "EOR", 0x00},
  {90, 1, stack_relative, 3, "PHY", 0x00}, /* Strange */
  {91, 1, implied, 2, "TCD", 0x00},
  {92, 4, absolute_long, 4, "JMP", 0x00},
  {93, 3, absolute_Xindexed, 4, "EOR", 0x00},
  {94, 3, absolute_Yindexed, 7, "LSR", 0x00},
  {95, 4, absolute_indexed_long, 5, "EOR", 0x00},
  {96, 1, absolute, 6, "RTS", 0x00}, /* placeholder adressing */
  {97, 2, direct_page_indirect_indexed, 6, "ADC", 0x00},
  {98, 3, relative_long, 6, "PER", 0x00}, /* Strange */
  {99, 2, stack_relative, 4, "ADC", 0x00},
  {100, 2, direct_page, 3, "STZ", 0x00},
  {101, 2, 0, 3, "ADC", 0x00},
  {102, 2, direct_page, 5, "ROR", 0x00},
  {103, 2, direct_page_indirect_long, 2, "ADC", 0x00},
  {104, 1, stack_relative, 4, "PLA", 0x00}, /* Strange */
  {105, 2, immediate, 2, "ADC", 0x00},
  {106, 1, implied_accumulator, 2, "ROR", 0x00},
  {107, 1, absolute, 6, "RTL", 0x00}, /* placeholder adressing */
  {108, 3, absolute_indirect, 5, "JMP", 0x00},
  {109, 3, absolute, 4, "ADC", 0x00},
  {110, 3, absolute, 6, "ROR", 0x00},
  {111, 4, absolute_long, 5, "ADC", 0x00},
  {112, 2, relative, 2, "BVS", 0x00},
  {113, 2, direct_page_indirect_indexed, 5, "ADC", 0x00},
  {114, 2, direct_page_indirect, 5, "ADC", 0x00},
  {115, 2, stack_relative_indexed, 7, "ADC", 0x00},
  {116, 2, direct_page_Xindexed, 4, "STZ", 0x00},
  {117, 2, direct_page_Xindexed, 4, "ADC", 0x00},
  {118, 2, direct_page_Xindexed, 6, "ROR", 0x00},
  {119, 2, direct_page_indirect_indexed_long, 6, "ADC", 0x00},
  {120, 1, implied, 2, "SEO", 0x00},
  {121, 3, absolute_Yindexed, 4, "ADC", 0x00},
  {122, 1, stack_relative, 4, "PLY", 0x00}, /* Strange */
  {123, 1, implied, 2, "TDC", 0x00},
  {124, 3, absolute_indexed_indirect, 6, "JMP", 0x00},
  {125, 3, absolute_Xindexed, 4, "ADC", 0x00},
  {126, 3, absolute_Xindexed, 7, "ROR", 0x00},
  {127, 4, absolute_indexed_long, 5, "ADC", 0x00},
  {128, 2, relative, 3, "BRA", 0x00},
  {129, 2, direct_page_indirect_indexed, 6, "STA", 0x00},
  {130, 3, relative_long, 4, "BRL", 0x00},
  {131, 2, stack_relative, 4, "STA", 0x00},
  {132, 2, direct_page, 3, "STY", 0x00},
  {133, 2, direct_page, 3, "STA", 0x00},
  {134, 2, direct_page, 3, "STX", 0x00},
  {135, 2, direct_page_indirect_long, 6, "STA", 0x00},
  {136, 1, implied, 2, "DEY", 0x00},
  {137, 2, immediate, 2, "BIT", 0x00},
  {138, 1, implied, 2, "TXA", 0x00},
  {139, 1, stack_relative, 3, "PHB", 0x00}, /* Starnge */
  {140, 3, absolute, 4, "STY", 0x00},
  {141, 3, absolute, 4, "STA", 0x00},
  {142, 3, absolute, 4, "STX", 0x00},
  {143, 4, absolute_long, 5, "STA", 0x00},
  {144, 2, relative, 2, "BCC", 0x00},
  {145, 2, direct_page_indirect_indexed, 6, "STA", 0x00},
  {146, 2, direct_page_indirect, 5, "STA", 0x00},
  {147, 2, stack_relative_indirect, 7, "STA", 0x00},
  {148, 2, direct_page_Xindexed, 4, "STY", 0x00},
  {149, 2, direct_page_Xindexed, 4, "STA", 0x00},
  {150, 2, direct_page_Yindexed, 4, "STX", 0x00},
  {151, 2, direct_page_indirect_indexed_long, 6, "STA", 0x00},
  {152, 1, implied, 2, "TYA", 0x00},
  {153, 3, absolute_Yindexed, 5, "STA", 0x00},
  {154, 1, implied, 2, "TXS", 0x00},
  {155, 1, implied, 2, "TXY", 0x00}OB,
  {156, 3, absolute, 4, "STZ", 0x00},
  {157, 3, absolute_Xindexed, 5, "STA", 0x00},
  {158, 3, absolute_Xindexed, 5, "STZ", 0x00},
  {159, 4, absolute_indexed_long, 5, "STA", 0x00},
  {160, 2, immediate, 2, "LDY", 0x00},
  {161, 2, direct_page_indirect_indexed, 6, "LDA", 0x00},
  {162, 2, immediate, 2, "LDX", 0x00},
  {163, 2, stack_relative, 4, "LDA", 0x00},
  {164, 2, direct_page, 3, "LDY", 0x00},
  {165, 2, direct_page, 3, "LDA", 0x00},
  {166, 2, direct_page, 3, "LDX", 0x00},
  {167, 2, direct_page_indirect_long, 3, "LDA", 0x00},
  {168, 1, implied, 2, "TAY", 0x00},
  {169, 2, immediate, 2, "LDA", 0x00},
  {170, 1, implied, 2, "TAX", 0x00},
  {171, 1, stack_relative, 4, "PLB", 0x00},
  {172, 3, absolute, 4, "LDY", 0x00},
  {173, 3, absolute, 4, "LDA", 0x00},
  {174, 3, absolute, 4, "LDX", 0x00},
  {175, 4, absolute_long, 5, "LDA", 0x00},
  {176, 2, relative, 2, "BCC", 0x00},
  {177, 2, direct_page_indirect_indexed, 5, "LDA", 0x00},
  {178, 2, direct_page_indirect, 5, "LDA", 0x00},
  {179, 2, stack_relative_indexed, 7, "LDA", 0x00},
  {180, 3, absolute_Xindexed, 4, "LDY", 0x00},
  {181, 2, direct_page_Xindexed, 4, "LDA", 0x00},
  {182, 2, direct_page_Yindexed, 4, "LDX", 0x00},
  {183, 2, direct_page_indirect_long_indexed, 6, "LDA", 0x00},
  {184, 1, implied, 2, "CLV", 0x00},
  {185, 3, absolute_Yindexed, 4, "LDA", 0x00},
  {186, 1, implied, 2, "TSX", 0x00},
  {187, 1, implied, 2, "TYX", 0x00},
  {188, 3, absolute_Xindexed, 4, "LDY", 0x00},
  {189, 3, absolute_Xindexed, 4, "LDA", 0x00},
  {190, 3, absolute_Yindexed, 4, "LDX", 0x00},
  {191, 4, absolute_long_indexed, 5, "LDA", 0x00},
  {192, 2, immediate, 2, "CPY", 0x00},
  {193, 2, direct_page_indirect_indexed, 6, "CMP", 0x00},
  {194, 2, immediate, 3, "REP", 0x00},
  {195, 2, relative, 4, "CMP", 0x00},
  {196, 2, direct, 3, "CPY", 0x00},
  {197, 2, direct, 3, "CMP", 0x00},
  {198, 2, direct, 5, "DEC", 0x00},
  {199, 2, direct_page_indirect_long, 6, "CMP", 0x00},
  {200, 1, implied, 2, "INY", 0x00},
  {201, 2, immediate, 3, "CMP", 0x00},
  {202, 1, implied, 2, "DEX", 0x00},
  {203, 1, implied, 3, "WAI", 0x00},
  {204, 3, absolute, 4, "CPY", 0x00},
  {205, 3, absolute, 4, "CMP", 0x00},
  {206, 3, absolute, 7, "DEC", 0x00},
  {207, 4, absolute_long, 5, "CMP", 0x00},
  {208, 2, relative, 2, "BNE", 0x00},
  {209, 2, direct_page_indirect_indexed, 5, "CMP", 0x00},
  {210, 2, direct_page_indirect, 5, "CMP", 0x00},
  {211, 2, stack_relative_indexed, 7, "CMP", 0x00},
  {212, 2, direct_page_indirect, 6, "PEI", 0x00}, /* Strange */
  {213, 2, direct_page_Xindexed, 4, "CMP", 0x00},
  {214, 2, direct_page_Xindexed, 6, "DEC", 0x00},
  {215, 2, direct_page_indirect_indexed_long, 6, "CMP", 0x00},
  {216, 1, implied, 2, "CLD", 0x00},
  {217, 3, absolute_Yindexed, 4, "CMP", 0x00},
  {218, 1, stack_relative, 3, "PHX", 0x00}, /* Strange */
  {219, 1, implied, 3, "STP", 0x00},
  {220, 3, absolute_indirect_long, 6, "JMP", 0x00},
  {221, 3, absolute_Xindexed, 4, "CMP", 0x00},
  {222, 3, absolute_Xindexed, 7, "DEC", 0x00},
  {223, 4, absolute_indexed_long, 5, "CMP", 0x00},
  {224, 2, immediate, 2, "CPX", 0x00},
  {225, 2, direct_page_indirect_indexed, 6, "SBC", 0x00},
  {226, 2, immediate, 3, "SEP", 0x00},
  {227, 2, stack_relative, 4, "SBC", 0x00},
  {228, 2, direct, 3, "CPX", 0x00},
  {229, 2, direct_page, 3, "SBC", 0x00},
  {230, 2, direct, 5, "INC", 0x00},
  {231, 2, direct_page_indirect_long, 7, "SBC", 0x00},
  {232, 1, implied, 2, "INX", 0x00},
  {233, 2, immediate, 2, "SBC", 0x00},
  {234, 1, implied, 2, "NOP", 0x00},
  {235, 1, implied, 3, "XBA", 0x00},
  {236, 3, absolute, 4, "CPX", 0x00},
  {237, 3, absolute, 4, "SBC", 0x00},
  {238, 3, absolute, 6, "INC", 0x00},
  {239, 4, absolute_long, 5, "SBC", 0x00},
  {240, 2, relative, 2, "BEQ", 0x00},
  {241, 2, direct_page_indirect_indexed, 5, "SBC", 0x00},
  {242, 2, direct_page_indirect, 5, "SBC", 0x00},
  {243, 2, stack_relative_indexed, 7, "SBC", 0x00},
  {244, 3, absolute, 5, "PEA", 0x00}, /* Strange */
  {245, 2, direct_page_Xindexed, 4, "SBC", 0x00},
  {246, 2, direct_page_Xindexed, 6, "INC", 0x00},
  {247, 2, direct_page_indirect_indexed_long, 6, "SBC", 0x00},
  {248, 1, implied, 2, "SED", 0x00},
  {249, 3, absolute_Yindexed, 4, "SBC", 0x00},
  {250, 1, stack_relative, 4, "PLX", 0x00}, /* Strange */
  {251, 1, implied, 2, "XCE", 0x00},
  {252, 3, absolute_indexed_indirect, 8, "JSR", 0x00},
  {253, 3, absolute_Xindexed, 4, "SBC", 0x00},
  {254, 3, absolute_Xindexed, 7, "INC", 0x00},
  {255, 4, absolute_indexed_long, 5, "SBC", 0x00}
};

#endif
