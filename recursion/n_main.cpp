#include <iostream>
#include "funciones.h"
using namespace std;

int main() {
    Funciones fun;
    int i = 0;

    // Valores que vamos a probar
    int pruebas[] = {5, 8, 10, 15};
    int totalPruebas = sizeof(pruebas) / sizeof(pruebas[0]);

    for (int j = 0; j < totalPruebas; j++) {
        int n = pruebas[j];
        int esperado = (n * (n + 1)) / 2;

        cout << "\n" << i++ << ".- respuesta esperada " << esperado
             << " programa " << fun.sumaIterativa(n) << "\n";
        cout << " " << ((esperado == fun.sumaIterativa(n)) ? "success\n" : "fail\n");

        cout << "\n" << i++ << ".- respuesta esperada " << esperado
             << " programa " << fun.sumaRecursiva(n) << "\n";
        cout << " " << ((esperado == fun.sumaRecursiva(n)) ? "success\n" : "fail\n");

        cout << "\n" << i++ << ".- respuesta esperada " << esperado
             << " programa " << fun.sumaDirecta(n) << "\n";
        cout << " " << ((esperado == fun.sumaDirecta(n)) ? "success\n" : "fail\n");
    }

    return 0;
}