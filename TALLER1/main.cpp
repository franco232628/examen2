#include "src/AuxiliaryFunctions.hpp"


;




int main() {
    struct Libro *arrLibro = new struct Libro[40]{};
    int cant_Libro = 0;

    leerLibro(arrLibro, cant_Libro, "Data/Libros.csv");
    // reporte(arrLibro, cant_Libro, "Reports/reporteInicail.txt");
    mostrarLibros("Reports/reporteInicail.txt",arrLibro, cant_Libro);

    struct Usuario *arrUsuario = new struct Usuario[60]{};
    int cant_Usuario = 0;
    leerUsuario(arrUsuario, cant_Usuario, "Data/Usuarios.csv");
    mostrarUsuarios("Reports/reporteInicailUsuario.txt",arrUsuario, cant_Usuario);


    leerPresatamo(arrLibro, cant_Libro,arrUsuario, cant_Usuario, "Data/PrestamoDeLibros.txt");

    mostrarLibros("Reports/reporteInicailFINALL.txt",arrLibro, cant_Libro);
    mostrarUsuarios("Reports/reporteInicailUsuarioFINALKLLL.txt",arrUsuario, cant_Usuario);

    ordenarPorCodigo(arrLibro, cant_Libro,arrUsuario, cant_Usuario);
    mostrarLibros("Reports/reporteInicailFINALLOrdenado.txt",arrLibro, cant_Libro);
    mostrarUsuarios("Reports/reporteInicailUsuarioFINALKLLLOrdenado.txt",arrUsuario, cant_Usuario);
    return 0;
}
