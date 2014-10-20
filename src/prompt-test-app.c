#include <pebble.h>
#include "strap/strap.h"

static Window *window;
static TextLayer *text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (persist_read_bool(STRAP_OPT_OUT)) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "strap is off");
  } else {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "strap is on");
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  prompt_opt_out(true);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  prompt_opt_out(false);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 20 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, "Up- display prompt again, default of yes.\n\nSelect- display an app log with strap status.\n\nDown- display prompt again, default of no.");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {

  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  int in_size = app_message_inbox_size_maximum();
  int out_size = app_message_outbox_size_maximum();
  app_message_open(in_size, out_size);

  // initialize strap
  strap_init();

  prompt_opt_out(true); // do not call it from window_load of your main window.
}

static void deinit(void) {
  // unload strap
  strap_deinit();

  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
