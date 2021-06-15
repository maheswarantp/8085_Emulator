#include <iostream>

class Registers
{
    private:
        const char* array[7][7];
    public:
        Registers()
        {
            initializeArray();
        }
        void initializeArray()
        {
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++){
                    if(i == 0 || i ==6){
                        array[i][j] = "-";
                    } else if (j == 0 || j == 6)
                        array[i][j] = "|";
                    else
                        array[i][j] = "*";
                }
            }
        }

        void insertValues()
        {
            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    if(i % 2 == 0 && array[i][j] == "*"){
                        array[i][j] = "-";
                    }
                }
            }

            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    if(j == 3 && array[i][j] == "*")
                    {
                        array[i][j] = "|";
                    }
                }
            }
        }

        void displayArray()
        {
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++)
                    std::cout << array[i][j];
                std::cout << "\n" ;                
            }
        }
};

class Flags
{
    private:
        const char* array[4][10];
    public:
        Flags()
        {
            initializeArray();
        }

        void initializeArray()
        {
            for(int i=0; i < 4; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(i == 0 || i == 3)
                        array[i][j] = "-";
                    else if(j == 0 || j == 9)
                        array[i][j] = "|";
                    else
                        array[i][j] = "*";
                }
            }

            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 10; j++){
                    if(array[i][j] == "*" && j %2 == 0)
                        array[i][j] = "|";
                }
            }
        }

        void displayArray()
        {
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 10; j++)
                    std::cout << array[i][j];
                std::cout << std::endl;
            }

        }
};



int main()
{
    Registers register_visualize;
    std::cout << "FLAGS"<< std::endl;
    Flags flags;
    flags.displayArray();
    return 0;
}