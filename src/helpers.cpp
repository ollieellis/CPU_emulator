#include "helpers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

void FileIo::getBinaryFile(string filePath)
{
    cout << "getting binary file \n";

    streampos size;
    char *memblock;
    uint32_t *instructions;

    ifstream file(filePath, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        ifstream fileOut("test.bin", ios::out | ios::binary | ios::ate);
        fileOut.write(memblock, 32);
        fileOut.close();

        
        cout << size;
        for (size_t i = 0; i < 4; i++)
        {
            std::cout << std::hex << (int)memblock[i];
        }
    }
    else
        cout << "Unable to open file";
}
