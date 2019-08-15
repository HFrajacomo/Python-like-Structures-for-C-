#include <cstdlib>

class Slice{
public:
	int init;
	int end;

	Slice(int i=0, int j=-1){
		this->init = i;
		this->end = j;
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

template <class T>
class List{
public:
	int length;
	Node<T> *zero;
	Node<T> *end;

	List(){
		this->length = 0;
		this->zero = NULL;
		this->end = NULL;
	}

	void append(T element){
		Node<T>* novo = new Node<T>;
		novo->data = element;

		if(this->length == 0){
			this->zero = novo;
			this->end = novo;
		}

		novo->next = this->zero;
		novo->prev = this->end;
		this->end->next = novo;
		this->end = novo;
		this->length++;
	}

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
		if(a == this->end){
			this->end = this->end->prev;
		}

		a->prev->next = a->next;
		a->next->prev = a->prev;

		this->length--;

		return a->data;
	}

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

	List<T> operator [](Slice s){
		Node<T> *i_ptr = this->search(s.init);
		Node<T> *j_ptr = this->search(s.end);
		if(i_ptr == NULL || j_ptr == NULL){
			std::cout << "Slice index out of bounds" << std::endl;
			return List<T>();
		}

		List<T> l;

		while(i_ptr != j_ptr){
			l.append(i_ptr->data);
			i_ptr = i_ptr->next;
		}
		if(j_ptr != NULL && s.end < 0){
			l.append(j_ptr->data);
		}
		return l;
	}

	void insert(T x, int i=0){
		Node<T>* node = this->search(i);

		if(node == NULL){
			if(this->search(i-1)->next == this->zero){
				this->append(x);
				return;
			}
			std::cout << "Index out of bounds" << std::endl;
			return;
		}

		if(node == this->zero){
			this->zero = n;
			Node<T>* n = new Node<T>;
			n->data = x;
			n->prev = node->prev;
			n->next = node;
			n->prev->next = n;
			node->prev = n;
		}


		this->length++;
	}

private:
	Node<T> *search(int i){
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
			Node<T>* act = this->end;

			for(int j=-1;j>i;j--){
				act = act->prev;
			}

			return act;
		}
	}
};