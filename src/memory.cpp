#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include "exceptions.hpp"
#include <algorithm>

using namespace std;

Memory::Memory()
{
    //only allocating each element once it is written to, when reading, return 0 if key does not exist
}

//==============================================private functions==============================================

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

void Memory::set_n_bytes(int n, int start_address, uint32_t value) //maximum of 4 bytes
{
    for (int i = 0; i < n; i++)
    {
        int index = start_address + i;
        set_address(index, Bitwise_helper::extract_char(n - 1 - i, value));
        cerr << hex << "address set at 0x" << index << ": " << (int)memory[index] << endl;
    }
}

uint32_t Memory::get_n_bytes(int n, int start_address) //maximum of 4 bytes
{
    uint32_t result = 0;
    for (int i = 0; i < n; i++)
    {
        result += get_address(start_address + (n - 1 - i)) << (i * 8);
    }
    return result;
}

//==============================================public functions==============================================

void Memory::set_instructions(uint32_t *instructions, int number_of_instructions)
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        set_n_bytes(4, Memory::ADDR_INSTR + i * 4, instructions[i]);
    }
}

uint32_t Memory::get_instruction(int address)
{
    if (!is_in_addr_instr_range(address))
    {
        throw Memory_exception();
    }
    return get_n_bytes(4, address);
}

void Memory::set_n_bytes_of_data(int n, int start_address, uint32_t value)
{
    if (is_trying_to_set_stdout(n, start_address))
    {
        cerr << dec << "putchar should be: " << value << endl;
        putchar(value); //gets least significant 8 bits i think
        cerr << endl;
        return;
    } //must be before range check or will throw as its out of range

    if (!is_in_addr_data_range(start_address))
    {
        throw Memory_exception();
    }

    set_n_bytes(n, start_address, value);
}

uint32_t Memory::get_n_bytes_of_data(int n, int start_address)
{
    // cerr << "start address: " << start_address << endl;
    if (is_trying_to_read_stdin(n, start_address)) //should be in get data function because its 'part' of it... so is addr null set
    {
        //cerr << "is trying to read stdin" << endl;
        int input = getchar();
        cerr << dec << "stdin: " << input << endl;
        if (input == EOF)
        {
            cerr << "eof reached" << endl;
            return -1;
        }
        return input; //will be in lsb of return result
    }                 //must be before range check

    if (!is_in_addr_data_range(start_address))
    {
        throw Memory_exception();
    }

    return get_n_bytes(n, start_address);
}

bool Memory::is_in_addr_data_range(int address) //applies to both read and write
{
    if (address >= Memory::ADDR_DATA && address < Memory::ADDR_DATA + Memory::ADDR_DATA_LENGTH) //not <= or we'd be validating address outside the range
    {
        return true;
    }
    return false;
}

bool Memory::is_in_addr_instr_range(int address)
{
    //if address is greater tan number of instructions loaded in then it should be invalid instruction
    if (address >= Memory::ADDR_INSTR && address < Memory::ADDR_INSTR + Memory::ADDR_INSTR_LENGTH) //not <= or we'd be validating address outside the range
    {
        return true;
    }
    return false;
}

bool Memory::is_trying_to_read_stdin(int number_of_bytes_being_got, int start_address) //checks if any bytes being gotten are in the getc range
{
    for (int i = start_address; i < start_address + number_of_bytes_being_got; i++)
    {
        if (i >= Memory::ADDR_GETC && i < Memory::ADDR_GETC + Memory::ADDR_GETC_LENGTH)
        {
            return true;
        }
    }
    return false;
}

bool Memory::is_trying_to_set_stdout(int number_of_bytes_being_set, int start_address) //checks if any bytes being set are in the putc range
{
    for (int i = start_address; i < start_address + number_of_bytes_being_set; i++)
    {
        if (i >= Memory::ADDR_PUTC && i < Memory::ADDR_PUTC + Memory::ADDR_PUTC_LENGTH)
        {
            return true;
        }
    }
    return false;
}
