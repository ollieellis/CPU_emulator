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
    memory->load_instructions_in(file_io->instructions, file_io->number_of_instructions);  
    

    // cout <<  hex << "lollol " <<  (int)Binary_helper::extract_char(2, 0x8FA80004) << endl;
    //cout << hex << "foob: " << memory->get_instruction(4);

    return 0;
}
