#include <utility>
#include <iostream>
#include <string>
#include <vector>

class strinx : public std::string {
public:
    using std::string::string;
    using std::string::at;
    using std::string::clear;
    using std::string::iterator;
    using std::string::const_iterator;
    using std::string::begin;
    using std::string::end;
    using std::string::cbegin;
    using std::string::cend;
    using std::string::crbegin;
    using std::string::crend;
    using std::string::rbegin;
    using std::string::rend;
    using std::string::empty;
    using std::string::size;
    using std::string::reserve;
    using std::string::assign;
    using std::string::insert;
    using std::string::erase;
    using std::string::front;
    using std::string::back;
    using std::string::pop_back;
    using std::string::push_back;
    using std::string::resize;
    using std::string::operator+=;
    using std::string::operator[];
    using std::string::operator=;
    //strinx(string v) : std::string(v) {};
    strinx(char v) : std::string(new char[2]{ v ,'\0' }) {};
    strinx(int v) : std::string(std::to_string(v)) {};
    strinx(float v) : std::string(std::to_string(v)) {};
    strinx(double v) : std::string(std::to_string(v)) {};
    template <typename T> strinx(std::initializer_list<T> v) {
        strinx t;
        t += "{ ";
        for (const T& i : v) {
            t += strinx(i);
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
            t += strinx(i);
            t += ", ";
        };
        t.pop_back();
        t.pop_back();
        t += " }";
        *this = t;
    };
    inline auto operator*() const { return data(); };
    inline auto operator*() { return data(); };
    strinx operator[](std::initializer_list<int> v) const {
        strinx t;
        for (const auto& i : v) t += (*this)[i];
        return t;
    };
    inline strinx operator+(strinx v) const { return strcat(_strdup(data()), v.c_str()); };
    inline strinx operator+(const auto& v) const { return *this + (strinx)v; };
    inline strinx& operator+=(strinx v) { *this += v.c_str(); return *this; };
    inline strinx& operator+=(const auto& v) { *this += (strinx)v; return *this; };
    inline strinx& operator<<(const auto& v) { return (*this) += (strinx)v; };
    inline operator bool() const { return !empty(); };
    inline bool operator!() const { return empty(); };
    template <std::integral T> requires(!std::same_as<T, char>) inline operator T() const { return std::stoi(*this); };
    template <std::floating_point T> inline operator T() const { return std::stof(*this); };
    inline operator char* () { return data(); };
    inline operator const char* () const { return data(); };
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
    strinx operator()(const int& _begin, const int& _end) const {
        const auto _b = (_begin < 0) ? (size() + _begin) : _begin;
        const auto _e = (_end < 0) ? (size() + _end) : _end;
        const auto rv = _b < _e;
        const auto st = rv ? 1 : -1;
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
    inline auto& print() const { std::cout << c_str() << '\n'; return std::cout; };
    strinx first() const { return strinx(data()[0]); };
    strinx last() const { return strinx((*this)[size() - 1u]); };
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
    bool in(const strinx& is_in) {
        if (is_in.size() > size())
            return false;
        else if (is_in.size() == 1)
            return std::find(begin(), end(), is_in[0]) != end();
        else if (is_in.size() > 1) {
            const auto& sl = is_in.size() - 1;
            for (size_t i = 0; i < size(); i++) {
                if (is_in == operator()(i, i + sl))
                    return true;
            }
            return false;
        };
        return false;
    };
    strinx upper() const {
        strinx t;
        for (const auto i : *this) t += (i > 96 and i < 123) ? char(i - ' ') : char(i);
        return t;
    };
    strinx lower() const {
        strinx t;
        for (const auto i : *this) t += (i > 64 and i < 91) ? char(i + ' ') : char(i);
        return t;
    };
};
typedef strinx stx;
inline strinx operator""_stx(const char* v, size_t) { return strinx(v); };
inline strinx operator""_stx(unsigned long long v) { return strinx(int(v)); };
inline strinx operator+(const char* l, strinx v) { return strinx(l) + v; };
