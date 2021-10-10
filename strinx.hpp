#include <sstream>
#include <vector>

class strinx{
private:
	char* _str = new char[1]{'\0'};
	size_t _size = 0;
	size_t _it = 0;
	std::string stx(float v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(double v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(int v) { return std::to_string(v); };
	std::string stx(char v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(const char* v) { return std::string(v); };
	std::vector<strinx> _split;
	bool _splt = false;
public:
	friend std::ostream& operator<<(std::ostream& os, const strinx& v);
	operator bool() { return _size > 0 ? true : false; };
	operator int() { return this->to_int(); };
	operator float() { return this->to_float(); };
	operator double() { return this->to_double(); };
	operator std::string() { return this->str(); };
	class Split_it_t {
	private:
		std::vector<char> _ss;
		bool _is_in(char v) {
			for (auto i : _ss)
				if (i == v)
					return true;
			return false;
		};
	public:
		Split_it_t() { _ss.push_back(' '); _ss.push_back('\n'); _ss.push_back('\t'); };
		void reset() { *this = Split_it_t(); };
		bool operator()(char v) {
			if (_is_in(v))
				return false;
			else {
				_ss.push_back(v);
				return true;
			};
		};
		bool del(char v) {
			if (!_is_in(v))
				for (volatile size_t i = 0; i < _ss.size(); i++)
					if (_ss[i] == v) {
						_ss.erase(_ss.begin() + i);
						return true;
					};
			return false;
		};
		bool operator-=(char v) { return del(v); };
		bool operator+=(char v) {
			if (_is_in(v))
				return false;
			else {
				_ss.push_back(v);
				return true;
			};
		};
		char& operator[](size_t v) { return _ss[v]; };
		void print() { for (volatile size_t i = 0; i < _ss.size(); i++) { std::cout << _ss[i]; }; };
		size_t size() { return _ss.size(); };
		size_t lenght() { return _ss.size(); };
	};
	char* data() { return _str; };
	size_t size() { return _size; };
	size_t lenght() { return _size; };
	size_t len() { return _size; };
	char& front() { return _str[0]; };
	char& back() { return _str[_size - 1]; };
	strinx first() { return strinx(_str[0]); };
	strinx last() { return strinx(_str[_size - 1]); };
	char& middle() { return _str[_size / 2]; };
	Split_it_t split_it;
	size_t& iterator() { return _it; };
	void reset() { _it = 0; };
	bool canmove() { return _it >= _size ? false : true; };
	bool canmoveback() { return _it == 0 ? false : true; };
	bool canmoveline() {
		if (canmove()) {
			for (volatile size_t _i = _it; ; _i++) {
				if (_i >= _size)
					return false;
				if (_str[_i] == '\n' || _i == _size - 1)
					return true;
			};
		}
		else
			return false;
	}
	bool move() {
		if (_it < _size) {
			_it++;
			return true;
		}
		else
			_it = 0;
		return true;
	};
	bool moveback() {
		if (_it > -1) {
			_it--;
			return true;
		}
		else
			_it = _size - 1;
		return false;
	};
	bool move(size_t v) {
		if (_it < _size && _it + v < _size) {
			_it += v;
			return true;
		}
		else
			_it = _it + v - _size;
		return false;
	};
	bool moveback(size_t v) {
		if (_it > -1 && _it - v > -1) {
			_it -= v;
			return false;
		}
		else
			_it = _size - (_it + v - _size);
		return false;
	};
	/*bool moveline() {
		if (canmove()) {
			move();
			while (true) {
				if (_str[_it] == '\n')
					return true;
				if (!canmove())
					return false;
				_it++;
			};
		}
		else
			return false;
	}*/
	bool operator++() { return move(); };
	bool operator--() { return moveback(); };
	const char* c_str() { return _str; };
	std::string str() { return std::string(c_str()); };
	strinx() = default;
	strinx(const strinx&) = default;
	strinx(const char* v)	{ strcpy(_str, _strdup(v)); _size = strlen(_str); };
	strinx(char v)			{ strcpy(_str, new char[2]{ v, '\0' }); _size = 1; };
	strinx(std::string& v)	{ strcpy(_str, _strdup(v.c_str())); _size = v.size(); };
	strinx(int v)			{ strcpy(_str, _strdup(stx(v).c_str())); _size = strlen(_str); };
	strinx(double v)		{ strcpy(_str, _strdup(stx(v).c_str())); _size = strlen(_str); };
	strinx(float v)			{ strcpy(_str, _strdup(stx(v).c_str())); _size = strlen(_str); };
	strinx(std::initializer_list<int> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	strinx(std::initializer_list<const char*> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	strinx(std::initializer_list<float> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	char& operator[](const size_t& v) { return _str[v]; };
	strinx operator()() { return *this; };
	strinx operator()(const size_t& v) { return strinx(_str[v]); };
	strinx operator()(const size_t& begin, const size_t& end) {
		strinx _t;
		if (begin < end)
			for (size_t i = begin; i < end; i++)
				_t += _str[i];
		else if (begin == end)
			_t = _str[begin];
		else
			for (size_t i = begin; i > end; i--)
				_t += _str[i];
		return _t;
	};
	void print() { std::cout << c_str() << '\n'; };
	void clear() { memset(_str, 0, _size); _size = 0; };
	void resize(const size_t& v, char c = ' ') {
		if (v < _size) {
			strinx _c = *this;
			*this = _c(0, v);
			_size = v;
		}
		else {
			strinx _c = *this;
			*this = _c(0, _size) + _c(_size, v);
			_size = v;
		};
	};
	void pop_last() { *this = _size > 0 ? this->operator()(0, _size - 1) : *this; };
	void pop_first() { *this = _size > 0 ? this->operator()(1, _size) : *this; };
	typedef std::vector<strinx> Split_t;
	Split_t& split() {
		if (!_splt) {
			strinx c = *this, s;
			while (c >> s)
				_split.push_back(s);
			_splt = true;
			return _split;
		}
		else
			return _split;
	};

	strinx random() {
		strinx temp;
		size_t p;
		std::vector<size_t> ss;
		for (size_t i = 0; i < _size; i++) {
			p = rand() % _size;
		_r:;
			for (auto& j : ss)
				if (j == p) {
					p = rand() % _size;
					goto _r;
				};
			ss.push_back(p);
			temp += this->operator[](p);
		}
		_splt = false;
		return temp;
	};

	void format() {};
	template <typename T, typename ...TAIL>
	strinx& format(const T& v, TAIL... tail) {
		strinx c = *this;
		c.reset();
		strinx s, t;
		while (c >> s) {
			if (s == "{}") {
				t += v;
				std::cout << t << '\n';
				format(tail...);
			}
			else
				t += s;
			if (c.canmove())
				t += ' ';
		};
		_splt = false;
		*this = t;
		return t;
	};

	strinx title() {
		strinx c = *this, s, t;
		while (c >> s) {
			s.reset();
			s.up();
			t += s;
			if (c.canmove())
				t += ' ';
		}
		return t;
	};

	strinx reverse() {
		strinx t;
		for (int i = this->size() - 1; i >= 0; i--)
			t += this->operator[](i);
		return t;
	};

	strinx strip() {
		strinx c = *this, s, t;
		c >> s;
		c = c(c.iterator() - s.size(), c.size());
		c.reset();
		c.reverse();
		c >> s;
		t = c(c.iterator() - s.size(), c.size());
		return t;
	};

	bool starts_with(char v) {
		if (_size > 0)
			return _str[0] == v;
		else
			return false;
	};
	bool starts_with(const char* v) {
		if (_size > strlen(v))
			return this->operator()(0, strlen(v)) == v;
		else if (_size == strlen(v))
			return *this == v;
		else
			return false;
	};
	bool starts_with(std::string v) {
		if (_size > v.size())
			return this->operator()(0, v.size() - 1) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(strinx v) {
		if (_size > v.size())
			return this->operator()(0, v.size() - 1) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(int v) {
		if (_size > stx(v).size())
			return this->operator()(0, stx(v).size() - 1) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(float v) {
		if (_size > stx(v).size())
			return this->operator()(0, stx(v).size() - 1) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};

	bool ends_with(char v) {
		if (_size > 0)
			return _str[_size-1] == v;
		else
			return false;
	};
	bool ends_with(const char* v) {
		if (_size > strlen(v))
			return this->operator()(_size - strlen(v), _size) == v;
		else if (_size == strlen(v))
			return *this == v;
		else
			return false;
	};
	bool ends_with(std::string v) {
		if (_size > v.size())
			return this->operator()(_size - v.size(), _size) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(strinx v) {
		if (_size > v.size())
			return this->operator()(_size - v.size(), _size) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(int v) {
		if (_size > stx(v).size())
			return this->operator()(_size - stx(v).size(), _size) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(float v) {
		if (_size > stx(v).size())
			return this->operator()(_size - stx(v).size(), _size) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};

	void operator=(char v)			{ _str = new char[2]{ v, '\0' }; _size = 1; _splt = false; };
	void operator=(const char* v)	{ _str = _strdup(v); _size = strlen(v); _splt = false; };
	void operator=(std::string v)	{ _str = _strdup(v.c_str()); _size = v.size(); _splt = false; };
	void operator=(int v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); _splt = false; };
	void operator=(float v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); _splt = false; };
	void operator=(std::initializer_list<int> v) { *this = strinx(v); _splt = false; };
	void operator=(std::initializer_list<float> v) { *this = strinx(v); _splt = false; };
	void operator=(std::initializer_list<const char*> v) { *this = strinx(v); _splt = false; };

	void operator+=(const char* v)	{
		if (_size == 0)
			_str = _strdup(v);
		else {
			const size_t s = _size + strlen(v);
			char* c = new char[s]{0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v);
			_str = c;
		};
		_size += strlen(v);
		_splt = false;
	};
	void operator+=(char v) {
		char* c = new char[2]{ v, '\0'};
		if (_size == 0)
			_str = c;
		else {
			char* c = new char[_size + 1]{ 0 };
			strncpy(c, (const char*)_str, _size);
			strcat(c, &v);
			_str = c;
		};
		_size++;
		_splt = false;
	};
	void operator+=(std::string v) {
		if (_size == 0)
			_str = _strdup(v.c_str());
		else {
			const size_t s = _size + v.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v.c_str());
			_str = c;
		};
		_size += v.size();
		_splt = false;
	};
	void operator+=(strinx v) {
		if (_size == 0)
			_str = _strdup(v.c_str());
		else {
			const size_t s = _size + v.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v.c_str());
			_str = c;
		};
		_size += v.size();
		_splt = false;
	};
	void operator+=(int v) {
		const std::string f = stx(v);
		if (_size == 0)
			_str = _strdup(f.c_str());
		else {
			const size_t s = _size + f.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, f.c_str());
			_str = c;
		};
		_size += f.size();
		_splt = false;
	};
	void operator+=(float v) {
		const std::string f = stx(v);
		if (_size == 0)
			_str = _strdup(f.c_str());
		else {
			const size_t s = _size + f.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, f.c_str());
			_str = c;
		};
		_size += f.size();
		_splt = false;
	};
	void operator+=(std::initializer_list<int> v) { *this += strinx(v); _splt = false; };
	void operator+=(std::initializer_list<float> v) { *this += strinx(v); _splt = false; };
	void operator+=(std::initializer_list<const char*> v) { *this += strinx(v); _splt = false; };

	strinx& operator<<(const char* v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(char v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::string v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(strinx v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(int v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(float v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<int> v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<float> v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<const char*> v) { *this += ' '; *this += v; return *this; };

	strinx& operator<(const char* v) { *this += v; return *this; };
	strinx& operator<(char v) { *this += v; return *this; };
	strinx& operator<(std::string v) { *this += v; return *this; };
	strinx& operator<(strinx v) { *this += v; return *this; };
	strinx& operator<(int v) { *this += v; return *this; };
	strinx& operator<(float v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<int> v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<float> v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<const char*> v) { *this += v; return *this; };

	bool operator==(char v) {
		if (_size == 1 && _str[0] == v)
			return true;
		return false;
	};
	bool operator==(const char* v) {
		if (_size == strlen(v)) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	};
	bool operator==(std::string v) {
		if (_size == v.size()) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(int v) {
		if (_size == stx(v).size()) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == stx(v)[i])
					_c++;
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(float v) {
		if (_size == stx(v).size()) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == stx(v)[i])
					_c++;
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(strinx v) {
		if (_size == v.size()) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	}

	bool operator!=(char v) { return !(*this == v); };
	bool operator!=(const char* v) { return !(*this == v); };
	bool operator!=(std::string v) { return !(*this == v); };
	bool operator!=(int v) { return !(*this == v); };
	bool operator!=(float v) { return !(*this == v); };

	void operator-=(char v) { takeout(v); };
	void operator-=(const char* v) { takeout(v); };
	void operator-=(std::string v) { takeout(v); };
	void operator-=(strinx v) { takeout(v); };
	void operator-=(int v) { takeout(v); };
	void operator-=(float v) { takeout(v); };

	strinx operator-(char v) { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(const char* v) { strinx _t = *this; _t.takeout(v); false; return _t; };
	strinx operator-(std::string v) { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(strinx v) { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(int v) { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(float v) { strinx _t = *this; _t.takeout(v); return _t; };

	strinx operator+(char v) { strinx _t = *this; _t += v; return _t; };
	strinx operator+(const char* v) { strinx _t = *this; _t += v; return _t; };
	strinx operator+(std::string v) { strinx _t = *this; _t += v; return _t; };
	strinx operator+(strinx v) { strinx _t = *this; _t += v; return _t; };
	strinx operator+(int v) { strinx _t = *this; _t += v; return _t; };
	strinx operator+(float v) { strinx _t = *this; _t += v; return _t; };

	bool operator>>(strinx& v) {
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < split_it.size(); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < split_it.size(); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					v += _str[_it];
				else
					break;
			};
			return true;
		}
		else
			return false;
	};
	bool operator>>(std::string& v) {
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < split_it.size(); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < split_it.size(); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					v += _str[_it];
				else
					break;
			};
			return true;
		}
		else
			return false;
	};
	bool operator>>(const char*& v) {
		std::string  _v;
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < split_it.size(); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			_v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < split_it.size(); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					_v += _str[_it];
				else
					break;
			};
			v = _v.c_str();
			return true;
		}
		else
			return false;
	};
	bool operator>(char& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool operator>(strinx& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool operator>(std::string& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool getline(strinx& v) {
		v.clear();
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				v += _str[_it];
			};
			return true;
		}
		else
			return false;
	};
	bool getline(std::string& v) {
		v.clear();
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				v += _str[_it];
			};
			return true;
		}
		else
			return false;
	};
	bool getline(const char*& v) {
		std::string _v;
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				_v += _str[_it];
			};
			v = _v.c_str();
			return true;
		}
		else
			return false;
	};
	bool get(char& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool get(strinx& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool get(std::string& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};

	strinx operator*(size_t v) {
		strinx _t;
		for (volatile size_t i = 0; i < v; i++)
			_t += *this;
		return _t;
	};
	void operator*=(size_t v) {
		const strinx _t = *this;
		this->clear();
		for (volatile size_t i = 0; i < v; i++)
			*this += _t;
		_splt = false;
	};
	strinx operator*(char v) {
		strinx _t = *this, _j;
		this->resize(_size);
		for (size_t i = 0; i < _size * 2; i += 2) {
			_j[i] = _t[i / 2];
			_j[i + 1] = v;
		};
		return _j;
	};
	void operator*=(char v) {
		strinx _t = *this;
		this->resize(_size);
		for (size_t i = 0; i < _size * 2; i+=2) {
			_str[i] = _t[i/2];
			_str[i+1] = v;
		};
		_splt = false;
	};

	float to_float() { return std::stof(_str); };
	int to_int() { return std::stoi(_str); };
	double to_double() { return std::stof(_str); };

	strinx upper() {
		strinx _t = *this;
		for (size_t i = 0; i < _size; i++) {
			switch (_t[i]) {
			case 'a': _t[i] = 'A'; break;
			case 'b': _t[i] = 'B'; break;
			case 'c': _t[i] = 'C'; break;
			case 'd': _t[i] = 'D'; break;
			case 'e': _t[i] = 'E'; break;
			case 'f': _t[i] = 'F'; break;
			case 'g': _t[i] = 'G'; break;
			case 'h': _t[i] = 'H'; break;
			case 'i': _t[i] = 'I'; break;
			case 'j': _t[i] = 'J'; break;
			case 'k': _t[i] = 'K'; break;
			case 'l': _t[i] = 'L'; break;
			case 'm': _t[i] = 'M'; break;
			case 'n': _t[i] = 'N'; break;
			case 'o': _t[i] = 'O'; break;
			case 'p': _t[i] = 'P'; break;
			case 'r': _t[i] = 'R'; break;
			case 's': _t[i] = 'S'; break;
			case 't': _t[i] = 'T'; break;
			case 'q': _t[i] = 'Q'; break;
			case 'u': _t[i] = 'U'; break;
			case 'v': _t[i] = 'V'; break;
			case 'w': _t[i] = 'W'; break;
			case 'x': _t[i] = 'X'; break;
			case 'y': _t[i] = 'Y'; break;
			case 'z': _t[i] = 'Z'; break;
			}
		}
		return _t;
	};
	strinx lower() {
		strinx _t = *this;
		for (size_t i = 0; i < _size; i++) {
			switch (_t[i]) {
			case 'A': _t[i] = 'a'; break;
			case 'B': _t[i] = 'b'; break;
			case 'C': _t[i] = 'c'; break;
			case 'D': _t[i] = 'd'; break;
			case 'E': _t[i] = 'e'; break;
			case 'F': _t[i] = 'f'; break;
			case 'G': _t[i] = 'g'; break;
			case 'H': _t[i] = 'h'; break;
			case 'I': _t[i] = 'i'; break;
			case 'J': _t[i] = 'j'; break;
			case 'K': _t[i] = 'k'; break;
			case 'L': _t[i] = 'l'; break;
			case 'M': _t[i] = 'm'; break;
			case 'N': _t[i] = 'n'; break;
			case 'O': _t[i] = 'o'; break;
			case 'P': _t[i] = 'p'; break;
			case 'R': _t[i] = 'r'; break;
			case 'S': _t[i] = 's'; break;
			case 'T': _t[i] = 't'; break;
			case 'Q': _t[i] = 'q'; break;
			case 'U': _t[i] = 'u'; break;
			case 'V': _t[i] = 'v'; break;
			case 'W': _t[i] = 'w'; break;
			case 'X': _t[i] = 'x'; break;
			case 'Y': _t[i] = 'y'; break;
			case 'Z': _t[i] = 'z'; break;
			}
		}
		return _t;
	};
	strinx numbers() {
		strinx _t;
		for (size_t i = 0; i < _size; i++) {
			switch (_str[i]) {
			case '1': _t += '1'; break;
			case '2': _t += '2'; break;
			case '3': _t += '3'; break;
			case '4': _t += '4'; break;
			case '5': _t += '5'; break;
			case '6': _t += '6'; break;
			case '7': _t += '7'; break;
			case '8': _t += '8'; break;
			case '9': _t += '9'; break;
			case '0': _t += '0'; break;
			}
		}
		return _t;
	}

	bool up() {
		switch (_str[_it]) {
		case 'a': _str[_it] = 'A'; break;
		case 'b': _str[_it] = 'B'; break;
		case 'c': _str[_it] = 'C'; break;
		case 'd': _str[_it] = 'D'; break;
		case 'e': _str[_it] = 'E'; break;
		case 'f': _str[_it] = 'F'; break;
		case 'g': _str[_it] = 'G'; break;
		case 'h': _str[_it] = 'H'; break;
		case 'i': _str[_it] = 'I'; break;
		case 'j': _str[_it] = 'J'; break;
		case 'k': _str[_it] = 'K'; break;
		case 'l': _str[_it] = 'L'; break;
		case 'm': _str[_it] = 'M'; break;
		case 'n': _str[_it] = 'N'; break;
		case 'o': _str[_it] = 'O'; break;
		case 'p': _str[_it] = 'P'; break;
		case 'r': _str[_it] = 'R'; break;
		case 's': _str[_it] = 'S'; break;
		case 't': _str[_it] = 'T'; break;
		case 'q': _str[_it] = 'Q'; break;
		case 'u': _str[_it] = 'U'; break;
		case 'v': _str[_it] = 'V'; break;
		case 'w': _str[_it] = 'W'; break;
		case 'x': _str[_it] = 'X'; break;
		case 'y': _str[_it] = 'Y'; break;
		case 'z': _str[_it] = 'Z'; break;
		}
		_splt = false;
		return move();
	};
	bool low() {
		switch (_str[_it]) {
		case 'A': _str[_it] = 'a'; break;
		case 'B': _str[_it] = 'b'; break;
		case 'C': _str[_it] = 'c'; break;
		case 'D': _str[_it] = 'd'; break;
		case 'E': _str[_it] = 'e'; break;
		case 'F': _str[_it] = 'f'; break;
		case 'G': _str[_it] = 'g'; break;
		case 'H': _str[_it] = 'h'; break;
		case 'I': _str[_it] = 'i'; break;
		case 'J': _str[_it] = 'j'; break;
		case 'K': _str[_it] = 'k'; break;
		case 'L': _str[_it] = 'l'; break;
		case 'M': _str[_it] = 'm'; break;
		case 'N': _str[_it] = 'n'; break;
		case 'O': _str[_it] = 'o'; break;
		case 'P': _str[_it] = 'p'; break;
		case 'R': _str[_it] = 'r'; break;
		case 'S': _str[_it] = 's'; break;
		case 'T': _str[_it] = 't'; break;
		case 'Q': _str[_it] = 'q'; break;
		case 'U': _str[_it] = 'u'; break;
		case 'V': _str[_it] = 'v'; break;
		case 'W': _str[_it] = 'w'; break;
		case 'X': _str[_it] = 'x'; break;
		case 'Y': _str[_it] = 'y'; break;
		case 'Z': _str[_it] = 'z'; break;
		}
		_splt = false;
		return move();
	};
	bool up(size_t v) {
		if (v > _size)
			return false;
		else
			switch (_str[v]) {
			case 'a': _str[v] = 'A'; break;
			case 'b': _str[v] = 'B'; break;
			case 'c': _str[v] = 'C'; break;
			case 'd': _str[v] = 'D'; break;
			case 'e': _str[v] = 'E'; break;
			case 'f': _str[v] = 'F'; break;
			case 'g': _str[v] = 'G'; break;
			case 'h': _str[v] = 'H'; break;
			case 'i': _str[v] = 'I'; break;
			case 'j': _str[v] = 'J'; break;
			case 'k': _str[v] = 'K'; break;
			case 'l': _str[v] = 'L'; break;
			case 'm': _str[v] = 'M'; break;
			case 'n': _str[v] = 'N'; break;
			case 'o': _str[v] = 'O'; break;
			case 'p': _str[v] = 'P'; break;
			case 'r': _str[v] = 'R'; break;
			case 's': _str[v] = 'S'; break;
			case 't': _str[v] = 'T'; break;
			case 'q': _str[v] = 'Q'; break;
			case 'u': _str[v] = 'U'; break;
			case 'v': _str[v] = 'V'; break;
			case 'w': _str[v] = 'W'; break;
			case 'x': _str[v] = 'X'; break;
			case 'y': _str[v] = 'Y'; break;
			case 'z': _str[v] = 'Z'; break;
			default: return false;
			};
		_splt = false;
		return true;
	};
	bool low(size_t v) {
		if (v > _size)
			return false;
		else
			switch (_str[v]) {
			case 'A': _str[v] = 'a'; break;
			case 'B': _str[v] = 'b'; break;
			case 'C': _str[v] = 'c'; break;
			case 'D': _str[v] = 'd'; break;
			case 'E': _str[v] = 'e'; break;
			case 'F': _str[v] = 'f'; break;
			case 'G': _str[v] = 'g'; break;
			case 'H': _str[v] = 'h'; break;
			case 'I': _str[v] = 'i'; break;
			case 'J': _str[v] = 'j'; break;
			case 'K': _str[v] = 'k'; break;
			case 'L': _str[v] = 'l'; break;
			case 'M': _str[v] = 'm'; break;
			case 'N': _str[v] = 'n'; break;
			case 'O': _str[v] = 'o'; break;
			case 'P': _str[v] = 'p'; break;
			case 'R': _str[v] = 'r'; break;
			case 'S': _str[v] = 's'; break;
			case 'T': _str[v] = 't'; break;
			case 'Q': _str[v] = 'q'; break;
			case 'U': _str[v] = 'u'; break;
			case 'V': _str[v] = 'v'; break;
			case 'W': _str[v] = 'w'; break;
			case 'X': _str[v] = 'x'; break;
			case 'Y': _str[v] = 'y'; break;
			case 'Z': _str[v] = 'z'; break;
			default: return false;
			};
		_splt = false;
		return true;
	};
	void up(size_t begin, size_t end) {
		for (size_t i = begin; i < end && i < _size; i++) {
			switch (_str[i]) {
			case 'a': _str[i] = 'A'; break;
			case 'b': _str[i] = 'B'; break;
			case 'c': _str[i] = 'C'; break;
			case 'd': _str[i] = 'D'; break;
			case 'e': _str[i] = 'E'; break;
			case 'f': _str[i] = 'F'; break;
			case 'g': _str[i] = 'G'; break;
			case 'h': _str[i] = 'H'; break;
			case 'i': _str[i] = 'I'; break;
			case 'j': _str[i] = 'J'; break;
			case 'k': _str[i] = 'K'; break;
			case 'l': _str[i] = 'L'; break;
			case 'm': _str[i] = 'M'; break;
			case 'n': _str[i] = 'N'; break;
			case 'o': _str[i] = 'O'; break;
			case 'p': _str[i] = 'P'; break;
			case 'r': _str[i] = 'R'; break;
			case 's': _str[i] = 'S'; break;
			case 't': _str[i] = 'T'; break;
			case 'q': _str[i] = 'Q'; break;
			case 'u': _str[i] = 'U'; break;
			case 'v': _str[i] = 'V'; break;
			case 'w': _str[i] = 'W'; break;
			case 'x': _str[i] = 'X'; break;
			case 'y': _str[i] = 'Y'; break;
			case 'z': _str[i] = 'Z'; break;
			}
		}
		_splt = false;
	};
	void low(size_t begin, size_t end) {
		for (size_t i = begin; i < end && i < _size; i++) {
			switch (_str[i]) {
			case 'A': _str[i] = 'a'; break;
			case 'B': _str[i] = 'b'; break;
			case 'C': _str[i] = 'c'; break;
			case 'D': _str[i] = 'd'; break;
			case 'E': _str[i] = 'e'; break;
			case 'F': _str[i] = 'f'; break;
			case 'G': _str[i] = 'g'; break;
			case 'H': _str[i] = 'h'; break;
			case 'I': _str[i] = 'i'; break;
			case 'J': _str[i] = 'j'; break;
			case 'K': _str[i] = 'k'; break;
			case 'L': _str[i] = 'l'; break;
			case 'M': _str[i] = 'm'; break;
			case 'N': _str[i] = 'n'; break;
			case 'O': _str[i] = 'o'; break;
			case 'P': _str[i] = 'p'; break;
			case 'R': _str[i] = 'r'; break;
			case 'S': _str[i] = 's'; break;
			case 'T': _str[i] = 't'; break;
			case 'Q': _str[i] = 'q'; break;
			case 'U': _str[i] = 'u'; break;
			case 'V': _str[i] = 'v'; break;
			case 'W': _str[i] = 'w'; break;
			case 'X': _str[i] = 'x'; break;
			case 'Y': _str[i] = 'y'; break;
			case 'Z': _str[i] = 'z'; break;
			}
		}
		_splt = false;
	};

	strinx filter(char _find, char _change) {
		strinx c = *this;
		while (c.check(_find)) {
			std::cout << c << '\n';
			c.replace(_find, _change);
		};
		return c;
	};
	strinx filter(const char* _find, char _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(std::string _find, char _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(strinx _find, char _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(int _find, char _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(float _find, char _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};

	strinx filter(char _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(const char* _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(std::string _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(strinx _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(int _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};
	strinx filter(float _find, const char* _change) {
		strinx c = *this;
		while (c.check(_find))
			c.replace(_find, _change);
		return c;
	};

	bool check(char v) {
		for (size_t i = 0; i < _size; i++) {
			if (v == _str[i]) {
				return true;
			};
		};
		return false;
	};
	bool check(const char* v) {
		 size_t s = _size - strlen(v), sl = strlen(v);
		 for (size_t i = 0; i < s; i++)
			 if (this->operator()(i, i + sl) == v)
				 return true;
		return false;
	};
	bool check(std::string v) {
		strinx _v = v;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(strinx v) {
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(int v) {
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(float v) {
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};

	size_t scan(char v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size; i++)
			if (v == _str[i])
				_c++;
		return _c;
	};
	size_t scan(const char* v) {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - strlen(v), sl = strlen(v);
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t scan(std::string v) {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t scan(strinx v) {
		size_t _c = 0;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++)
			if (v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t scan(int v) {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t scan(float v) {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};

	size_t find(char v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size; i++) {
			if (v == _str[i]) {
				_c = i;
				break;
			};
		};
		return _c;
	};
	size_t find(const char* v) {
		size_t _c = -1;
		const size_t s = _size - strlen(v), sl = strlen(v);
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(std::string v) {
		size_t _c = -1;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(strinx v) {
		size_t _c = -1;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(int v) {
		size_t _c = -1;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == _v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(float v) {
		size_t _c = -1;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == _v) {
				_c = i;
				break;
			};
		}
		return _c;
	};

	void takeout(char v) {
		if (check(v)) {
			const size_t _f = find(v);
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + 1, c.size());
			_splt = false;
		};
	};
	void takeout(const char* v) {
		if (check(v)) {
			const size_t _f = find(v), sl = strlen(v);
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
		};
	};
	void takeout(std::string v) {
		if (check(v)) {
			const size_t _f = find(v), sl = v.size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
		};
	};
	void takeout(strinx v) {
		if (check(v)) {
			const size_t _f = find(v), sl = v.size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
		};
	};
	void takeout(int v) {
		if (check(v)) {
			const size_t _f = find(v), sl = stx(v).size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
		};
	};
	void takeout(float v) {
		if (check(v)) {
			const size_t _f = find(v), sl = stx(v).size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
		};
	};

	void insert(char v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	}
	void insert(const char* v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(std::string v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(strinx v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(int v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(float v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};

	void insert(size_t j, char v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, const char* v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, std::string v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, strinx v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, int v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, float v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};

	void replace(char v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, char q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, char q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, char q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(char v, const char* q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, const char* q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, const char* q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, const char* q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, const char* q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, const char* q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(char v, std::string q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, std::string q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, std::string q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, std::string q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, std::string q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, std::string q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(char v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, strinx q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, strinx q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, strinx q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(char v, int q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, int q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, int q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, int q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, int q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, int q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(char v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(const char* v, float q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(std::string v, float q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(strinx v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(int v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
	void replace(float v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); }; };
};
typedef strinx stx;
strinx operator""stx(const char* v, size_t) { return strinx(v); };
strinx operator""stx(unsigned long long v) { return strinx(int(v)); };
std::ostream& operator<<(std::ostream& os, const strinx& v) {
	strinx _v = v;
	os << _v.c_str();
	return os;
};
std::vector<strinx> operator""split(const char* v, size_t) {
	strinx t = v, s;
	std::vector<strinx> m;
	while (t >> s)
		m.push_back(s);
	return m;
};
