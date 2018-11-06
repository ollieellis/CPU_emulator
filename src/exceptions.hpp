#include <iostream>
#include <exception>

struct Mips_exception : public std::exception
{
    virtual int exit_code() const = 0;
};

struct Arithmetic_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Arithmetic exception";
    }

    int exit_code() const override
    {
        return -10;
    }
};

struct Memory_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Memory exception";
    }
    int exit_code() const override
    {
        return -11;
    }
};

struct Invalid_instruction_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Invalid instruction exception";
    }
    int exit_code() const override
    {
        return -12;
    }
};

struct IO_error : public Mips_exception
{
    const char *what() const throw() override
    {
        return "IO Error";
    }
    int exit_code() const override
    {
        return -21;
    }
};

struct Internal_error : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Internal Error";
    }
    int exit_code() const override
    {
        return -22;
    }
};

struct Environment_error : public Internal_error
{
    const char *what() const throw() override
    {
        return "Environment Error";
    }
};