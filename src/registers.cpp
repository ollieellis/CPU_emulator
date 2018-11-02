#include "registers.hpp"

Registers::Registers()
{
    program_counter = 0;
    registers.reserve(32);
    fill(registers.begin(), registers.end(), 0); //init to 0
}