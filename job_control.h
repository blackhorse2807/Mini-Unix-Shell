#pragma once
#include <vector>
#include <string>
#include <sys/types.h>

struct Job {
    pid_t pgid;
    std::string command;
    bool stopped;
};

void add_job(pid_t pgid, const std::string& cmd, bool stopped);
void list_jobs();
Job* get_job(pid_t pgid);
void remove_job(pid_t pgid);
