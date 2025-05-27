#include "City.hpp"
#include <iostream>


int main() {
    try {
        City symulation;
        symulation.start();
    }
    catch (const std::exception& lambert) {
        std::cerr << "Fatal error: " << lambert.what() << '\n';
        return 1;
    }
    return 0;

}



