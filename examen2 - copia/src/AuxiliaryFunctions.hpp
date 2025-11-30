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




void leerLexicon(struct Palabra * lexicon, int &cant_lexicon, const char * file_name);
void leerPlato(struct Plato * platos, int &cant_platos, const char * file_name);

void leerAntenciones(struct Atencion * atenciones, int &cant_atencion,
    struct Plato * platos, int cant_platos, const char * file_name);

int buscarPlato(char * codigo_leido, struct Plato * platos, int cant_platos);


int BuscarAtencion(struct Atencion * atencion,
    int cant_atencion, int num_atencion_leido);
void cargarComentarios1(struct Atencion *atenciones,
    int cant_atencion, struct Palabra * lexicon,
    int cant_lexicon, const char * file_name);
char * preProcesarPalabra(char * oracion_grande);


void elaborarReporte(struct Atencion *atenciones, int cantAtenciones) ;

void procesarComentario( struct Comentario & comentario, struct Palabra * lexicon, int cant_lexicon);
int buscarPolaridad(struct Palabra * palabra, int cant_lexicon, char * texto);







#endif //EXAMEN2_AUXILIARYFUNCTIONS_HPP
