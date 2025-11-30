//
// Created by GRINGO on 30/11/2025.
//

#include "AuxiliaryFunctions.hpp"


int read_int(ifstream &input) {
    int num;
    input >> num;
    input.get();
    return num;
}

void reporte(struct Libro *arrLibro, int cant_libro, const char *file_name) {
    ofstream output;
    open_print(output, file_name);
    output << "REPORTE" << endl;
    print_line(output, '=', 100);
    for (int i = 0; i < cant_libro; i++) {
        output << arrLibro[i].codigo <<  "    -   "
        << arrLibro[i].titulo <<  "    -   "
        << arrLibro[i].autor <<  "    -   "
        << arrLibro[i].cantidad <<  "    -   "
        << arrLibro[i].precio << endl;

    }
}




void leerPresatamo(struct Libro *arrLibro, int cant_libro,
                   struct Usuario *arrUsuario, int cant_usuario,
                   const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    char libro[8],c;
    int dni,d,m,a,fecha,idLibro,cantLib,cantUsu,idUsuario;
    struct LibroEnSuPoder libroAux;
    struct UsuarioConElLibro usuarioAux;
    while (true) {
        input>>libro;
        if (input.eof()) break;
        idLibro=buscarLibro(arrLibro,cant_libro,libro);
        if (idLibro!=-1) {
            while (true) {
                input>>dni>>d>>c>>m>>c>>a;
                fecha=a*10000+m*100+d;
                idUsuario=buscarUsuario(arrUsuario,cant_usuario,dni);
                if (idUsuario!= -1) {
                    libroAux.codLibro=new char[strlen(libro)+1];
                    strcpy(libroAux.codLibro,libro);
                    libroAux.fechaDevolucion=fecha;
                    usuarioAux.dni=dni;
                    usuarioAux.fechaDevolucion=fecha;
                    cantLib=arrUsuario[idUsuario].cantLibros;
                    arrUsuario[idUsuario].libros[cantLib]=libroAux;
                    arrUsuario[idUsuario].cantLibros++;
                    cantUsu=arrLibro[idLibro].cantUsuarios;
                    arrLibro[idLibro].usuarios[cantUsu]=usuarioAux;
                    arrLibro[idLibro].cantUsuarios++;
                }
                if (input.get()=='\n') break;
            }
        }
        else
            while (input.get()!='\n');
    }
}

int buscarLibro(struct Libro *arrLibros, int cant_libro, char *str) {
    for (int i = 0; i < cant_libro; i++) {
        if (strcmp(arrLibros[i].codigo, str) ==0) return i;
    }
    return -1;
}

int buscarUsuario(struct Usuario *usuario, int cant_usuario, int dni) {
    for (int i = 0; i < cant_usuario; i++) {
        if (dni ==  usuario[i].dni) return i;
    }
    return -1;
}




void ordenarPorCodigo(struct Libro *&libro, int cant_libro, struct Usuario *&usuario, int cant_usuario) {
    for (int i = 0; i < cant_libro - 1; i++) {
        for (int j = i +1; j < cant_libro; j++) {
            if (strcmp(libro[i].codigo, libro[j].codigo) >0) {
                swapC(libro[i], libro[j]);
            }
        }
    }
    for (int k=0; k<cant_libro;k++) {
        for (int i = 0; i < libro[k].cantUsuarios - 1; i++) {
            for (int j = i +1; j < libro[k].cantUsuarios; j++) {
                if (libro[k].usuarios[i].fechaDevolucion < libro[k].usuarios[j].fechaDevolucion or
                    (libro[k].usuarios[i].fechaDevolucion == libro[k].usuarios[j].fechaDevolucion and
                        libro[k].usuarios[i].dni > libro[k].usuarios[j].dni)) {
                    swapO(libro[k].usuarios[i], libro[k].usuarios[j]);
                }
            }
        }
    }

}


void swapC(struct Libro &libro, struct Libro &libro1) {
    struct Libro temp;
    temp = libro;
    libro=libro1;
    libro1=temp;
}

void swapU(struct Usuario &usuario, struct Usuario &usuario1) {
    struct Usuario temp;
    temp = usuario;
    usuario=usuario1;
    usuario1=temp;
}

void swapO(struct UsuarioConElLibro &usuario, struct UsuarioConElLibro &usuario_con_el_libro) {
    struct UsuarioConElLibro temp;
    temp = usuario;
    usuario=usuario_con_el_libro;
    usuario_con_el_libro=temp;
}

void open_read(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (!input.is_open()) {
        cout << "Error al abrir el archivo" << file_name << endl;
        exit(1);
    }
}

char *read_str(ifstream &input, char delim, int max) {
    char *str, buffer[max];
    input >> ws;
    input.getline(buffer, max, delim);
    if (input.eof()) return nullptr;
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}

void open_print(ofstream &output, const char *file_name) {
    output.open(file_name, ios::out);
    if (!output.is_open()) {
        cout << "Error al abrir el archivo" << file_name << endl;
        exit(1);
    }
}

void print_line(ofstream &output, char caract, int max) {
    for (int i = 0; i < max; i++) output.put(caract);
    output << endl;
}

double read_double(ifstream &input) {
    double num;
    input >> num;
    input.get();
    return num;
}

