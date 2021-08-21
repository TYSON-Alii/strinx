#include <sstream>
#include <vector>
class strinx {
private:
	char* _str = new char[1]{'\0'};
	size_t _size = 0;
	size_t _it = 0;
	std::string stx(float v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(double v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(int v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(char v) { std::stringstream ss; ss << v; return ss.str(); };
	std::string stx(const char* v) { std::stringstream ss; ss << v; return ss.str(); };
	class Split {
	private:
		std::vector<char> _ss;
		bool _is_in(char v) {
			for (auto i : _ss)
				if (i == v)
					return true;
			return false;
		};
	public:
		Split() { _ss.push_back(' '); _ss.push_back('\n'); _ss.push_back('\t'); };
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
		char* chars() {
			char* _t = new char[_ss.size()];
			for (volatile size_t i = 0; i < _ss.size(); i++)
				_t[i] = _ss[i];
			return _t;
		};
		size_t size() { return _ss.size(); };
		size_t lenght() { return _ss.size(); };
	};
public:
	size_t size() { return _size; };
	size_t lenght() { return _size; };
	size_t len() { return _size; };
	char& front() { return _str[0]; };
	char& back() { return _str[_size - 1]; };
	char& first() { return _str[0]; };
	char& last() { return _str[_size - 1]; };
	char& middle() { return _str[_size / 2]; };
	Split split;
	size_t& iterator() { return _it; };
	void reset() { _it = 0; };
	bool canmove() { return _it == _size - 1 ? false : true; };
	bool canmoveback() { return _it == 0 ? false : true; };
	/*bool canmoveline() {
		if (canmove()) {
			size_t _i = _it;
			while (true) {
				if (_str[_i] == '\n')
					return true;
				if (!canmove())
					return false;
				_i++;
			};
		}
		else
			return false;
	}*/
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
	bool moveline() {
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
	}
	bool operator++() { return move(); };
	bool operator--() { return moveback(); };
	const char* c_str() { return _str; };
	std::string str() { return std::string(c_str()); };
	strinx() {};
	strinx(const char* v) { _str = strcat(_strdup(v), "\0"); _size = strlen(_str); };
	strinx(char v) { _str = new char[2]{ v, '\0' }; _size = 1; };
	strinx(std::string v) { _str = strcat(_strdup(v.c_str()), "\0"); _size = v.size(); };
	strinx(int v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };
	strinx(double v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };
	strinx(float v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };
	char& operator[](size_t v) { return _str[v]; };
	strinx operator()() { return *this; };
	strinx operator()(size_t v) { return strinx(_str[v]); };
	strinx operator()(size_t const volatile begin, size_t const volatile end) {
		strinx _t;
		if (begin < end)
			for (size_t i = begin; i < end; i++)
				_t += _str[i];
		else
			for (size_t i = begin; i > end; i--)
				_t += _str[i];
		return _t;
	};
	void clear() { _str = new char[1]{ '\0' }; _size = 0; };

	void operator=(char v) { _str = new char[2]{ v, '\0' }; _size = 1; };
	void operator=(std::string& v) { _str = strcat(_strdup(v.c_str()), "\0"); _size = v.size(); };
	void operator=(int v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };
	void operator=(double v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };
	void operator=(float v) { _str = strcat(_strdup(stx(v).c_str()), "\0"); _size = strlen(_str); };

	void operator+=(const char* v) { _str = strcat(strcat(_str, v), "\0"); _size += strlen(v); };
	void operator+=(char v) { _str = strcat(_str, new char[2]{ v, '\0' }); _size++; };
	void operator+=(std::string v) { _str = strcat(_str, v.c_str()); _size += v.size(); };
	void operator+=(strinx v) { _str = strcat(_str, v.c_str()); _size += v.size(); };
	void operator+=(int v) { _str = strcat(strcat(_str, _strdup(stx(v).c_str())), "\0"); _size += stx(v).size(); };
	void operator+=(float v) { _str = strcat(strcat(_str, _strdup(stx(v).c_str())), "\0"); _size += stx(v).size(); };
	void operator+=(double v) { _str = strcat(strcat(_str, _strdup(stx(v).c_str())), "\0"); _size += stx(v).size(); };

	bool operator==(char v) {
		if (_str[0] == v)
			return true;
		return false;
	};
	bool operator==(const char* v) {
		if (_size == strlen(v)) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i])
					_c++;
				else
					return false;
			return true;
		};
		return false;
	};
	bool operator==(std::string v) {
		if (_size == v.size()) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i])
					_c++;
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

	void operator-=(char v) { takeout(v); };
	void operator-=(const char* v) { takeout(v); };
	void operator-=(std::string v) { takeout(v); };
	void operator-=(strinx v) { takeout(v); };
	void operator-=(int v) { takeout(v); };
	void operator-=(float v) { takeout(v); };

	strinx operator-(char v) { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(const char* v) { strinx _t = *this; _t.takeout(v); return _t; };
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
			for (volatile size_t i = 0; i < split.size(); i++)
				if (_str[_it] == split.chars()[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			v.clear();
			while (_str[_it] != ' ' && _str[_it] != '\n' && _str[_it] != '\t' && canmove()) {
				v += _str[_it];
				move();
			};
			return true;
		}
		else
			return false;
	};
	/*bool getline(strinx& v) {
		if (canmoveline()) {
			v.clear();
			while (_str[_it] != '\n') {
				v += _str[_it];
				_it++;
			};
			return true;
		}
		else
			false;
	}*/

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

	void up() {
		if (_size > 0)
			switch (_str[0]) {
			case 'a': _str[0] = 'A'; break;
			case 'b': _str[0] = 'B'; break;
			case 'c': _str[0] = 'C'; break;
			case 'd': _str[0] = 'D'; break;
			case 'e': _str[0] = 'E'; break;
			case 'f': _str[0] = 'F'; break;
			case 'g': _str[0] = 'G'; break;
			case 'h': _str[0] = 'H'; break;
			case 'i': _str[0] = 'I'; break;
			case 'j': _str[0] = 'J'; break;
			case 'k': _str[0] = 'K'; break;
			case 'l': _str[0] = 'L'; break;
			case 'm': _str[0] = 'M'; break;
			case 'n': _str[0] = 'N'; break;
			case 'o': _str[0] = 'O'; break;
			case 'p': _str[0] = 'P'; break;
			case 'r': _str[0] = 'R'; break;
			case 's': _str[0] = 'S'; break;
			case 't': _str[0] = 'T'; break;
			case 'q': _str[0] = 'Q'; break;
			case 'u': _str[0] = 'U'; break;
			case 'v': _str[0] = 'V'; break;
			case 'w': _str[0] = 'W'; break;
			case 'x': _str[0] = 'X'; break;
			case 'y': _str[0] = 'Y'; break;
			case 'z': _str[0] = 'Z'; break;
			}
	};
	void low() {
		if (_size > 0)
			switch (_str[0]) {
			case 'A': _str[0] = 'a'; break;
			case 'B': _str[0] = 'b'; break;
			case 'C': _str[0] = 'c'; break;
			case 'D': _str[0] = 'd'; break;
			case 'E': _str[0] = 'e'; break;
			case 'F': _str[0] = 'f'; break;
			case 'G': _str[0] = 'g'; break;
			case 'H': _str[0] = 'h'; break;
			case 'I': _str[0] = 'i'; break;
			case 'J': _str[0] = 'j'; break;
			case 'K': _str[0] = 'k'; break;
			case 'L': _str[0] = 'l'; break;
			case 'M': _str[0] = 'm'; break;
			case 'N': _str[0] = 'n'; break;
			case 'O': _str[0] = 'o'; break;
			case 'P': _str[0] = 'p'; break;
			case 'R': _str[0] = 'r'; break;
			case 'S': _str[0] = 's'; break;
			case 'T': _str[0] = 't'; break;
			case 'Q': _str[0] = 'q'; break;
			case 'U': _str[0] = 'u'; break;
			case 'V': _str[0] = 'v'; break;
			case 'W': _str[0] = 'w'; break;
			case 'X': _str[0] = 'x'; break;
			case 'Y': _str[0] = 'y'; break;
			case 'Z': _str[0] = 'z'; break;
			}
	};
	void up(size_t v) {
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
		}
	};
	void low(size_t v) {
		if (_size > 0)
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
			}
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
	};

	bool check(char v) {
		for (size_t i = 0; i < _size; i++)
			if (v == _str[i])
				goto _true;
		return false;
	_true:;
		return true;
	};
	bool check(const char* v) {
		for (size_t i = 0; i < _size - strlen(v); i++)
			for (size_t j = 0; j < strlen(v); j++)
				if (v[i + j] == _str[i + j])
					goto _true;
		return false;
	_true:;
		return true;
	};
	bool check(std::string v) {
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j])
					goto _true;
		return false;
	_true:;
		return true;
	};
	bool check(strinx v) {
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j])
					goto _true;
		return false;
	_true:;
		return true;
	};
	bool check(int v) {
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j])
					goto _true;
		return false;
	_true:;
		return true;
	};
	bool check(float v) {
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j])
					goto _true;
		return false;
	_true:;
		return true;
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
		for (size_t i = 0; i < _size - strlen(v); i++)
			for (size_t j = 0; j < strlen(v); j++)
				if (v[i + j] == _str[i + j])
					_c++;
		return _c;
	};
	size_t scan(std::string v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j])
					_c++;
		return _c;
	};
	size_t scan(strinx v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j])
					_c++;
		return _c;
	};
	size_t scan(int v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j])
					_c++;
		return _c;
	};
	size_t scan(float v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j])
					_c++;
		return _c;
	};

	size_t find(char v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size; i++)
			if (v == _str[i]) {
				_c = i;
				goto _true;
			};
	_true:;
		return _c;
	};
	size_t find(const char* v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - strlen(v); i++)
			for (size_t j = 0; j < strlen(v); j++)
				if (v[i + j] == _str[i + j]) {
					_c = i;
					goto _true;
				}
	_true:;
		return _c;
	};
	size_t find(std::string v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j]) {
					_c = i;
					goto _true;
				}
	_true:;
		return _c;
	};
	size_t find(strinx v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - v.size(); i++)
			for (size_t j = 0; j < v.size(); j++)
				if (v[i + j] == _str[i + j]) {
					_c = i;
					goto _true;
				}
	_true:;
		return _c;
	};
	size_t find(int v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j]) {
					_c = i;
					goto _true;
				}
	_true:;
		return _c;
	};
	size_t find(float v) {
		size_t _c = 0;
		for (size_t i = 0; i < _size - stx(v).size(); i++)
			for (size_t j = 0; j < stx(v).size(); j++)
				if (stx(v)[i + j] == _str[i + j]) {
					_c = i;
					goto _true;
				}
	_true:;
		return _c;
	};

	void takeout(char v) {
		if (check(v)) {
			const char* _t = _str;
			_str = new char[_size];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + 1; i < _size; i++)
				_str[i - 1] = _t[i];
			_size--;
			_str[_size] = '\0';
		};
	};
	void takeout(const char* v) {
		if (check(v)) {
			const volatile char* _t = _str;
			const volatile size_t _l = strlen(v);
			_str = new char[_size - _l + 1];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + _l; i < _size; i++)
				_str[i - _l] = _t[i];
			_size -= _l;
			_str[_size] = '\0';
		};
	};
	void takeout(std::string v) {
		if (check(v)) {
			const volatile char* _t = _str;
			const volatile size_t _l = v.size();
			_str = new char[_size - _l + 1];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + _l; i < _size; i++)
				_str[i - _l] = _t[i];
			_size -= _l;
			_str[_size] = '\0';
		};
	};
	void takeout(strinx v) {
		if (check(v)) {
			const volatile char* _t = _str;
			const volatile size_t _l = v.size();
			_str = new char[_size - _l + 1];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + _l; i < _size; i++)
				_str[i - _l] = _t[i];
			_size -= _l;
			_str[_size] = '\0';
		};
	};
	void takeout(int v) {
		if (check(v)) {
			const volatile char* _t = _str;
			const volatile size_t _l = stx(v).size();
			_str = new char[_size - _l + 1];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + _l; i < _size; i++)
				_str[i - _l] = _t[i];
			_size -= _l;
			_str[_size] = '\0';
		};
	};
	void takeout(float v) {
		if (check(v)) {
			const volatile char* _t = _str;
			const volatile size_t _l = stx(v).size();
			_str = new char[_size - _l + 1];
			const volatile size_t _f = find(v);
			for (volatile size_t i = 0; i < _f; i++)
				_str[i] = _t[i];
			for (volatile size_t i = _f + _l; i < _size; i++)
				_str[i - _l] = _t[i];
			_size -= _l;
			_str[_size] = '\0';
		};
	};

	void insert(char v) {
		const volatile char* _t = _str;
		_str = new char[_size + 2];
		_str[0] = v;
		_size++;
		for (volatile size_t i = 1; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	}
	void insert(const char* v) {
		const volatile char* _t = _str;
		const volatile size_t _l = strlen(v);
		_str = new char[_size + _l + 1];
		for (volatile size_t i = 0; i < _l; i++)
			_str[i] = v[i];
		_size += _l;
		for (volatile size_t i = _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(std::string v) {
		const volatile char* _t = _str;
		const volatile size_t _l = v.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = 0; i < _l; i++)
			_str[i] = v[i];
		_size += _l;
		for (volatile size_t i = _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(strinx v) {
		const volatile char* _t = _str;
		const volatile size_t _l = v.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = 0; i < _l; i++)
			_str[i] = v[i];
		_size += _l;
		for (volatile size_t i = _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(int v) {
		const volatile char* _t = _str;
		const volatile size_t _l = stx(v).size();
		const std::string _s = stx(v);
		_str = new char[_size + _l + 1];
		for (volatile size_t i = 0; i < _l; i++)
			_str[i] = _s[i];
		_size += _l;
		for (volatile size_t i = _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(float v) {
		const volatile char* _t = _str;
		const volatile size_t _l = stx(v).size();
		const std::string _s = stx(v);
		_str = new char[_size + _l + 1];
		for (volatile size_t i = 0; i < _l; i++)
			_str[i] = _s[i];
		_size += _l;
		for (volatile size_t i = _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};

	void insert(size_t j, char v) {
		const volatile char* _t = _str;
		_str = new char[_size + 2];
		for (volatile size_t i = 1; i < j; i++)
			_str[i] = _t[i];
		_str[j] = v;
		_size++;
		for (volatile size_t i = j; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(size_t j, const char* v) {
		const volatile char* _t = _str;
		const volatile size_t _l = strlen(v);
		_str = new char[_size + _l + 1];
		for (volatile size_t i = _l; i < j; i++)
			_str[i] = _t[i];
		for (volatile size_t i = 0; i < _l; i++)
			_str[j + i] = v[i];
		_size += _l;
		for (volatile size_t i = j + _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(size_t j, std::string v) {
		const volatile char* _t = _str;
		const volatile size_t _l = v.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = _l; i < j; i++)
			_str[i] = _t[i];
		for (volatile size_t i = 0; i < _l; i++)
			_str[j + i] = v[i];
		_size += _l;
		for (volatile size_t i = j + _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(size_t j, strinx v) {
		const volatile char* _t = _str;
		const volatile size_t _l = v.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = _l; i < j; i++)
			_str[i] = _t[i];
		for (volatile size_t i = 0; i < _l; i++)
			_str[j + i] = v[i];
		_size += _l;
		for (volatile size_t i = j + _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(size_t j, int v) {
		const volatile char* _t = _str;
		const std::string _s = stx(v);
		const volatile size_t _l = _s.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = _l; i < j; i++)
			_str[i] = _t[i];
		for (volatile size_t i = 0; i < _l; i++)
			_str[j + i] = _s[i];
		_size += _l;
		for (volatile size_t i = j + _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};
	void insert(size_t j, float v) {
		const volatile char* _t = _str;
		const std::string _s = stx(v);
		const volatile size_t _l = _s.size();
		_str = new char[_size + _l + 1];
		for (volatile size_t i = _l; i < j; i++)
			_str[i] = _t[i];
		for (volatile size_t i = 0; i < _l; i++)
			_str[j + i] = _s[i];
		_size += _l;
		for (volatile size_t i = j + _l; i < _size; i++)
			_str[i] = _t[i];
		_str[_size] = '\0';
	};

	void replace(char v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, char q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(char v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, const char* q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(char v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, std::string q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(char v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, strinx q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(char v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, int q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(char v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(const char* v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(std::string v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(strinx v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(int v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
	void replace(float v, float q) { if (check(v)) { this->takeout(v); this->insert(find(v), q); }; };
};