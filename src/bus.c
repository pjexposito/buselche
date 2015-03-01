// POR HACER
// Meter las funciones de BD en un único archivo. 
// Quitarle roña al código


#include <pebble.h>
#include "bus.h"
#include "busdb.h"
  
  
  
Window* window;
// Barra de opciones
ActionBarLayer *action_bar;

// Capas del programa
static Layer *marcador;
TextLayer *textolinea_layer, *textoparada_layer, *nombreparada_layer,*dig1_layer, *dig2_layer, *dig3_layer, *linea_layer, *mensaje_layer;


// Variables de imágenes
GBitmap *arriba_bitmap, *abajo_bitmap, *pulsar_bitmap, *play_bitmap, *buscar_bitmap;


// Lineas
char lineas[]= {"ABCDEFGHIJKLR2"};


// Resto de variables
char texto[1024], tiempo1[1024], tiempo2[1024];
static int numero1, numero2, numero3, letra, posicion=0, cargando=0, tamano_array_lineas, pre_parada=0;

// Asignación para recibir datos
enum {
	KEY_T1 = 0,
	KEY_T2 = 1
};

int numero_parada()
  {
  // Aquí se debe comprabar si la parada existe
  int valor=(numero1*100)+(numero2*10)+numero3;
  return valor;
}

void pinta_datos(void)
{

  static char buffer1[]="12",buffer2[]="12",buffer3[]="12";

  snprintf(buffer1, sizeof(buffer1), "%d", numero1);
	text_layer_set_text(dig1_layer, buffer1);
  snprintf(buffer2, sizeof(buffer2), "%d", numero2);
	text_layer_set_text(dig2_layer, buffer2);
  snprintf(buffer3, sizeof(buffer3), "%d", numero3);
	text_layer_set_text(dig3_layer, buffer3);
  
  
  if (numero_parada() < total_paradas) 
    text_layer_set_text(linea_layer, devuelve_linea(numero_parada(), letra)); 

  
}

void process_tuple(Tuple *t)
{

  int key = t->key;
	switch(key) 
    {
		case KEY_T1:
      strcat(tiempo1, t->value->cstring);
        //APP_LOG(APP_LOG_LEVEL_DEBUG, "Datos: %s %lu", t->value->cstring, t->key);

      break;
		case KEY_T2:
      strcat(tiempo2, t->value->cstring);
			break;
    }


}

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Acabo de recibir datos (pebble).");

	memset(&tiempo1[0], 0, sizeof(tiempo1));
  memset(&tiempo2[0], 0, sizeof(tiempo2));


  (void) context;	
	Tuple *t = dict_read_first(iter);
	if(t)	process_tuple(t);
	while(t != NULL)
	{
		t = dict_read_next(iter);
		if(t)	process_tuple(t);
	}
  
  
    // CODIGOS DE ERROR
    // 97 = Error 404. La web no existe. Posiblemente por que la parada seleccionada no existe.
    // 98 = Existe la línea y la parada pero no hay datos (posiblemente no circulen autobueses a esas horas).
    // 99 = No pasa esa linea por la parada seleccionada.
    if (strcmp(tiempo1,"99")==0)
      text_layer_set_text(mensaje_layer, "Servicio no disponible.");
    else if (strcmp(tiempo1,"98")==0)
      text_layer_set_text(mensaje_layer, "Parada sin autobuses disponibles.");
    else if (strcmp(tiempo1,"97")==0)
      text_layer_set_text(mensaje_layer, "La parada seleccionada no existe.");
    else
      {
        strcpy(texto,"Tiempo estimado: ");
        strcat(texto, tiempo1);
        strcat(texto, " y ");
        strcat(texto, tiempo2);
        strcat(texto, " minutos.");
        text_layer_set_text(mensaje_layer, texto);
      }  
    posicion=0;
    layer_mark_dirty(marcador);
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);
    cargando = 0;
    vibes_short_pulse();

}

void send_int(int16_t parada, const char *linea)
{
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
  dict_write_int16(iter, KEY_T1, parada);
  dict_write_cstring(iter, KEY_T2, linea);
  dict_write_end(iter);
 	app_message_outbox_send();
}

void envia_peticion()
  {
      text_layer_set_text(mensaje_layer, "Cargando...");
      cargando = 1;
      //Borro la variable de tiempo 1 y 2 antes de volver a pedir datos.
      memset(&tiempo1[0], 0, sizeof(tiempo1));
      memset(&tiempo2[0], 0, sizeof(tiempo2));

      send_int(numero_parada(),devuelve_linea(numero_parada(), letra));
}

