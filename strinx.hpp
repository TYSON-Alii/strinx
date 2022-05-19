#include <string>
#include <vector>
class strinx : public std::string {
    using str = std::string;
    using stx = strinx;
public:
    using std::string::string;
    strinx() : str() { };
    strinx(const str& s) : str(s) { };
    strinx(const stx&) = default;
    strinx(char v) : str(new char[2]{ v ,'\0' }) {};
    strinx(int v) : str(std::to_string(v)) {};
    strinx(float v) : str(std::to_string(v)) {};
    strinx(double v) : str(std::to_string(v)) {};
    template <typename T> strinx(const std::basic_string<T>& s) : str(s.begin(), s.end()) { }
    template <typename T> strinx(std::initializer_list<T> v) {
        stx& t = *this;
        t += "{ ";
        if (v.size() != 0) {
            const auto& beg = v.begin();
            const auto& end = v.end() - 1;
            for (auto it = beg; it != end; it++) {
                t += stx(*it);
                t += ", ";
            };
            t += *end;
        };
        t += "}";
    };
    template <typename T> strinx(std::vector<T>::iterator beg, std::vector<T>::iterator end) {
        stx& t = *this;
        t += "{ ";
        if (std::distance(beg, end) != 0) {
            const auto& b = beg;
            const auto& e = end - 1;
            for (auto it = b; it != e; it++) {
                t += stx(*it);
                t += ", ";
            };
            t += *end;
            t += ' ';
        };
        t += "}";
    };
    inline operator bool() const { return not empty(); };
    inline bool operator!() const { return empty(); };
    inline auto operator*() { return data(); };
    inline explicit operator int() { return stoi(*this); };
    inline explicit operator float() { return stof(*this); };
    inline explicit operator double() { return stod(*this); };
    inline explicit operator unsigned long() { return stoul(*this); };
    inline explicit operator unsigned long long() { return stoull(*this); };
    inline explicit operator char*() { return data(); };
    inline explicit operator char*() const { return _strdup(data()); };
    inline explicit operator const char*() const { return data(); };
    inline stx operator()(const int& index) const { return empty() ? (*this) : stx(operator[]((index < 0) ? (size() - ((-index) % (size()+1)-1)) : (index % (size()+1)))); };
    stx operator()(int beg, int end) const {
        if (!empty()) {
            const auto& s = size() + 1;
            beg = (beg < 0) ? (size() - ((-beg) % s - 1)) : (beg % s);
            end = (end < 0) ? (size() - ((-end) % s - 1)) : (end % s);
            return ((beg < end) ? (stx(this->begin() + beg, this->begin() + end)) : (stx(this->rbegin() + end, this->rbegin() + beg)));
        }
        else return *this;
    };
    inline stx operator+(const auto& v) const { return str::operator+(stx(v)); };
    inline stx& operator+=(const auto& v) { str::operator+=(stx(v)); return (*this); };
    inline stx operator-(const auto& v) const { return takeout((stx)v); };
    inline stx& operator-=(const auto& v) { takeout((stx)v); return (*this); };
    inline stx& push(const auto& v) { push_back((stx)v); return *this; };
    inline stx& pop() { if (!empty()) pop_back(); return *this; };
    inline stx& operator--() { return pop(); };
    inline stx& pop(int index) { if (!empty()) erase(begin() + ((index < 0) ? (size() - ((-index) % (size()+1)-1)) : (index % (size()+1)))); return *this; };
    stx operator*(const size_t& n) const {
        const auto copy = *this;
        strinx t;
        for (size_t i = 0u; i < n; ++i) t += copy;
        return t;
    };
    stx& operator*=(const size_t& n) {
        const auto c = *this;
        clear();
        for (size_t i = 0u; i < n; ++i) *this += c;
        return *this;
    };
    std::vector<stx> operator%(const auto& split_) const {
        const stx& split_v = (stx)split_;
        stx c = *this;
        std::vector<stx> l;
        while (c.find(split_v) != str::npos) {
            const auto& f = c.begin() + c.find(split_v);
            l.push_back(str(c.begin(), f));
            c.erase(c.begin(), f + split_v.size());
        };
        l.push_back(str(c.begin(), c.end()));
        return l;
    };
    stx operator/(const auto& split_) const {
        const stx& split_v = (stx)split_;
        stx t, c = *this;
        while (c.find(split_v) != str::npos) {
            const auto& f = c.begin() + c.find(split_v);
            t += str(c.begin(), f);
            c.erase(c.begin(), f + split_v.size());
        };
        t += str(c.begin(), c.end());
        return t;
    };
    stx& operator/=(const auto& split_) {
        const stx& split_v = (stx)split_;
        stx c = *this;
        clear();
        while (c.find(split_v) != str::npos) {
            const auto& f = c.begin() + c.find(split_v);
            (*this) += str(c.begin(), f);
            c.erase(c.begin(), f + split_v.size());
        };
        (*this) += str(c.begin(), c.end());
        return *this;
    };
    stx random() const {
        stx temp;
        size_t p;
        std::vector<size_t> l;
        for (const auto& i : (*this)) {
            p = rand() % size();
        _r:;
            for (const auto& j : l) {
                if (j == p) {
                    p = rand() % size();
                    goto _r;
                };
            };
            l.push_back(p);
            temp += operator[](p);
        };
        return temp;
    };
    stx& fill(const auto& fill_) {
        const stx& fill_v = (stx)fill_;
        if (fill_v.empty())
            clear();
        else if (fill_v.size() == 1)
            std::fill(begin(), end(), fill_v.back());
        else {
            const auto& s = size();
            *this = fill_v;
            *this *= s;
        };
        return *this;
    };
    stx filter(const auto& filter_, const auto& v_) {
        const stx& filter = (stx)filter_, v = (stx)v_;
        stx t, c = *this;
        while (c.find(filter) != str::npos) {
            const auto& f = c.begin() + c.find(filter);
            t += stx(c.begin(), f);
            t += v;
            c.erase(c.begin(), f + filter.size());
        };
        t += stx(c.begin(), c.end());
        return t;
    };
    stx& takeout(const auto& f_) {
        const stx& f = (stx)f_;
        const auto& i = this->find(f);
        if (i != str::npos) erase(begin() + i, begin() + i + f.size());
        return *this;
    };
    stx takeout(const auto& f_) const {
        const stx& f = (stx)f_;
        stx t = *this;
        const auto& i = t.find(f);
        if (i != str::npos) t.erase(t.begin() + i, t.begin() + i + f.size());
        return t;
    };
    stx reverse() const { return stx(rbegin(), rend()); };
    template <typename T> stx join(const std::initializer_list<T>& l) const {
        stx temp;
        if (l.size() != 0) {
            const auto& sep = *this;
            auto it = l.begin();
            const auto& end = l.end();
            temp += (stx)(*it);
            it++;
            while (it != end) {
                temp += sep;
                temp += *it;
                it++;
            }
        }
        return temp;
    };
    template <typename T> stx join(const T& l, auto it_beg, auto it_end) const {
        stx temp;
        if (l.size() != 0) {
            const auto& sep = *this;
            auto it = it_beg;
            const auto& end = it_end;
            temp += (stx)(*it);
            it++;
            while (it != end) {
                temp += sep;
                temp += *it;
                it++;
            }
        }
        return temp;
    };
    template <typename T> inline stx join(const T& l) const { return join(l, l.begin(), l.end()); };
    inline bool in(const auto& is_in_) const {
        const stx& is_in = (stx)is_in_;
        if (is_in.empty() or empty() or is_in.size() > size())
            return false;
        else if (is_in.size() == 1)
            return std::find(begin(), end(), is_in[0]) != end();
        else
            return this->find(is_in) != str::npos;
        return false;
    };
    stx upper() const {
        strinx t;
        for (const auto& i : *this) t += (i > 96 and i < 123) ? char(i - ' ') : char(i);
        return t;
    };
    stx lower() const {
        strinx t;
        for (const auto& i : *this) t += (i > 64 and i < 91) ? char(i + ' ') : char(i);
        return t;
    };
    bool is_upper(int index = 0) const { const auto& i = operator()(index); return (i > 96 and i < 123); };
    bool is_lower(int index = 0) const { const auto& i = operator()(index); return (i > 64 and i < 91); };
};
using stx = strinx;
strinx operator""_stx(const char* v, size_t) { return strinx(v); };
inline strinx operator+(const char* l, strinx v) { return strinx(l) + v; };
