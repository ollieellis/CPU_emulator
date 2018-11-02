#include "instructions.hpp"
#include "helpers.hpp"
#include <iostream>

using namespace std;

R_type::R_type(uint32_t instruction)
{
    opcode = Binary_helper::extract_bits(31, 6, instruction);
    source1 = Binary_helper::extract_bits(25, 5, instruction);
    source2 = Binary_helper::extract_bits(20, 5, instruction);
    destination = Binary_helper::extract_bits(15, 5, instruction);
    shift = Binary_helper::extract_bits(10, 5, instruction);
    function = Binary_helper::extract_bits(5, 6, instruction);
}

I_type::I_type(uint32_t instruction)
{
    opcode = Binary_helper::extract_bits(31, 6, instruction);
    source = Binary_helper::extract_bits(25, 5, instruction);
    destination = Binary_helper::extract_bits(20, 5, instruction);
    immediate = Binary_helper::extract_bits(15, 16, instruction);
}

J_type::J_type(uint32_t instruction)
{
    opcode = Binary_helper::extract_bits(31, 6, instruction);
    address = Binary_helper::extract_bits(25, 26, instruction);
}

Instruction_type Instruction_helper::get_type(uint32_t instruction)
{
    uint32_t opcode = Binary_helper::extract_bits(31, 6, instruction);
    if (opcode == 0)
    {
        return r_type;
    }
    if (opcode == 2 || opcode == 3)
    {
        return j_type;
    }

    return i_type; //if not r_type or j_type, must be i_type
}

void R_type::deSYTHER()
{
    switch (function)
    {
    case 0:
        SLL();
        break;
    case 2:
        SRL();
        break;
    case 3:
        SRA();
        break;
    case 4:
        SLLV();
        break;
    case 6:
        SRLV();
        break;
    case 7:
        SRAV();
        break;
    case 8:
        JR();
        break;
    case 9:
        JALR();
        break;
    case 16:
        MFHI();
        break;
    case 17:
        MTHI();
        break;
    case 18:
        MFLO();
        break;
    case 19:
        MTLO();
        break;
    case 24:
        MULT();
        break;
    case 25:
        MULTU();
        break;
    case 26:
        DIV();
        break;
    case 27:
        DIVU();
        break;
    case 32:
        ADD();
        break;
    case 33:
        ADDU();
        break;
    case 34:
        SUB();
        break;
    case 35:
        SUBU();
        break;
    case 36:
        AND();
        break;
    case 37:
        OR();
        break;
    case 38:
        XOR();
        break;
    case 42:
        SLT();
        break;
    case 43:
        SLTU();
        break;
    default:
        break; // throw error?
    }
}

void I_type::deSYTHER()
{
    switch (opcode)
    {
    case 1:
        switch (destination)
        {
        case 0:
            BLTZ();
            break;
        case 1:
            BGEZ();
            break;
        case 16:
            BLTZAL();
            break;
        case 17:
            BGEZAL();
            break;
        default:
            break;
        }
        break;
    case 4:
        BEQ();
        break;
    case 5:
        BNE();
        break;
    case 6:
        BLEZ();
        break;
    case 7:
        BGTZ();
        break;
    case 8:
        ADDI();
        break;
    case 9:
        ADDIU();
        break;
    case 10:
        SLTI();
        break;
    case 11:
        SLTIU();
        break;
    case 12:
        ANDI();
        break;
    case 13:
        ORI();
        break;
    case 14:
        XORI();
        break;
    case 15:
        LUI();
        break;
    case 32:
        LB();
        break;
    case 33:
        LH();
        break;
    case 34:
        LWL();
        break;
    case 35:
        LW();
        break;
    case 36:
        LBU();
        break;
    case 37:
        LHU();
        break;
    case 38:
        LWR();
        break;
    case 40:
        SB();
        break;
    case 41:
        SH();
        break;
    case 43:
        SW();
        break;
    default:
        break;
    }
}

void J_type::deSYTHER()
{
    switch (opcode)
    {
    case 2:
        J();
        break;
    case 3:
        JAL();
        break;

    default:
        break;
    }
}

void Instruction_helper::execute(uint32_t instruction)
{
    cout << "executing instruction: " << hex << instruction << endl;

    switch (get_type(instruction))
    {
    case r_type:
    {
        R_type r_instruction = R_type(instruction);
        r_instruction.deSYTHER();
        break;
    }
    case i_type:
    {
        I_type i_instruction = I_type(instruction);
        i_instruction.deSYTHER();
        break;
    }

    case j_type:
    {
        J_type j_instruction = J_type(instruction);
        j_instruction.deSYTHER();
        break;
    }
    }
}