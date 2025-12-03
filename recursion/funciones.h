#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
#include <stdexcept>
using namespace std;

class Funciones {
public:
    Funciones() {}

    // Suma iterativa usando un ciclo
    long sumaIterativa(int num) {
        long sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        return sum;
    }

    // Suma Recursiva
    int sumaRecursiva(int n) {
        if (n == 0) {
            return 0;   // caso base
        }
        if (n==1){
            return 1;
        }
        return (n + sumaRecursiva(n - 1)); // recursion
    }

    // Suma usando formula 
    //Se uso la formula de Gauss
    // S= (n*(n+1))/2
    int sumaDirecta(int n) {
        if (n < 1) {
            return 0; 
        }
        return ((n * (n + 1)) / 2);
    }
};

#endif /* FUNCIONES_H_ */
