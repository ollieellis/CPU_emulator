#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>


using namespace std;

void Memory::load_instructions_into_memory(Instructions instructions_obj) 
{ 
    cout << "\npoop " << instructions_obj.instructions[0];
    for (size_t i = 0; i < instructions_obj.size / sizeof(instructions_obj.instructions[0]); i++)
    {
        cout << "\ninst at i " << instructions_obj.instructions[i];
        memory[0x10000000 + i*4] = instructions_obj.instructions[i];
    }
    cout << hex << "value in mem: " << memory[0x10000000] << endl;
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