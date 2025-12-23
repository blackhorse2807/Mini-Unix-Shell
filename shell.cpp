#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "signals.h"
#include "job_control.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


void Shell::run() {
    setup_signal_handlers();

    while (true) {
        while (waitpid(-1, nullptr, WNOHANG) > 0);

        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        std::cout << "mini-shell:" << cwd << "$ ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input == "jobs") {
            list_jobs();
            continue;
        }

        ParsedLine line = parse_line(input);
        execute_line(line);
    }
}
