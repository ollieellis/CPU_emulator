#include "helpers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cstdint>

using namespace std;

uint32_t *file_io::get_binary_file(string file_path)
{
    cout << "getting binary file \n";

    // ifstream in;
    // in.open(filePath, ios_base::binary | ios_base::in | ios_base::ate);
    // int size = in.tellg();
    // in.seekg(0, ios::beg);

    // char current;
    // vector<char> vec;

    // while (size-- > 0)
    // {
    //     in >> current;
    //     std::cout << std::hex << current;
    //     vec.push_back(current);
    // }
    //yusu

    streampos size;
    char *memblock;
    uint32_t *instructions;

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

        for (size_t i = 0; i < size / sizeof(instructions[0]); i++)
        {
            instructions[i] = file_io::rotate_left(instructions[i], 0);
            cout << "instruction: ";
            cout << hex << uppercase << instructions[i] << std::endl;
        }
        return instructions; //remember to delete
    }
    else
    {
        cout << "Unable to open file";
        //throw error
    }
    delete[] memblock;
    return instructions;
}

template <class T>
inline T file_io::rotate_left(T v, std::int32_t shift)
{
    std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
    T s = shift >= 0 ? shift % m : -((-shift) % m);
    return (v << s) | (v >> (m - s));
}

template <class T>
inline T file_io::rotate_right(T v, std::int32_t shift)
{
    std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
    T s = shift >= 0 ? shift % m : -((-shift) % m);
    return (v >> s) | (v << (m - s));
}
