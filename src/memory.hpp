#include <vector>
#include "helpers.hpp"

class Memory
{
    //function to load bin file to instruction memory map
    std::vector<uint32_t> memory;

  public:
    Memory();
    void set_range_of_memory(int start, int end, uint32_t value);
    void load_instructions_into_memory(Instructions instructions);  
    
};