#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>

using namespace std;

void Memory::load_instructions_in(uint32_t *instructions, int number_of_instructions)
{
    for (size_t i = 0; i < number_of_instructions; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int index = Memory::ADDR_INSTR + i * 4 + j ;
            memory[index] = Binary_helper::extract_char(3-j, instructions[i]);
            cout << hex << "instruction loaded into memory " << index  << ": "<< (int)memory[index] << endl;
        }
    }
}

void Memory::fill_range(int start, int end, char value)
{
    fill(memory.begin() + start, memory.begin() + end + 1, value);
}

Memory::Memory()
{
    memory.reserve(0x30000008);
    fill_range(0x20000000, 0x24000000, 0);
}