#include "hint.hpp"

Hint::Hint() {
}

Hint::Hint(size_t n) {
    data.resize(n);
}

Hint::Hint(const std::vector<size_t> &d) {
    data = d;
}

Hint::~Hint() {
}

size_t Hint::size() const {
    return data.size();
}

size_t &Hint::operator[](size_t i) {
    return data[i];
}

const size_t &Hint::operator[](size_t i) const {
    return data[i];
}

const std::vector<size_t> &Hint::getAll() const {
    return data;
}

