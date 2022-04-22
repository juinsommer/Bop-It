#include <iostream>

int main() {
    int value = 10;

    int tens, ones;

    while(value < 100) {
        ones = value % 10;
        tens = (value / 10) % 10;

        std::cout << tens << " " << ones << std::endl;
        ++value;
    }
    return 0;
}

