#include <string>
#pragma once



class File_io
{
public:
  int number_of_instructions;
  uint32_t *instructions;

public:
  void get_binary_file(std::string file_path);
};


class Binary_helper
{
public:
  template <class T>
  static inline T rotate_left(T v, std::int32_t shift);
  template <class T>
  static inline T rotate_right(T v, std::int32_t shift);
  static unsigned int swap_bits(unsigned int n, unsigned int p1, unsigned int p2);
  static unsigned int swap_bytes(unsigned int n, unsigned int p1, unsigned int p2);
  static uint32_t extract_bits(int start_position, int length, uint32_t word) ;
  static unsigned char extract_char(int nth_char, uint32_t word); //nth char can only be 0 8 16 or 24
};
