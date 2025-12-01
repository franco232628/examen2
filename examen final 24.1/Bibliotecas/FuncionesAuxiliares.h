//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_FINAL_24_1_FUNCIONESAUXILIARES_H
#define EXAMEN_FINAL_24_1_FUNCIONESAUXILIARES_H
void leerClientes(struct Cliente *arrClientes, int &cantClientes);
char * leerCadenaExacta(ifstream & archivo, char c);
void leerLibros(struct Libro * arrLibros, int &cantLibros);
void leerVentas(struct Libro *arrLibros, int cantLibros, struct Cliente *arrClientes, int cantClientes);
int buscarDni(struct Cliente *arrCliente, int cantClientes, int dni);
int buscarLibro(struct Libro *arrLibro, int cantLibros, char *codigo);
int buscarLibreria(struct Libro libro, int cant, int libreria);
#endif //EXAMEN_FINAL_24_1_FUNCIONESAUXILIARES_H