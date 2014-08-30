#include <pebble.h>

#define NUM_1_DEFAULT 0
#define NUM_2_DEFAULT 0
#define NUM_3_DEFAULT 0
#define NUM_LETRA_DEFAULT 0

#define NUM_1_PKEY 1
#define NUM_2_PKEY 2
#define NUM_3_PKEY 3
#define NUM_LETRA_PKEY 4

  
  
Window* window;
static Layer *marcador;
ActionBarLayer *action_bar;


TextLayer *textolinea_layer, *textoparada_layer, *dig1_layer, *dig2_layer, *dig3_layer, *text_layer2, *t1_layer;
static int numero1, numero2, numero3, letra;
int posicion=0, numero_parada;
char texto[1024];
char tiempo1[1024];
char tiempo2[1024];

static char buf[] = "12";
static char buf1[] = "12";
static char buf2[] = "12";
static char buf3[] = "12";

GBitmap *arriba_bitmap, *abajo_bitmap, *pulsar_bitmap, *play_bitmap, *buscar_bitmap;



const char *lineas[]= {"A","B","C","D","E","F","G","H","I","J","K","L","R","R2"};
int tamano = sizeof(lineas)/sizeof(lineas[0]);
int cargando = 0;

char t1_buffer[64], t2_buffer[64];

enum {
	KEY_T1 = 0,
	KEY_T2 = 1
};



void process_tuple(Tuple *t)
{
  
  int key = t->key;
	switch(key) {
		case KEY_T1:
      strcat(tiempo1, t->value->cstring);
      break;
		case KEY_T2:
      strcat(tiempo2, t->value->cstring);

			break;
  }
  
      // CODIGOS DE ERROR
      // 97 = Error 404. La web no existe. Posiblemente por que la parada seleccionada no existe.
      // 98 = Existe la línea y la parada pero no hay datos (posiblemente no circulen autobueses a esas horas).
      // 99 = No pasa esa linea por la parada seleccionada.
      if (strcmp(tiempo1,"99")==0)
                text_layer_set_text(t1_layer, "Sin linea en la parada seleccionada.");
      else if (strcmp(tiempo1,"98")==0)
                text_layer_set_text(t1_layer, "Parada sin autobuses disponibles.");
      else if (strcmp(tiempo1,"97")==0)
                text_layer_set_text(t1_layer, "La parada seleccionada no existe.");
  

      else
        {
          strcpy(texto,"Tiempo estimado: ");
          strcat(texto, tiempo1);
          strcat(texto, " y ");
          strcat(texto, tiempo2);
          strcat(texto, " minutos.");


        text_layer_set_text(t1_layer, texto);
        }  
  
    posicion=0;
    layer_mark_dirty(marcador);
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);
    cargando = 0;

}

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
	(void) context;
	
	//Get data
	Tuple *t = dict_read_first(iter);
	if(t)
	{
		process_tuple(t);
	}
	
	//Get next
	while(t != NULL)
	{
		t = dict_read_next(iter);
		if(t)
		{
			process_tuple(t);
		}
	}
}

