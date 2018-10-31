#include <string> //makes vscode recognize uint32_t

class Instructions
{
  public:
    void execute(uint32_t instruction); 
  private:
    //we don't need to split up into r type i type j type, it is useless. when parsing the uint32_t instruction, deSYTHER what type it is there and call the correct function
    //here are all the functions - obvs the function signature needs editing for each one
    void ADD();
    void ADDI();
    void ADDIU();
    void ADDU();
    void AND();
    void ANDI();
    void BEQ();
    void BGEZ();
    void BGEZAL();
    void BGTZ();
    void BLEZ();
    void BLTZ();
    void BLTZAL();
    void BNE();
    void DIV();
    void DIVU();
    void J();
    void JALR();
    void JAL();
    void JR();
    void LB();
    void LBU();
    void LH();
    void LHU();
    void LUI();
    void LW();
    void LWL();
    void LWR();
    void MFHI();
    void MFLO();
    void MTHI();
    void MTLO();
    void MULT();
    void MULTU();
    void OR();
    void ORI();
    void SB();
    void SH();
    void SLL();
    void SLLV();
    void SLT();
    void SLTI();
    void SLTIU();
    void SLTU();
    void SRA();
    void SRAV();
    void SRL();
    void SRLV();
    void SUB();
    void SUBU();
    void SW();
    void XOR();
    void XORI();
};