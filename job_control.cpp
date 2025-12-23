#include "job_control.h"
#include <algorithm>
#include <iostream>

static std::vector<Job> jobs;

void add_job(pid_t pgid, const std::string& cmd, bool stopped) {
    jobs.push_back({pgid, cmd, stopped});
}

void list_jobs() {
    for (size_t i = 0; i < jobs.size(); ++i) {
        std::cout << "[" << i + 1 << "] "
                  << (jobs[i].stopped ? "Stopped" : "Running")
                  << " " << jobs[i].command << "\n";
    }
}

Job* get_job(pid_t pgid) {
    for (auto& job : jobs)
        if (job.pgid == pgid)
            return &job;
    return nullptr;
}

void remove_job(pid_t pgid) {
    jobs.erase(
        std::remove_if(jobs.begin(), jobs.end(),
            [&](const Job& j) { return j.pgid == pgid; }),
        jobs.end()
    );
}
