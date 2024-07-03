#include <iostream>
#include "../include/driver.h"

int main(int argc, char **argv)
{
    std::cout << std::string(argv[2]) << '\n';
    compress_file(std::string(argv[2]));
    return EXIT_SUCCESS;
}
