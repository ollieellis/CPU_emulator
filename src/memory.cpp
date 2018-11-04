#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>

using namespace std;

Memory::Memory()
{
    memory.reserve(0x30000008);
    fill_range(Memory::ADDR_DATA, Memory::ADDR_DATA + Memory::ADDR_DATA_LENGTH, 0);
   // fill_range(Memory::ADDR_INSTR, Memory::ADDR_INSTR + Memory::ADDR_INSTR_LENGTH, 0);
}

void Memory::set_address(int address, unsigned char data)
{
    memory[address] = data; 
}

unsigned char Memory::get_address(int address)
{
    return memory[address];
}

void Memory::fill_range(int start, int end, char value)
{
    fill(memory.begin() + start, memory.begin() + end + 1, value);
}

void Memory::load_instructions_in(uint32_t *instructions, int number_of_instructions)
{
    for (size_t i = 0; i < number_of_instructions; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int index = Memory::ADDR_INSTR + i * 4 + j;
            memory[index] = Binary_helper::extract_char(3 - j, instructions[i]);
            cout << hex << "instruction loaded into memory 0x" << index << ": " << (int)memory[index] << endl;
        }
    }
}

// uint32_t Memory::get_instruction(int offset)
// {
//     //offset must be multiple of 4 or throw error
//     int start_index = Memory::ADDR_INSTR + offset;
//     return (memory[start_index] << 24) + (memory[start_index + 1] << 16) + (memory[start_index + 2] << 8) + (memory[start_index + 3] << 0);
// }


uint32_t Memory::get_n_bytes(int n, int address)
{
    uint32_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        result += get_address(address + (n - 1 - i)) << (i * 8);
    }
    // cout << "Poop";
    return result;
}

