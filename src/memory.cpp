#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include <algorithm>

using namespace std;

Memory::Memory()
{
    //only allocating each element once it is written to, when reading, return 0 if key does not exist
}

void Memory::set_address(int address, unsigned char data)
{
    memory[address] = data;
}

unsigned char Memory::get_address(int address)
{
    if (memory.find(address) == memory.end())
    {
        return 0; //if the address has not been allocated yet
    }
    return memory[address];
}

void Memory::load_instructions_in(uint32_t *instructions, int number_of_instructions)
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        set_n_bytes(4, Memory::ADDR_INSTR + i * 4, instructions[i]);
    }
}

void Memory::set_n_bytes(int n, int start_address, uint32_t value) //maximum of 4 bytes
{
    if (is_output(n, start_address))
    {
        cerr << dec << "putchar should be: " << value << endl;
        cerr << "putchar result: ";
        putchar(value); //gets least significant 8 bits i think
        cerr << endl;
    }

    for (int i = 0; i < n; i++)
    {
        int index = start_address + i;
        set_address(index, Bitwise_helper::extract_char(n - 1 - i, value));
        cerr << hex << "address set at 0x" << index << ": " << (int)memory[index] << endl;
    }
}

uint32_t Memory::get_n_bytes(int n, int start_address) //maximum of 4 bytes
{
    if (is_input(n, start_address))
    {
        unsigned char input = getchar();
        set_address(start_address, input); //needed because we return the memory at this address to this function
    }

    uint32_t result = 0;
    for (int i = 0; i < n; i++)
    {
        result += get_address(start_address + (n - 1 - i)) << (i * 8);
    }
    return result;
}

bool Memory::is_input(int number_of_bytes_being_got, int start_address)//checks if any bytes being gotten are in the getc range
{   
    for(int i = start_address; i < start_address + number_of_bytes_being_got; i++)
    {
       if (i >= Memory::ADDR_GETC && i < Memory::ADDR_GETC + Memory::ADDR_GETC_LENGTH)
       {
           return true;
       }
    }
    return false;
}

bool Memory::is_output(int number_of_bytes_being_set, int start_address)//checks if any bytes being set are in the putc range
{
    for(int i = start_address; i < start_address + number_of_bytes_being_set; i++)
    {
       if (i >= Memory::ADDR_PUTC && i < Memory::ADDR_PUTC + Memory::ADDR_PUTC_LENGTH)
       {
           return true;
       }
    }
    return false;
}