void pinta_nombredeparada()
  {
   //APP_LOG(APP_LOG_LEVEL_DEBUG, "Parada: %d y total es %d.", numero_parada(), total_paradas);

  if (numero_parada() < total_paradas) 
    text_layer_set_text(mensaje_layer, devuelve_nombre_parada(numero_parada()));
  else
    text_layer_set_text(mensaje_layer, "Parada inexistente");

}

void carga_lineas()
  {
  memset(&lineas[0], 0, sizeof(lineas));
  snprintf(lineas, sizeof(lineas), "%s",devuelve_lineasxparada(numero_parada()));
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Se carga: %s, de la posicion %i", array_lineasxparada[t_parada], t_parada);
  for (int t=0;lineas[t] != '0';t++)
    tamano_array_lineas = t;
  pinta_datos();

  }
  

void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
   if (cargando==1) return;
   switch(posicion) 
    {
		case 0:
      numero1==9 ? numero1=0 : numero1++;
      break;
		case 1:
      numero2==9 ? numero2=0 : numero2++;
      break;
		case 2:
      numero3==9 ? numero3=0 : numero3++;
      break;
	  case 3:      
      letra++;
      if (letra==tamano_array_lineas+1) letra=0;
      break;     
    }
  pinta_nombredeparada();
  pinta_datos();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  if (cargando==1) return;

  switch(posicion) 
    {
		case 0:
      numero1==0 ? numero1=9 : numero1--;
      break;
		case 1:
      numero2==0 ? numero2=9 : numero2--;
      break;
		case 2:
      numero3==0 ? numero3=9 : numero3--;
      break;
	  case 3:
      if (lineas[letra] == '0') letra=0;

      letra==0 ? letra=tamano_array_lineas : letra--;
      break;     
    }
  pinta_nombredeparada();
  pinta_datos();
}

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  if (cargando==1)
    return;
  
  switch(posicion) 
    {
		case 0:
      posicion=1;
      break;
		case 1:
      posicion=2;
			break;
		case 2:
      if ((numero_parada()+2 > total_paradas) || (numero_parada() == 0))
      {
        posicion =0;
      }
    else
      {
      carga_lineas();
      if (lineas[0] == '-')
        {
        posicion =0;
        }
      else
        {
          //APP_LOG(APP_LOG_LEVEL_DEBUG, "Numero: %d, Preparada: %d", (numero1*100)+(numero2*10)+numero3, pre_parada);

         if (numero_parada()!=pre_parada) letra = 0;
         pre_parada = numero_parada();
         posicion=3;
         action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, buscar_bitmap);
        }
      }
      break;    
		case 3:
      envia_peticion();
      break;     
    }

  layer_mark_dirty(marcador);
}


void select_long_click_handler(ClickRecognizerRef recognizer, void *context)
{
  persist_write_int(FAV5_PKEY, persist_read_int(FAV4_PKEY));
  persist_write_int(FAV4_PKEY, persist_read_int(FAV3_PKEY));
  persist_write_int(FAV3_PKEY, persist_read_int(FAV2_PKEY));
  persist_write_int(FAV2_PKEY, persist_read_int(FAV1_PKEY));
  persist_write_int(FAV1_PKEY, (numero1*10000) + (numero2*1000) + (numero3*100) + letra);

  text_layer_set_text(mensaje_layer, "Parada agregada a favoritos.");

}

void marcador_update_callback(Layer *me, GContext* ctx) 
{

  // Color del fondo y color del trazo
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);

	switch(posicion) 
    {
		case 0:
      graphics_fill_rect(ctx, GRect(62, 37, 15, 2), 0, GCornerNone);  
      break;
		case 1:
      graphics_fill_rect(ctx, GRect(77, 37, 15, 2), 0, GCornerNone);    
			break;
		case 2:
      graphics_fill_rect(ctx, GRect(92, 37, 15, 2), 0, GCornerNone);  
			break;    
		case 3:
      graphics_fill_rect(ctx, GRect(48, 67, 20, 2), 0, GCornerNone);  
			break;     
    }
} 


void click_config_provider(void *context) 
{
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 2000, select_long_click_handler, NULL);
}


static TextLayer* init_text_layer(GRect location, GColor colour, GColor background, const char *res_id, GTextAlignment alignment)
{
	TextLayer *layer = text_layer_create(location);
	text_layer_set_text_color(layer, colour);
	text_layer_set_background_color(layer, background);
	text_layer_set_font(layer, fonts_get_system_font(res_id));
  text_layer_set_overflow_mode(layer, GTextOverflowModeWordWrap);
	text_layer_set_text_alignment(layer, alignment);
	return layer;
}


