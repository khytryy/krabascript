#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "parser.h"

constexpr const char* KSC_VERSION = "0.0.1";
constexpr const char* KSC_TARGET_X86_64_W64 = "-target=x86_64-w64";
constexpr const char* KSC_TARGET_X86_64_W32 = "-target=x86_64-w32";

constexpr const char* KSC_TARGET_X86_64_UNKNOWN = "-target=x86_64-unknown";

constexpr const char* KSC_TARGET_X86_64_ELF64 = "-target=x86_64-elf64";

constexpr const char* KSC_TARGET_DEFAULT = "-target=x86_64-w64";

std::string platform;
std::string arch;

std::vector<std::string> sourceCode;

Tokenizer tokenizer;

void showUsage() {
    std::cout << "usage: ksc [options] file..." << std::endl;
}

void showVersion() {
    std::cout << "krabascript compiler (created by ks-tools project) " << KSC_VERSION << "\n";
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

int main(int argc, char* argv[]) {
    sourceCode.clear();
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

            if (!tokenizer.loadSource(arg, sourceCode)) {
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
