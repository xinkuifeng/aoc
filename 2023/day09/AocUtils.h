#ifndef FXK_AOC_UTILS_H_
#define FXK_AOC_UTILS_H_

#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace fxk {

// Returns all the ints in that line.
inline std::vector<int> parse_int(std::string line, bool negative = false) {
    std::stringstream ss;
    ss << "(";
    if (negative) {
        ss << "[-]?";
    }
    ss << "\\d+" << ")";

    std::regex r(ss.str());
    std::smatch sm;
    std::vector<int> res;
    while (std::regex_search(line, sm, r))
    {
        int n = std::stoi(sm.str());
        res.push_back(n);
        line = sm.suffix();
    }
    return res;
}

inline std::vector<long> parse_long(std::string line, bool negative = false) {
    std::stringstream ss;
    ss << "(";
    if (negative) {
        ss << "[-]?";
    }
    ss << "\\d+" << ")";

    std::regex r(ss.str());
    std::smatch sm;
    std::vector<long> res;
    while (std::regex_search(line, sm, r))
    {
        long n = std::stol(sm.str());
        res.push_back(n);
        line = sm.suffix();
    }
    return res;
}

inline std::vector<std::string> split(const std::string line, char c) {
    std::stringstream ss(line);
    std::vector<std::string> res;
    std::string item;

    while (std::getline(ss, item, c)) {
        if (!item.empty()) res.emplace_back(item);
    }

    return res;
}

}

#endif
