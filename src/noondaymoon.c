#include "pebble.h"


Window		*window;
TextLayer	*time_layer;
TextLayer	*date_layer;
TextLayer	*wday_layer;
Layer		*line_layer;
Layer		*window_layer;

BitmapLayer *watchicon_layer;
BitmapLayer *batt_layer;
BitmapLayer *bt_layer;

//////////////////////////// line colour ///////////////////////////////////
void draw_line(Layer *layer, GContext* ctx) {
	graphics_context_set_fill_color(ctx, GColorPictonBlue);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);} 

//////////////////////////// time and date format ////////////////////////////
static void handle_time_tick(struct tm* tick_time, TimeUnits units_changed) {

	static char time_text[] = "00:00";
	static char date_text[] = "00/00/00";
	
	char *time_format;
		if	 (clock_is_24h_style()) {time_format = "%R";}
		else {time_format = "%I:%M";}

	strftime(time_text, sizeof(time_text), time_format, tick_time);
	
	if  (!clock_is_24h_style() && (time_text[0] =='0'))
		{memmove(time_text, &time_text[1], sizeof(time_text) - 1);}
	
	text_layer_set_text(time_layer, time_text);

	strftime(date_text, sizeof(date_text), "%d/%m/%y", tick_time); 
	text_layer_set_text(date_layer, date_text);
	
	/*dayname
	int wday_flag = tick_time -> tm_wday;
	//tm_wday: 0(sun) to 6(sat)
	if		 (wday_flag == 0) {text_layer_set_text(wday_layer, " sun");}
	else if  (wday_flag == 1) {text_layer_set_text(wday_layer, " mon");}
	else if  (wday_flag == 2) {text_layer_set_text(wday_layer, " tue");}
	else if  (wday_flag == 3) {text_layer_set_text(wday_layer, " wed");}
	else if  (wday_flag == 4) {text_layer_set_text(wday_layer, " thu");}
	else if  (wday_flag == 5) {text_layer_set_text(wday_layer, " fri");}
	else if  (wday_flag == 6) {text_layer_set_text(wday_layer, " sat");}
	*/
}

// bluetooth settings  /////////
static void handle_bluetooth(bool connected) {
	if		(connected) {bitmap_layer_set_bitmap(bt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_1));}
	else	{bitmap_layer_set_bitmap(bt_layer,gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_0));
			//vibes_long_pulse();
			}
}

//battery
void handle_battery(BatteryChargeState charge) {
	
	// Charging
	if (charge.is_charging){
		
		bitmap_layer_destroy(batt_layer);
		bitmap_layer_destroy(bt_layer);
		bt_layer = bitmap_layer_create(GRect(105, 10, 11, 10));
		batt_layer = bitmap_layer_create(GRect(123, 10, 14, 10));
		
		//pebble time用に追記（"#ifdef PBL_COLOR" - "#endif" で分岐する）
		#ifdef PBL_COLOR
		if (charge.charge_percent >90){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_09));}
			else if (charge.charge_percent > 80){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_08));}
			else if (charge.charge_percent > 70){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_07));}
			else if (charge.charge_percent > 60){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_06));}
			else if (charge.charge_percent > 50){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_05));}
			else if (charge.charge_percent > 40){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_04));}
			else if (charge.charge_percent > 30){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_03));}
			else if (charge.charge_percent > 20){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_12));}
			else if (charge.charge_percent > 10){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_11));}
			else if (charge.charge_percent > 0){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_10));}
			else {
	        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_10));}
		
		#endif //pebble classic
		if (charge.charge_percent >90){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_09));}
			else if (charge.charge_percent > 80){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_08));}
			else if (charge.charge_percent > 70){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_07));}
			else if (charge.charge_percent > 60){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_06));}
			else if (charge.charge_percent > 50){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_05));}
			else if (charge.charge_percent > 40){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_04));}
			else if (charge.charge_percent > 30){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_03));}
			else if (charge.charge_percent > 20){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_12));}
			else if (charge.charge_percent > 10){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_11));}
			else if (charge.charge_percent > 0){
		        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_10));}
			else {
	        bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_10));}
		
		layer_add_child(window_layer, bitmap_layer_get_layer(bt_layer));
		layer_add_child(window_layer, bitmap_layer_get_layer(batt_layer));
		
		handle_bluetooth(bluetooth_connection_service_peek());
		bluetooth_connection_service_subscribe(&handle_bluetooth);

		bitmap_layer_set_bitmap(watchicon_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_thunder));
		}

	// Plugged in
	else if (charge.is_plugged){
		
		bitmap_layer_destroy(batt_layer);
		bitmap_layer_destroy(bt_layer);
		
		bt_layer = bitmap_layer_create(GRect(105, 10, 11, 10));
		batt_layer = bitmap_layer_create(GRect(123, 10, 14, 10));
		
		bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_09));
		bitmap_layer_set_bitmap(watchicon_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FULL));
		bitmap_layer_set_compositing_mode(watchicon_layer, GCompOpAssign);
		
		layer_add_child(window_layer, bitmap_layer_get_layer(bt_layer));
		layer_add_child(window_layer, bitmap_layer_get_layer(batt_layer));
		
		handle_bluetooth(bluetooth_connection_service_peek());
		bluetooth_connection_service_subscribe(&handle_bluetooth);
	}

	/////////// Icons not Charging
	else if (! charge.is_charging){
		bitmap_layer_set_bitmap(watchicon_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLANK));
		
		bitmap_layer_destroy(batt_layer);
		bitmap_layer_destroy(bt_layer);
		
		bt_layer = bitmap_layer_create(GRect(105, 10, 11, 10));
		batt_layer = bitmap_layer_create(GRect(123, 10, 14, 10));
		
		#ifdef PBL_COLOR
		if (charge.charge_percent > 90){
    	    bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_29));}
		else if (charge.charge_percent > 80){
			bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_28));}
		else if (charge.charge_percent > 70){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_27));}
		else if (charge.charge_percent > 60){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_26));}
		else if (charge.charge_percent > 50){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_25));}
		else if (charge.charge_percent > 40){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_24));}
		else if (charge.charge_percent > 30){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_23));}
		else if (charge.charge_percent > 20){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_02));}
		else if (charge.charge_percent > 10){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_01));}
		else if (charge.charge_percent > 0){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_00));}
    	else{
	        // 無いとは思うけどコレ以外の状況が発生した場合に対応するため以下を記載（電池アイコンの表示なし）
			layer_set_hidden(bitmap_layer_get_layer(batt_layer), true);
		}
		
		#endif
		if (charge.charge_percent > 90){
    	    bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_29));}
		else if (charge.charge_percent > 80){
			bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_28));}
		else if (charge.charge_percent > 70){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_27));}
		else if (charge.charge_percent > 60){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_26));}
		else if (charge.charge_percent > 50){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_25));}
		else if (charge.charge_percent > 40){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_24));}
		else if (charge.charge_percent > 30){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_23));}
		else if (charge.charge_percent > 20){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_02));}
		else if (charge.charge_percent > 10){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_01));}
		else if (charge.charge_percent > 0){
        	bitmap_layer_set_bitmap(batt_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_00));}
    	else{
	        // 無いとは思うけどコレ以外の状況が発生した場合に対応するため以下を記載（電池アイコンの表示なし）
			layer_set_hidden(bitmap_layer_get_layer(batt_layer), true);
		}
		
		handle_bluetooth(bluetooth_connection_service_peek());
		bluetooth_connection_service_subscribe(&handle_bluetooth);
		
		layer_add_child(window_layer, bitmap_layer_get_layer(bt_layer));
		layer_add_child(window_layer, bitmap_layer_get_layer(batt_layer));
		
	}
}

