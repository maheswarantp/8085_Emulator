#include <iostream>
#include "cell.hpp"

class Memory 
{
    private:
        cell8 memory_addresses[65536];
        int NULL_VAL = 0x00;

    public:
        Memory()
        {
            initializeMemoryAddresses();
        }
        void initializeMemoryAddresses()
        {
            for(int i = 0; i < 65536; i++)
                memory_addresses[i].b = NULL_VAL;
        }
        void printMemoryAddress(int* memoryAddress)
        {
            std::cout << std::hex << memory_addresses[*memoryAddress].b << std::endl;
        }
        void setMemoryAddress(int* memoryAddress, cell8 val)
        {
            memory_addresses[*memoryAddress].b = val.b;
        }
        void clearMemoryAddress(int* memoryAddress)
        {
            memory_addresses[*memoryAddress].b = 0x00;
        }
        
        cell8 returnFromMemory(int* memoryAddress)
        {
            return memory_addresses[*memoryAddress];
        }
};
