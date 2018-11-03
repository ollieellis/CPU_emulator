#include <iostream>
#include <exception> 


struct ArithmeticException : public std::exception { 
   const char * what () const throw () {
      return "Arithmetic exception";
   }
};

struct MemoryException : public std::exception { 
   const char * what () const throw () {
      return "Memory exception";
   }
};

struct InvalidInstructionException : public std::exception { 
   const char * what () const throw () {
      return "Invalid instruction exception";
   }
};