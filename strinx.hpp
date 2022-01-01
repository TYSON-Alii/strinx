#include <utility>
#include <iostream>
#include <string>
#include <vector>

#define _XS_STRINX_

class strinx : public std::string {
public:
    strinx() = default;
    strinx(const strinx&) = default;
    strinx(string v) : std::string(v) {};
    strinx(const char* v) : std::string(v) {};
    strinx(char v) : std::string(new char[2]{ v ,'\0'}) {};
    strinx(int v) : std::string(std::to_string(v)) {};
    strinx(float v) : std::string(std::to_string(v)) {};
    strinx(double v) : std::string(std::to_string(v)) {};
    template <typename T> strinx(std::initializer_list<T> v) {
        strinx t;
        t += "{ ";
        for (const T& i : v) {
            t += std::to_string(i);
            t += ", ";
        };
        t.pop_back();
        t.pop_back();
        t += " }";
        *this = t;
    };
    template <typename T> strinx(std::vector<T> v) {
        strinx t;
        t += "{ ";
        for (const T& i : v) {
            t += std::to_string(i);
            t += ", ";
        };
        t.pop_back();
        t.pop_back();
        t += " }";
        *this = t;
    };
    char& operator[](const size_t index) { return *(begin() + index); };
    char operator[](const size_t index) const { return *(begin() + index); };
    strinx operator[](std::initializer_list<int> v) const {
        strinx t;
        for (const auto& i : v) t += (*this)[i];
        return t;
    };
    strinx operator+(strinx v) const { return strcat(_strdup(data()), v.c_str()); };
    strinx operator+(auto v) const { return *this + (strinx)v; };
    strinx& operator+=(strinx v) { *this = strcat(data(), v.c_str()); return *this; };
    strinx& operator+=(auto v) { *this += (strinx)v; return *this; };
    inline operator bool() const { return !empty(); };
    inline bool operator!() const { return empty(); };
    template <std::integral T> requires(!std::same_as<T,char>) inline operator T() const { return std::stoi(*this); };
    template <std::floating_point T> inline operator T() const { return std::stof(*this); };
    inline operator char*() { return data(); };
    inline operator const char*() const { return data(); };
    std::vector<strinx> operator%(char split_v) const {
        strinx t;
        std::vector<strinx> s;
        for (const auto& i : *this) {
            if (split_v == i) {
                s.push_back(t);
                t.clear();
            }
            else
                t += i;
        };
        s.push_back(t);
        return s;
    };
    strinx operator/(char split_v) const {
        strinx t;
        for (const auto& i : *this)
            if (split_v != i)
                t += i;
        return t;
    };
    strinx& operator/=(char split_v) {
        const strinx t = *this;
        clear();
        for (const auto& i : t)
            if (split_v != i)
                *this += i;
        return *this;
    };
    inline strinx operator()() const { return *this; };
    inline strinx operator()(int index) const { return this->operator[]((index < 0) ? (size() - index) : index); };
    strinx operator()(int _begin, int _end) const {
        const auto& _b = (_begin < 0) ? (size() + _begin) : _begin;
        const auto& _e = (_end < 0) ? (size() + _end) : _end;
        const auto& rv = _b < _e;
        const auto& st = rv ? 1 : -1;
        auto b = begin() + _b;
        const auto e = begin() + _e;
        strinx s;
        while (b != e) {
            s += *b;
            b += st;
        };
        s += *b;
        return s;
    };
    strinx operator*(const size_t& n) const {
        const auto c = *this;
        strinx t;
        for (size_t i = 0u; i < n; ++i)
            t += c;
        return t;
    };
    strinx& operator*=(const size_t& n) {
        const auto c = *this;
        clear();
        for (size_t i = 0u; i < n; ++i)
            *this += c;
        return *this;
    };
    inline void print() const { std::cout << c_str() << '\n'; };
    strinx first() const { return strinx(data()[0]); };
    strinx last() const { return strinx((*this)[size()-1u]); };
    strinx& reverse() {
        const auto& b = begin();
        auto e = end();
        strinx t;
        while (b != e) {
            e--;
            t += *e;
        };
        *this = t;
        return *this;
    };
    strinx reverse() const {
        const auto& b = begin();
        auto e = end();
        strinx t;
        while (b != e) {
            e--;
            t += *e;
        };
        return t;
    };
    strinx& swap(int index1, int index2) {
        index1 = (index1 < 0) ? (int(size()) - index1) : index1;
        index2 = (index2 < 0) ? (int(size()) - index2) : index2;
        const auto& i1 = begin() + index1;
        const auto& i2 = begin() + index2;
        std::swap(*i1, *i2);
        return *this;
    };
    strinx swap(int index1, int index2) const {
        strinx t(*this);
        index1 = (index1 < 0) ? (int(size()) - index1) : index1;
        index2 = (index2 < 0) ? (int(size()) - index2) : index2;
        const auto& i1 = t.begin() + index1;
        const auto& i2 = t.begin() + index2;
        std::swap(*i1, *i2);
        return t;
    };
    strinx random() const {
        strinx temp;
        size_t p;
        std::vector<size_t> ss;
        const int& _size = int(size());
        for (size_t i = 0; i < size(); i++) {
            p = rand() % _size;
        _r:;
            for (const auto& j : ss)
                if (j == p) {
                    p = rand() % _size;
                    goto _r;
                };
            ss.push_back(p);
            temp += data()[p];
        }
        return temp;
    };
};
typedef strinx stx;
strinx operator""stx(const char* v, size_t) { return strinx(v); };
strinx operator""stx(unsigned long long v) { return strinx(int(v)); };
