#ifndef NONOGRAM_HPP
#define NONOGRAM_HPP
#include <iostream>
#include <string>
#include <vector>

class Line{
    private:
        std::vector<bool> data;
        size_t length;
        bool horizontal;
    public:
        Line(size_t n, bool h);
        Line(std::vector<bool> d, bool h);
        ~Line();
        Line operator&(Line o);
        bool implies(Line o);
        size_t size();
        bool at(size_t n);
        Line operator|(Line o);
        Line operator!();
        bool compatible(Line o);
        bool valid(size_t hused, size_t bitsused, std::vector<int> hint, bool debug);
};

class Nonogram{ 
    private:
        std::vector<std::vector<bool>> board;
        size_t height;
        size_t width;
        std::vector<std::vector<int>> hclues;
        std::vector<std::vector<int>> vclues;
    public:
        Nonogram(size_t w, size_t h);
        ~Nonogram();
        void display();
        void set(size_t x, size_t y);
        void scramble();
        void updateHints();
        size_t getHeight();
        size_t getWidth();
        std::vector<std::vector<int>> getHorizontalClues();
        std::vector<std::vector<int>> getVerticalClues();
        bool get(size_t x, size_t y);
        Line getLine(size_t n, bool horizontal);
};

#endif