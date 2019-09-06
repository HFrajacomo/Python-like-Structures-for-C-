#include <iostream>
#include "data.h"

int main(){
	using namespace std;

	PyList<int> a;

	for(int i=0; i<100; i++){
		a.append(i);
	}

	for(int n: a){
		cout << n << endl;
	}
}