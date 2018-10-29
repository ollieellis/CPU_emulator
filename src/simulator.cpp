#include <iostream>
#include <bitset>
#include "memory.hpp"


using namespace std;
int main(int argc, char *argv[])
{
    cout << "programme path: " << argv[0] << endl;

    Instructions instructions = File_io::get_binary_file(argv[1]);
    Memory *memory = new Memory();
    cout << "\npoop " << instructions.instructions[0];
    memory->load_instructions_into_memory(instructions);

    return 0;
}