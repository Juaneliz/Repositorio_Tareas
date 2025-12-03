#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
using namespace std;

template <class T>
class Sorts {
public:
    Sorts() {}

	void swap(vector<T> &v, int i, int j);
    void ordenaSeleccion(vector<T> &v);
    void ordenaBurbuja(vector<T> &v);
    void ordenaMerge(vector<T> &v);

    int busqSecuencial(const vector<T> &v, T val);
    int busqBinaria(const vector<T> &v, T val);

private:

    void mergeSplit(vector<T> &v,vector<T> &s, int low, int high);
    void mergeArray(vector<T> &v, vector<T> &s, int low, int mid, int high);
};


template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j){
		T aux = v[i];
	v[i] = v[j];
	v[j] = aux;		
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(v,i, minIndex);
        }
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v, j, j + 1);
            }
        }
    }
}


template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v) {
    if (v.size() > 1) {
		vector<T> s(v.size());
        mergeSplit(v,s, 0, v.size() - 1);
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &v,vector<T> &s, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSplit(v,s, low, mid);
        mergeSplit(v,s, mid + 1, high);
        mergeArray(v,s, low, mid, high);
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &v,vector<T> &s, int low, int mid, int high) {

	int i = low; 
	int j = mid + 1;
	int k = low;


    while (i <= mid && j <= high) {
        if (v[i] <= v[j]) {
            s[k++] = v[i++];
        } else {
            s[k++] = v[j++];
        }
    }

    while (i <= mid) {
        s[k++] = v[i++];
    }

    while (j <= high) {
        s[k++] = v[j++];
    }

    for (int m = low; m <= high; m++) {
        v[m] = s[m];
    }
    


}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &v, T val) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}


template <class T>
int Sorts<T>::busqBinaria(const vector<T> &v, T val) {
    int low = 0; 
	int high = v.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (v[mid] == val) {
            return mid;
        } 
		if (v[mid] < val) {
            low = mid + 1;
        } 
		if (v[mid] > val){
            high = mid - 1;
        }
    }
    return -1;
}

#endif //SORTS_H_ //
