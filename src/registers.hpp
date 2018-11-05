#include <vector>
#include <cstdint>

#pragma once

class Registers
{
    std::vector<uint32_t> registers;
    uint32_t program_counter;

  public:
    Registers();
    void set_register(int index, uint32_t value);
    uint32_t get_register(int index);
    void set_program_counter(uint32_t value); //should enforce multiple of 4 or throw exception??
    uint32_t get_program_counter();
    void advance_program_counter(); //for maintainablitiy and neatness
    
};
