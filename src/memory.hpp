#include <vector>
#include "helpers.hpp"

class Memory
{
  std::vector<unsigned char> memory;

public:
  static const int ADDR_NULL = 0x00000000;
  static const int ADDR_NULL_LENGTH = 0x4;
  static const int ADDR_INSTR = 0x10000000;
  static const int ADDR_INSTR_LENGTH = 0x10000000;
  static const int ADDR_DATA = 0x20000000;
  static const int ADDR_DATA_LENGTH = 0x4000000;
  static const int ADDR_GETC = 0x30000000;
  static const int ADDR_GETC_LENGTH = 0x4;
  static const int ADDR_PUTC = 0x30000004;
  static const int ADDR_PUTC_LENGTH = 0x4;

public:
  Memory();
  void set_data(int offset, unsigned char data);
  unsigned char get_data(int offset);
  void fill_range(int start, int end, char value);
  void load_instructions_in(uint32_t *instructions, int number_of_instructions);
  uint32_t get_instruction(int offset);
};