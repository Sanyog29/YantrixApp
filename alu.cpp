#include "alu.h"
#include <sstream>
#include <limits>

ALU::ALU() : registerA(0), registerB(0), result(0), 
             carryFlag(false), zeroFlag(false), 
             overflowFlag(false), negativeFlag(false) {}

void ALU::setRegisterA(int value) {
    registerA = value;
}

void ALU::setRegisterB(int value) {
    registerB = value;
}

int ALU::getRegisterA() const {
    return registerA;
}

int ALU::getRegisterB() const {
    return registerB;
}

int ALU::getResult() const {
    return result;
}

bool ALU::getCarryFlag() const {
    return carryFlag;
}

bool ALU::getZeroFlag() const {
    return zeroFlag;
}

bool ALU::getOverflowFlag() const {
    return overflowFlag;
}

bool ALU::getNegativeFlag() const {
    return negativeFlag;
}

void ALU::resetFlags() {
    carryFlag = false;
    zeroFlag = false;
    overflowFlag = false;
    negativeFlag = false;
}

void ALU::add() {
    resetFlags();
    
    // Overflow check krne ke liye hai ye section
    if ((registerA > 0 && registerB > 0 && registerA > std::numeric_limits<int>::max() - registerB) ||
        (registerA < 0 && registerB < 0 && registerA < std::numeric_limits<int>::min() - registerB)) {
        overflowFlag = true;
    }
    
    // Perform addition
    result = registerA + registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
    
    // Carry flag for unsigned addition
    carryFlag = ((unsigned int)registerA + (unsigned int)registerB) > std::numeric_limits<unsigned int>::max();
}

void ALU::subtract() {
    resetFlags();
    
    // Check for overflow
    if ((registerA > 0 && registerB < 0 && registerA > std::numeric_limits<int>::max() + registerB) ||
        (registerA < 0 && registerB > 0 && registerA < std::numeric_limits<int>::min() + registerB)) {
        overflowFlag = true;
    }
    
    // Perform subtraction
    result = registerA - registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
    
    // Borrow flag (equivalent to carry in subtraction)
    carryFlag = (registerA < registerB);
}

void ALU::multiply() {
    resetFlags();
    
    // Check for overflow
    if (registerA != 0 && registerB != 0) {
        if (registerA > std::numeric_limits<int>::max() / std::abs(registerB) ||
            registerA < std::numeric_limits<int>::min() / std::abs(registerB)) {
            overflowFlag = true;
        }
    }
    
    // Perform multiplication
    result = registerA * registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::divide() {
    resetFlags();
    
    // Check for division by zero
    if (registerB == 0) {
        overflowFlag = true;
        result = 0;
        return;
    }
    
    // Check for overflow (only case in 2's complement)
    if (registerA == std::numeric_limits<int>::min() && registerB == -1) {
        overflowFlag = true;
        result = std::numeric_limits<int>::min(); // Result would overflow
        return;
    }
    
    // Perform division
    result = registerA / registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::bitwiseAND() {
    resetFlags();
    
    // Perform bitwise AND
    result = registerA & registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::bitwiseOR() {
    resetFlags();
    
    // Perform bitwise OR
    result = registerA | registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::bitwiseXOR() {
    resetFlags();
    
    // Perform bitwise XOR
    result = registerA ^ registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::bitwiseNOT() {
    resetFlags();
    
    // Perform bitwise NOT on register A
    result = ~registerA;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
}

void ALU::shiftLeft() {
    resetFlags();
    
    // Perform left shift
    result = registerA << registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
    
    // Carry flag for shift operations
    if (registerB > 0 && registerB < 32) {
        carryFlag = (registerA & (1 << (32 - registerB))) != 0;
    }
}

void ALU::shiftRight() {
    resetFlags();
    
    // Perform right shift
    result = registerA >> registerB;
    
    // Set flags
    zeroFlag = (result == 0);
    negativeFlag = (result < 0);
    
    // Carry flag for shift operations
    if (registerB > 0 && registerB < 32) {
        carryFlag = (registerA & (1 << (registerB - 1))) != 0;
    }
}

std::string ALU::getStatusFlags() const {
    std::stringstream ss;
    ss << "Flags: ";
    ss << "Z=" << (zeroFlag ? "1" : "0") << " ";
    ss << "N=" << (negativeFlag ? "1" : "0") << " ";
    ss << "C=" << (carryFlag ? "1" : "0") << " ";
    ss << "V=" << (overflowFlag ? "1" : "0");
    return ss.str();
}