void send_int(int16_t parada, const char *linea)
{
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
 	/*
 	Tuplet value = TupletInteger(KEY_T1, parada);
  Tuplet value2 = TupletInteger(KEY_T2, linea);
 	dict_write_tuplet(iter, &value);
 	dict_write_tuplet(iter, &value2); 	
  */
  dict_write_int16(iter, KEY_T1, parada);
  dict_write_cstring(iter, KEY_T2, linea);
  dict_write_end(iter);

  
 	app_message_outbox_send();
  
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  if (cargando==1)
    return;
  
  
/*  
  
  //Esto que va a continuación se debe usar para añadir el valor de un int a una cadena de texto
  //Texto ahora es Pulsado: 
  strcpy(texto,"Pulsado: ");
  numero++;
  // Se convierte la variable número de decimal a char. Se guarda en buf
  snprintf(buf, sizeof(buf), "%d", numero);
  // Ahora, se añade el valor de buf (el número) a la cadena texto
  strcat(texto, buf);
  // Ahora que texto tiene todo el valor, se muestra.
  text_layer_set_text(text_layer, texto);
  
*/
  if (posicion==0){
    if (numero1==9)
      numero1=0;
    else
      numero1++;
    
    snprintf(buf1, sizeof(buf1), "%d", numero1);
	  text_layer_set_text(dig1_layer, buf1);
  }
  
  
  if (posicion==1){
    if (numero2==9)
      numero2=0;
    else
      numero2++;
    
    snprintf(buf2, sizeof(buf2), "%d", numero2);
	  text_layer_set_text(dig2_layer, buf2);
  }
  
  
  if (posicion==2){
    if (numero3==9)
      numero3=0;
    else
      numero3++;
    
    snprintf(buf3, sizeof(buf3), "%d", numero3);
	  text_layer_set_text(dig3_layer, buf3);
  }
  
  
  if (posicion==3)
  {
   letra++;
   if (letra==tamano)
    letra=0;
   text_layer_set_text(text_layer2, lineas[letra]); 
  }  
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  
  if (cargando==1)
    return;
  
  buf[0] = 0;

  if (posicion==0){
    if (numero1==0) 
      numero1=9;
    else
      numero1--;
    snprintf(buf1, sizeof(buf1), "%d", numero1);
	  text_layer_set_text(dig1_layer, buf1);
  }

  
  if (posicion==1){
    if (numero2==0) 
      numero2=9;
    else
      numero2--;
    snprintf(buf2, sizeof(buf2), "%d", numero2);
	  text_layer_set_text(dig2_layer, buf2);
  }
  
  if (posicion==2){
    if (numero3==0) 
      numero3=9;
    else
      numero3--;
    snprintf(buf3, sizeof(buf3), "%d", numero3);
	  text_layer_set_text(dig3_layer, buf3);
  }
  
  
  if (posicion==3)
  {
   if (letra==0)
     letra=tamano;
   letra--;

   text_layer_set_text(text_layer2, lineas[letra]); 
  }  
}

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  if (cargando==1)
    return;
  
  
  if (posicion==3)
    {
    text_layer_set_text(t1_layer, "Cargando...");
    cargando = 1;

    
    numero_parada=(numero1*100)+(numero2*10)+numero3;
      //Borro la variable de tiempo 1 y 2 antes de volver a pedir datos.
      memset(&tiempo1[0], 0, sizeof(tiempo1));
      memset(&tiempo2[0], 0, sizeof(tiempo2));

    send_int(numero_parada,lineas[letra]);
    }
  
  if (posicion==2) 
    {
    posicion=3;
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, buscar_bitmap);
    }
  if (posicion==1) 
    posicion=2;
  if (posicion==0) 
    posicion=1;

  layer_mark_dirty(marcador);
}



void marcador_update_callback(Layer *me, GContext* ctx) 
{

  // Color del fondo y color del trazo
    graphics_context_set_stroke_color(ctx, GColorBlack);
    graphics_context_set_fill_color(ctx, GColorBlack);


     if (posicion==0) 
        graphics_fill_rect(ctx, GRect(62, 37, 15, 2), 0, GCornerNone);  
     if (posicion==1) 
        graphics_fill_rect(ctx, GRect(77, 37, 15, 2), 0, GCornerNone);    
     if (posicion==2) 
        graphics_fill_rect(ctx, GRect(92, 37, 15, 2), 0, GCornerNone);  
     if (posicion==3) 
        graphics_fill_rect(ctx, GRect(45, 67, 20, 2), 0, GCornerNone);  
  
} 


