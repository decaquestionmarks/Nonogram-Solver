#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>

constexpr bool debugmode = false;

void debug(std::string s);

enum Direction {
    Horizontal,
    Vertical
};

#endif
