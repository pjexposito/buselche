#include "pebble.h"
#include "bus.h"
#include "busdb.h"

  
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 2
#define NUM_SECOND_MENU_ITEMS 5
  
static Window *window;

static MenuLayer *menu_layer;


// Lineas
static char buffer[]="Parada: XXX";


int devuelve_valor(int key)
  {
    int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
    return valor;
}

char * texto_favoritos(int key)
  {
    int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
    //char t_linea = devuelve_linea(t_parada, v4);
    snprintf(buffer, sizeof(buffer), "Parada: %d", valor);
    return buffer;
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
          menu_cell_basic_draw(ctx, cell_layer, texto_favoritos(FAV1_PKEY), devuelve_datos_parada(devuelve_valor(FAV1_PKEY),0)/*fav1_cadena*/, NULL);
          break; 
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, texto_favoritos(FAV2_PKEY), devuelve_datos_parada(devuelve_valor(FAV2_PKEY),0)/*fav1_cadena*/, NULL);
          break;
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, texto_favoritos(FAV3_PKEY), devuelve_datos_parada(devuelve_valor(FAV3_PKEY),0)/*fav1_cadena*/, NULL);
          break;
        case 3:
          menu_cell_basic_draw(ctx, cell_layer, texto_favoritos(FAV4_PKEY), devuelve_datos_parada(devuelve_valor(FAV4_PKEY),0)/*fav1_cadena*/, NULL);
          break;  
        case 4:
          menu_cell_basic_draw(ctx, cell_layer, texto_favoritos(FAV5_PKEY), devuelve_datos_parada(devuelve_valor(FAV5_PKEY),0)/*fav1_cadena*/, NULL);
          break;
      }
  }
}
  
  
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  int numero_parada;
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
      case 0:
        numero_parada = devuelve_valor(PRINCIPAL_PKEY);
        carga_paradas(numero_parada, 0, 0);
        break;
      case 1:
        numero_parada = devuelve_valor(PRINCIPAL_PKEY);
        carga_paradas(numero_parada, 0, 1);
        break;
      }
      break;
    
    case 1:
      switch (cell_index->row) {
      case 0:
         numero_parada = devuelve_valor(FAV1_PKEY);
         carga_paradas(numero_parada, 1, 0);
         break;
      case 1:
         numero_parada = devuelve_valor(FAV2_PKEY);
         carga_paradas(numero_parada, 1, 0);
         break;
      case 2:
         numero_parada = devuelve_valor(FAV3_PKEY);
         carga_paradas(numero_parada, 1, 0);
         break;
      case 3:
         numero_parada = devuelve_valor(FAV4_PKEY);
         carga_paradas(numero_parada, 1, 0);
         break;
      case 4:
         numero_parada = devuelve_valor(FAV5_PKEY);
         carga_paradas(numero_parada, 1, 0);
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