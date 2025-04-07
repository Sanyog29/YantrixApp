#ifndef ALU_H
#define ALU_H

#include <string>

//Ye hai ALU class ka definition hai jismein registerA, registerB, result, carryFlag, zeroFlag, overflowFlag, and negativeFlag variables hai.
class ALU {
private:
    int registerA;
    int registerB;
    int result;
    bool carryFlag;
    bool zeroFlag;
    bool overflowFlag;
    bool negativeFlag;

public:
    ALU();
    
    // Values assign krne ke liye ye section hai
    void setRegisterA(int value);
    void setRegisterB(int value);
    
    // Values lene ke liye ye section hai
    int getRegisterA() const;
    int getRegisterB() const;
    int getResult() const;
    bool getCarryFlag() const;
    bool getZeroFlag() const;
    bool getOverflowFlag() const;
    bool getNegativeFlag() const;
    
    // ALU Operations perform krne ke liye ye section hai
    void add();
    void subtract();
    void multiply();
    void divide();
    void bitwiseAND();
    void bitwiseOR();
    void bitwiseXOR();
    void bitwiseNOT();
    void shiftLeft();
    void shiftRight();
    
    // helping functions hai ye
    std::string getStatusFlags() const;
    void resetFlags();
};

#endif 