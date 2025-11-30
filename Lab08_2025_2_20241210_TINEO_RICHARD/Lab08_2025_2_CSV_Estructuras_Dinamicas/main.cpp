#include "Bibliotecas/AuxiliaryFunctions.hpp"

// Nombre: Tineo Quispe Richard Franco
// Codigo: 20241210
// Descripcion: Leer los archivos de categorias, comentarios, streams, y generar un reporte basandonos en los codigos,
//nombres, descipciones, canales, comprendiendo en los minutos, ratings y las descripcion que hubo en cada canal.
//observando las distintas reacciones, comentarios en los disntintos estilos de streams realizados.
int main() {
    struct Categoria *arrCategoria = new Categoria[110]{};
    int cantidadCategorias = 0;
    leerCategoria(arrCategoria, cantidadCategorias,
                  "ArchivosDeDatos/Categorias.csv");
    imprimirReporteDePruebaDeCategorias(arrCategoria, cantidadCategorias,
        "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
        "ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", "ArchivosDeReporte/ReporteDePruebaOrdenado.txt",
        "ArchivosDeReporte/ReporteDePruebaConComentarios.txt",1);


    leerStreams(arrCategoria, cantidadCategorias,
                  "ArchivosDeDatos/StreamsReproducidos.csv");

    imprimirReporteDePruebaDeCategorias(arrCategoria, cantidadCategorias,
        "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
        "ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", "ArchivosDeReporte/ReporteDePruebaOrdenado.txt",
        "ArchivosDeReporte/ReporteDePruebaConComentarios.txt",-1);

    imprimirReporteDePruebaDeCategorias(arrCategoria, cantidadCategorias,
        "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
        "ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", "ArchivosDeReporte/ReporteDePruebaOrdenado.txt",
        "ArchivosDeReporte/ReporteDePruebaConComentarios.txt",2);

    leerComentarios(arrCategoria, cantidadCategorias,
                  "ArchivosDeDatos/ComentariosAlCanal.csv");
    imprimirReporteDePruebaDeCategorias(arrCategoria, cantidadCategorias,
        "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
        "ArchivosDeReporte/ReporteDePruebaConReproducciones.txt", "ArchivosDeReporte/ReporteDePruebaOrdenado.txt",
        "ArchivosDeReporte/ReporteDePruebaConComentarios.txt",-2);

    return 0;
}
