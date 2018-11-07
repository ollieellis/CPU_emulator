#include "helpers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cstdint>
#include "exceptions.hpp"

using namespace std;

void File_io::get_binary_file(string file_path)
{
    cerr << "getting binary file \n";
    streampos size;
    char *memblock; //dont deconstruct
    uint32_t *instructions;

    ifstream file(file_path, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        cerr << "file size: " << size << endl;
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        instructions = reinterpret_cast<uint32_t *>(memblock);
        this->number_of_instructions = size / sizeof(instructions[0]);
        cerr << "instructions: ";
        for (int i = 0; i < this->number_of_instructions; i++)
        {
            instructions[i] = Bitwise_helper::swap_bytes(instructions[i], 0, 3);
            instructions[i] = Bitwise_helper::swap_bytes(instructions[i], 1, 2);
            cerr << hex << uppercase << instructions[i] << " ";
        }
        cerr << endl;
        this->instructions = instructions;
    }
    else
    {
        cerr << "Unable to open file";
        throw Environment_error();
        //throw error
    }
}

// template <class T>
// inline T Bitwise_helper::rotate_left(T v, std::int32_t shift)
// {
//     std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
//     T s = shift >= 0 ? shift % m : -((-shift) % m);
//     return (v << s) | (v >> (m - s));
// }

// template <class T>
// inline T Bitwise_helper::rotate_right(T v, std::int32_t shift)
// {
//     std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
//     T s = shift >= 0 ? shift % m : -((-shift) % m);
//     return (v >> s) | (v << (m - s));
// }

// This function swaps bit at positions p1 and p2 in an integer n
unsigned int Bitwise_helper::swap_bits(unsigned int n, unsigned int p1, unsigned int p2)
{
    /* Move p1'th to rightmost side */
    unsigned int bit1 = (n >> p1) & 1;

    /* Move p2'th to rightmost side */
    unsigned int bit2 = (n >> p2) & 1;

    /* XOR the two bits */
    unsigned int x = (bit1 ^ bit2);

    /* Put the xor bit back to their original positions */
    x = (x << p1) | (x << p2);

    /* XOR 'x' with the original number so that the 
       two sets are swapped */
    unsigned int result = n ^ x;
    return result;
}

unsigned int Bitwise_helper::swap_bytes(unsigned int n, unsigned int p1, unsigned int p2)
{
    unsigned int result = n;
    for (size_t i = 0; i < 8; i++)
    {
        result = Bitwise_helper::swap_bits(result, p1 * 8 + i, p2 * 8 + i);
    }
    return result;
}

uint32_t Bitwise_helper::extract_bits(int start_position, int length, uint32_t word)
{
    unsigned mask;
    mask = ((1 << length) - 1) << start_position;
    uint32_t masked = word & mask;
    return masked >> start_position;
}

unsigned char Bitwise_helper::extract_char(int nth_char, uint32_t word)
{
    return extract_bits(nth_char * 8, 8, word);
}

uint32_t Bitwise_helper::set_nth_bit(int index, bool bit, uint32_t value)
{
    return (value & (~(1 << index))) | (bit << index);
}

uint32_t Bitwise_helper::sign_extend_to_32(int size, uint32_t value)
{
    uint32_t result = value;
    bool sign_bit = extract_bits(size - 1, 1, value);
    for(size_t i = size; i < 32; i++) 
    {
       result = set_nth_bit(i, sign_bit, result);
    }
    return result;
}
