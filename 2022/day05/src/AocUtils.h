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

}

#endif
