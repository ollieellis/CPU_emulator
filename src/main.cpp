#include <iostream>
#include <bitset>
#include "helpers.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    cout << "programme path: " << argv[0] << endl;
       
    FileIo::getBinaryFile("instructions.bin");
    return 0;
}