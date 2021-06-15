#include <iostream>
#include <unordered_map>
#include "memory.hpp"

// Register module ==> contains the Entire Registers module of 8085
class register_class
{
    private:
        std::unordered_map < std::string, cell8 > umap;
        Memory memory; 
    public:
        // Util functions
        register_class()
        {
            initializeRegisters();
        }

        void initializeRegisters()
        {
            umap["A"].b = 0x00;
            umap["B"].b = 0x00;
            umap["C"].b = 0x00;
            umap["D"].b = 0x00;
            umap["E"].b = 0x00;
            umap["H"].b = 0x00;
            umap["L"].b = 0x00;
            umap["CARRY"].b = 0x00;
            umap["SIGN"].b = 0x00;
        }

        void showFlagsStatus()
        {
            std::cout << std::hex << umap["CARRY"].b << " CARRY FLAG \n"; 
            std::cout << std::hex << umap["SIGN"].b << " SIGN FLAG \n"; 
            // Rest flags to be done (sign, zero, etc)
        }

        void showRegistersStatus()
        {
            std::cout << std::hex << umap["A"].b << " Accumulator \n";
            std::cout << std::hex << umap["B"].b << " Register B \n";     
            std::cout << std::hex << umap["C"].b << " Register C \n";     
            std::cout << std::hex << umap["D"].b << " Register D \n";     
            std::cout << std::hex << umap["E"].b << " Register E \n";     
            std::cout << std::hex << umap["H"].b << " Register H \n";     
            std::cout << std::hex << umap["L"].b << " Register L \n";     
        }

        void printMemoryAddresses(int *memoryAddress)
        {
            std::cout << "The value at the Memory address is " << std::endl;
            memory.printMemoryAddress(memoryAddress);
        }

        // DATA TRANSFER GROUP
        void LDA(int* memory_address)
        {
            umap["A"] = memory.returnFromMemory(memory_address);
        }

        void STA(int* memory_address)
        {
            memory.setMemoryAddress(memory_address, umap["A"].b);
        }

        void LXI(const char* register_pair, int* val_16bit)
        {
            if(register_pair == "B")
            {
                umap["C"].b = *val_16bit % 0x100;
                umap["B"].b = *val_16bit / 0x100;
            } else if(register_pair == "D")
            {
                umap["E"].b = *val_16bit % 0x100;
                umap["D"].b = *val_16bit / 0x100;
            } else 
            {
                umap["L"].b = *val_16bit % 0x100;
                umap["H"].b = *val_16bit / 0x100;
            }
        }

        void LHLD(int* memoryAddress)
        {
            umap["L"] = memory.returnFromMemory(memoryAddress);
            *memoryAddress = *memoryAddress + 1;
            umap["H"] = memory.returnFromMemory(&(*memoryAddress));
        }

        void SHLD(int* memoryAddress)
        {
            memory.setMemoryAddress(memoryAddress, umap["L"].b);
            *memoryAddress = *memoryAddress + 1;
            memory.setMemoryAddress(&(*memoryAddress), umap["H"].b);
        }

        void MVI(const char* register_name, int* val)
        {
            umap[register_name].b = *val;
        }

        void MOV(const char* register_name, const char* register_name_2)
        {
            if(register_name != "M" && register_name_2 != "M")
                umap[register_name].b = umap[register_name_2].b;
            else
            {
                int mainLand = (int)(umap["H"].b * 0x100 + umap["L"].b);
                if(register_name == "M")
                    memory.setMemoryAddress(&mainLand, umap[register_name_2].b);
                else
                    umap[register_name] = memory.returnFromMemory(&mainLand);
            }

        }

        void LDAX(const char* register_pair)
        {
            int memoryAddress;
            if(register_pair == "B")
            {
                memoryAddress = (int)(umap["B"].b  * 0x100 + umap["C"].b);
            } else if(register_pair == "D")
            {
                memoryAddress = (int)(umap["D"].b  * 0x100 + umap["E"].b);
            }
            umap["A"] = memory.returnFromMemory(&memoryAddress);
        }

        void XCHG()
        {
            cell8 temp;
            
            // higher bit exchange
            temp = umap["H"];
            umap["H"] = umap["D"];
            umap["D"] = temp;

            // lower bit exchange
            temp = umap["L"];
            umap["L"] = umap["E"];
            umap["E"] = temp;

        }

        // ARITHMATIC GROUP

        void ADD(const char* register_name){
            cell8 temp = {umap["A"].b};
            umap["CARRY"].b = 0;

            if(register_name != "M"){
                umap["A"].b = temp.b + umap[register_name].b; 
            } else {
                int memoryAddress = umap["H"].b * 0x100 + umap["L"].b;
                umap["A"].b = temp.b + memory.returnFromMemory(&memoryAddress).b;
            }
        
            if(umap["A"].b <= temp.b || umap["A"].b <= umap[register_name].b)
                umap["CARRY"].b = 1; 
        }

