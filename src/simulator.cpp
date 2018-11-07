#include <iostream>
#include <bitset>
#include "memory.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "exceptions.hpp"

using namespace std;

void custom_exit(int exit_code,  Memory *memory, File_io *file_io, Registers *registers, Instruction_helper *instruction_helper)
{
    delete memory;
    delete file_io;
    delete registers;
    delete instruction_helper;
    std::exit(exit_code);
}

int main(int argc, char *argv[])
{

        cerr << "programme path: " << argv[0] << endl;

        Memory *memory = new Memory();
        File_io *file_io = new File_io();
        Registers *registers = new Registers();
        Instruction_helper *instruction_helper = new Instruction_helper(registers, memory);

        if (argc != 2)
            throw Environment_error(); //incorrect number of command line args

        file_io->get_binary_file(argv[1]);
        memory->load_instructions_in(file_io->instructions, file_io->number_of_instructions);
        instruction_helper->number_of_instructions = file_io->number_of_instructions;

        char hi =  memory->get_address(0x30000000);
        cout << hex <<"hi " << hi;
        bool has_program_finished = false;
        int test_counter = 0;
        while (!has_program_finished)
        {
            test_counter++;
            uint32_t next_instruction = memory->get_n_bytes(4, registers->get_program_counter());
            if (registers->get_program_counter() == Memory::ADDR_NULL)
            {
                cerr << "\n*** terminating execution due to end of binary file ***\n";
                has_program_finished = true;
                uint8_t exit_code = Bitwise_helper::extract_char(0, registers->get_register(2));
                custom_exit(exit_code, memory, file_io, registers, instruction_helper);
            }
            try
            {
                instruction_helper->execute(next_instruction);
            }
            catch (const Mips_exception &e)
            {
                std::cerr << e.what() << '\n';
                custom_exit(e.exit_code(), memory, file_io, registers, instruction_helper);
            }catch (...)
            {
                custom_exit(-22, memory, file_io, registers, instruction_helper);
            }

            if (registers->get_program_counter() > Memory::ADDR_INSTR + 100 || test_counter > 100)
            {
                has_program_finished = true;
            }
        }
   
    return 0;
}