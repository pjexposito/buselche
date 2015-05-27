#include "pebble.h"
#include "bus.h"
#include "busdb.h"

  
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 2
#define NUM_SECOND_MENU_ITEMS 5
  
static Window *window;

static MenuLayer *menu_layer;


// Lineas
char lineas_bus[]= {"ABCDEFGHIJKLR2"};
static char buffer1[]="12",buffer2[]="12",buffer3[]="12";


struct datos_entrada { 
    unsigned int v1; 
    unsigned int v2; 
    unsigned int v3; 
    };

struct texto_paradas { 
    char texto[20]; 
    int parada; 
    };


int devuelve_valor(int key)
  {
    int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
    int unsigned v1 = valor/10000;
    int unsigned v2 = (valor % 10000) /1000;
    int unsigned v3 = (valor % 1000) /100;
    return (v1*100)+(v2*10)+v3;
}

struct texto_paradas texto_favoritos_separado(int key)
  {
    struct texto_paradas item;

    int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
    int unsigned v1 = valor/10000;
    int unsigned v2 = (valor % 10000) /1000;
    int unsigned v3 = (valor % 1000) /100;
    int t_parada = (v1*100)+(v2*10)+v3;
    //char t_linea = devuelve_linea(t_parada, v4);
    snprintf(buffer1, sizeof(buffer1), "%d", v1);
    snprintf(buffer2, sizeof(buffer2), "%d", v2);
    snprintf(buffer3, sizeof(buffer3), "%d", v3);

  
  
    strcpy(item.texto, "Parada: ");
    strcat(item.texto,buffer1);
    strcat(item.texto, buffer2);
    strcat(item.texto, buffer3);

    item.parada = t_parada;

    return item;
}

struct datos_entrada carga_datos(int key)
{
  struct datos_entrada b;        
  int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
  b.v1 = valor/10000;
  b.v2 = (valor % 10000) /1000;
  b.v3 = (valor % 1000) /100;
  return b;
}


static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}
  
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1:
      return NUM_SECOND_MENU_ITEMS;
    default:
      return 0;
  }
}
  
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer, "Bus Elche");
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "Favoritos");
      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  struct texto_paradas datos;

  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Nueva busqueda", "Pulsa para iniciar", NULL);
          break;
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "Buscar parada", "Pulsa para iniciar", NULL);
          break;
      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          datos = texto_favoritos_separado(FAV1_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.texto, devuelve_datos_parada(datos.parada,0)/*fav1_cadena*/, NULL);
          break; 
        case 1:
          datos = texto_favoritos_separado(FAV2_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.texto, devuelve_datos_parada(datos.parada,0)/*fav1_cadena*/, NULL);
          break;
        case 2:
          datos = texto_favoritos_separado(FAV3_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.texto, devuelve_datos_parada(datos.parada,0)/*fav1_cadena*/, NULL);
          break;
        case 3:
          datos = texto_favoritos_separado(FAV4_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.texto, devuelve_datos_parada(datos.parada,0)/*fav1_cadena*/, NULL);
          break;  
        case 4:
          datos = texto_favoritos_separado(FAV5_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.texto, devuelve_datos_parada(datos.parada,0)/*fav1_cadena*/, NULL);
          break;
      }
  }
}
  
  
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  struct datos_entrada valores;
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
      case 0:
        valores = carga_datos(PRINCIPAL_PKEY);
        carga_paradas(valores.v1,valores.v2,valores.v3, 0, 0);
        break;
      case 1:
        valores = carga_datos(PRINCIPAL_PKEY);
        carga_paradas(valores.v1,valores.v2,valores.v3, 0, 1);
        break;
      }
      break;
    
    case 1:
      switch (cell_index->row) {
      case 0:
         valores = carga_datos(FAV1_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3, 1, 0);
         break;
      case 1:
         valores = carga_datos(FAV2_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3, 1, 0);
         break;
      case 2:
         valores = carga_datos(FAV3_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3, 1, 0);
         break;
      case 3:
         valores = carga_datos(FAV4_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3, 1, 0);
         break;
      case 4:
         valores = carga_datos(FAV5_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3, 1, 0);
         layer_mark_dirty(menu_layer_get_layer(menu_layer));
         break;
      }
      break;    
  }
}
  
  



static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  menu_layer_set_click_config_onto_window(menu_layer, window);
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
  
}

static void window_unload(Window *window) {
  menu_layer_destroy(menu_layer);

}

int main(void) {
  window = window_create();
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());		
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  #ifdef PBL_SDK_2
    window_set_fullscreen(window, true);
  #endif
  window_stack_push(window, true);
  app_event_loop();
  window_destroy(window);
}