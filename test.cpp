#include <iostream>
#include <windows.h>

using namespace std;

int barl = 20;

int main()
{
    float progress = 0.0;
    while (progress < 1.0) {
        int barWidth = 70;

        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();

        progress += 0.00016; // for demonstration only
    }
}