//////////////////////////////////////////////// Visuals //////////////////////////////////////////////////////////////////////
static void do_init(void) {
	window = window_create();
	window_stack_push(window, true);
	window_set_background_color(window, GColorBlack);
	window_layer = window_get_root_layer(window);
		
  
  //Time
	time_layer = text_layer_create(GRect(17, 40, 118, 70));
	text_layer_set_text_color(time_layer, GColorVividCerulean);
	text_layer_set_background_color(time_layer, GColorClear);
	text_layer_set_font(time_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Font_Prototype_42)));
	text_layer_set_text_alignment(time_layer,GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(time_layer));
	
  // divider
  GRect line_frame = GRect(25, 100, 100, 2);
	line_layer = layer_create(line_frame);
  layer_set_update_proc(line_layer, draw_line);
	layer_add_child(window_layer, line_layer);
  
  //long date
	date_layer = text_layer_create(GRect(15, 115, 118, 70));
	text_layer_set_text_color(date_layer, GColorCeleste);
	text_layer_set_background_color(date_layer, GColorClear);
  text_layer_set_text_alignment(date_layer,GTextAlignmentCenter);
	text_layer_set_font(date_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Font_Prototype_18)));
	layer_add_child(window_layer, text_layer_get_layer(date_layer));
	
  /*week day font
	wday_layer = text_layer_create(GRect(60, 143, 50, 25));
	text_layer_set_text_color(wday_layer, GColorWhite); // 
	text_layer_set_background_color(wday_layer, GColorClear);
	text_layer_set_font(wday_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_font_droid_18)));
	layer_add_child(window_layer, text_layer_get_layer(wday_layer));
	*/
	
	
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	handle_time_tick(current_time, SECOND_UNIT);
	
	tick_timer_service_subscribe(SECOND_UNIT, &handle_time_tick);

	batt_layer = bitmap_layer_create(GRect(123, 10, 100, 100));
	layer_add_child(window_layer, bitmap_layer_get_layer(batt_layer)); 
	
  /*
	watchicon_layer = bitmap_layer_create(GRect(131, 151, 6, 10));
	layer_add_child(window_layer, bitmap_layer_get_layer(watchicon_layer));
	bitmap_layer_set_background_color(watchicon_layer, GColorClear);
	*/
  
	bt_layer = bitmap_layer_create(GRect(100, 10, 50, 10));
	layer_add_child(window_layer, bitmap_layer_get_layer(bt_layer));
	
	handle_battery(battery_state_service_peek());
	battery_state_service_subscribe(&handle_battery);

	handle_bluetooth(bluetooth_connection_service_peek());
	bluetooth_connection_service_subscribe(&handle_bluetooth);
}

static void do_deinit(void) {

	layer_destroy(line_layer);
	bitmap_layer_destroy(watchicon_layer);
	
	bluetooth_connection_service_unsubscribe();
	bitmap_layer_destroy(bt_layer);

	battery_state_service_unsubscribe();
	bitmap_layer_destroy(batt_layer);

	tick_timer_service_unsubscribe();
	text_layer_destroy(wday_layer);
	text_layer_destroy(date_layer);
	text_layer_destroy(time_layer);

	window_destroy(window);
}

int main(void) {
	do_init();
	app_event_loop();
	do_deinit();
}