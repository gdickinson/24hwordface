#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xDF, 0x08, 0xC5, 0x6F, 0x8A, 0xD2, 0x4E, 0xFF, 0x98, 0xB3, 0x3F, 0x80, 0xE3, 0xAC, 0x07, 0x4A }
PBL_APP_INFO(MY_UUID,
             "Template App", "Your Company",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
static GFont = font;

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

void handle_init(AppContextRef ctx) {
  (void) ctx;

  window_init(&window, "Window!");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);
  resource_init_current_app(&RESOURCES);

  fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_28));
}

static void handle_deinit(AppContextRef ctx) {
  (void) ctx;

  //fonts_unload_custom_font(font_thin);
  //fonts_unload_custom_font(font_thick);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent* const event) {
  (void) ctx;
  const PblTm* const ptm = event->tick_time;
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
