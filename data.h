#include <cstdlib>

template <class T>
class PyList;

class Slice{
public:
	int init;
	int final;

	Slice(int i=0, int j=-1){
		this->init = i;
		this->final = j;
	}

};

template <class T>
class Node{
public:
	Node *next;
	Node *prev;
	T data;

	Node(){
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
	int length;
	Node<T> *zero;
	Node<T> *final;

	// Basic Constructor
	PyList(){
		this->length = 0;
		this->zero = NULL;
		this->final = NULL;
	}

	// Iterators
	ListIter<T> begin(){
		return ListIter<T>(this, 0);
	}

	ListIter<T> end(){
		return ListIter<T>(this, this->length);
	}

	// Appends element at the end of the list
	void append(T element){
		Node<T>* novo = new Node<T>;
		novo->data = element;

		if(this->length == 0){
			this->zero = novo;
			this->final = novo;
		}

		novo->next = this->zero;
		novo->prev = this->final;
		this->final->next = novo;
		this->final = novo;
		this->length++;
	}

	// Pops element of position i
	T pop(int i=-1){
		Node<T>* a = this->search(i);

		if(a == this->zero){
			if(this->length <= 1){
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

		this->length--;

		return a->data;
	}

	// Simple list print
	void print(){
		std::cout << "[";
		Node<T>* index = this->zero;
		for(int i=0;i<this->length;i++){
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
		Node<T> *a = this->search(i);
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
		Node<T> *i_ptr = this->search(s.init);
		Node<T> *j_ptr = this->search(s.final);
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

	// Inserts a new node at position i having x as data
	void insert(T x, int i=0){
		// Negatives fix
		if(i < 0){
			i = i + this->length + 1; 
		}

		Node<T>* node = this->search(i);
		Node<T>* n = new Node<T>;

		if(node == NULL){
			if(i == this->length){
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
		n->next = node;
		n->prev = node->prev;
		this->final->next = n;
		node->prev = n;

		this->length++;

	}

	// Inverts the list in place
	void reverse(){
		Node<T>* aux;
		Node<T>* iterator = this->zero;

		for(int i=0;i<this->length;i++){
			aux = iterator->prev;
			iterator->prev = iterator->next;
			iterator->next = aux;
			iterator = iterator->prev;
		}

		aux = this->zero;
		this->zero = this->final;
		this->final = aux;
	}

	// Gets ith position node
	T get(int i) const{
		Node<T> *a = this->search(i);
		return a->data;
	}

private:
	Node<T> *search(int i) const{
		if(i>=0){
			if(i+1>this->length){
				return NULL;
			}
			Node<T>* act = this->zero;

			for(int j=0;j<i;j++){
				act = act->next;
			}

			return act;
		}
		else{
			if(abs(i-1)>this->length){
				return NULL;
			}
			Node<T>* act = this->final;

			for(int j=-1;j>i;j--){
				act = act->prev;
			}

			return act;
		}
	}
};
