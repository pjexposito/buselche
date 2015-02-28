#ifndef BUSDB_H  
#define BUSDB_H
  
// Incluyendo lo de arriba y declarando las variables como extern, puedo cargar esta librería en varios .C
  
extern int total_paradas;
extern char * devuelve_nombre_parada(int parada);
extern char devuelve_linea(int parada, int linea);
extern char * devuelve_lineasxparada(int parada);


#endif