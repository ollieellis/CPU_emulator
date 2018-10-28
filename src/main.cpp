#include <iostream>
#include <bitset>
#include "helpers.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    cout << "programme path: " << argv[0] << endl;
       
    file_io::get_binary_file("instructions.bin");
    return 0;
}