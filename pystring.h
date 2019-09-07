#include <string>
#include <iostream>

using namespace std;

class PyString;

class StringIter{
public:
	StringIter(const PyString* pointer, int pos) : _pos(pos), _pointer(pointer){}

	bool operator!=(const StringIter& a){
		return _pos != a._pos;
	}

	int operator*() const;

	const StringIter& operator++(){
		++_pos;
		return *this;
	}	
private:
	int _pos;
	const PyString* _pointer;	
};


class PyString{
private:
	string data;
	
public:
	int len;

	// Empty String Declaration
	PyString(){
		this->len = 0;
	}

	PyString(char c){
		this->data += c;
		this->len++;
	}

	// Convert std::string to PyString
	PyString(string a){
		this->data = a;
		this->len = a.length();
	}

	// Python equivalent to str(list)
	template <class T>
	PyString(PyList<T> l){
		for(T elem: l){
			this->data += to_string(elem);
			this->len++;
		}
	}

	// Iterators
	StringIter begin(){
		return StringIter(this, 0);
	}

	StringIter end(){
		return StringIter(this, this->len);
	}

	// Gets value of ith position
	char operator[](int i){
		return this->data[i];
	}	

	char get(int i) const{
		return this->data[i];
	}

	PyString operator[](Slice s){
		PyString out;

		for(int i=s.init;i<s.final;i++){
			out += this->data[i];
		}

		return out;
	}

	// s = 'testing'
	void operator=(const char *s){
		this->data = string(s);
		this->len = string(s).size();
	}

	// s = string("testing")
	void operator=(string s){
		this->data = s;
		this->len = s.length();
	}

	PyString operator+(const char c){
		PyString out;

		out.data += c;
		out.len++;
		return out;
	}

	PyString operator+(const char* c){
		PyString out;

		out.data += string(c);
		out.len += string(c).length();
		return out;
	}

	PyString operator+(PyString ps){
		PyString out;

		out.data += ps.data;
		out.len += ps.len;
		return out;
	}

	void operator+=(const char c){
		this->data += c;
		this->len++;
	}

	void operator+=(const char* c){
		this->data += string(c);
		this->len += string(c).length();
	}

	void operator+=(PyString ps){
		this->data += ps.data;
		this->len += ps.len;
	}

	void print(){
		cout << this->data << endl;
	}
};

int StringIter::operator*() const{
	return _pointer->get(_pos);
}