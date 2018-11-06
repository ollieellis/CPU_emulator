#include <iostream>
#include <bitset>
#include "memory.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "exceptions.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    cerr << "programme path: " << argv[0] << endl;

    // std::shared_ptr<Memory> memory(new Memory()); //smart pointer
    // std::shared_ptr<File_io> file_io(new File_io());
    // std::shared_ptr<Registers> registers(new Registers());
    // std::shared_ptr<Instructions> instructions(new Instructions());

    Memory *memory = new Memory();
    File_io *file_io = new File_io();
    Registers *registers = new Registers();
    Instruction_helper *instruction_helper = new Instruction_helper(registers);


    if (argc != 2) throw Internal_error();//incorrect number of command line args

    file_io->get_binary_file(argv[1]);
    memory->load_instructions_in(file_io->instructions, file_io->number_of_instructions);
    instruction_helper->number_of_instructions = file_io->number_of_instructions;

    bool has_program_finished = false;
    int test_counter = 0;
    while (!has_program_finished)
    {
        test_counter++;
        uint32_t next_instruction = memory->get_n_bytes(4, registers->get_program_counter());
        if (registers->get_program_counter() == Memory::ADDR_NULL)
        {
            //terminate execution
            cerr << "\n*** terminating execution due to reaching end of binary file ***\n";
            uint8_t exit_code = Bitwise_helper::extract_char(0, registers->get_register(2));
            std::exit(exit_code);
        }

        try
        {
            //cout << "next instruction " << next_instruction;
            instruction_helper->execute(next_instruction);
        }
        catch (const Arithmetic_exception &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-10);
        }
        catch (const Memory_exception &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-11);
        }
        catch (const Invalid_instruction_exception &e)
        {
          //  std::cerr << e.what() << '\n';
            std::exit(-12);
        }
        catch (const Internal_error &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-20);
        }
		catch (const IO_error &e)
		{
			std::cerr << e.what() << '\n';
            std::exit(-21);
		}


        if (registers->get_program_counter() > Memory::ADDR_INSTR + 100 || test_counter > 100 )
        {
            has_program_finished = true;
        }
    }
    return 0;
}