#include "pebble.h"
#include "bus.h"
 
  
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_ITEMS 5
  
static Window *window;

static MenuLayer *menu_layer;

unsigned int valor, v1, v2, v3, v4;

// Lineas
const char *lineas_bus[]= {"A","B","C","D","E","F","G","H","I","J","K","L","R","R2"};
static char buffer1[]="12",buffer2[]="12",buffer3[]="12", texto[1024], tfav1[20], tfav2[20], tfav3[20], tfav4[20], tfav5[20];


//Callbacks

const char *texto_favoritos(int KEY)
  {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Me da %i", KEY);

    valor = persist_exists(KEY) ? persist_read_int(KEY) : NUM_DEFAULT;
     v1 = valor/10000;
     v2 = (valor % 10000) /1000;
     v3 = (valor % 1000) /100;
     v4 = (valor % 100);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Cargado: %i, que vale: %i, %i, %i, %i", valor, v1, v2, v3, v4);

    snprintf(buffer1, sizeof(buffer1), "%d", v1);
    snprintf(buffer2, sizeof(buffer2), "%d", v2);
    snprintf(buffer3, sizeof(buffer3), "%d", v3);
    strcpy(texto,buffer1);
    strcat(texto, buffer2);
    strcat(texto, buffer3);
    strcat(texto, lineas_bus[v4]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Texto vale: %s", texto);
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
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "Bus Elche");
      break;

    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "Favoritos");
      break;
  }
}

  
// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Nueva busqueda", "Pulsa para iniciar", NULL);

          break;
      }
      break;

    case 1:
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV1_PKEY));
          break; 
        case 1:
          // This is a basic menu icon with a cycling icon
          menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV2_PKEY));
          break;
        case 2:
          menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV3_PKEY));
          break;
        case 3:
          menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV4_PKEY));
          break;  
        case 4:
          menu_cell_title_draw(ctx, cell_layer, texto_favoritos(FAV5_PKEY));
          break;
        
      }
  }
}
  
  
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
      // This is the menu item with the cycling icon
      case 0:
        // Aqui va la opcion tras pulsar

        valor = persist_exists(PRINCIPAL_PKEY) ? persist_read_int(PRINCIPAL_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
        carga_paradas(v1,v2,v3,v4);
        break;
      }
    
      break;
    case 1:
      switch (cell_index->row) {
      // This is the menu item with the cycling icon
      case 0:
         valor = persist_exists(FAV1_PKEY) ? persist_read_int(FAV1_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
         carga_paradas(v1,v2,v3,v4);
         break;
      case 1:
         valor = persist_exists(FAV2_PKEY) ? persist_read_int(FAV2_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
         carga_paradas(v1,v2,v3,v4);
         break;
      case 2:
         valor = persist_exists(FAV3_PKEY) ? persist_read_int(FAV3_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
         carga_paradas(v1,v2,v3,v4);
         break;
      case 3:
         valor = persist_exists(FAV4_PKEY) ? persist_read_int(FAV4_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
         carga_paradas(v1,v2,v3,v4);
         layer_mark_dirty(menu_layer_get_layer(menu_layer));
         break;
      case 4:
         valor = persist_exists(FAV5_PKEY) ? persist_read_int(FAV5_PKEY) : NUM_DEFAULT;
         v1 = valor/10000;
         v2 = (valor % 10000) /1000;
         v3 = (valor % 1000) /100;
         v4 = (valor % 100);
         carga_paradas(v1,v2,v3,v4);
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
  // Set all the callbacks for the menu layer
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