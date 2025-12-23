#include "parser.h"
#include <sstream>

ParsedLine parse_line(const std::string& input) {
    ParsedLine result;
    result.background = false;

    std::stringstream ss(input);
    std::string token;
    Command current;

    while (ss >> token) {
        if (token == "&") {
            result.background = true;
        } else if (token == "|") {
            result.pipeline.push_back(current);
            current = Command{};
        } else if (token == "<") {
            ss >> current.input_redir;
        } else if (token == ">") {
            ss >> current.output_redir;
        } else {
            current.args.push_back(token);
        }
    }
    result.pipeline.push_back(current);
    return result;
}
