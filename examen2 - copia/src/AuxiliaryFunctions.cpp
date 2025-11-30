//
// Created by GRINGO on 30/11/2025.
//

#include "AuxiliaryFunctions.hpp"


void elaborarReporte(struct Atencion *atenciones, int cantAtenciones) {
    ofstream archReporte;
    open_print(archReporte, "Reports/ReporteAtencionesAnalisisSentimiento.txt");
    archReporte << setprecision(2) << fixed;

    int polaridadAtencion;

    archReporte << setw(80) << "EMPRESA DE REPARTOS A DOMICILIO TP S. A." << endl;
    archReporte << setw(70) << "RELACIÓN DE ATENCIONES" << endl;

    for (int i = 0; i < cantAtenciones; i++) {
        archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
        archReporte << "No. ATENCION " << atenciones[i].codigo << setw(85);
        archReporte << "Atendido a las: " << setfill('0') << setw(2) << atenciones[i].hora / 100 << ':' << setw(2) <<
                atenciones[i].hora % 100 << " AM" << endl;
        archReporte << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');

        for (int j = 0; j < atenciones[i].cantidad_platos; j++) {
            archReporte << atenciones[i].platos_atendidos[j].codigo << ") ";
            archReporte << left << setw(40) << atenciones[i].platos_atendidos[j].nombre;
            archReporte << right << setw(7) << atenciones[i].platos_atendidos[j].precio << setw(10) << atenciones[i].
                    platos_atendidos[j].cantidad;
            archReporte << setw(15) << atenciones[i].platos_atendidos[j].precio * atenciones[i].platos_atendidos[j].
                    cantidad << endl;
        }

        polaridadAtencion = 0;
        for (int k = 0; k < atenciones[i].cantidad_comentarios; k++)
            polaridadAtencion += atenciones[i].comentarios[k].polaridad_total;

        archReporte << "Polaridad total de los comentarios :   " << polaridadAtencion << endl;
    }

    cout << "jueguen oneshot";
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

void leerLexicon(struct Palabra *lexicon, int &cant_lexicon, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        //rapido,1
        lexicon[cant_lexicon].texto = read_str(input, ',', 20);
        if (lexicon[cant_lexicon].texto == nullptr) break;
        input >> lexicon[cant_lexicon].polaridad;
        cant_lexicon++;
    }
}

void leerPlato(struct Plato *platos, int &cant_platos, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        //A3H6GJ,Causa de Atun,12.57
        platos[cant_platos].codigo = read_str(input, ',', 10);
        if (platos[cant_platos].codigo == nullptr) break;
        platos[cant_platos].nombre = read_str(input, ',', 30);
        input >> platos[cant_platos].precio;
        platos[cant_platos].cantidad = 0;
        cant_platos++;
    }
}


void leerAntenciones(struct Atencion *atenciones, int &cant_atencion, struct Plato *platos, int cant_platos,
                     const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    int num_atencion, hora, minuto, cantidad_plato_porcodigo;
    char c, *codigo_leido;
    while (true) {
        // 415217 21:36 B959AG 2 FK25HJ 1 S92K8X 3
        input >> num_atencion;
        if (input.eof()) break;
        input >> hora >> c >> minuto;
        atenciones[cant_atencion].hora = hora * 100 + minuto;
        atenciones[cant_atencion].codigo = num_atencion;
        while (true) {
            codigo_leido = read_str(input, ' ', 10);
            input >> cantidad_plato_porcodigo;

            int posPlato = buscarPlato(codigo_leido, platos, cant_platos);

            if (posPlato != -1) {
                int numPlatosAtendidos = atenciones[cant_atencion].cantidad_platos;
                if (numPlatosAtendidos == 0) atenciones[cant_atencion].platos_atendidos = new struct Plato[20];

                atenciones[cant_atencion].platos_atendidos[numPlatosAtendidos].codigo = asignar(codigo_leido);
                atenciones[cant_atencion].platos_atendidos[numPlatosAtendidos].nombre =
                        asignar(platos[posPlato].codigo);
                atenciones[cant_atencion].platos_atendidos[numPlatosAtendidos].precio = platos[posPlato].precio;
                atenciones[cant_atencion].platos_atendidos[numPlatosAtendidos].cantidad = cantidad_plato_porcodigo;

                atenciones[cant_atencion].total_venta +=
                        atenciones[cant_atencion].platos_atendidos[numPlatosAtendidos].precio *
                        cantidad_plato_porcodigo;

                atenciones[cant_atencion].cantidad_platos++;
            }

            if (input.get() == '\n') break;
        }
        cant_atencion++;
    }
}

