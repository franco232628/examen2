//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_ESPECIAL_25_1_FUNCIONESAUXILIARES_H
#define EXAMEN_ESPECIAL_25_1_FUNCIONESAUXILIARES_H
void leerLexicon(struct NodoPalabra *&listaLexicon);
char *leerCadenaExacta(ifstream &archivo, char lim);
void insertarPalabra(struct NodoPalabra *&lista, struct Palabra dato);
void leerPlatos(struct NodoPlato *&listaPlato);
void insertarPlato(struct NodoPlato *&lista, struct Plato dato);
void leerAtenciones(struct NodoAtencion *&listaAtencion, struct NodoPlato *listaPlato);
char * asignarCadena(char * str);
struct NodoPlato * buscarEnLista(struct NodoPlato *lista, char *codigo);
void insertarAtencion(struct NodoAtencion *&lista, struct Atencion dato);
struct NodoAtencion * buscarCodigo(struct NodoAtencion *lista, int codigo);
void procesar(struct Comentario &comentario, struct NodoPalabra *listaLexicon);
char * preProcesar(char * texto);
int buscarPalabra(struct NodoPalabra *lista, char * texto);
void leerComentarios(struct NodoAtencion*&listaAtencion, struct NodoPalabra *listaLexicon);

#endif //EXAMEN_ESPECIAL_25_1_FUNCIONESAUXILIARES_H