#include <vector>

class Registers
{

    //programme counter goes here as it is a register - remember to add an offset to get to the correct block of memory

    //array of 32 registers each 32 bits. keep private

    //function to get a register at specific index

    //function to set a register at specific index
    std::vector<uint32_t> registers;
    uint32_t program_counter;

  public:
    Registers();
    void set_register(int index, uint32_t value);
    uint32_t get_register(int index);
    
};
