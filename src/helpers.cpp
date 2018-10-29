#include "helpers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cstdint>

using namespace std;

Instructions::Instructions(uint32_t* instructions_in, int size_in){
    instructions = instructions_in;
    size = size_in;
}

Instructions File_io::get_binary_file(string file_path) 
{
    cout << "getting binary file \n";
    streampos size;
    char *memblock;
    uint32_t *instructions;
    Instructions* instruction_obj;

    ifstream file(file_path, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        cout << "file size: " << size << endl;
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        instructions = reinterpret_cast<uint32_t *>(memblock);
        cout << "instructions: ";
        for (size_t i = 0; i < size / sizeof(instructions[0]); i++)
        {
            instructions[i] = Binary_helper::swap_bytes(instructions[i], 0, 3);
            instructions[i] = Binary_helper::swap_bytes(instructions[i], 1, 2);
            cout << hex << uppercase << instructions[i] << " ";
        }
        instruction_obj = new Instructions(instructions, size);
        cout << endl;
    }
    else
    {
        cout << "Unable to open file";
        //throw error
    }
    delete[] memblock;
    return *instruction_obj;
}

template <class T>
inline T Binary_helper::rotate_left(T v, std::int32_t shift)
{
    std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
    T s = shift >= 0 ? shift % m : -((-shift) % m);
    return (v << s) | (v >> (m - s));
}

template <class T>
inline T Binary_helper::rotate_right(T v, std::int32_t shift)
{
    std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
    T s = shift >= 0 ? shift % m : -((-shift) % m);
    return (v >> s) | (v << (m - s));
}

// This function swaps bit at positions p1 and p2 in an integer n
unsigned int Binary_helper::swap_bits(unsigned int n, unsigned int p1, unsigned int p2)
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

unsigned int Binary_helper::swap_bytes(unsigned int n, unsigned int p1, unsigned int p2)
{
    unsigned int result = n;
    for (size_t i = 0; i < 8; i++)
    {
        result = Binary_helper::swap_bits(result, p1 * 8 + i, p2 * 8 + i);
    }
    return result;
}