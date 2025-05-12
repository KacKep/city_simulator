

#include "City.hpp"

//constexpr int hight = 128;
//constexpr int lenght = 72;

int main() {
    try {
        City app;
        app.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}


