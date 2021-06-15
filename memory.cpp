#include <iostream>

class Memory 
{
    private:
        int memory_addresses[65536];
    
    public:
        Memory()
        {
            initializeMemoryAddresses();
        }
        void initializeMemoryAddresses()
        {
            int NULL_VAL = 0x00;
            for(int i = 0; i < 65536; i++)
                memory_addresses[i] = NULL_VAL;
        }
        void printMemoryAddress(int* memoryAddress)
        {
            std::cout << memory_addresses[*memoryAddress] << std::endl;
        }
        void setMemoryAddress(int* memoryAddress, int* val)
        {
            memory_addresses[*memoryAddress] = *val;
        }
};

int main()
{
    Memory RAM;
    int memoryAddress = 0x00;
    int val = 0x33;
    RAM.printMemoryAddress(&memoryAddress);
    RAM.setMemoryAddress(&memoryAddress, &val);
    RAM.printMemoryAddress(&memoryAddress);
}
