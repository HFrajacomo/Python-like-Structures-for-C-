#include <cstdlib>
#include "slice.h"

template <class T>
class PyList;

template <class T>
class ListNode{
public:
	ListNode *next;
	ListNode *prev;
	T data;

	ListNode(){
		this->next = NULL;
		this->prev = NULL;
	}
};

/*
This is an Iterator Class for PyList
Because of it we can use iterators in for loops like:

for(T a: mylist){}
*/

template <class T>
class ListIter{
public:
	ListIter(const PyList<T>* pointer, int pos) : _pos(pos), _pointer(pointer){}

	bool operator!=(const ListIter& a){
		return _pos != a._pos;
	}

	int operator*() const;

	const ListIter& operator++(){
		++_pos;
		return *this;
	}

private:
	int _pos;
	const PyList<T>* _pointer;

};

template <class T>
int ListIter<T>::operator*() const{
	return _pointer->get(_pos);
}

/*
This is the main class for PyLists.
It is linked to the iterator class above
*/

template <class T>
class PyList{
public:
	int len;
	ListNode<T> *zero;
	ListNode<T> *final;

	// Basic Constructor
	PyList(){
		this->len = 0;
		this->zero = NULL;
		this->final = NULL;
	}

	// Iterators
	ListIter<T> begin(){
		return ListIter<T>(this, 0);
	}

	ListIter<T> end(){
		return ListIter<T>(this, this->len);
	}

	// Appends element at the end of the list
	void append(T element){
		ListNode<T>* novo = new ListNode<T>;
		novo->data = element;

		if(this->len == 0){
			this->zero = novo;
			this->final = novo;
		}

		novo->next = this->zero;
		novo->prev = this->final;
		this->final->next = novo;
		this->final = novo;
		this->len++;
	}

	// Pops element of position i
	T pop(int i=-1){
		ListNode<T>* a = this->search(i);

		if(a == this->zero){
			if(this->len <= 1){
				this->zero = NULL;
			}
			else{
				this->zero = this->zero->next;
			}
		}
		if(a == this->final){
			this->final = this->final->prev;
		}

		a->prev->next = a->next;
		a->next->prev = a->prev;

		this->len--;

		return a->data;
	}

	// Simple list print
	void print(){
		std::cout << "[";
		ListNode<T>* index = this->zero;
		for(int i=0;i<this->len;i++){
			if(i!=0){
				std::cout << ", " << index->data;
			}
			else{
				std::cout << index->data;
			}

			index = index->next;
		}
		std::cout << "]" << std::endl;
	}

	// Gets value of ith position
	T operator [](int i){
		ListNode<T> *a = this->search(i);
		if(a == NULL){
			std::cout << "Index out of bounds" << std::endl;
			return NULL;
		}
		else{
			return a->data;
		}
	}

	// Gets sublist with [Slice()]
	PyList<T> operator [](Slice s){
		ListNode<T> *i_ptr = this->search(s.init);
		ListNode<T> *j_ptr = this->search(s.final);
		if(i_ptr == NULL || j_ptr == NULL){
			std::cout << "Slice index out of bounds" << std::endl;
			return PyList<T>();
		}

		PyList<T> l;

		while(i_ptr != j_ptr){
			l.append(i_ptr->data);
			i_ptr = i_ptr->next;
		}
		if(j_ptr != NULL && s.final < 0){
			l.append(j_ptr->data);
		}
		return l;
	}

	// Inserts a new ListNode at position i having x as data
	void insert(T x, int i=0){
		// Negatives fix
		if(i < 0){
			i = i + this->len + 1; 
		}

		ListNode<T>* ln = this->search(i);
		ListNode<T>* n = new ListNode<T>;

		if(ln == NULL){
			if(i == this->len){
				this->append(x);
				return;
			}
			else{
				std::cout << "Index out of bounds" << std::endl;
				return;
			}
		}

		if(i == 0){
			this->zero = n;
		}


		// Basic insertion
		n->data = x;
		n->next = ln;
		n->prev = ln->prev;
		this->final->next = n;
		ln->prev = n;

		this->len++;

	}

	// Inverts the list in place
	void reverse(){
		ListNode<T>* aux;
		ListNode<T>* iterator = this->zero;

		for(int i=0;i<this->len;i++){
			aux = iterator->prev;
			iterator->prev = iterator->next;
			iterator->next = aux;
			iterator = iterator->prev;
		}

		aux = this->zero;
		this->zero = this->final;
		this->final = aux;
	}

	// Gets ith position ListNode
	T get(int i) const{
		ListNode<T> *a = this->search(i);
		return a->data;
	}

private:
	ListNode<T> *search(int i) const{
		if(i>=0){
			if(i+1>this->len){
				return NULL;
			}
			ListNode<T>* act = this->zero;

			for(int j=0;j<i;j++){
				act = act->next;
			}

			return act;
		}
		else{
			if(abs(i-1)>this->len){
				return NULL;
			}
			ListNode<T>* act = this->final;

			for(int j=-1;j>i;j--){
				act = act->prev;
			}

			return act;
		}
	}
};
