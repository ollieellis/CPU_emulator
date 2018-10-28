#include <string>

using namespace std;

class file_io
{
  public:
    static uint32_t* get_binary_file(string file_path);
}; 

class bitwise_helper
{
  public:
    template< class T>
    static inline T rotate_left( T v, std::int32_t shift);
    template< class T>
    static inline T rotate_right( T v, std::int32_t shift);
    static unsigned int swap_bits(unsigned int n, unsigned int p1, unsigned int p2) ; 
    static unsigned int swap_bytes(unsigned int n, unsigned int p1, unsigned int p2);
};