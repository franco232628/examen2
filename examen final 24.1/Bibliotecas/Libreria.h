//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_FINAL_24_1_LIBRERIA_H
#define EXAMEN_FINAL_24_1_LIBRERIA_H
struct Libreria {
  int codigo;
  struct Venta *ventas;
  int cantVentas;
  double totalVentas;
};
#endif //EXAMEN_FINAL_24_1_LIBRERIA_H