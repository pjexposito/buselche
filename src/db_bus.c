#include "db_bus.h"


struct a_tag return_struct(int parada) {
   struct a_tag a;
     a.c = 'Y';
   a.i = 88;
   a.w = "Sin datos";
   switch(parada)
   {
		case 0:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 0";
      break;
   case 1:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 1";
      break;
    case 2:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 2";
      break;
    case 10:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 10";
      break;     
    case 12:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 12";
      break;
    case 100:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 100";
      break;  
    case 103:
      a.c = 'Y';
      a.i = 88;
      a.w = "Calle 103";
      break;
   }
  return a;

}