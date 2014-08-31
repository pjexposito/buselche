// Gran parte del código de menu sacado de https://github.com/PabloLlosa/FormulaOne2014Pebble

#include "pebble.h"
#include "bus.h"
 
  
#define NUM_PRINCIPAL_MENU_ITEMS 1
#define NUM_MENU_SECTIONS 2
#define NUM_FAVORITOS_MENU_ITEMS 5
  
static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem PRINCIPAL_menu_items[NUM_PRINCIPAL_MENU_ITEMS];
static SimpleMenuItem FAVORITOS_menu_items[NUM_FAVORITOS_MENU_ITEMS];


// Lineas
const char *lineas_bus[]= {"A","B","C","D","E","F","G","H","I","J","K","L","R","R2"};
static char buffer1[]="12",buffer2[]="12",buffer3[]="12", texto[1024], tfav1[20], tfav2[20], tfav3[20], tfav4[20], tfav5[20];


//Callbacks


static void NUEVO_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(PRINCIPAL_PKEY) ? persist_read_int(PRINCIPAL_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Cargado: %i, que vale: %i, %i, %i, %i", valor, v1, v2, v3, v4);

  carga_paradas(v1,v2,v3,v4);
}

static void FAV1_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(FAV1_PKEY) ? persist_read_int(FAV1_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Cargado: %d, que vale: %i, %i, %i, %i", valor, v1, v2, v3, v4);

  carga_paradas(v1,v2,v3,v4);
}

static void FAV2_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(FAV2_PKEY) ? persist_read_int(FAV2_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
  carga_paradas(v1,v2,v3,v4);
}

static void FAV3_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(FAV3_PKEY) ? persist_read_int(FAV3_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
  carga_paradas(v1,v2,v3,v4);
}

static void FAV4_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(FAV4_PKEY) ? persist_read_int(FAV4_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
  carga_paradas(v1,v2,v3,v4);
}

static void FAV5_select_callback(int index, void *ctx) {
  unsigned int valor = persist_exists(FAV5_PKEY) ? persist_read_int(FAV5_PKEY) : NUM_DEFAULT;
  int v1 = valor/10000;
  int v2 = (valor % 10000) /1000;
  int v3 = (valor % 1000) /100;
  int v4 = (valor % 100);
  carga_paradas(v1,v2,v3,v4);
}

static void texto_favoritos(int KEY)
  {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Me da %i", KEY);

    unsigned int valor = persist_exists(KEY) ? persist_read_int(KEY) : NUM_DEFAULT;
    int v1 = valor/10000;
    int v2 = (valor % 10000) /1000;
    int v3 = (valor % 1000) /100;
    int v4 = (valor % 100);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Cargado: %i, que vale: %i, %i, %i, %i", valor, v1, v2, v3, v4);

    snprintf(buffer1, sizeof(buffer1), "%d", v1);
    snprintf(buffer2, sizeof(buffer2), "%d", v2);
    snprintf(buffer3, sizeof(buffer3), "%d", v3);
    strcpy(texto,buffer1);
    strcat(texto, buffer2);
    strcat(texto, buffer3);
    strcat(texto, lineas_bus[v4]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Texto vale: %s", texto);

  }

static void window_load(Window *window) {

  int num_a_items = 0;
  int num_a2_items = 0;
 
  /////////
  /////////
  /////////
  // OJO, es una prueba sólo
  persist_write_int(FAV1_PKEY, 12303);
  persist_write_int(FAV2_PKEY, 99900);
  persist_write_int(FAV3_PKEY, 76309);
  persist_write_int(FAV4_PKEY, 33301);
  persist_write_int(FAV5_PKEY, 11100);

  


//=====================================================================================================
  
  PRINCIPAL_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Nueva busqueda",
	  .subtitle = "Pulsa para iniciar",
    .callback = NUEVO_select_callback,
  };

  
//=====================================================================================================
  


  texto_favoritos(FAV1_PKEY);  
  strcpy(tfav1,texto);
  FAVORITOS_menu_items[num_a2_items++] = (SimpleMenuItem){
    .title = "Parada 1",
	  .subtitle = tfav1,
    .callback = FAV1_select_callback,
  };
  texto_favoritos(FAV2_PKEY);  
  strcpy(tfav2,texto);

  FAVORITOS_menu_items[num_a2_items++] = (SimpleMenuItem){
    .title = "Parada 2",
	  .subtitle = tfav2,
    .callback = FAV2_select_callback,

  };
  texto_favoritos(FAV3_PKEY); 
  strcpy(tfav3,texto);

  FAVORITOS_menu_items[num_a2_items++] = (SimpleMenuItem){
    .title = "Parada 3",
	  .subtitle = tfav3,
    .callback = FAV3_select_callback,

  };
  texto_favoritos(FAV4_PKEY); 
  strcpy(tfav4,texto);

  FAVORITOS_menu_items[num_a2_items++] = (SimpleMenuItem){
    .title = "Parada 4",
	  .subtitle = tfav4,
    .callback = FAV4_select_callback,

  };
  texto_favoritos(FAV5_PKEY); 
  strcpy(tfav5,texto);


  FAVORITOS_menu_items[num_a2_items++] = (SimpleMenuItem){
    .title = "Parada 5",
	  .subtitle = tfav5,
    .callback = FAV5_select_callback,

  };
  
//=====================================================================================================
  
  menu_sections[0] = (SimpleMenuSection){
  .title ="Bus Elche",
  .num_items = NUM_PRINCIPAL_MENU_ITEMS,
  .items = PRINCIPAL_menu_items,
  };
  menu_sections[1] = (SimpleMenuSection){
  .title ="Favoritos",
  .num_items = NUM_FAVORITOS_MENU_ITEMS,
  .items = FAVORITOS_menu_items,
  };
	
//=====================================================================================================
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections,NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}

static void window_unload(Window *window) {
  simple_menu_layer_destroy(simple_menu_layer);
}

int main(void) {
  window = window_create();
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());		

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  
  
  window_stack_push(window, true);

  app_event_loop();

  window_destroy(window);
}