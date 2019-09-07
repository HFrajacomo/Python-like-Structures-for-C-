#include <iostream>
#include "pylist.h"
#include "pystring.h"

int main(){
	using namespace std;

	PyList<char> a;

	PyString c = PyString("Hello World");
	

	for(char e:c){
		cout << e << endl;
	}
}