#ifndef SOLVER_HPP
#define SOLVER_HPP
#include <iostream>
#include <string>
#include "nonogram.hpp"


class Solver{ 
    private:
        Nonogram puzzle;
        std::vector<std::vector<bool>> board;
        std::vector<std::vector<bool>> xboard;
        size_t height;
        size_t width;
        std::vector<std::vector<int>> hclues;
        std::vector<std::vector<int>> vclues;
    public:
        Solver(Nonogram n);
        ~Solver();
        void display(bool debug);
        void flip(size_t x, size_t y);
        bool valid(bool debug);
        bool Partialcorrect();
        bool correct();
        Line getLine(size_t n, bool horizontal);
        void markx(size_t x, size_t y);
        Line getxLine(size_t n, bool horizontal);
        std::vector<std::vector<bool>> generateAll(const std::vector<int> &hint, size_t n);
        void solveLine(size_t n, bool horizontal);
        void stepBoard();
};

#endif