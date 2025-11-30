#include "src/AuxiliaryFunctions.hpp"




int main() {
    struct Palabra lexicon[100]{};
    struct Plato *platos = new struct Plato[200]{};
    struct Atencion atenciones[100]{};
    int cant_atencion = 0, cant_lexicon = 0, cant_platos = 0;

    leerLexicon(lexicon, cant_lexicon, "Data/lexicon.csv");
    leerPlato(platos, cant_platos, "Data/platos.csv");

    leerAntenciones(atenciones,cant_atencion,platos, cant_platos, "Data/atenciones.txt");

    cargarComentarios1(atenciones,cant_atencion, lexicon, cant_lexicon,"Data/comentarios.csv" );


    elaborarReporte(atenciones, cant_atencion);

    return 0;
}
