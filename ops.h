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
	{1, 0, 0, 0, "Undefined", 0x00},
	{2, 0, 0, 0, "Undefined", 0x00},
	{3, 0, 0, 0, "Undefined", 0x00},
	{4, 0, 0, 0, "Undefined", 0x00},
	{5, 0, 0, 0, "Undefined", 0x00},
	{6, 2, direct, 5, "ASL", 0x00},
	{7, 0, 0, 0, "Undefined", 0x00},
	{8, 0, 0, 0, "Undefined", 0x00},
	{9, 0, 0, 0, "Undefined", 0x00},
	{10, 2, implied_accumulator, 2, "ASL", 0x00},
	{11, 0, 0, 0, "Undefined", 0x00},
	{12, 0, 0, 0, "Undefined", 0x00},
	{13, 0, 0, 0, "Undefined", 0x00},
	{14, 3, absolute, 6, "ASL", 0x00},
	{15, 0, 0, 0, "Undefined", 0x00},
	{16, 2, relative, 2, "BPL", 0x00},
	{17, 0, 0, 0, "Undefined", 0x00},
	{18, 0, 0, 0, "Undefined", 0x00},
	{19, 0, 0, 0, "Undefined", 0x00},
	{20, 0, 0, 0, "Undefined", 0x00},
	{21, 0, 0, 0, "Undefined", 0x00},
	{22, 0, 0, 0, "Undefined", 0x00},
	{23, 0, 0, 0, "Undefined", 0x00},
	{24, 1, implied, 2, "CLC", 0x00},
	{25, 0, 0, 0, "Undefined", 0x00},
	{26, 0, 0, 0, "Undefined", 0x00},
	{27, 0, 0, 0, "Undefined", 0x00},
	{28, 0, 0, 0, "Undefined", 0x00},
	{29, 0, 0, 0, "Undefined", 0x00},
	{30, 0, 0, 0, "Undefined", 0x00},
	{31, 0, 0, 0, "Undefined", 0x00},
  {32, 3, 0, absolute_long, "JSR", 0x00},
	{33, 2, direct_page_indirect_indexed, 6, "AND", 0x00},
	{34, 0, 0, 0, "Undefined", 0x00},
	{35, 2, stack_relative, 4, "AND", 0x00},
	{36, 3, direct, 2, "BIT", 0x00},
	{37, 2, direct_page_Xindexed, 3, "AND", 0x00},
	{38, 0, 0, 0, "Undefined", 0x00},
	{39, 2, direct_page_indirect_long, 6, "AND", 0x00},
	{40, 0, 0, 0, "Undefined", 0x00},
	{41, 2, immediate, 2, "AND", 0x00},
	{42, 0, 0, 0, "Undefined", 0x00},
	{43, 0, 0, 0, "Undefined", 0x00},
	{44, 3, absolute, 4, "BIT", 0x00},
	{45, 3, absolute, 4, "AND", 0x00},
	{46, 0, 0, 0, "Undefined", 0x00},
	{47, 4, absolute_long, 5, "AND", 0x00},
	{48, 2, relative, 2, "BIM", 0x00},
	{49, 2, direct_page_indirect_indexed, 5, "AND", 0x00},
	{50, 2, direct_page_indirect, 5, "AND", 0x00},
	{51, 2, stack_relative_indexed, 7, "AND", 0x00},
	{52, 2, direct_page_Xindexed, 4, "BIT", 0x00},
	{53, 2, direct_page_Xindexed, 4, "AND", 0x00},
	{54, 0, 0, 0, "Undefined", 0x00},
	{55, 2, direct_page_indirect_indexed_long, 6, "AND", 0x00},
	{56, 0, 0, 0, "Undefined", 0x00},
	{57, 3, absolute_Yindexed, 4, "AND", 0x00},
	{58, 0, 0, 0, "Undefined", 0x00},
	{59, 0, 0, 0, "Undefined", 0x00},
	{60, 3, absolute_Xindexed, 4, "BIT", 0x00},
	{61, 3, absolute_Xindexed, 4, "AND", 0x00},
	{62, 0, 0, 0, "Undefined", 0x00},
	{63, 4, absolute_indexed_long, 5, "AND", 0x00},
	{64, 0, 0, 0, "Undefined", 0x00},
  {65, 2, direct_page_indirect_indexed, 0, "EOR", 0x00},
	{66, 0, 0, 0, "Undefined", 0x00},
	{67, 0, 0, 0, "Undefined", 0x00},
	{68, 0, 0, 0, "Undefined", 0x00},
	{69, 0, 0, 0, "Undefined", 0x00},
	{70, 0, 0, 0, "Undefined", 0x00},
	{71, 0, 0, 0, "Undefined", 0x00},
	{72, 0, 0, 0, "Undefined", 0x00},
  {73, 3, block_move, 0, "MVN", 0x00},
	{74, 0, 0, 0, "Undefined", 0x00},
	{75, 0, 0, 0, "Undefined", 0x00},
	{76, 0, 0, 0, "Undefined", 0x00},
	{77, 0, 0, 0, "Undefined", 0x00},
	{78, 0, 0, 0, "Undefined", 0x00},
	{79, 0, 0, 0, "Undefined", 0x00},
	{80, 2, relative, 2, "BVC", 0x00},
	{81, 0, 0, 0, "Undefined", 0x00},
  {82, 2, direct_page_indirect, 0, "EOR", 0x00},
	{83, 0, 0, 0, "Undefined", 0x00},
  {84, 3, block_move, 0, "MVN", 0x00},
	{85, 0, 0, 0, "Undefined", 0x00},
	{86, 0, 0, 0, "Undefined", 0x00},
	{87, 0, 0, 0, "Undefined", 0x00},
	{88, 1, implied, 2, "CLI", 0x00},
	{89, 0, 0, 0, "Undefined", 0x00},
	{90, 0, 0, 0, "Undefined", 0x00},
	{91, 0, 0, 0, "Undefined", 0x00},
	{92, 0, 0, 0, "Undefined", 0x00},
	{93, 0, 0, 0, "Undefined", 0x00},
	{94, 0, 0, 0, "Undefined", 0x00},
	{95, 0, 0, 0, "Undefined", 0x00},
	{96, 0, 0, 0, "Undefined", 0x00},
	{97, 2, direct_page_indirect_indexed, 6, "ADC", 0x00},
	{98, 0, 0, 0, "Undefined", 0x00},
	{99, 2, stack_relative, 4, "ADC", 0x00},
	{100, 0, 0, 0, "Undefined", 0x00},
	{101, 2, 0, 3, "ADC", 0x00},
	{102, 0, 0, 0, "Undefined", 0x00},
	{103, 2, direct_page_indirect_long, 2, "ADC", 0x00},
	{104, 0, 0, 0, "Undefined", 0x00},
	{105, 2, immediate, 2, "ADC", 0x00},
	{106, 0, 0, 0, "Undefined", 0x00},
	{107, 0, 0, 0, "Undefined", 0x00},
	{108, 0, 0, 0, "Undefined", 0x00},
	{109, 3, absolute, 4, "ADC", 0x00},
	{110, 0, 0, 0, "Undefined", 0x00},
	{111, 4, absolute_long, 5, "ADC", 0x00},
	{112, 2, relative, 2, "BVS", 0x00},
	{113, 2, direct_page_indirect_indexed, 5, "ADC", 0x00},
	{114, 2, direct_page_indirect, 5, "ADC", 0x00},
  {115, 2, stack_relative_indexed, 7, "ADC", 0x00},
	{116, 0, 0, 0, "Undefined", 0x00},
	{117, 2, direct_page_Xindexed, 4, "ADC", 0x00},
	{118, 0, 0, 0, "Undefined", 0x00},
	{119, 2, direct_page_indirect_indexed_long, 6, "ADC", 0x00},
	{120, 0, 0, 0, "Undefined", 0x00},
	{121, 3, absolute_Yindexed, 4, "ADC", 0x00},
	{122, 0, 0, 0, "Undefined", 0x00},
	{123, 0, 0, 0, "Undefined", 0x00},
	{124, 0, 0, 0, "Undefined", 0x00},
	{125, 3, absolute_Xindexed, 4, "ADC", 0x00},
	{126, 0, 0, 0, "Undefined", 0x00},
	{127, 4, absolute_indexed_long, 5, "ADC", 0x00},
	{128, 2, relative, 3, "BRA", 0x00},
	{129, 0, 0, 0, "Undefined", 0x00},
	{130, 3, relative_long, 4, "BRL", 0x00},
	{131, 0, 0, 0, "Undefined", 0x00},
	{132, 0, 0, 0, "Undefined", 0x00},
	{133, 0, 0, 0, "Undefined", 0x00},
	{134, 0, 0, 0, "Undefined", 0x00},
	{135, 0, 0, 0, "Undefined", 0x00},
	{136, 0, 0, 0, "Undefined", 0x00},
	{137, 2, immediate, 2, "BIT", 0x00},
	{138, 0, 0, 0, "Undefined", 0x00},
	{139, 0, 0, 0, "Undefined", 0x00},
	{140, 0, 0, 0, "Undefined", 0x00},
	{141, 0, 0, 0, "Undefined", 0x00},
	{142, 0, 0, 0, "Undefined", 0x00},
	{143, 0, 0, 0, "Undefined", 0x00},
	{144, 2, relative, 2, "BCC", 0x00},
	{145, 0, 0, 0, "Undefined", 0x00},
	{146, 0, 0, 0, "Undefined", 0x00},
	{147, 0, 0, 0, "Undefined", 0x00},
	{148, 0, 0, 0, "Undefined", 0x00},
	{149, 0, 0, 0, "Undefined", 0x00},
	{150, 0, 0, 0, "Undefined", 0x00},
	{151, 0, 0, 0, "Undefined", 0x00},
	{152, 0, 0, 0, "Undefined", 0x00},
	{153, 0, 0, 0, "Undefined", 0x00},
	{154, 0, 0, 0, "Undefined", 0x00},
	{155, 0, 0, 0, "Undefined", 0x00},
	{156, 0, 0, 0, "Undefined", 0x00},
	{157, 0, 0, 0, "Undefined", 0x00},
	{158, 0, 0, 0, "Undefined", 0x00},
	{159, 0, 0, 0, "Undefined", 0x00},
	{160, 0, 0, 0, "Undefined", 0x00},
	{161, 0, 0, 0, "Undefined", 0x00},
	{162, 0, 0, 0, "Undefined", 0x00},
	{163, 0, 0, 0, "Undefined", 0x00},
	{164, 0, 0, 0, "Undefined", 0x00},
	{165, 0, 0, 0, "Undefined", 0x00},
	{166, 0, 0, 0, "Undefined", 0x00},
	{167, 0, 0, 0, "Undefined", 0x00},
	{168, 0, 0, 0, "Undefined", 0x00},
	{169, 0, 0, 0, "Undefined", 0x00},
	{170, 0, 0, 0, "Undefined", 0x00},
	{171, 0, 0, 0, "Undefined", 0x00},
	{172, 0, 0, 0, "Undefined", 0x00},
	{173, 0, 0, 0, "Undefined", 0x00},
	{174, 0, 0, 0, "Undefined", 0x00},
	{175, 0, 0, 0, "Undefined", 0x00},
  {211, 0, 0, 0, "Undefined", 0x00},
  {176, 2, relative, 2, "BCC", 0x00},
	{177, 0, 0, 0, "Undefined", 0x00},
	{178, 0, 0, 0, "Undefined", 0x00},
	{179, 0, 0, 0, "Undefined", 0x00},
	{180, 0, 0, 0, "Undefined", 0x00},
	{181, 0, 0, 0, "Undefined", 0x00},
	{182, 0, 0, 0, "Undefined", 0x00},
	{183, 0, 0, 0, "Undefined", 0x00},
	{184, 1, implied, 2, "CLV", 0x00},
	{185, 0, 0, 0, "Undefined", 0x00},
	{186, 0, 0, 0, "Undefined", 0x00},
	{187, 0, 0, 0, "Undefined", 0x00},
	{188, 0, 0, 0, "Undefined", 0x00},
	{189, 0, 0, 0, "Undefined", 0x00},
	{190, 0, 0, 0, "Undefined", 0x00},
	{191, 0, 0, 0, "Undefined", 0x00},
	{192, 0, 0, 0, "Undefined", 0x00},
	{193, 2, direct_page_indirect_indexed, 6, "CMP", 0x00},
	{194, 0, 0, 0, "Undefined", 0x00},
	{195, 2, relative, 4, "CMP", 0x00},
	{196, 0, 0, 0, "Undefined", 0x00},
	{197, 2, direct, 3, "CMP", 0x00},
	{198, 0, 0, 0, "Undefined", 0x00},
	{199, 2, direct_page_indirect_long, 6, "CMP", 0x00},
	{200, 0, 0, 0, "Undefined", 0x00},
	{201, 0, 0, 0, "Undefined", 0x00},
	{202, 0, 0, 0, "Undefined", 0x00},
	{203, 0, 0, 0, "Undefined", 0x00},
	{204, 0, 0, 0, "Undefined", 0x00},
	{205, 3, absolute, 4, "CMP", 0x00},
	{206, 0, 0, 0, "Undefined", 0x00},
	{207, 4, absolute_long, 5, "CMP", 0x00},
	{208, 2, relative, 2, "BNE", 0x00},
	{209, 2, direct_page_indirect_indexed, 5, "CMP", 0x00},
	{210, 0, 0, 0, "Undefined", 0x00},
	{212, 0, 0, 0, "Undefined", 0x00},
	{213, 0, 0, 0, "Undefined", 0x00},
	{214, 0, 0, 0, "Undefined", 0x00},
	{215, 0, 0, 0, "Undefined", 0x00},
	{216, 1, implied, 2, "CLD", 0x00},
	{217, 0, 0, 0, "Undefined", 0x00},
	{218, 0, 0, 0, "Undefined", 0x00},
	{219, 0, 0, 0, "Undefined", 0x00},
	{220, 0, 0, 0, "Undefined", 0x00},
	{221, 0, 0, 0, "Undefined", 0x00},
	{222, 0, 0, 0, "Undefined", 0x00},
	{223, 0, 0, 0, "Undefined", 0x00},
	{224, 0, 0, 0, "Undefined", 0x00},
	{225, 0, 0, 0, "Undefined", 0x00},
	{226, 0, 0, 0, "Undefined", 0x00},
	{227, 0, 0, 0, "Undefined", 0x00},
	{228, 0, 0, 0, "Undefined", 0x00},
	{229, 0, 0, 0, "Undefined", 0x00},
	{230, 0, 0, 0, "Undefined", 0x00},
	{231, 0, 0, 0, "Undefined", 0x00},
	{232, 0, 0, 0, "Undefined", 0x00},
	{233, 0, 0, 0, "Undefined", 0x00},
	{234, 0, 0, 0, "Undefined", 0x00},
	{235, 0, 0, 0, "Undefined", 0x00},
	{236, 0, 0, 0, "Undefined", 0x00},
	{237, 0, 0, 0, "Undefined", 0x00},
  {238, 0, 0, 0, "Undefined", 0x00},
	{239, 0, 0, 0, "Undefined", 0x00},
	{240, 2, relative, 2, "BEQ", 0x00},
	{241, 0, 0, 0, "Undefined", 0x00},
	{242, 0, 0, 0, "Undefined", 0x00},
	{243, 0, 0, 0, "Undefined", 0x00},
	{244, 0, 0, 0, "Undefined", 0x00},
	{245, 0, 0, 0, "Undefined", 0x00},
	{246, 0, 0, 0, "Undefined", 0x00},
	{247, 0, 0, 0, "Undefined", 0x00},
	{248, 0, 0, 0, "Undefined", 0x00},
	{249, 0, 0, 0, "Undefined", 0x00},
	{250, 0, 0, 0, "Undefined", 0x00},
	{251, 0, 0, 0, "Undefined", 0x00},
	{252, 0, 0, 0, "Undefined", 0x00},
	{253, 0, 0, 0, "Undefined", 0x00},
	{254, 0, 0, 0, "Undefined", 0x00},
	{255, 0, 0, 0, "Undefined", 0x00}
};

#endif
