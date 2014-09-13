#include "pebble.h"
#include "workout.h"



#define NUM_FIRST_MENU_ITEMS 0
#define NUM_SECOND_MENU_ITEMS 3
#define NUM_MENU_SECTIONS 2
static AppSync sync;
static uint8_t sync_buffer[1024];
ActionBarLayer *action_bar;
static time_t t = 0;
static uint16_t start_ms = 0;
static uint16_t stop_ms = 0;
static struct tm *tm_info;
static int diff = 0;
static int diff_ms = 0;
static time_t start;
static time_t stop;
static Window *window;
static int walk = 0;
static AppTimer *timerz;
static AppTimer *timers;
static AppTimer *timer;
static GBitmap *image;
static Layer *layers;
static GBitmap *imager;
static int ped = 0;
struct NutriInfo info;
static char text_buffer[2048];


static GBitmap *imagers;
static GBitmap *imagerz;


static GBitmap *imagez;

static GBitmap *images;
Layer *window_layers;
Layer *window_layerz;
Layer *window_layer;
static DictionaryIterator *iter;
static TextLayer *text_layer;
// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;

// Menu items can optionally have an icon drawn with them


static int current_icon = 0;
enum WeatherKey {
  WEATHER_ICON_KEY = 0x1  // TUPLE_CSTRING
};



static void update_layer_callback(Layer *layer, GContext* ctx) {
  graphics_context_set_text_color(ctx, GColorBlack);
  

  

    
    
        



  GRect bounds = layer_get_frame(layer);


  
  layers = layer_create(bounds);
  

  graphics_draw_text(ctx,
      text_buffer,
      fonts_get_system_font(FONT_KEY_FONT_FALLBACK),
      GRect(0, 100, bounds.size.w-0, 100),
      GTextOverflowModeWordWrap,
      GTextAlignmentCenter,
      NULL);
 
 

}



// You can draw arbitrary things in a menu item such as a background
static GBitmap *menu_background;

// A callback is used to specify the amount of sections of menu items
// With this, you can dynamically add and remove sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

// Each section has a number of items;  we use a callback to specify this
// You can also dynamically add and remove items using this
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
 switch(section_index){
   case 0:
    return NUM_FIRST_MENU_ITEMS;
   
   case 1:
    return NUM_SECOND_MENU_ITEMS;
     
     default:
   return 0;
 }
     

    
  
  
}

const VibePattern custom_pattern = {
  .durations = (uint32_t []) {200},
  .num_segments = 1
};







static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}

static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
  switch (key) {
    case WEATHER_ICON_KEY:
    
     snprintf(text_buffer, 1024, "%s", new_tuple->value->cstring);
       APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %s", new_tuple->value->cstring);
    
  
 
           layer_set_update_proc(layers, update_layer_callback);
 layer_add_child(window_layerz, layers);
        

   
    //  text_layer_set_text(text_layer, new_tuple->value->cstring);
      break;
  }
}



// A callback is used to specify the height of the section header
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (section_index){
    case 0:
  info.cal = 0;
  info.car = 0;
  info.pro = 0;
  info.sug = 0;
    snprintf(text_buffer, 2048, "C:%d P:%d F:%d S:%d", info.cal, info.pro, info.car, info.sug);
    menu_cell_basic_header_draw(ctx, cell_layer, text_buffer);
  }

      

   
}

// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in

      switch (cell_index->row) {
        case 0:

          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Nutrition", NULL, NULL);
          break;

        case 1:
          // This is a basic menu icon with a cycling icon

          menu_cell_basic_draw(ctx, cell_layer, "Gym Session", NULL, images);
          break;

        case 2:

                  menu_cell_basic_draw(ctx, cell_layer, "StopWatch", NULL, image);
          break;
		
      
      }
     
  }





void sendMes(Tuplet tup){
app_message_outbox_begin(&iter);


  dict_write_tuplet(iter, &tup);
  dict_write_end(iter);

  app_message_outbox_send();

}

static void timer_callback(void *data) {



  
}

tatic void my_previous_click_handler(ClickRecognizerRef recognizer, void *context) {
 
}



static void music_back_handler(ClickRecognizerRef recognizer, void *context){
  
}

static void music_forward_handler(ClickRecognizerRef recognizer, void *context){
  int symbolz = 3;
     register Tuplet symbol_tuplez = TupletInteger(SPY_KEY_START, symbolz);

  sendMes(symbol_tuplez);
  
  
}


static void my_next_click_handler(ClickRecognizerRef recognizer, void *context) {
 
}

void click_config_provider(void *context) {
  window_long_click_subscribe(BUTTON_ID_UP, 1000, (ClickHandler) music_back_handler, NULL);
    window_long_click_subscribe(BUTTON_ID_DOWN, 1000, (ClickHandler) music_forward_handler, NULL);

  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) my_next_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) my_previous_click_handler);
}


void window_sets(Window *window, MenuLayerCallbacks men) {
Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

    

  // Create the menu layer
  menu_layer = menu_layer_create(bounds);

 
  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, men);

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(click_config_provider, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));

}





