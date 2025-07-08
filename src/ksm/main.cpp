#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


#ifdef _WIN32
#include <direct.h>

#else

#include <sys/stat.h>
#include <unistd.h>
#endif

constexpr const char* KSM_VERSION = "0.0.1";

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string command = argv[1];

        if (command == "--version") {

            std::cout << "krabascript manager (created by ks-tools project) " << KSM_VERSION << "\n";
            std::cout << "copyright (C) 2025 khytryy\n";
            std::cout << "this is free software. see the source for copying conditions.\n";
            return 0;

        } else if (command == "build") {
            const char* command = "ksc src/main.ks";
            int result = std::system(command);
            return result;
        } else if (command == "help") {
            std::cout << "usage: ksm [option] name\n";
            std::cout << "options:\n" << "\n";

            std::cout << "  general:\n" << "\n";

            std::cout << "  help        help menu\n";
            std::cout << "  build       compiles the project\n";
            std::cout << "              (reads params from settings.toml)\n" << "\n";

            std::cout << "  run         builds and runs the project\n" << "\n";

            std::cout << "  project management:\n" << "\n";

            std::cout << "  new         creates a new project\n";
            std::cout << "  delete      deletes a project\n" << "\n";

            return 0;

        } else {

            std::cerr << "ksm: \033[31merror:\033[0m unknown command '" << command << "'\n";
            return 1;

        }

        

    } else if (argc > 2) {
        std::string command = argv[1];
        std::string projectName = argv[2];

        if (command == "new") {

            #ifdef _WIN32

            int ret = _mkdir(projectName.c_str());
            _chdir(projectName.c_str());
            _mkdir("src");

            _mkdir("build");
            _chdir("src");

            std::ofstream outfile("main.ks");

            if (!outfile) {
                std::cerr << "ksm: \033[31merror:\033[0m failed to create a main.ks\n";
                return 1;
            }

            #else
            int ret = mkdir(projectName.c_str(), 0755);
            _mkdir("src");

            _mkdir("build");
            _chdir("src");

            std::ofstream outfile("main.ks");

            if (!outfile) {
                std::cerr << "ksm: \033[31merror:\033[0m failed to create a main.ks\n";
                return 1;
            }
            #endif

            if (ret == 0) {
                std::cout << "\033[33mksm: created a new project '" << projectName << "'\033[0m\n";
                return 0;
            } else {
                perror("ksm: \033[31merror:\033[0m failed to create a project");
                return 1;
            }
        } else {
            std::cerr << "ksm: \033[31merror:\033[0m unknown option '" << command << "'\n";
            return 1;
        }
    } else {
        std::cerr << "ksm: \033[31merror:\033[0m nothing to do...\n";
        return 1;
    }
}