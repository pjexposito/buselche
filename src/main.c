#include "pebble.h"
#include "bus.h"
#include "busdb.h"

  
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_ITEMS 5
  
static Window *window;

static MenuLayer *menu_layer;


// Lineas
const char *lineas_bus[]= {"A","B","C","D","E","F","G","H","I","J","K","L","R","R2"};
static char buffer1[]="12",buffer2[]="12",buffer3[]="12", texto[1024];


struct datos_entrada { 
    unsigned int v1; 
    unsigned int v2; 
    unsigned int v3; 
    unsigned int v4; 
    };

struct texto_paradas { 
    char parada[20]; 
    char linea[20]; 
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
    int unsigned v4 = (valor % 100);
  
    snprintf(buffer1, sizeof(buffer1), "%d", v1);
    snprintf(buffer2, sizeof(buffer2), "%d", v2);
    snprintf(buffer3, sizeof(buffer3), "%d", v3);
    strcpy(item.parada, "Parada: ");
    strcat(item.parada,buffer1);
    strcat(item.parada, buffer2);
    strcat(item.parada, buffer3);
    strcat(item.parada, " ");
    strcat(item.parada, lineas_bus[v4]);
    //strcpy(item.linea, "Linea: ");

    return item;
}

struct datos_entrada carga_datos(int key)
{
  struct datos_entrada b;        
  int unsigned valor = persist_exists(key) ? persist_read_int(key) : NUM_DEFAULT;
  b.v1 = valor/10000;
  b.v2 = (valor % 10000) /1000;
  b.v3 = (valor % 1000) /100;
  b.v4 = (valor % 100);
  return b;
}

const char *texto_favoritos(int KEY)
  {
    struct datos_entrada valores;
    valores = carga_datos(KEY);
    snprintf(buffer1, sizeof(buffer1), "%d", valores.v1);
    snprintf(buffer2, sizeof(buffer2), "%d", valores.v2);
    snprintf(buffer3, sizeof(buffer3), "%d", valores.v3);
    strcpy(texto,buffer1);
    strcat(texto, buffer2);
    strcat(texto, buffer3);
    strcat(texto, lineas_bus[valores.v4]);
    return texto;
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
      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          //menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV1_PKEY));
          datos = texto_favoritos_separado(FAV1_PKEY);
          //menu_cell_basic_draw(ctx, cell_layer, datos.parada, datos.linea, NULL);
          menu_cell_basic_draw(ctx, cell_layer, datos.parada, array_nombre_parada[devuelve_valor(FAV1_PKEY)], NULL);
          break; 
        case 1:
          datos = texto_favoritos_separado(FAV2_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.parada, array_nombre_parada[devuelve_valor(FAV2_PKEY)], NULL);
          break;
        case 2:
          datos = texto_favoritos_separado(FAV3_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.parada, array_nombre_parada[devuelve_valor(FAV3_PKEY)], NULL);
          break;
        case 3:
          datos = texto_favoritos_separado(FAV4_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.parada, array_nombre_parada[devuelve_valor(FAV4_PKEY)], NULL);
          break;  
        case 4:
          datos = texto_favoritos_separado(FAV5_PKEY);
          menu_cell_basic_draw(ctx, cell_layer, datos.parada, array_nombre_parada[devuelve_valor(FAV5_PKEY)], NULL);
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
        carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 0);
        break;
      }
      break;
    
    case 1:
      switch (cell_index->row) {
      case 0:
         valores = carga_datos(FAV1_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 1);
         break;
      case 1:
         valores = carga_datos(FAV2_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 1);
         break;
      case 2:
         valores = carga_datos(FAV3_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 1);
         break;
      case 3:
         valores = carga_datos(FAV4_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 1);
         break;
      case 4:
         valores = carga_datos(FAV5_PKEY);
         carga_paradas(valores.v1,valores.v2,valores.v3,valores.v4, 1);
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
  //texto_favoritos(FAV1_PKEY);  
  //strcpy(tfav1,texto);
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
  window_stack_push(window, true);
  app_event_loop();
  window_destroy(window);
}