void changeWindow(Window *window, MenuLayerCallbacks man){
window = window_create();


window_sets(window, man);





  window_stack_push(window, true /* Animated */);

}

static bool audi = false;
static bool flash = false;
int symbol = 1;
int symbols = 2;
int symbolz = 3;
int sign = 4;
int signs = 5;
int signz = 6;
int sigs = 7;
// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
   Tuplet initial_values[] = {
    TupletInteger(WEATHER_ICON_KEY, (uint8_t) 1)};
  
    app_sync_init(&sync, sync_buffer, sizeof(sync_buffer),   initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);


     register Tuplet symbol_tuple = TupletInteger(SPY_KEY_START, symbol);
     register Tuplet symbol_tuples = TupletInteger(SPY_KEY_START, symbols);
     register Tuplet symbol_tuplez = TupletInteger(SPY_KEY_START, symbolz);
     register Tuplet symbol_tups = TupletInteger(SPY_KEY_START, sign);
     register Tuplet symbol_tupz = TupletInteger(SPY_KEY_START, signs);
     register Tuplet symbol_tupez = TupletInteger(SPY_KEY_START, signz);
	  register Tuplet symbol_tup = TupletInteger(SPY_KEY_START, sigs);
  
 window_layerz = window_get_root_layer(window);
  
    GRect boundsz = layer_get_frame(window_layerz);
    layers = layer_create(boundsz);
         

  

  
  switch (cell_index->row) {

case 0:


//sendMes(symbol_tupez);
 window_layers = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layers);
 text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w-0, 200 } });
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    action_bar = action_bar_layer_create();
                  image = gbitmap_create_with_resource(RESOURCE_ID_stop);
                      images = gbitmap_create_with_resource(RESOURCE_ID_x);


  // Associate the action bar with the window:

 //   time(&start);
////time_ms(NULL, &start_ms);
//diff = difftime(stop, start);
//diff_ms = difftime(stop_ms, start_ms);
//snprintf(text_buffer, sizeof(text_buffer), "%d:%d", diff, diff_ms);

 text_layer_set_text(text_layer, "test");
     layer_add_child(window_layers, text_layer_get_layer(text_layer));
    action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, image);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, images);
    
    action_bar_layer_add_to_window(action_bar, window);
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar,
                                             click_config_provider);
break;
    
case 1:


sendMes(symbol_tuplez);
window_layers = window_get_root_layer(window);
  GRect bound = layer_get_bounds(window_layers);
 text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bound.size.w-0, 200 } });
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
text_layer_set_text(text_layer, "Loading Camera");
  layer_add_child(window_layers, text_layer_get_layer(text_layer));
break;
    
    case 2:


sendMes(symbol_tups);
    if(audi == false){
      audi = true;
    window_layers = window_get_root_layer(window);
  GRect bounde = layer_get_bounds(window_layers);
 text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounde.size.w-0, 200 } });
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
text_layer_set_text(text_layer, "Recording Started...");
  layer_add_child(window_layers, text_layer_get_layer(text_layer));
      
    }else
      if(audi == true){
      layer_destroy(text_layer_get_layer(text_layer));

      audi = false;
      window_layers = window_get_root_layer(window);
  GRect bounde = layer_get_bounds(window_layers);
 text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounde.size.w-0, 200 } });
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
text_layer_set_text(text_layer, "Recording stopped");
  layer_add_child(window_layers, text_layer_get_layer(text_layer));
    
    
    }

      break;


  }

}
  






// This initializes the menu upon window load
void window_load(Window *window) {
  // Here we load the bitmap assets
  // resource_init_current_app must be called before all asset loading
  const int num_menu_icons = 0;
                image = gbitmap_create_with_resource(RESOURCE_ID_stopwatch);
                        images = gbitmap_create_with_resource(RESOURCE_ID_workout);
                                imager = gbitmap_create_with_resource(RESOURCE_ID_stretch);
                                imagez = gbitmap_create_with_resource(RESOURCE_ID_ped);
                                  imagerz = gbitmap_create_with_resource(RESOURCE_ID_phones);
                                    imagers = gbitmap_create_with_resource(RESOURCE_ID_count);






  
  // And also load the background


  // Now we prepare to initialize the menu layer
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
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

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

void window_unload(Window *window) {
  // Destroy the menu layer
  app_sync_deinit(&sync); 
  menu_layer_destroy(menu_layer);
app_timer_cancel(timerz);
  
  // Cleanup the menu icons
  
}

int main(void) {
 

  window = window_create();

    app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
 
  // Init buffers
  // Register message handlers
//  app_message_register_inbox_received(in_received_handler);
 //  app_message_register_inbox_dropped(in_dropped_handler);
 //  app_message_register_outbox_sent(out_sent_handler);
  // app_message_register_outbox_failed(out_failed_handler);

     app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());


  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);


  app_event_loop();

  window_destroy(window);
  accel_data_service_unsubscribe();
}
