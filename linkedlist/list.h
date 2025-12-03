#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val):value(val),next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) :value(val),next(nxt){}

template <class T>
Link<T>::Link(const Link<T> &source): value(source.value),next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
    ~List();


    void insertion(T val);
	int search(T);
    void update (int pos, T newVal);
    T deleteAt(int pos);
	std::string toString() const;

    bool empty() const;
    int length() const;
    void clear();

private:
	Link<T> *head;
	int 	size;

};


template <class T>
List<T>::List():head(0),size(0) {}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
void List<T>::clear() {
	while (!empty()) {
		deleteAt(0);
	}
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
int List<T>::length() const {
	return size;
}
template <class T>
void List<T>::insertion(T val)  {
	Link<T> *newlink,*p;
	newlink=new Link<T>(val);

	if (head==0) {
        head = newlink;
        size++;
	}
    else{
        p=head;
        while (p->next !=0) {
            p=p->next;
        }
        newlink->next=0;
        p->next=newlink;
        size++;
}
}

template <class T>
int List<T>::search(T val) {
	Link<T> *ptr;
	ptr=head;
    int index=0;
	while (ptr !=0) {
		if( ptr->value== val){
			return index;
		}
		ptr= ptr->next;
        index ++;
	}
	return -1;

}


template <class T>
void List<T>::update(int pos, T newVal) {
    if (pos<0 || pos >= size){
        return;    
    }
    Link<T> *ptr;
    ptr=head;
    for (int i=0;i<pos;i++) {
        ptr=ptr->next;
    }
    ptr->value=newVal;
}

template<class T>
T List<T>:: deleteAt(int pos) {
    if (pos<0 || pos>= size){
        return 0;
    }
    Link<T> *p;
    p=head;
    T deletedValue;
    if (pos==0){
        deletedValue= head->value;
        head = head->next;
        delete p;
    }
    else {
        Link<T> *ptr;
    ptr= 0;
    for (int i=0;i<pos;i++){
        ptr= p;
        p= p->next;
    }
    deletedValue= p->value;
    ptr->next= p->next;
    delete p;
    }
    size--;
    return deletedValue;


}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
List<T>::List(const List<T> &source)  {
}

#endif //linkedlist