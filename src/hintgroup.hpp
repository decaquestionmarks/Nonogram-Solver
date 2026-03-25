#ifndef HINTGROUP_HPP
#define HINTGROUP_HPP


#include <vector>
#include "hint.hpp"
#include "helpers.hpp"
#include <string>
#include <iostream>

class HintGroup {
    private:
        std::vector<Hint> data;
        const Direction dir;
        size_t longest;
    public:
        HintGroup(Direction d);
        HintGroup(size_t n, Direction d);
        HintGroup(const std::vector<Hint> &d, Direction di);
        ~HintGroup();

        void findLongest();
        size_t size() const;
        const Direction getDirection() const;

        Hint &operator[](size_t i);
        const Hint &operator[](size_t i) const;
        const std::vector<Hint> &getAllHints() const;

        void vertPrint(std::ostream &os, size_t offset) const;
        std::string getHorizPrint(size_t i) const;
};

#endif