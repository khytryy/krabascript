#include <iostream>
#include <fstream>
#include <string>

constexpr const char* KSC_VERSION = "0.0.1";
constexpr const char* KSC_TARGET_X86_64_W64 = "-target=x86_64-w64";
constexpr const char* KSC_TARGET_X86_64_W32 = "-target=x86_64-w32";

constexpr const char* KSC_TARGET_X86_64_UNKNOWN = "-target=x86_64-unknown";

constexpr const char* KSC_TARGET_X86_64_ELF64 = "-target=x86_64-elf64";

constexpr const char* KSC_TARGET_DEFAULT = "-target=x86_64-w64";

std::string platform;
std::string arch;

void showUsage() {
    std::cout << "usage: ksc [options] file..." << std::endl;
}

void showVersion() {
    std::cout << "ksc (build by ks-tools project) " << KSC_VERSION << "\n";
    std::cout << "copyright (C) 2025 khytryy\n";
    std::cout << "this is free software. see the source for copying conditions.\n";
}

bool handleOption(const std::string& arg) {
    if (arg == "--help") {
        showUsage();
        std::exit(0);
    }
    if (arg == "--version") {
        showVersion();
        std::exit(0);
    }
    if (arg == KSC_TARGET_X86_64_W64) {
        platform = "w64";
        return true;
    }

    return false;
}


bool loadSource(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ksc: \033[31merror:\033[0m cannot open file '" << filename << "'\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "ksc: \033[31merror:\033[0m no input file" << std::endl;
        return 1;
    }

    bool fileOpened = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (!arg.empty() && arg[0] == '-') {
            if (!handleOption(arg)) {
                std::cerr << "ksc: \033[31merror:\033[0m unknown option '" << arg << "'\n";
                return 1;
            }
        } else {
            if (!loadSource(arg)) {
                return 1;
            }
            fileOpened = true;
        }
    }

    if (!fileOpened) {
        std::cerr << "ksc: \033[31merror:\033[0m no input file.\n";
        return 1;
    }

    return 0;
}
