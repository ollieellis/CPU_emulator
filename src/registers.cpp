#include "registers.hpp"

Registers::Registers()
{
    program_counter = 0;
    registers.reserve(32);
    fill(registers.begin(), registers.end(), 0); //init to 0
}

void Registers::set_register(int index, uint32_t value)
{
    registers[index] = value;
}
uint32_t Registers::get_register(int index)
{
    return registers[index];
}
void Registers::set_program_counter(uint32_t value)
{
    program_counter = value;
}
uint32_t Registers::get_program_counter()
{
    return program_counter;
}