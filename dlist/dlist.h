#ifndef DLIST_H
#define DLIST_H

#include <sstream>
using namespace std;

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *previous;
	Link<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), previous(0), next(0) {}

template <class T>
Link<T>::Link(T val, Link *prev, Link* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), previous(source.previous), next(source.next) {}


// ======================= LIST ===========================
template <class T>
class DList {
private:
    Link<T>* head;
    Link<T>* tail;
    int size;

    friend class DListIterator<T>;

public:
    DList();
    ~DList();

    bool empty() const;
    int length() const;
    void clear();

    void insertion(const T&);          // insertar al final
    int search(const T&) const;        // buscar y devolver posición
    void update(int, const T&);        // actualizar por posición
    T deleteAt(int);                   // eliminar por posición

    string toStringForward() const;
    string toStringBackward() const;
};

// --- Implementación ---
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return head==0;
}

template <class T>
int DList<T>::length() const {
    return size;
}

template <class T>
void DList<T>::clear() {
	Link<T> *p,*q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

// Insertar al final
template <class T>
void DList<T>::insertion(const T& val) {
    Link<T>* newLink = new Link<T>(val);
    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous=tail;
        tail = newLink;
    }
    size++;
}

// Buscar y devolver índice (o -1 si no está)
template <class T>
int DList<T>::search(const T& val) const {
    int pos = 0;
    Link<T>* p;
    p = head;
    while (p != 0) {
        if (p->value == val) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return -1;
}

// Actualizar por posición
template <class T>
void DList<T>::update(int index, const T& val) {
    if (index < 0 || index >= size) {
        return;
    }
    Link<T>* p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    p->value = val;
}

// Eliminar por posición
template <class T>
T DList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return 0;
    }

    Link<T>* p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    T val = p->value;

    if (p->previous != 0) {
        p->previous->next = p->next;
    } else {
        head = p->next;
    }
    if (p->next != 0) {
        p->next->previous = p->previous;
    } else {
        tail = p->previous;
    }

    delete p;
    size--;

    return val;
}

// Recorrido hacia adelante
template <class T>
string DList<T>::toStringForward() const {
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

// Recorrido hacia atrás
template <class T>
string DList<T>::toStringBackward() const {
	std::stringstream aux;
	Link<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}


// ======================= ITERATOR ===========================
template <class T>
class DListIterator {
private:
    Link<T>* current;

    friend class DList<T>;

public:
    DListIterator(Link<T>* start);
    bool hasNext();
    T next();
};

template <class T>
DListIterator<T>::DListIterator(Link<T>*start) : current(start){}

template <class T>
bool DListIterator<T>::hasNext(){
    return current !=0;

}

template <class T>
T DListIterator<T> ::next(){
    T val= current->value;
    current=current->next;
    return val;
}

#endif // DLIST_H
