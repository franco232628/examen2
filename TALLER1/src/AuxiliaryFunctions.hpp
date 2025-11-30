//
// Created by GRINGO on 30/11/2025.
//

#ifndef EXAMEN2_AUXILIARYFUNCTIONS_HPP
#define EXAMEN2_AUXILIARYFUNCTIONS_HPP

#include "Utils.hpp"

void open_read(ifstream &input, const char *file_name) ;
char *read_str(ifstream &input, char delim, int max) ;
void open_print(ofstream &output, const char *file_name);
void print_line(ofstream &output, char caract, int max) ;
double read_double(ifstream &input);
int read_time(ifstream &input, int cond);
void print_time(ofstream &output, int time) ;
char * asignar(char *str);
void asignarCadena(char *&cadDestino, char *cadOrigen);

void leerLibro(struct Libro * arrLibro, int &cant_libro, const char * file_name);
void leerUsuario(struct Usuario * arrUsuario, int &cant_usuario, const char * file_name);


int read_int( ifstream & input);


void reporte(struct Libro * arrLibro, int cant_libro, const char * file_name);
void leerPresatamo(struct Libro * arrLibro, int cant_libro, struct Usuario * arrUsuario, int cant_usuario, const char * file_name);


// int buscarLibroo(int cant_usuario, struct Usuario * arrUsuario, int dni_leido);



// int buscarUsuario(int cant_libro, struct Libro * arrLibro, char * codigo_leido);

void reporteValidacion(Libro *arrLibro, int cant_libro,
                       Usuario *arrUsuario, int cant_usuario,
                       const char *nombreArchivo);

bool validarDNI(int dni);

bool validarFecha(int dd, int mm, int anho);


void mostrarLibros(const char *nombArch,struct Libro *arrLibros,int cantLibros);

void mostrarUsuarios(const char *nombArch,struct Usuario *arrUsuarios,int cantUsuarios);
int buscarLibro(struct Libro * arrLibros, int cant_libro, char * str);
int buscarUsuario(struct Usuario * usuario, int cant_usuario, int dni);


void ordenarPorCodigo(struct Libro * &libro, int cant_libro, struct Usuario * &usuario, int cant_usuario);
void swapC( struct Libro & libro, struct Libro & libro1);
void swapU(struct Usuario & usuario,  struct Usuario & usuario1);
void swapO(struct UsuarioConElLibro &usuario, struct UsuarioConElLibro &usuario_con_el_libro);


#endif //EXAMEN2_AUXILIARYFUNCTIONS_HPP
