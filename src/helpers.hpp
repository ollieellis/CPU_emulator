#include <string>
#pragma once


using namespace std;


struct Instructions
  {
    uint32_t *instructions;
    int size;

  public:
    Instructions(uint32_t *instructions_in, int size_in) : instructions(instructions_in),  size(size_in) {};  
  };


class File_io
{
public:
  static Instructions get_binary_file(string file_path);
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
};