        void SUB(const char* register_name){
            cell8 temp = {umap["A"].b};
            umap["SIGN"].b = 0;
            umap["CARRY"].b = 0;            // ? check if this is ryt p1

            if(register_name != "M"){
                umap["A"].b = umap["A"].b - umap[register_name].b;  
            } else {
                int memoryAddress = umap["H"].b * 0x100 + umap["L"].b;
                umap["A"].b = temp.b - memory.returnFromMemory(&memoryAddress).b;
            }

            if(umap["A"].b >= temp.b || umap["A"].b >= umap[register_name].b)
                umap["SIGN"].b = 1;
                umap["CARRY"].b = 1;        // ? check if this is ryt p2
        }

        void ADC(const char* register_name)
        {
            cell8 temp = {umap["A"].b};
            umap["CARRY"] = 0;

            if(register_name != "M"){
                umap["A"].b = temp.b + umap[register_name].b + umap["CARRY"].b; 
            } else {
                int memoryAddress = umap["H"].b * 0x100 + umap["L"].b;
                umap["A"].b = temp.b + memory.returnFromMemory(&memoryAddress).b + umap["CARRY"].b;
            }
        
            if(umap["A"].b <= temp.b || umap["A"].b <= umap[register_name].b)
                umap["CARRY"].b = 1; 
        }

        void SBB(const char* register_name)
        {
            cell8 temp = {umap["A"].b};
            umap["SIGN"].b = 0;
            umap["CARRY"].b = 0;            // ? check if this is ryt p1

            if(register_name != "M"){
                umap["A"].b = umap["A"].b - umap[register_name].b - umap["CARRY"].b;  
            } else {
                int memoryAddress = umap["H"].b * 0x100 + umap["L"].b;
                umap["A"].b = temp.b - memory.returnFromMemory(&memoryAddress).b - umap["CARRY"].b;
            }

            if(umap["A"].b >= temp.b || umap["A"].b >= umap[register_name].b)
                umap["SIGN"].b = 1;
                umap["CARRY"].b = 1;        // ? check if this is ryt p2
        }

        void ADI(int* val)
        {
            umap["A"].b = umap["A"].b + *val;
        }

        void ACI(int* val)
        {
            umap["A"].b = umap["A"].b + *val + umap["CARRY"].b;
        }

        void SUI(int* val)
        {
            umap["A"].b = umap["A"].b - *val;
        }

        void SBI(int* val)
        {
            umap["A"].b = umap["A"].b - *val - umap["CARRY"].b;
        }

        void INR(const char* register_name)
        {
            if(register_name != "M")
                umap[register_name].b = umap[register_name].b + 0x01;
            else {
                int memoryAddress = (int)(umap["H"].b * 0x100 + umap["L"].b);
                cell8 temp = {memory.returnFromMemory(&memoryAddress).b + 0x01};
                memory.setMemoryAddress(&memoryAddress, temp);
            }
        }

        void DCR(const char* register_name)
        {
            if(register_name != "M")
                umap[register_name].b = umap[register_name].b - 0x01;
            else{
                int memoryAddress = (int)(umap["H"].b * 0x100 + umap["L"].b);
                cell8 temp = {memory.returnFromMemory(&memoryAddress).b + 0x01};
                memory.setMemoryAddress(&memoryAddress, temp);
            }
        }
        // BRANCH GROUP

        void JZ()       
        {}

        // LOGICAL GROUP

        
        // STACK /IO /MACHINE CONTROL GROUP
        
        void RST()
        {
            initializeRegisters();
        }
};

int main()
{
    register_class registers;
<<<<<<< HEAD
    int lowerbit_DE = 0x05;
    int higherbit_DE = 0xff;
    int lowerbit_HL = 0xab;
    int higherbit_HL = 0xcc;
    int newNumber = 0xab;
    int memoryAddress = 0xff * 0x100 + 0x05;
    registers.MVI("E", &lowerbit_DE);
    registers.MVI("D", &higherbit_DE);
    registers.MVI("L", &lowerbit_HL);
    registers.MVI("H", &higherbit_HL);

    registers.XCHG();
    registers.showRegistersStatus();
    // registers.showFlagsStatus();
=======
    int a = 0x01;
    int b = 0xff;
    std::cout << std::hex << a - b << std::endl; 
    registers.MVI("A", &a);
    registers.MVI("B", &b);
    registers.SUB("B");
    registers.showFlagsStatus();
    registers.showRegistersStatus();
>>>>>>> a821fdfd6324e22495bb189a5a7ee4cc5cceb35d
    return 0;
}
