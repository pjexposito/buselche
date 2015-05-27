#ifndef BUSDB_H  
#define BUSDB_H
  
// Incluyendo lo de arriba y declarando las variables como extern, puedo cargar esta librería en varios .C
  
extern int total_paradas;
extern char * devuelve_datos_parada(int parada, int dato);
extern char * devuelve_linea(int parada, int linea);



#endif