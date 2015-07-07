// LEER: http://forums.getpebble.com/discussion/12606/tips-tricks-use-app-resource-and-save-ram-memory

#include "busdb.h"
#include "pebble.h"

int total_paradas = 312;  
  
typedef struct {
  char numero[4];
  char nombre[40];
  char lineas[11];
} Parada;
  
static Parada parada;
static int posicion;


unsigned short n_paradas[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,142,143,144,145,146,147,148,149,150,151,152,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,183,184,185,186,187,188,189,190,191,192,193,194,196,197,198,200,201,202,203,204,206,207,208,209,212,213,214,215,216,217,218,219,220,221,222,223,224,226,227,228,229,230,231,232,233,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,296,297,298,299,300,301,302,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,991,992,993,994,995};
  
static void obtenParada(int id_, Parada* parada_){
  ResHandle rh = resource_get_handle(RESOURCE_ID_RECURSO_BUS);
  resource_load_byte_range(rh, id_ * sizeof(Parada), (uint8_t*)parada_, sizeof(Parada));
}  

char * devuelve_datos_parada(int parada_solicitada, int dato)
  {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Parada %i. Total %i", parada_solicitada, total_paradas);
    static char sin_parada[]="Parada inexistente";

    // Si Dato es 1, devuelve las lineas por parada. Si es 0, devuelve el nombre  
    posicion = -1;
    for (int x=0;x<total_paradas;x++)
    {
      if (n_paradas[x]==parada_solicitada)     
        posicion = x;
    }
  
    if (posicion >-1) 
      obtenParada(posicion, &parada);
    else
      return sin_parada;
    if (dato==0) 
      return parada.nombre;
    else 
      return parada.lineas;
};


char * devuelve_linea(int parada, int linea)
  {
  static char buffer[]="12";
  if (devuelve_datos_parada(parada,1)[linea] == '1')
          snprintf(buffer, sizeof(buffer), "%s", "R");
  else  if (devuelve_datos_parada(parada,1)[linea] == '2')
          snprintf(buffer, sizeof(buffer), "%s", "R2");
  else  if (devuelve_datos_parada(parada,1)[linea] == '3')
          snprintf(buffer, sizeof(buffer), "%s", "R");
  else
          snprintf(buffer, sizeof(buffer), "%c", devuelve_datos_parada(parada, 1)[linea]);

  return buffer;
}