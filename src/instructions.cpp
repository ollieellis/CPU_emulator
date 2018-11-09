#include "instructions.hpp"
#include "helpers.hpp"
#include "registers.hpp"
#include "memory.hpp"
#include "exceptions.hpp"
#include <iostream>

using namespace std;

Instruction_helper::Instruction_helper(Registers *registers, Memory *memory)
{
	this->registers = registers;
	this->memory = memory;
}

R_type::R_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	// cerr << "extracted op code " << dec << opcode << endl;
	source1 = Bitwise_helper::extract_bits(21, 5, instruction);
	source2 = Bitwise_helper::extract_bits(16, 5, instruction);
	destination = Bitwise_helper::extract_bits(11, 5, instruction);
	shift = Bitwise_helper::extract_bits(6, 5, instruction);
	function = Bitwise_helper::extract_bits(0, 6, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

I_type::I_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	// cerr << "extracted op code " << dec << opcode << endl;
	source1 = Bitwise_helper::extract_bits(21, 5, instruction);
	source2_or_destination = Bitwise_helper::extract_bits(16, 5, instruction);
	immediate = Bitwise_helper::extract_bits(0, 16, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

J_type::J_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	address = Bitwise_helper::extract_bits(0, 26, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

Instruction_helper::Type Instruction_helper::get_type(uint32_t instruction)
{
	uint32_t opcode = Bitwise_helper::extract_bits(26, 6, instruction);
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
		throw Internal_error();
		break;
	}
}

void I_type::deSYTHER()
{
	switch (opcode)
	{
	case 1:
		switch (source2_or_destination)
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
		throw Internal_error();
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
		throw Internal_error(); //instruction not found
		break;
	}
}

void Instruction_helper::execute(uint32_t instruction)
{
	cerr << "executing instruction: " << hex << instruction << endl;

	if (registers->get_program_counter() > Memory::ADDR_INSTR + (uint32_t)number_of_instructions * 4 || registers->get_program_counter() < Memory::ADDR_INSTR) //check if pc is still in range where instructions are. should be here and not in main while loop because execute can be called from other instructions coz of branch delay slot for example. but acc we aren't actually increasing the pc when calling instructions in the delay slot. still, i think it's better practice to keep it here.
	{
		throw Invalid_instruction_exception();
	}

	switch (get_type(instruction))
	{
	case r_type:
	{
		// cerr << "is r type " << endl;
		R_type r_instruction = R_type(instruction, registers, memory, this);
		r_instruction.deSYTHER();
		break;
	}
	case i_type:
	{
		//cerr << "is i type" << endl;
		I_type i_instruction = I_type(instruction, registers, memory, this);
		i_instruction.deSYTHER();
		break;
	}
	case j_type:
	{
		J_type j_instruction = J_type(instruction, registers, memory, this);
		j_instruction.deSYTHER();
		break;
	}
	}
}

void R_type::ADD() //check to see if this is correct - what if we used negative 2s complement? will that even make a difference
{
	//we need to check for overflow
	uint64_t guaranteed_correct_result = registers->get_register(source1) + registers->get_register(source2);
	uint32_t result = guaranteed_correct_result; // trunc to 32 bits

	if (result != guaranteed_correct_result)
	{
		throw Arithmetic_exception();
	}
	registers->set_register(destination, result);
	registers->advance_program_counter();
}

void R_type::ADDU()
{
	uint32_t result = registers->get_register(source1) + registers->get_register(source2);
	registers->set_register(destination, result);
	registers->advance_program_counter();
}
void R_type::AND()
{
	uint32_t result = registers->get_register(source1) & registers->get_register(source2);
	registers->set_register(destination, result);
	registers->advance_program_counter();
}
void R_type::DIV()
{
	registers->advance_program_counter();
}
void R_type::DIVU()
{
	registers->advance_program_counter();
}
void R_type::JALR()
{
	registers->advance_program_counter();
}
void R_type::JR()
{
	uint32_t jump_address = registers->get_register(source1); //ensure we store the correct address before executing delay slot (as it could change the value of address source1)
	if (Bitwise_helper::extract_bits(0, 2, jump_address) != 0)
	{
		throw Memory_exception();
	}
	int32_t next_instruction = memory->get_n_bytes(4, registers->get_program_counter() + 4);
	instruction_helper->execute(next_instruction);
	registers->set_program_counter(jump_address);
}
void R_type::MFHI()
{
	registers->advance_program_counter();
}
void R_type::MFLO()
{
	registers->advance_program_counter();
}
void R_type::MTHI()
{
	registers->advance_program_counter();
}
void R_type::MTLO()
{
	registers->advance_program_counter();
}
void R_type::MULT()
{
	registers->advance_program_counter();
}
void R_type::MULTU()
{
	registers->advance_program_counter();
}
void R_type::OR()
{
	registers->advance_program_counter();
}
void R_type::SLL()
{
	registers->advance_program_counter();
}
void R_type::SLLV()
{
	registers->advance_program_counter();
}
void R_type::SLT()
{
	registers->advance_program_counter();
}
void R_type::SLTU()
{
	uint32_t result = 0;
	if (registers->get_register(source1) < registers->get_register(source2))
	{
		result = 1;
	}
	registers->set_register(destination, result);
	registers->advance_program_counter();
}
void R_type::SRA()
{
	registers->advance_program_counter();
}
void R_type::SRAV()
{
	registers->advance_program_counter();
}
void R_type::SRL()
{
	registers->advance_program_counter();
}
void R_type::SRLV()
{
	registers->advance_program_counter();
}
void R_type::SUB()
{
	registers->advance_program_counter();
}
void R_type::SUBU()
{
	registers->advance_program_counter();
}
void R_type::XOR()
{
	registers->advance_program_counter();
}

void I_type::ADDI()
{
	uint64_t guaranteed_correct_result = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	uint32_t result = guaranteed_correct_result; //trunc to 32 bits

	if (result != guaranteed_correct_result)
	{
		throw Arithmetic_exception();
	}
	registers->set_register(source2_or_destination, result);
	registers->advance_program_counter();
}
void I_type::ADDIU()
{
	uint32_t result = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	registers->set_register(source2_or_destination, result);
	registers->advance_program_counter();
}
void I_type::ANDI()
{
	uint32_t result = registers->get_register(source1) & immediate;
	registers->set_register(source2_or_destination, result);
	registers->advance_program_counter();
}

void I_type::BEQ()
{
	if (registers->get_register(source1) == registers->get_register(source2_or_destination))
	{
		uint32_t offset = Bitwise_helper::sign_extend_to_32(18, immediate << 2);
		uint32_t branch_address = registers->get_program_counter() + 4 + offset; //ensure we store the correct address before executing delay slot
		uint32_t next_instruction = memory->get_n_bytes(4, registers->get_program_counter() + 4);
		instruction_helper->execute(next_instruction);  //branch works by executing the next instruction first
		registers->set_program_counter(branch_address); //pc wil have been advanced by here
	}
	else
	{
		registers->advance_program_counter();
	}
}
void I_type::BGEZ()
{
	if (registers->get_register(source1) >= 0)
	{
		uint32_t offset = Bitwise_helper::sign_extend_to_32(18, immediate << 2);
		uint32_t next_instruction = memory->get_n_bytes(4, registers->get_program_counter() + 4);
		instruction_helper->execute(next_instruction);							   //branch works by executing the next instruction first
		registers->set_program_counter(registers->get_program_counter() + offset); //pc wil have been advanced by here
	}
	else
	{
		registers->advance_program_counter();
	}
}
void I_type::BGEZAL()
{
	registers->advance_program_counter();
}
void I_type::BGTZ()
{
	registers->advance_program_counter();
}
void I_type::BLEZ()
{
	registers->advance_program_counter();
}
void I_type::BLTZ()
{
	registers->advance_program_counter();
}
void I_type::BLTZAL()
{
	registers->advance_program_counter();
}
void I_type::BNE()
{
	registers->advance_program_counter();
}
void I_type::LB()
{
	registers->advance_program_counter();
}
void I_type::LBU()
{
	registers->advance_program_counter();
}
void I_type::LH()
{
	registers->advance_program_counter();
}
void I_type::LHU()
{
	registers->advance_program_counter();
}
void I_type::LUI()
{
	registers->advance_program_counter();
}
void I_type::LW()
{
	registers->advance_program_counter();
}
void I_type::LWL()
{
	registers->advance_program_counter();
}
void I_type::LWR()
{
	registers->advance_program_counter();
}
void I_type::ORI()
{
	registers->advance_program_counter();
}
void I_type::SB()
{
	registers->advance_program_counter();
}
void I_type::SH()
{
	registers->advance_program_counter();
}
void I_type::SLTI()
{
	registers->advance_program_counter();
}
void I_type::SLTIU()
{
	registers->advance_program_counter();
}
void I_type::SW()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	if (Bitwise_helper::extract_bits(0, 2, address) != 0)
	{
		throw Memory_exception();
	}
	memory->set_n_bytes(4, address, registers->get_register(source2_or_destination));
	registers->advance_program_counter();
}
void I_type::XORI()
{
	registers->advance_program_counter();
}

void J_type::J()
{
	registers->advance_program_counter();
}
void J_type::JAL()
{
	registers->advance_program_counter();
}
