#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "ops.h"
#include "snes.h"

int main()
{
  int       fd;
  uint8_t   buffer[4097];
  t_header  head;
  t_vector  vectors;

  fd = open("rom", O_RDONLY);
  printf("Opened in fd %d\n", fd);
  /* Moving pointer to header
  TODO : remove hardcoded value */
  lseek(fd, 0x007FC0, SEEK_SET);
  read(fd, buffer, 255);
  parse_header(buffer, &head, &vectors);
  display_header(&head);
  printf("%02X\n", vectors.fields.reset);
  print_array(vectors.data, VECTORS_SIZE);
  lseek(fd, 0x007FC0, SEEK_SET);
  read(fd, buffer, 4096);
  print_array(buffer, 255);
  decompile_function(buffer, 4000);
}

void display_header(t_header *head)
{
  char      title[23];

  memcpy(title, head->fields.title, 22);
  title[22] = '\0';
  printf("Titre : %s\n", title);
  printf("ROM speed : %x\n", head->fields.rom_speed);
  printf("chipset : %x\n", head->fields.chipset);
  printf("ROM size : %x\n", head->fields.rom_size);
  printf("RAM size : %x\n", head->fields.ram_size);
  printf("country : %x\n", head->fields.country);
  printf("DEV ID : %x\n", head->fields.dev_id);
  printf("ROM Version : %x\n", head->fields.rom_version);

  print_array(head->data, HEADER_SIZE);
}

void parse_header(uint8_t *buffer, t_header *head, t_vector *vectors)
{
  memcpy(head->data, buffer, HEADER_SIZE);
  memcpy(vectors->data, &buffer[HEADER_SIZE], VECTORS_SIZE);
  print_array(vectors->data, VECTORS_SIZE);
}

void decompile_function(uint8_t *buffer, int size)
{
  int i;
  struct s_op *current;

  i = 0;
  while (i < size)
  {
    current = &ops[buffer[i]];
//    printf("op : %x\n", current->opcode);
    printf("%s", current->name);
    switch (current->adm)
      {
      case implied:
	break;
      case immediate:
      case immediate_memory:
      case immediate_index:
	printf(" $%02X", buffer[i + 1]);
	break;
      case block_move:
	printf(" $%02X $%02X %03d", buffer[i + 1], buffer[i + 2], buffer[i + 3]);
	break;
      case absolute_long:
	printf(" $%02X%02X%02X", buffer[i + 1], buffer[i + 2], buffer[i + 3]);
	break;
      default:
	for (int j = 1; j < current->size; ++j)
	  {
	    printf(" %02X", buffer[i + j]);
	  }
      }
    i += MAX(current->size, 1);
    printf("\n");
//    printf("%d\n", i);
  }
}

void print_array(uint8_t *buffer, int size)
{
  for (int i = 0; i < size; ++i)
    {
      if (i % 12 == 0 && i != 0)
        printf("\n");
      else if (i % 4 == 0 && i != 0)
        printf(" ");
      printf("%02X ", *buffer);
      buffer++;
    }
    printf("\n");
}
