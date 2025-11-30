//
// Created by aml on 17/11/2025.
//

#include "AuxiliaryFunctions.hpp"


void open_read(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (!input.is_open()) {
        cout << "Error al abrir el archivo " << file_name << endl;
        exit(1);
    }
}

void open_print( ofstream & output, const char * file_name) {
    output.open(file_name, ios::out);
    if (!output.is_open()) {
        cout << "Error al abrir el archivo " << file_name << endl;
        exit(1);
    }
}

void print_line(ofstream &output, int size, char caract) {
    for (int i = 0; i < size; i++) output.put(caract);
    output << endl;
}



char * read_str(ifstream &input, char delim, int MAX) {
    char *str, buffer[MAX];
    input >> ws;
    input.getline(buffer, MAX, delim);
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}
// char *asignarCadena(char *str,const char buffer) {
//     str = new char[strlen(buffer) + 1];
//     strcpy(str, buffer);
//     return str;
// }

//parte de la impresion
void ordenarPorNombre(struct Categoria *&arrCategoria, int cantidadCategorias) {
    for (int i = 0; i < cantidadCategorias -1; i++) {
        for (int j = i+1; j < cantidadCategorias; j++) {
            if (strcmp(arrCategoria[i].nombre, arrCategoria[j].nombre) > 0) {
                swapC(arrCategoria[i], arrCategoria[j]);
            }
        }
    }
}

void printHeaders(ofstream &output, int cantidadCategorias, struct Categoria *arrCategoria, int posicion) {
    print_line(output, MAX_REPORTE, '=');
    output << left << "Codigo: " << arrCategoria[posicion].codigo << endl;
    output << left << "Nombre: " << arrCategoria[posicion].nombre << endl;
    output << left << "Descripcion: " << arrCategoria[posicion].descripcion << endl;
    print_line(output, MAX_REPORTE, '-');
}


void imprimirReporteDePruebaDeCategorias(struct Categoria * arrCategoria,
                                         int cantidadCategorias, const char * file_name, const char * file_nameReprod,
                                         const char * file_nameOrden, const char * file_nameComentario, int cond) {
    ofstream output;
    if (cond == 1) open_print(output, file_name);if (cond == -1) open_print(output, file_nameReprod);
    if (cond == 2) open_print(output, file_nameOrden);
    if (cond==-2) open_print(output, file_nameComentario);
    if (cond == 2 or cond == -2) {
        ordenarPorNombre(arrCategoria, cantidadCategorias);
    }
    output << right << setw((MAX_REPORTE/2)+22)<<"REPORTE POR CATEGORIAS" << endl;
    for (int i = 0; i < cantidadCategorias; i++) {
        printHeaders(output, cantidadCategorias, arrCategoria, i);
        if (cond == -1 or cond == 2 or cond == -2) {
            output << "REPRODUCCIONES: " << endl;
            for (int j = 0; j < arrCategoria[i].numReproducciones; j++) {
                output << "CANAL: " << setw(20) << arrCategoria[i].reproducciones[j].canal << "RATING: " <<setw(9)<< arrCategoria[i].reproducciones[j].rating <<  "DURACION: ";
                print_time(output, arrCategoria[i].reproducciones[j].duracion);
                output << left << endl;
                if (cond == -2) {
                    output << right << setw(15) <<"COMENTARIOS:"<<endl;
                    for (int k = 0; k < arrCategoria[i].reproducciones[j].numComentarios; k++) {
                        output << right << setw(5) <<"- "<<arrCategoria[i].reproducciones[j].comentarios[k] << endl<< left;
                    }
                }
            }
        }
    }
}

void leerCategoria(struct Categoria *arrCategoria,
                   int &cantidadCategorias, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        // UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
        arrCategoria[cantidadCategorias].codigo = read_str(input, ',', 10 );
        if (input.eof()) break;
        arrCategoria[cantidadCategorias].nombre = read_str(input, ',', 100 );
        arrCategoria[cantidadCategorias].descripcion = read_str(input, '\n', 100 );

        arrCategoria[cantidadCategorias].reproducciones = new Reproduccion[15];
        arrCategoria[cantidadCategorias].numReproducciones = 0;
        arrCategoria[cantidadCategorias].promedioRating = 0;
        arrCategoria[cantidadCategorias].duracionTotal = 0;
        cantidadCategorias++;
    }
}

void leerStreams(struct Categoria *arrCategoria, int cantidadCategorias, const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    char *nombreCanalLeido, *codeCategoria;
    while (true) {
        nombreCanalLeido = read_str(input, ',', 40 );
        if (input.eof()) break;
        codeCategoria = read_str(input, ',', 20 );
        int posCategoria = buscarCategoria(arrCategoria, cantidadCategorias, codeCategoria);
        if (posCategoria != -1) {
            arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].canal = nombreCanalLeido;
            arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].rating = read_double(input);
            arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].duracion = read_time(input);
            arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].numComentarios = 0;
            arrCategoria[posCategoria].promedioRating += arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].rating;
            arrCategoria[posCategoria].duracionTotal +=arrCategoria[posCategoria].reproducciones[arrCategoria[posCategoria].numReproducciones].duracion ;
            arrCategoria[posCategoria].numReproducciones++;
        }
    }
    for (int i = 0; i < cantidadCategorias; i++) {
        arrCategoria[i].promedioRating = arrCategoria[i].promedioRating/double(arrCategoria[i].numReproducciones);
    }
}

int buscarCategoria(struct Categoria *arrCategoria, int cantidadCategorias, char *code_categoria) {
    for (int i = 0; i < cantidadCategorias; i++) {
       if (strcmp(arrCategoria[i].codigo, code_categoria) == 0){
           return i;
       }
    }
    return -1;
}

double read_double(ifstream &input) {
    double num;
    input >> num;
    input.get();
    return num;
}

int read_time(ifstream &input) {
    int hh, mm, ss;
    char c;
    input >> hh >> c >> mm >> c>> ss;
    return hh*3600 + mm*60 + ss;
}

void print_time(ofstream &output, int duracion) {
    int hora = duracion / 3600;
    int minutes = (duracion/60)%60;
    int segundo = duracion%60;

    output << right << setfill('0') << setw(2) << hora << ":" << setw(2) << minutes << ":" << setw(2) << segundo;
    output << setfill(' ');
}

void swapC(struct Categoria &categoria1, struct Categoria &categoria2) {
    struct Categoria temp;
    temp = categoria1;
    categoria1 = categoria2;
    categoria2 = temp;
}



void leerComentarios(struct Categoria *arrCategoria, int cantidadCategorias, const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    char *canal_leido, *descripcion;
    while (true) {
        canal_leido = read_str(input, ',', 100);
        if (input.eof()) break;
        descripcion = read_str(input, '\n', 100);
        agregarDescripcion(arrCategoria, cantidadCategorias, canal_leido, descripcion);

    }
}
void agregarDescripcion(struct Categoria * &arrCategoria,
    int cantidadCategorias, char * canal_leido, char * descripcion_leido){

    for (int i = 0; i < cantidadCategorias; i++) {
        for (int j=0; j < arrCategoria[i].numReproducciones; j++) {
            if (strcmp(arrCategoria[i].reproducciones[j].canal, canal_leido) == 0) {
                arrCategoria[i].reproducciones[j].comentarios[arrCategoria[i].reproducciones[j].numComentarios] = descripcion_leido;
                arrCategoria[i].reproducciones[j].numComentarios++;
            }
        }

    }
}

