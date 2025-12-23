#pragma once
#include <vector>
#include <string>

struct Command {
    std::vector<std::string> args;
    std::string input_redir;
    std::string output_redir;
};

struct ParsedLine {
    std::vector<Command> pipeline;
    bool background;
};

ParsedLine parse_line(const std::string& input);
