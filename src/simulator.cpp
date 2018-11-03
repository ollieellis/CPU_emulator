#include <iostream>
#include <bitset>
#include "memory.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "exceptions.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "programme path: " << argv[0] << endl;

    // std::shared_ptr<Memory> memory(new Memory()); //smart pointer
    // std::shared_ptr<File_io> file_io(new File_io());
    // std::shared_ptr<Registers> registers(new Registers());
    // std::shared_ptr<Instructions> instructions(new Instructions());

    Memory *memory = new Memory();
    File_io *file_io = new File_io();
    Registers *registers = new Registers();
    Instruction_helper *instruction_helper = new Instruction_helper(registers);

    file_io->get_binary_file(argv[1]);
    memory->load_instructions_in(file_io->instructions, file_io->number_of_instructions);
    instruction_helper->number_of_instructions = file_io->number_of_instructions;

    bool has_program_finished = false;
    while (!has_program_finished)
    {
        uint32_t current_program_counter = registers->get_program_counter();

        try
        {
            instruction_helper->execute(memory->get_instruction(registers->get_program_counter()));
        }
        catch (const ArithmeticException &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-10);
        }
        catch (const MemoryException &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-11);
        }
        catch (const InvalidInstructionException &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(-12);
        }

        registers->set_program_counter(current_program_counter + 4);

        if (registers->get_program_counter() > 100)
        {
            has_program_finished = true;
        }
    }
    return 0;
}