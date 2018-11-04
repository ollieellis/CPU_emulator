#include <iostream>
#include <exception>

struct Arithmetic_exception : public std::exception
{
    const char *what() const throw()
    {
        return "Arithmetic exception";
    }
};

struct Memory_exception : public std::exception
{
    const char *what() const throw()
    {
        return "Memory exception";
    }
};

struct Invalid_instruction_exception : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid instruction exception";
    }
};

struct Internal_error : public std::exception
{
    const char *what() const throw()
    {
        return "Internal Error";
    }
};

struct IO_error : public std::exception
{
    const char *what() const throw()
    {
        return "IO Error";
    }
};