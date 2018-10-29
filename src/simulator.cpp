#include <iostream>
#include <bitset>
#include "memory.hpp"


using namespace std;

int main(int argc, char *argv[])
{
    
    cout << "programme path: " << argv[0] << endl;

    Memory *memory = new Memory();
    File_io *file_io = new File_io();
    
    file_io->get_binary_file(argv[1]);
    memory->load_instructions_into_memory(file_io->instructions, file_io->number_of_instructions);  


    return 0;
}
