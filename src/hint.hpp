#ifndef HINT_HPP
#define HINT_HPP

#include <vector>

class Hint {
    private:
        std::vector<size_t> data;
    public:
        Hint();
        Hint(size_t n);
        Hint(const std::vector<size_t> &d);
        ~Hint();

        size_t size() const;

        size_t &operator[](size_t i);
        const size_t &operator[](size_t i) const;

        const std::vector<size_t> &getAll() const;
};

#endif