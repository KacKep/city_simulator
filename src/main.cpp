

#include "City.hpp"

//constexpr int hight = 128;
//constexpr int lenght = 72;

int main() {
    try {
        City symulation;
        symulation.start();
    }
    catch (const std::exception& lambert) {
        std::cerr << "Fatal error: " << lambert.what() << '\n';
        return 1;
    }
    //std::cout << "Program exit complete\n";
    return 0;

}