int read_time(ifstream &input, int cond) {
    int hh, mm, ss;
    char c;
    if (cond == 1) {
        input >> hh >> c >> mm >> c >> ss;
    } else {
        input >> mm >> c >> ss;
    }
    return hh * 3600 + mm * 60 + ss;
}

void print_time(ofstream &output, int time) {
    int hora = time / 3600;
    int min = (time / 60) % 60;
    int seg = time % 60;

    output << right << setfill('0') << setw(2) << hora << ":" << setw(2) << min
            << ":" << setw(2) << seg;
    output << setfill(' ') << left;
}


char *asignar(char *str) {
    char *palabra = new char[strlen(str) + 1];
    strcpy(palabra, str);
    return palabra;
}


void asignarCadena(char *&cadDestino, char *cadOrigen) {
    // para que dos punteros no apunten al mismo dato
    cadDestino = new char[strlen(cadOrigen) + 1]; // asignar espacio independiente
    strcpy(cadDestino, cadOrigen); // copiar lo mismo que en el otro
}



void leerLibro(struct Libro *arrLibro,
               int &cant_libro, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        arrLibro[cant_libro].codigo = read_str(input, ',', 10);
        if (arrLibro[cant_libro].codigo == nullptr) break;
        arrLibro[cant_libro].titulo = read_str(input, ',', 80);
        arrLibro[cant_libro].autor = read_str(input, ',', 50);
        arrLibro[cant_libro].cantidad = read_int(input);
        input >> arrLibro[cant_libro].precio;

        arrLibro[cant_libro].usuarios = new struct UsuarioConElLibro[arrLibro[cant_libro].cantidad]{};
        cant_libro++;
    }
}

void leerUsuario(struct Usuario *arrUsuario, int &cant_usuario, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        //54393647,Reyes Tang Edward,V,13.00
        input >> arrUsuario[cant_usuario].dni;
        if (input.eof()) break;
        input.get();
        arrUsuario[cant_usuario].nombre = read_str(input, ',', 80);
        input >> arrUsuario[cant_usuario].categoria;
        input.get();
        input >> arrUsuario[cant_usuario].calificacion;
        arrUsuario[cant_usuario].cantLibros = 0;
        arrUsuario[cant_usuario].libros = new struct LibroEnSuPoder[6]{};

        cant_usuario++;
    }

}

void mostrarUsuarios(const char *nombArch,struct Usuario *arrUsuarios,int cantUsuarios){
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"El archivo "<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
    arch<<setw(40)<<"LISTA DE USUARIOS"<<endl<<fixed<<setprecision(2);
    print_line(arch, '=', 120);
    arch<<setw(6)<<"DNI"<<setw(20)<<"NOMBRE"<<setw(30)<<"CATEGORIA"<<setw(15)<<"CALIFICACION"
        <<setw(15)<<"CANT.LIBROS"<<endl;
    for (int i=0;i<cantUsuarios;i++) {
        arch<<setfill('0')<<setw(8)<<arrUsuarios[i].dni<<setfill(' ')<<setw(3)<<' '<<left
           <<setw(40)<<arrUsuarios[i].nombre<<right<<setw(5)<<arrUsuarios[i].categoria
           <<setw(12)<<arrUsuarios[i].calificacion<<setw(10)<<arrUsuarios[i].cantLibros<<endl;
        print_line(arch, '-', 120);
        if (arrUsuarios[i].cantLibros>0) {
            arch<<setw(6)<<"DNI"<<setw(10)<<"FECHA"<<endl;
            for (int j=0;j<arrUsuarios[i].cantLibros;j++)
                arch<<arrUsuarios[i].libros[j].codLibro
                    <<setw(12)<<arrUsuarios[i].libros[j].fechaDevolucion<<endl;
            print_line(arch, '=', 120);
        }
    }
    arch.close();
}

void mostrarLibros(const char *nombArch,struct Libro *arrLibros,int cantLibros) {
    ofstream output;
    open_print(output, nombArch);
    output<<setw(40)<<"LISTA DE LIBROS"<<endl<<fixed<<setprecision(2);
    output<<"CODIGO"<<setw(20)<<"TITULO"<<setw(30)<<"AUTOR"<<setw(28)<<"CANTIDAD"
    <<setw(7)<<"PRECIO"<<setw(15)<<"CANT.USUARIOS"<<endl;
    print_line(output, '=', 120);
    for (int i=0;i<cantLibros;i++) {
        output<<left<<setw(10)<<arrLibros[i].codigo<<setw(30)<<arrLibros[i].titulo

        <<setw(30)<<arrLibros[i].autor<<right<<setw(12)<<arrLibros[i].cantidad
        <<setw(10)<<arrLibros[i].precio<<setw(10)<<arrLibros[i].cantUsuarios<<endl;
        print_line(output, '-', 120);
        if (arrLibros[i].cantUsuarios>0) {
            output<<setw(6)<<"DNI"<<setw(10)<<"FECHA"<<endl;
            for (int j=0;j<arrLibros[i].cantUsuarios;j++) {
                output<<setfill('0')<<setw(8)<<arrLibros[i].usuarios[j].dni<<setfill(' ')
                <<setw(12)<<arrLibros[i].usuarios[j].fechaDevolucion<<endl;
            }
            print_line(output, '=', 120);
        }

    }
}

