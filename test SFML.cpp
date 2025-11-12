#include <iostream>
#include <SFML/Config.hpp>

int main() {
    std::cout << "SFML Major: " << SFML_VERSION_MAJOR << std::endl;
    std::cout << "SFML Minor: " << SFML_VERSION_MINOR << std::endl;
    std::cout << "SFML Patch: " << SFML_VERSION_PATCH << std::endl;
    return 0;
}