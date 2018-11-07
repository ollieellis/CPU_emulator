#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>

using namespace std;

Memory::Memory()
{
    memory.reserve(0x30000008);
    fill_range(Memory::ADDR_DATA, Memory::ADDR_DATA + Memory::ADDR_DATA_LENGTH, 0);
}

void Memory::set_address(int address, unsigned char data)
{
    if (address >= Memory::ADDR_PUTC && address < Memory::ADDR_PUTC + 4)
    {
        putchar(data);
    }
    memory[address] = data;
}

unsigned char Memory::get_address(int address)
{
    if (address >= Memory::ADDR_GETC && address < Memory::ADDR_GETC + 4) // do this later, need clarification on all the read operations
    {
        unsigned char input = getchar();
        set_address(address, input); //needed because we return the memory at the address to this function
    }
    return memory[address];
}

void Memory::fill_range(int start, int end, char value)
{
    fill(memory.begin() + start, memory.begin() + end + 1, value);
}

void Memory::load_instructions_in(uint32_t *instructions, int number_of_instructions)
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int index = Memory::ADDR_INSTR + i * 4 + j;
            memory[index] = Bitwise_helper::extract_char(3 - j, instructions[i]);
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
    for (int i = 0; i < n; i++)
    {
        result += get_address(address + (n - 1 - i)) << (i * 8);
    }
    // cout << "Poop";
    return result;
}
