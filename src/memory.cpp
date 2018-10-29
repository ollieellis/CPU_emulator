#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>

using namespace std;

void Memory::load_instructions_into_memory(uint32_t *instructions, int number_of_instructions)  
{ 
    for (int i = 0; i < number_of_instructions; i++)
    {
        cout << "instruction loaded into memory: " << instructions[i] << endl;
        memory[0x10000000 + i*4] = instructions[i];
    }
}

void Memory::set_range_of_memory(int start, int end, uint32_t value)
{
    fill(memory.begin() + start, memory.begin() + end, value);
}

Memory::Memory()
{
    memory.reserve(0x30000008);
    set_range_of_memory(0x20000000, 0x24000000, 0);
}