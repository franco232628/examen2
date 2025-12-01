//
// Created by Diego Zapata on 30/11/2025.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "Palabra.h"
#include "Comentario.h"
#include "Plato.h"
#include "Atencion.h"
#include "NodoPalabra.h"
#include "NodoPlato.h"
#include "NodoAtencion.h"
#include "FuncionesAuxiliares.h"



void leerLexicon(struct NodoPalabra *&listaLexicon) {
    ifstream archivo("ArchivosDeDatos/lexicon.csv", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    struct Palabra dato;
    while (true) {
        //rapido,1

        dato.texto = leerCadenaExacta(archivo, ',');
        if (dato.texto==nullptr) break;
        archivo>>dato.polaridad;
        insertarPalabra(listaLexicon, dato);
    }
}
char *leerCadenaExacta(ifstream &archivo, char lim) {
    char buffer[1000], *str;
    archivo>>ws;
    archivo.getline(buffer, 1000, lim);
    if (archivo.eof()) return nullptr;
    str=new char [strlen(buffer)+1];
    strcpy(str, buffer);
    return str;
}
void insertarPalabra(struct NodoPalabra *&lista, struct Palabra dato) {
    struct NodoPalabra *nuevo=new struct NodoPalabra;
    nuevo->dato=dato;

    nuevo->next=lista;
    lista=nuevo;
}


void leerPlatos(struct NodoPlato *&listaPlato) {
    ifstream archivo("ArchivosDeDatos/platos.csv", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    struct Plato dato;
    while (true) {
        //A3H6GJ,Causa de Atun,12.57
        dato.codigo=leerCadenaExacta(archivo, ',');
        if (dato.codigo==nullptr) break;
        dato.nombre=leerCadenaExacta(archivo, ',');
        archivo>>dato.precio;
        dato.cantidad=0;
        insertarPlato(listaPlato, dato);
    }
}
void insertarPlato(struct NodoPlato *&lista, struct Plato dato) {
    struct NodoPlato *p=lista;
    struct NodoPlato *ant=nullptr;
    struct NodoPlato *nuevo=new struct NodoPlato;

    nuevo->plato=dato;
    while (p) {
        if (strcmp(p->plato.codigo, dato.codigo)>0) break;
        ant=p;
        p=p->next;
    }
    nuevo->next=p;
    if (ant==nullptr) lista=nuevo;
    else ant->next=nuevo;
}



void leerAtenciones(struct NodoAtencion *&listaAtencion, struct NodoPlato *listaPlato) {
    ifstream archivo("ArchivosDeDatos/atenciones.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    struct Atencion dato;
    struct NodoPlato *p;
    int hh, mm, cant;
    char c, codigo[10];
    while (true) {
        //415217 21:36 B959AG 2 FK25HJ 1 S92K8X 3
        archivo>>dato.codigo>>c>>hh>>c>>mm;
        if (archivo.eof()) break;
        dato.cantComentarios=0;
        dato.cantPlatos=0;
        dato.hora=hh*60+mm;
        dato.totalVenta=0;
        while (true) {
            archivo>>ws;
            archivo.getline(codigo, 10, ' ');
            archivo>>cant;
            dato.platosAtendidos[dato.cantPlatos].codigo=asignarCadena(codigo);
            p=buscarEnLista(listaPlato, codigo);

            dato.platosAtendidos[dato.cantPlatos].nombre=p->plato.nombre;
            dato.platosAtendidos[dato.cantPlatos].precio=p->plato.precio;
            dato.platosAtendidos[dato.cantPlatos].cantidad=cant;
            dato.cantPlatos++;
            dato.totalVenta+=p->plato.precio*cant;
            if (archivo.peek()=='\n' or archivo.eof()) break;
        }
        insertarAtencion(listaAtencion, dato);
    }
}
char * asignarCadena(char * str) {
    char *cadena=new char[strlen(str)+1];
    strcpy(cadena, str);
    return cadena;
}
struct NodoPlato * buscarEnLista(struct NodoPlato *lista, char *codigo) {
    struct NodoPlato *p=lista;
    while (p) {
        if (strcmp(p->plato.codigo, codigo)==0) return p;
        p=p->next;
    }
    return nullptr;
}
void insertarAtencion(struct NodoAtencion *&lista, struct Atencion dato) {
    struct NodoAtencion *nuevo=new struct NodoAtencion;
    struct NodoAtencion *p=lista;
    struct NodoAtencion *ant=nullptr;
    nuevo->dato=dato;
    while (p) {
        if (p->dato.codigo<dato.codigo) break;
        ant=p;
        p=p->next;
    }
    nuevo->next=p;
    if (ant==nullptr) lista=nuevo;
    else ant->next=nuevo;
}



void leerComentarios(struct NodoAtencion*&listaAtencion, struct NodoPalabra *listaLexicon) {
    ifstream archivo("ArchivosDeDatos/comentarios.csv", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    struct NodoAtencion *p;
    int codigo, cantCom;
    char comment[1000];
    while (true) {
        archivo>>codigo;
        if (archivo.eof()) break;
        archivo.get();
        archivo.getline(comment, 1000, '\n');
        p=buscarCodigo(listaAtencion, codigo);
        cantCom=p->dato.cantComentarios;
        p->dato.comentarios[cantCom].texto=asignarCadena(comment);
        procesar(p->dato.comentarios[cantCom], listaLexicon);
        p->dato.cantComentarios++;

    }
}



void procesar(struct Comentario &comentario, struct NodoPalabra *listaLexicon) {
    comentario.preProcesado = preProcesar(comentario.texto);
    comentario.cantPalabras =0;
    int k;
    char palabra[50]; //hola mundo
    for (int i=0, k=0; comentario.preProcesado[i]; i++, k++) {
        if (comentario.preProcesado[i]!=' ') palabra[k]=comentario.preProcesado[i];
        else {
            palabra[k]= 0;
            comentario.palabras[comentario.cantPalabras].texto=asignarCadena(palabra);
            comentario.palabras[comentario.cantPalabras].polaridad=buscarPalabra(listaLexicon, palabra);
            comentario.polaridadTotal+=comentario.palabras[comentario.cantPalabras].polaridad;
            comentario.cantPalabras++;
            k=-1;
        }

    }
}


struct NodoAtencion * buscarCodigo(struct NodoAtencion *lista, int codigo) {
    struct NodoAtencion *p=lista;
    while (p) {
        if (p->dato.codigo==codigo) return p;
        p=p->next;
    }
    return nullptr;
}

char * preProcesar(char * texto) {
    char *preProcesado, buffer[200];
    int k=0;
    for (int i=0; texto[i]; i++) {
        if (texto[i]>='a' and texto[i]<='z' or texto[i]>='A' and texto[i]<='Z' or texto[i]==' ') {
            if (texto[i]>='A' and texto[i]<='Z') texto[i]+=32;
            buffer[k]=texto[i];
            k++;
        }
    }
    buffer[k]='\0';
    preProcesado=asignarCadena(buffer);
    return preProcesado;
}

int buscarPalabra(struct NodoPalabra *lista, char * texto) {
    struct NodoPalabra *p=lista;
    while (p) {
        if (strcmp(texto, p->dato.texto)==0)break;
        p=p->next;
    }
    if (p==nullptr) return 0;
    else return p->dato.polaridad;
}