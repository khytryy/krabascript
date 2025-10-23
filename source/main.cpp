#include <iostream>
#include <colors.h>

#include <krabascript.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << RED << "krabascript: error: " << COLOR_RESET <<  "no input file\n";
    }
    return 0;
}