int buscarPlato(char *codigo_leido, struct Plato *platos, int cant_platos) {
    for (int i = 0; i < cant_platos; i++) {
        if (strcmp(codigo_leido, platos[i].codigo) == 0) return i;
    }
    return -1;
}




void cargarComentarios1(struct Atencion *atenciones,
    int cant_atencion, struct Palabra * lexicon,
    int cant_lexicon, const char * file_name) {
    ifstream input;
    open_read(input, file_name);
    int num_atencion_leido;
    char  *oracion_grande;
    while (true) {
        // 394386,"Los platos estuvieron muy ricos y sabrosos, el pedido fue rapido. ¡Volveria seguramente!"
        input >>num_atencion_leido;
        if ( input.eof()) break;
        input.get();
        oracion_grande = read_str(input, '\n', 120);

        int pos = BuscarAtencion(atenciones, cant_atencion, num_atencion_leido);
        if (pos != -1) {
            if (atenciones[pos].cantidad_comentarios == 0 ) atenciones[pos].comentarios = new struct Comentario[20]{};
            atenciones[pos].comentarios[atenciones[pos].cantidad_comentarios].texto = asignar(oracion_grande);
            atenciones[pos].comentarios[atenciones[pos].cantidad_comentarios].pre_procesado = preProcesarPalabra(oracion_grande);
            procesarComentario(atenciones[pos].comentarios[atenciones[pos].cantidad_comentarios], lexicon, cant_lexicon);
            atenciones[pos].cantidad_comentarios++;

        }
    }
}



void procesarComentario( struct Comentario &comentario, struct Palabra *lexicon, int cant_lexicon) {
    //atenciones[pos].comentarios[atenciones[pos].cantidad_comentarios] = comentario

    char aux[150];
    for (int i = 0, j=0; comentario.pre_procesado[i]; i++, j++) {
        if (comentario.pre_procesado[i] != ' '){
            aux[j]=comentario.pre_procesado[i];
        }
        else {
            aux[j] = '\0';
            comentario.palabras[comentario.cantidad_palabras].texto = asignar(aux);
            comentario.palabras[comentario.cantidad_palabras].polaridad = buscarPolaridad(lexicon, cant_lexicon, comentario.palabras[comentario.cantidad_palabras].texto);
            comentario.polaridad_total += comentario.palabras[comentario.cantidad_palabras].polaridad;

            comentario.cantidad_palabras ++;
            j=-1;
        }
    }
}

int buscarPolaridad(struct Palabra *lexicon, int cant_lexicon, char *texto) {
    for (int i = 0; i < cant_lexicon; i++) {
        if (strcmp(lexicon[i].texto, texto) == 0) return lexicon[i].polaridad;
    }
    return 0;
}

char * preProcesarPalabra(char *oracion_grande) {

    int k = 0;
    char aux[150],*cad;
    //"Los platos estuvieron muy ricos y sabrosos, el pedido fue rapido. ¡Volveria seguramente!"
    for (int i = 0; oracion_grande[i]; i++) {
        if (isalpha(oracion_grande[i]) or oracion_grande[i] == ' ') {
            aux[k++] = tolower(oracion_grande[i]);
        }

    }
    aux[k] = '\0';
    cad = asignar(aux);
    return cad;
}

int BuscarAtencion(struct Atencion *atencion, int cant_atencion, int num_atencion_leido) {
    for (int i = 0; i < cant_atencion; i++) {
        if (num_atencion_leido == atencion[i].codigo) return i;
    }
    return -1;
}


