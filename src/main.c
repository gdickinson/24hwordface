#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xDF, 0x08, 0xC5, 0x6F, 0x8A, 0xD2, 0x4E, 0xFF, 0x98, 0xB3, 0x3F, 0x80, 0xE3, 0xAC, 0x07, 0x4A }
PBL_APP_INFO(MY_UUID,
             "Hello World", "Your Company",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
static GFont font;
TextLayer hour_layer;
TextLayer minute_layer;
TextLayer static_hours_layer;

static const char* numbers[] = {
  "Zero",
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine",
  "Ten",
  "Eleven",
  "Twelve",
  "Thirteen",
  "Fourteen",
  "Fifteen",
  "Sixteen",
  "Seventeen",
  "Eighteen",
  "Nineteen",
  "Twenty",
  "Twenty-one",
  "Twenty-two",
  "Twenty-three"
};

static const char* hours_text = "Hours";

void handle_init(AppContextRef ctx) {
  (void) ctx;

  window_init(&window, "Window!");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  font = fonts_get_system_font(FONT_KEY_GOTHAM_34_LIGHT_SUBSET);

  text_layer_init(&hour_layer, GRect(0, 0, 144, 50));
  text_layer_set_font(&hour_layer, font);
  text_layer_set_background_color(&hour_layer, GColorBlack);
  text_layer_set_text_color(&hour_layer, GColorWhite);
  layer_add_child(&window.layer, &hour_layer.layer);

  text_layer_init(&minute_layer, GRect(0, 52, 144, 50));
  text_layer_set_font(&minute_layer, font);
  text_layer_set_background_color(&minute_layer, GColorBlack);
  text_layer_set_text_color(&minute_layer, GColorWhite);
  layer_add_child(&window.layer, &minute_layer.layer);

  text_layer_init(&static_hours_layer, GRect(0, 104, 144, 50));
  text_layer_set_font(&static_hours_layer, font);
  text_layer_set_background_color(&static_hours_layer, GColorBlack);
  text_layer_set_text_color(&static_hours_layer, GColorWhite);
  layer_add_child(&window.layer, &static_hours_layer.layer);
  text_layer_set_text(&static_hours_layer, hours_text);
}



static void handle_deinit(AppContextRef ctx) {
  (void) ctx;

  //fonts_unload_custom_font(font_thin);
  //fonts_unload_custom_font(font_thick);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent* const event) {
  (void) ctx;
  const PblTm* const ptm = event->tick_time;
  text_layer_set_text(&hour_layer, numbers[ptm->tm_hour]);
  text_layer_set_text(&minute_layer, numbers[ptm->tm_min]);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
