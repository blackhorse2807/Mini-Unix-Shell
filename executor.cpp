#include "executor.h"
#include "job_control.h"
#include <signal.h>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>

void execute_line(const ParsedLine& line) {
    int pipefd[2];
    int prev_fd = -1;
    pid_t pgid = 0;

    for (size_t i = 0; i < line.pipeline.size(); ++i) {
        if (i < line.pipeline.size() - 1)
            pipe(pipefd);

        pid_t pid = fork();

        if (pid == 0) {
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            if (pgid == 0) pgid = getpid();
            setpgid(0, pgid);

            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (i < line.pipeline.size() - 1) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            if (!line.pipeline[i].input_redir.empty()) {
                int fd = open(line.pipeline[i].input_redir.c_str(), O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }

            if (!line.pipeline[i].output_redir.empty()) {
                int fd = open(line.pipeline[i].output_redir.c_str(),
                              O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            std::vector<char*> args;
            for (auto& s : line.pipeline[i].args)
                args.push_back(const_cast<char*>(s.c_str()));
            args.push_back(nullptr);

            execvp(args[0], args.data());
            perror("exec");
            _exit(1);
        }

        if (pgid == 0) pgid = pid;
        setpgid(pid, pgid);

        if (prev_fd != -1) close(prev_fd);
        if (i < line.pipeline.size() - 1) {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
    }

    if (!line.background) {
        tcsetpgrp(STDIN_FILENO, pgid);
        waitpid(-pgid, nullptr, 0);
        tcsetpgrp(STDIN_FILENO, getpgrp());
    } else {
        add_job(pgid, line.pipeline[0].args[0], false);
        std::cout << "[BG] " << pgid << "\n";
    }
}
