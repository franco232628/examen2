//
// Created by Diego Zapata on 30/11/2025.
//
#include <iomanip>
using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include "Cliente.h"
#include "Venta.h"
#include "Libreria.h"
#include "Libro.h"
#include "FuncionesAuxiliares.h"


void leerClientes(struct Cliente *arrClientes, int &cantClientes) {
    ifstream archivo("ArchivosDeDatos/Clientes.csv", ios::in);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    while (true) {
        archivo>>arrClientes[cantClientes].dni;
        if (archivo.eof()) break;
        archivo.get();
        arrClientes[cantClientes].nombre = leerCadenaExacta(archivo, '\n');
        arrClientes[cantClientes].montoComprado=0;
        arrClientes[cantClientes].descuentoFuturo=0;
        cantClientes++;
    }
}

void leerLibros(struct Libro * arrLibros, int &cantLibros) {
    ifstream archivo("ArchivosDeDatos/Libros.csv", ios::in);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    while (true) {
        arrLibros[cantLibros].codigo=leerCadenaExacta(archivo, ',');
        if (arrLibros[cantLibros].codigo==nullptr) break;
        arrLibros[cantLibros].titulo=leerCadenaExacta(archivo, ',');
        arrLibros[cantLibros].autor=leerCadenaExacta(archivo, ',');
        archivo>>arrLibros[cantLibros].precio;
        arrLibros[cantLibros].cantBuenasCal=0;
        arrLibros[cantLibros].cantLibrerias=0;
        arrLibros[cantLibros].cantMalasCal=0;
        arrLibros[cantLibros].librerias=new struct Libreria [5]{};
        arrLibros[cantLibros].sumaBuenasCal=0;
        arrLibros[cantLibros].sumaMalasCal=0;
        arrLibros[cantLibros].totalVentas=0;
        arrLibros[cantLibros].unidadesVendidas=0;
        cantLibros++;
    }
}



void leerVentas(struct Libro *arrLibros, int cantLibros, struct Cliente *arrClientes, int cantClientes) {
    ifstream archivo("ArchivosDeDatos/Ventas.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int libreria, aa, mm, dd, dni, calificacion;
    char c, codigo[10];
    while (true) {
        archivo>>libreria>>dd>>c>>mm>>c>>aa;
        if (archivo.eof()) break;
        while (true) {
            archivo>>ws;
            archivo.getline(codigo, 10, ' ');
            archivo>>dni>>calificacion;
            int pos1=buscarDni(arrClientes, cantClientes, dni);
            int pos2=buscarLibro(arrLibros, cantLibros, codigo);
            if (pos2!=-1) {
                double venta=arrLibros[pos2].precio;
                if (pos1!=-1) {
                    arrClientes[pos1].montoComprado+=venta;
                    if (calificacion>50) {
                        arrLibros[pos2].sumaBuenasCal+=calificacion;
                        arrLibros[pos2].cantBuenasCal++;
                    }
                    else {
                        arrLibros[pos2].sumaMalasCal+=calificacion;
                        arrLibros[pos2].cantMalasCal++;
                    }
                    arrLibros[pos2].totalVentas+=venta;
                    arrLibros[pos2].unidadesVendidas++;
                    int k=buscarLibreria(arrLibros[pos2], arrLibros[pos2].cantLibrerias, libreria);
                    if (k==-1) {
                        int m=arrLibros[pos2].cantLibrerias;
                        arrLibros[pos2].librerias[m].codigo=libreria;
                        arrLibros[pos2].librerias[m].totalVentas+=venta;
                        int j=arrLibros[pos2].librerias[m].cantVentas;
                        if (j==0) arrLibros[pos2].librerias[m].ventas=new struct Venta[10];
                        arrLibros[pos2].librerias[arrLibros[pos2].cantLibrerias].ventas[j].dniComprador=arrClientes[pos1].dni;
                        arrLibros[pos2].librerias[arrLibros[pos2].cantLibrerias].ventas[j].nombreComprador=arrClientes[pos1].nombre;
                        arrLibros[pos2].librerias[arrLibros[pos2].cantLibrerias].ventas[j].fecha=aa*10000+mm*100+dd;
                        arrLibros[pos2].librerias[arrLibros[pos2].cantLibrerias].cantVentas++;
                        arrLibros[pos2].cantLibrerias++;
                    }
                    else {
                        arrLibros[pos2].librerias[k].totalVentas+=venta;
                        int j=arrLibros[pos2].librerias[k].cantVentas;
                        if (j==0) arrLibros[pos2].librerias[k].ventas=new struct Venta[10];
                        arrLibros[pos2].librerias[k].ventas[j].dniComprador=arrClientes[pos1].dni;
                        arrLibros[pos2].librerias[k].ventas[j].nombreComprador=arrClientes[pos1].nombre;
                        arrLibros[pos2].librerias[k].ventas[j].fecha=aa*10000+mm*100+dd;
                        arrLibros[pos2].librerias[k].cantVentas++;
                    }
                }
            }

            if (archivo.peek()=='\n' or archivo.eof()) break;
        }
    }
    for (int i = 0; i < cantClientes; i++) {
        if (arrClientes[i].montoComprado>5000) arrClientes[i].descuentoFuturo=0.3;
        else if (arrClientes[i].montoComprado>3000) arrClientes[i].descuentoFuturo=0.2;
        else arrClientes[i].descuentoFuturo=0.1;
    }
}

int buscarLibreria(struct Libro libro, int cant, int libreria) {
    for (int i = 0; i < cant; i++) {
        if (libro.librerias[i].codigo == libreria) return i;
    }
    return -1;
}

int buscarDni(struct Cliente *arrCliente, int cantClientes, int dni) {
    for (int i=0; i<cantClientes; i++) {
        if (arrCliente[i].dni==dni) return i;
    }
    return -1;
}

int buscarLibro(struct Libro *arrLibro, int cantLibros, char *codigo) {
    for (int i=0; i<cantLibros; i++) {
        if (strcmp(arrLibro[i].codigo, codigo)==0) return i;
    }
    return -1;
}

char * leerCadenaExacta(ifstream & archivo, char c) {
    char buffer[1000], *ptr;
    archivo>>ws;
    archivo.getline(buffer, 1000, c);
    if (archivo.eof()) return nullptr;
    ptr = new char[strlen(buffer) + 1];
    strcpy(ptr, buffer);
    return ptr;
}