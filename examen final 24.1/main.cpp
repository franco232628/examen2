#include <iostream>
using namespace std;
#include "Bibliotecas/Cliente.h"
#include "Bibliotecas/Venta.h"
#include "Bibliotecas/Libreria.h"
#include "Bibliotecas/Libro.h"
#include "Bibliotecas/FuncionesAuxiliares.h"



int main(int argc, const char * argv[]) {
    struct Cliente *arrClientes=new struct Cliente[100];
    struct Libro *arrLibros=new struct Libro[300];
    int cantClientes=0, cantLibros=0;
    leerClientes(arrClientes, cantClientes);
    leerLibros(arrLibros, cantLibros);
    leerVentas(arrLibros, cantLibros, arrClientes, cantClientes);
    for (int i = 0; i < cantClientes; i++) {
        cout << arrLibros[i].titulo << "   -   "<<arrLibros[i].codigo<<endl;
        for (int j = 0; j < arrLibros[i].cantLibrerias; j++) {
            cout <<"LIBRERIA  "<<j+1<<")  "<<arrLibros[i].librerias[j].codigo<<"   "<< arrLibros[i].librerias[j].cantVentas << endl;
            for (int k = 0; k < arrLibros[i].librerias[j].cantVentas; k++) {
                cout << arrLibros[i].librerias[j].ventas[k].dniComprador << "   nombre: "<<arrLibros[i].librerias[j].ventas[k].nombreComprador<<endl;
            }
        }
    }
    return 0;
}