void window_load(Window *window)
{
  //Capa para mostrar el marcador bajo los números
  marcador = layer_create(layer_get_bounds(window_get_root_layer(window)));
  layer_set_update_proc(marcador, marcador_update_callback); 
  layer_add_child(window_get_root_layer(window), marcador); 
  //Barra de opciones de la derecha
  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  //Asignación de recursos gráficos
  arriba_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICONO_ARRIBA);
  abajo_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_ABAJO);
  pulsar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICON_PULSAR);
  play_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PLAY);
  buscar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_BUSCAR);
  //Asignación de iconos a la barra de opciones
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, arriba_bitmap );
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, abajo_bitmap);
  if (posicion==3)
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, buscar_bitmap);
  else
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);

  //Capas principales del programa
  
  nombreparada_layer = init_text_layer(GRect(5, 30, 120, 25), GColorBlack, GColorClear, FONT_KEY_GOTHIC_18, GTextAlignmentLeft);
  //text_layer_set_text(nombreparada_layer, "Calle chula 3");
	layer_add_child(window_get_root_layer(window), (Layer*) nombreparada_layer);
  
  textoparada_layer = init_text_layer(GRect(5, 10, 120, 25), GColorBlack, GColorClear, FONT_KEY_GOTHIC_24, GTextAlignmentLeft);
  text_layer_set_text(textoparada_layer, "Parada:");
	layer_add_child(window_get_root_layer(window), (Layer*) textoparada_layer);
  
  textolinea_layer = init_text_layer(GRect(5, 40, 120, 25), GColorBlack, GColorClear, FONT_KEY_GOTHIC_24, GTextAlignmentLeft);
  text_layer_set_text(textolinea_layer, "Linea:");
	layer_add_child(window_get_root_layer(window), (Layer*) textolinea_layer);

  mensaje_layer = init_text_layer(GRect(5, 70, 120, 80), GColorBlack, GColorClear, FONT_KEY_GOTHIC_24_BOLD, GTextAlignmentLeft);
	text_layer_set_text(mensaje_layer, "Introduce parada y linea");
  layer_add_child(window_get_root_layer(window), (Layer*) mensaje_layer);
 
  dig1_layer = init_text_layer(GRect(60, 7, 20, 30), GColorBlack, GColorClear, FONT_KEY_GOTHIC_28_BOLD, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig1_layer);
  
  dig2_layer = init_text_layer(GRect(75, 7, 20, 30), GColorBlack, GColorClear, FONT_KEY_GOTHIC_28_BOLD, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig2_layer);
  
  dig3_layer = init_text_layer(GRect(90, 7, 20, 30), GColorBlack, GColorClear, FONT_KEY_GOTHIC_28_BOLD, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig3_layer);
  
  linea_layer = init_text_layer(GRect(43, 37, 30, 30), GColorBlack, GColorClear, FONT_KEY_GOTHIC_28_BOLD, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) linea_layer);
  
  carga_lineas(); 
  pinta_nombredeparada();
  if (posicion==3)
    {
    envia_peticion();
  }
  
}

void window_unload(Window *window)
{
  int t_parada = (numero1*10000) + (numero2*1000) + (numero3*100);
  if ((t_parada/100)>(total_paradas-1))
    t_parada=100;
  persist_write_int(PRINCIPAL_PKEY, t_parada + letra);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Se guarda: %d + %d", (numero1*10000) + (numero2*1000) + (numero3*100), letra);

  posicion = 0;
  gbitmap_destroy(arriba_bitmap);
  gbitmap_destroy(abajo_bitmap);
  gbitmap_destroy(pulsar_bitmap);
  gbitmap_destroy(play_bitmap);
  gbitmap_destroy(buscar_bitmap);
  
  action_bar_layer_destroy(action_bar);

  text_layer_destroy(nombreparada_layer);
  text_layer_destroy(textolinea_layer);
  text_layer_destroy(textoparada_layer);
  text_layer_destroy(dig1_layer);
  text_layer_destroy(dig2_layer);
	text_layer_destroy(dig3_layer);
  text_layer_destroy(linea_layer);
  text_layer_destroy(mensaje_layer);
  layer_destroy(marcador);
   window_destroy(window);

}

/* Initialize the main app elements */
void carga_paradas(int n1, int n2, int n3, int l, int fav)
{
  numero1 = n1;
  numero2 = n2;
  numero3 = n3;
  letra = l;
	window = window_create();
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload
	};
  
	app_message_register_inbox_received(in_received_handler);					 
	window_set_window_handlers(window, (WindowHandlers) handlers);
  if (fav==1)
    posicion=3;
	window_stack_push(window, true);


}



