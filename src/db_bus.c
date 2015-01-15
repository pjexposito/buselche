#include "db_bus.h"


struct a_tag return_struct(int parada) {
   struct a_tag a;
   a.w = "Sin datos";
   switch(parada)
   {
		case 0:
      a.lineas = "A";
      a.w = "Calle 0";
      break;
   case 1:
      a.w = "Centro. Doctor Caro";
      break;
    case 2:
      a.w = "Vicente Blasco Ibañez, 22";
      break;
    case 3:
      a.w = "Vicente Blasco Ibañez, 80";
      break;     
    case 4:
      a.w = "INEM Carrús";
      break;
    case 5:
      a.w = "Pedro Moreno Sastre, 62";
      break;  
    case 6:
      a.w = "Pedro Moreno Sastre, 80";
      break;
   }
  return a;

}