#include <iostream>
#include "pylist.h"
#include "pystring.h"

int main(){
	using namespace std;

	PyList<char> a;

	PyString c = PyString("Hello");
	PyString d = PyString(" World");
	c += d;
	
	cout << c[-1] << endl;
	//c+d.print();
}