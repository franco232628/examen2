#include <iomanip>
#include <iostream>
using namespace std;
#include "Bibliotecas/Palabra.h"
#include "Bibliotecas/Comentario.h"
#include "Bibliotecas/Plato.h"
#include "Bibliotecas/Atencion.h"
#include "Bibliotecas/NodoPalabra.h"
#include "Bibliotecas/NodoPlato.h"
#include "Bibliotecas/NodoAtencion.h"
#include "Bibliotecas/FuncionesAuxiliares.h"



int main() {
    struct NodoPalabra *listaLexicon=nullptr;
    struct NodoPlato *listaPlato=nullptr;
    struct NodoAtencion *listaAtencion=nullptr;
    leerLexicon(listaLexicon);
    leerPlatos(listaPlato);
    leerAtenciones(listaAtencion, listaPlato);
    leerComentarios(listaAtencion, listaLexicon);

    int n=1;
    while (listaAtencion) {
        cout<<n<<")  "<<listaAtencion->dato.codigo<<"    -    "<<setprecision(2)<<fixed<<listaAtencion->dato.totalVenta<<endl;
        for (int i=0; i<listaAtencion->dato.cantPlatos; i++) {
            cout <<listaAtencion->dato.platosAtendidos[i].nombre<<"   -   "<<listaAtencion->dato.platosAtendidos[i].precio<<"  -  "<<listaAtencion->dato.platosAtendidos[i].cantidad<<endl;
        }
        for (int j=0; j<listaAtencion->dato.cantComentarios;j++) {
            cout<<listaAtencion->dato.comentarios[j].preProcesado<<endl;
            for (int k=0; k<listaAtencion->dato.comentarios[j].cantPalabras; k++) {
                cout<<"  -  "<<listaAtencion->dato.comentarios[j].palabras[k].polaridad<<"  --   ";
            }
            cout<<"    TOTAL:   "<<listaAtencion->dato.comentarios[j].polaridadTotal<<endl;
        }
        listaAtencion=listaAtencion->next;
        n++;
    }
    return 0;
}
