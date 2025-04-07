#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "alu.h"

void displayHelp() {
    std::cout << "ALU Simulator Commands:\n";
    std::cout << "  set a <value>     - Set register A value\n";
    std::cout << "  set b <value>     - Set register B value\n";
    std::cout << "  add               - Add A and B\n";
    std::cout << "  sub               - Subtract B from A\n";
    std::cout << "  mul               - Multiply A and B\n";
    std::cout << "  div               - Divide A by B\n";
    std::cout << "  and               - Bitwise AND of A and B\n";
    std::cout << "  or                - Bitwise OR of A and B\n";
    std::cout << "  xor               - Bitwise XOR of A and B\n";
    std::cout << "  not               - Bitwise NOT of A\n";
    std::cout << "  shl               - Shift A left by B bits\n";
    std::cout << "  shr               - Shift A right by B bits\n";
    std::cout << "  status            - Display current status\n";
    std::cout << "  help              - Display this help message\n";
    std::cout << "  exit              - Exit the simulator\n";
}

void displayStatus(const ALU& alu) {
    std::cout << "Register A: " << alu.getRegisterA() << " (0x" 
              << std::hex << std::uppercase << alu.getRegisterA() << std::dec << ")\n";
    std::cout << "Register B: " << alu.getRegisterB() << " (0x" 
              << std::hex << std::uppercase << alu.getRegisterB() << std::dec << ")\n";
    std::cout << "Result:     " << alu.getResult() << " (0x" 
              << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
    std::cout << alu.getStatusFlags() << "\n";
}

int main() {
    ALU alu;
    std::string command;
    
    std::cout << "=== ALU Simulator ===\n";
    std::cout << "Type 'help' for available commands\n";
    
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, command);
        
        std::istringstream iss(command);
        std::string action;
        iss >> action;
        
        if (action == "exit") {
            break;
        } else if (action == "help") {
            displayHelp();
        } else if (action == "set") {
            std::string reg;
            int value;
            iss >> reg >> value;
            
            if (reg == "a") {
                alu.setRegisterA(value);
                std::cout << "Register A set to " << value << "\n";
            } else if (reg == "b") {
                alu.setRegisterB(value);
                std::cout << "Register B set to " << value << "\n";
            } else {
                std::cout << "Invalid register. Use 'a' or 'b'\n";
            }
        } else if (action == "add") {
            alu.add();
            std::cout << "Added A + B = " << alu.getResult() << "\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "sub") {
            alu.subtract();
            std::cout << "Subtracted A - B = " << alu.getResult() << "\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "mul") {
            alu.multiply();
            std::cout << "Multiplied A * B = " << alu.getResult() << "\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "div") {
            if (alu.getRegisterB() == 0) {
                std::cout << "Error: Division by zero\n";
            } else {
                alu.divide();
                std::cout << "Divided A / B = " << alu.getResult() << "\n";
                std::cout << alu.getStatusFlags() << "\n";
            }
        } else if (action == "and") {
            alu.bitwiseAND();
            std::cout << "A & B = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "or") {
            alu.bitwiseOR();
            std::cout << "A | B = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "xor") {
            alu.bitwiseXOR();
            std::cout << "A ^ B = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "not") {
            alu.bitwiseNOT();
            std::cout << "~A = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "shl") {
            alu.shiftLeft();
            std::cout << "A << B = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "shr") {
            alu.shiftRight();
            std::cout << "A >> B = " << alu.getResult() << " (0x" 
                      << std::hex << std::uppercase << alu.getResult() << std::dec << ")\n";
            std::cout << alu.getStatusFlags() << "\n";
        } else if (action == "status") {
            displayStatus(alu);
        } else {
            std::cout << "Unknown command. Type 'help' for available commands\n";
        }
    }
    
    std::cout << "ALU Simulator succesfully closed !!\n";
    return 0;
}