void pinta_datos(void)
{
  snprintf(buf1, sizeof(buf1), "%d", numero1);
	text_layer_set_text(dig1_layer, buf1);
  
  snprintf(buf2, sizeof(buf2), "%d", numero2);
	text_layer_set_text(dig2_layer, buf2);
  
  snprintf(buf3, sizeof(buf3), "%d", numero3);
	text_layer_set_text(dig3_layer, buf3);
  
  text_layer_set_text(text_layer2, lineas[letra]); 

}
  
  
void click_config_provider(void *context) 
{
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

/* Load all Window sub-elements */
void window_load(Window *window)
{
  marcador = layer_create(layer_get_bounds(window_get_root_layer(window)));
    layer_set_update_proc(marcador, marcador_update_callback); 
  layer_add_child(window_get_root_layer(window), marcador); 
  
    // Initialize the action bar:
  action_bar = action_bar_layer_create();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, window);
    action_bar_layer_set_click_config_provider(action_bar,
                                             click_config_provider);
  

  arriba_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICONO_ARRIBA);
  abajo_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_ABAJO);
  pulsar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICON_PULSAR);
  play_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PLAY);
  buscar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_BUSCAR);


  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, arriba_bitmap );
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, abajo_bitmap);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);


  
  textoparada_layer = text_layer_create(GRect(5, 10, 120, 25));
	text_layer_set_background_color(textoparada_layer, GColorClear);
  text_layer_set_text_color(textoparada_layer, GColorBlack);
  text_layer_set_font(textoparada_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(textoparada_layer, GTextAlignmentLeft);
  text_layer_set_text(textoparada_layer, "Parada:");
	layer_add_child(window_get_root_layer(window), (Layer*) textoparada_layer);

  
  textolinea_layer = text_layer_create(GRect(5, 40, 120, 25));
	text_layer_set_background_color(textolinea_layer, GColorClear);
  text_layer_set_text_color(textolinea_layer, GColorBlack);
  text_layer_set_font(textolinea_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(textolinea_layer, GTextAlignmentLeft);
  text_layer_set_text(textolinea_layer, "Linea:");
	layer_add_child(window_get_root_layer(window), (Layer*) textolinea_layer);

  
  t1_layer = text_layer_create(GRect(5, 70, 120, 80));
	text_layer_set_background_color(t1_layer, GColorClear);
  text_layer_set_font(t1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(t1_layer, GTextAlignmentLeft);
	text_layer_set_text_color(t1_layer, GColorBlack);
  text_layer_set_overflow_mode(t1_layer, GTextOverflowModeWordWrap);
	layer_add_child(window_get_root_layer(window), (Layer*) t1_layer);
	text_layer_set_text(t1_layer, "Introduce parada y linea");
  

  
  
	dig1_layer = text_layer_create(GRect(60, 7, 20, 30));
  text_layer_set_font(dig1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(dig1_layer, GColorClear);
	text_layer_set_text_color(dig1_layer, GColorBlack);
	text_layer_set_text_alignment(dig1_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig1_layer);
	text_layer_set_text(dig1_layer, "0");
  

	dig2_layer = text_layer_create(GRect(75, 7, 20, 30));
  text_layer_set_font(dig2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(dig2_layer, GColorClear);
	text_layer_set_text_color(dig2_layer, GColorBlack);
	text_layer_set_text_alignment(dig2_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig2_layer);
	text_layer_set_text(dig2_layer, "0");  
  
  
  dig3_layer = text_layer_create(GRect(90, 7, 20, 30));
  text_layer_set_font(dig3_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(dig3_layer, GColorClear);
	text_layer_set_text_color(dig3_layer, GColorBlack);
	text_layer_set_text_alignment(dig3_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig3_layer);
	text_layer_set_text(dig3_layer, "0");
  
  text_layer2 = text_layer_create(GRect(40, 37, 30, 30));
  text_layer_set_font(text_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(text_layer2, GColorClear);
	text_layer_set_text_color(text_layer2, GColorBlack);
	text_layer_set_text_alignment(text_layer2, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) text_layer2);
	text_layer_set_text(text_layer2, "A");
  
  
  pinta_datos();  
  
}

/* Un-load all Window sub-elements */
void window_unload(Window *window)
{
  gbitmap_destroy(arriba_bitmap);
  gbitmap_destroy(abajo_bitmap);
  gbitmap_destroy(pulsar_bitmap);
  gbitmap_destroy(play_bitmap);
  gbitmap_destroy(buscar_bitmap);
  
  action_bar_layer_destroy(action_bar);

  
  text_layer_destroy(textolinea_layer);
  text_layer_destroy(textoparada_layer);
  text_layer_destroy(dig1_layer);
  text_layer_destroy(dig2_layer);
	text_layer_destroy(dig3_layer);
  text_layer_destroy(text_layer2);
  text_layer_destroy(t1_layer);
  layer_destroy(marcador);
}

/* Initialize the main app elements */
void init()
{
	window = window_create();
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload
	};
  
	app_message_register_inbox_received(in_received_handler);					 
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());		//Largest possible input and output buffer sizes
	
	window_set_window_handlers(window, (WindowHandlers) handlers);
  
  // Lee valores guardados
  numero1 = persist_exists(NUM_1_PKEY) ? persist_read_int(NUM_1_PKEY) : NUM_1_DEFAULT;
  numero2 = persist_exists(NUM_2_PKEY) ? persist_read_int(NUM_2_PKEY) : NUM_2_DEFAULT;
  numero3 = persist_exists(NUM_3_PKEY) ? persist_read_int(NUM_3_PKEY) : NUM_3_DEFAULT;
  letra = persist_exists(NUM_LETRA_PKEY) ? persist_read_int(NUM_LETRA_PKEY) : NUM_LETRA_DEFAULT;
  
	window_stack_push(window, true);
}

/* De-initialize the main app elements */
void deinit()
{
  persist_write_int(NUM_1_PKEY, numero1);
  persist_write_int(NUM_2_PKEY, numero2);
  persist_write_int(NUM_3_PKEY, numero3);
  persist_write_int(NUM_LETRA_PKEY, letra);

	window_destroy(window);
}

/* Main app lifecycle */
int main(void)
{
	init();
	app_event_loop();
	deinit();
}