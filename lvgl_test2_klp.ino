//        _          _          _ _
//  _ __ (_)_  _____| | ___  __| (_)
// | '_ \| \ \/ / _ \ |/ _ \/ _` | |
// | |_) | |>  <  __/ |  __/ (_| | |
// | .__/|_/_/\_\___|_|\___|\__,_|_|
// |_|
// https://links.pixeledi.eu
// LVGL mit ESP32 | 04.2025

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

static int32_t hr_value = 98;
static int8_t hr_step = 1;
static lv_obj_t * needle_line = NULL;
static lv_obj_t * hr_value_label = NULL;
static lv_obj_t * bpm_label = NULL;
static lv_obj_t * scale = NULL;
typedef struct {
    lv_style_t items;
    lv_style_t indicator;
    lv_style_t main;
} section_styles_t;
static section_styles_t zone1_styles;
static section_styles_t zone2_styles;
static section_styles_t zone3_styles;
static section_styles_t zone4_styles;
static section_styles_t zone5_styles;

LV_IMAGE_DECLARE(img_hand);
//static lv_obj_t * needle_line;
static lv_obj_t * needle_img;

void setup() {
  lv_layer_t layer;
  Serial.begin(115200);
  Serial.println("LVGL Start");
  lv_init();
  lv_display_t* disp;
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
  lv_obj_t* text_label = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label, "Hello pixeledi!");
  lv_obj_align(text_label, LV_ALIGN_CENTER, 0, 0);
  static lv_style_t style_text_label;
  lv_style_init(&style_text_label);
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_18);
  lv_obj_add_style(text_label, &style_text_label, 0);


// Now then
//draw_triangle_example();
//lv_example_scale_modes();

//lv_example_scale_heart_rate();

lv_example_scale_needles();

}
void loop() {
  lv_timer_handler();
  lv_tick_inc(1);
  delay(1);
}

void lv_example_scale_modes(void)
{
    lv_obj_t * screen = lv_screen_active();
    /* 💡 Swap `mode` between the four `horizontal_*`/`vertical_*` values to compare layouts. */
    lv_obj_t * scale_1 = lv_scale_create(screen);
    lv_obj_set_size(scale_1, 120, 30);
    lv_scale_set_mode(scale_1, LV_SCALE_MODE_HORIZONTAL_TOP);
    lv_scale_set_total_tick_count(scale_1, 11);
    lv_scale_set_major_tick_every(scale_1, 2);
    lv_scale_set_label_show(scale_1, true);
    lv_scale_set_min_value(scale_1, 0);
    lv_scale_set_max_value(scale_1, 100);
    lv_obj_set_align(scale_1, LV_ALIGN_LEFT_MID);
    lv_obj_set_y(scale_1, 20);
    lv_obj_set_x(scale_1, 20);
    lv_obj_t * scale_2 = lv_scale_create(screen);
    lv_obj_set_size(scale_2, 120, 30);
    lv_scale_set_mode(scale_2, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_total_tick_count(scale_2, 11);
    lv_scale_set_major_tick_every(scale_2, 2);
    lv_scale_set_label_show(scale_2, true);
    lv_scale_set_min_value(scale_2, 0);
    lv_scale_set_max_value(scale_2, 100);
    lv_obj_set_align(scale_2, LV_ALIGN_LEFT_MID);
    lv_obj_set_y(scale_2, -20);
    lv_obj_set_x(scale_2, 20);
    lv_obj_t * scale_3 = lv_scale_create(screen);
    lv_obj_set_size(scale_3, 120, 120);
    lv_scale_set_mode(scale_3, LV_SCALE_MODE_ROUND_OUTER);
    lv_scale_set_total_tick_count(scale_3, 11);
    lv_scale_set_major_tick_every(scale_3, 2);
    lv_scale_set_label_show(scale_3, true);
    lv_scale_set_min_value(scale_3, 0);
    lv_scale_set_max_value(scale_3, 100);
    lv_obj_set_align(scale_3, LV_ALIGN_CENTER);
    lv_obj_t * scale_4 = lv_scale_create(screen);
    lv_obj_set_size(scale_4, 90, 90);
    lv_scale_set_mode(scale_4, LV_SCALE_MODE_ROUND_INNER);
    lv_scale_set_total_tick_count(scale_4, 11);
    lv_scale_set_major_tick_every(scale_4, 2);
    lv_scale_set_label_show(scale_4, true);
    lv_scale_set_min_value(scale_4, 0);
    lv_scale_set_max_value(scale_4, 100);
    lv_obj_set_align(scale_4, LV_ALIGN_CENTER);
    lv_obj_t * scale_5 = lv_scale_create(screen);
    lv_obj_set_size(scale_5, 30, 160);
    lv_scale_set_mode(scale_5, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_total_tick_count(scale_5, 11);
    lv_scale_set_major_tick_every(scale_5, 2);
    lv_scale_set_label_show(scale_5, true);
    lv_scale_set_min_value(scale_5, 0);
    lv_scale_set_max_value(scale_5, 100);
    lv_obj_set_align(scale_5, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(scale_5, -20);
    lv_obj_t * scale_6 = lv_scale_create(screen);
    lv_obj_set_size(scale_6, 30, 160);
    lv_scale_set_mode(scale_6, LV_SCALE_MODE_VERTICAL_RIGHT);
    lv_scale_set_total_tick_count(scale_6, 11);
    lv_scale_set_major_tick_every(scale_6, 2);
    lv_scale_set_label_show(scale_6, true);
    lv_scale_set_min_value(scale_6, 0);
    lv_scale_set_max_value(scale_6, 100);
    lv_obj_set_align(scale_6, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(scale_6, -60);
}

static lv_color_t get_hr_zone_color(int32_t hr)
{
    if(hr < 117) return lv_palette_main(LV_PALETTE_GREY); /* Zone 1 */
    else if(hr < 135) return lv_palette_main(LV_PALETTE_BLUE); /* Zone 2 */
    else if(hr < 158) return lv_palette_main(LV_PALETTE_GREEN); /* Zone 3 */
    else if(hr < 176) return lv_palette_main(LV_PALETTE_ORANGE); /* Zone 4 */
    else return lv_palette_main(LV_PALETTE_RED); /* Zone 5 */
}
static void hr_anim_timer_cb(lv_timer_t * timer)
{
    LV_UNUSED(timer);
    hr_value += hr_step;
    if(hr_value >= 195) {
        hr_value = 195;
        hr_step = -1;
    }
    else if(hr_value <= 98) {
        hr_value = 98;
        hr_step = 1;
    }
    /* Update needle */
    lv_scale_set_line_needle_value(scale, needle_line, 180, hr_value);
    /* Update HR text */
    lv_label_set_text_fmt(hr_value_label, "%d", hr_value);
    /* Update text color based on zone */
    lv_color_t zone_color = get_hr_zone_color(hr_value);
    lv_obj_set_style_text_color(hr_value_label, zone_color, 0);
    lv_obj_set_style_text_color(bpm_label, zone_color, 0);
}
static void init_section_styles(section_styles_t * styles, lv_color_t color)
{
    lv_style_init(&styles->items);
    lv_style_set_line_color(&styles->items, color);
    lv_style_set_line_width(&styles->items, 0);
    lv_style_init(&styles->indicator);
    lv_style_set_line_color(&styles->indicator, color);
    lv_style_set_line_width(&styles->indicator, 0);
    lv_style_init(&styles->main);
    lv_style_set_arc_color(&styles->main, color);
    lv_style_set_arc_width(&styles->main, 20);
}
static void add_section(lv_obj_t * target_scale,
                        int32_t from,
                        int32_t to,
                        const section_styles_t * styles)
{
    lv_scale_section_t * sec = lv_scale_add_section(target_scale);
    lv_scale_set_section_range(target_scale, sec, from, to);
    lv_scale_set_section_style_items(target_scale, sec, &styles->items);
    lv_scale_set_section_style_indicator(target_scale, sec, &styles->indicator);
    lv_scale_set_section_style_main(target_scale, sec, &styles->main);
}
/**
 * @title Heart-rate zone gauge with animated needle
 * @brief Round inner scale coloured by five heart-rate zones with a bpm readout.
 *
 * A 200 by 200 scale uses `LV_SCALE_MODE_ROUND_INNER` over the range
 * 98 to 195 bpm with a 280 degree sweep rotated to 130 degrees and
 * 15 ticks (major every third). Five sections colour the arc grey,
 * blue, green, orange, and red for zones 1 through 5, and a black
 * `lv_line` needle is placed with `lv_scale_set_line_needle_value`. A
 * centred circular overlay holds a flex-column container with a
 * Montserrat 40 bpm value and a Montserrat 18 `bpm` label. An 80 ms
 * `lv_timer` sweeps the displayed heart rate between 98 and 195,
 * updating the needle, the value, and the zone-matching text colour.
 */
void lv_example_scale_heart_rate(void)
{
    scale = lv_scale_create(lv_screen_active());
    lv_obj_center(scale);
    lv_obj_set_size(scale, 200, 200);
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);
    lv_scale_set_range(scale, 98, 195);
    lv_scale_set_total_tick_count(scale, 15);
    lv_scale_set_major_tick_every(scale, 3);
    lv_scale_set_angle_range(scale, 280);
    lv_scale_set_rotation(scale, 130);
    lv_scale_set_label_show(scale, false);
    lv_obj_set_style_length(scale, 6, LV_PART_ITEMS);
    lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(scale, 0, LV_PART_MAIN);
    /* Zone 1: (Grey) */
    init_section_styles(&zone1_styles, lv_palette_main(LV_PALETTE_GREY));
    add_section(scale, 98, 117, &zone1_styles);
    /* Zone 2: (Blue) */
    init_section_styles(&zone2_styles, lv_palette_main(LV_PALETTE_BLUE));
    add_section(scale, 117, 135, &zone2_styles);
    /* Zone 3: (Green) */
    init_section_styles(&zone3_styles, lv_palette_main(LV_PALETTE_GREEN));
    add_section(scale, 135, 158, &zone3_styles);
    /* Zone 4: (Orange) */
    init_section_styles(&zone4_styles, lv_palette_main(LV_PALETTE_ORANGE));
    add_section(scale, 158, 176, &zone4_styles);
    /* Zone 5: (Red) */
    init_section_styles(&zone5_styles, lv_palette_main(LV_PALETTE_RED));
    add_section(scale, 176, 195, &zone5_styles);
    needle_line = lv_line_create(scale);
    /* Optional styling */
    lv_obj_set_style_line_color(needle_line, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_line_width(needle_line, 12, LV_PART_MAIN);
    lv_obj_set_style_length(needle_line, 20, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(needle_line, false, LV_PART_MAIN);
    lv_obj_set_style_pad_right(needle_line, 50, LV_PART_MAIN);
    int32_t current_hr = 145;
    lv_scale_set_line_needle_value(scale, needle_line, 50, current_hr);
    lv_obj_t * circle = lv_obj_create(lv_screen_active());
    lv_obj_set_size(circle, 130, 130);
    lv_obj_center(circle);
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(circle, lv_obj_get_style_bg_color(lv_screen_active(), LV_PART_MAIN), 0);
    lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(circle, 0, LV_PART_MAIN);
    lv_obj_t * hr_container = lv_obj_create(circle);
    lv_obj_center(hr_container);
    lv_obj_set_size(hr_container, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(hr_container, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(hr_container, 0, 0);
    lv_obj_set_layout(hr_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(hr_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(hr_container, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(hr_container, 0, 0);
    lv_obj_set_flex_align(hr_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    hr_value_label = lv_label_create(hr_container);
    lv_label_set_text_fmt(hr_value_label, "%d", current_hr);
    lv_obj_set_style_text_font(hr_value_label, &lv_font_montserrat_40, 0);
    lv_obj_set_style_text_align(hr_value_label, LV_TEXT_ALIGN_CENTER, 0);
    bpm_label = lv_label_create(hr_container);
    lv_label_set_text(bpm_label, "bpm");
    lv_obj_set_style_text_font(bpm_label, &lv_font_montserrat_18, 0);
    lv_obj_set_style_text_align(bpm_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_color_t zone_color = get_hr_zone_color(current_hr);
    lv_obj_set_style_text_color(hr_value_label, zone_color, 0);
    lv_obj_set_style_text_color(bpm_label, zone_color, 0);
    lv_timer_create(hr_anim_timer_cb, 80, NULL);
}



void draw_triangle_example(void)
{
    /* 1. Define the 4 points to form a closed triangle */
    /* Point 1, Point 2, Point 3, and Point 1 again to close it */
    static lv_point_precise_t triangle_points[] = {
        {100, 50},   // Top vertex
        {150, 150},  // Bottom right vertex
        {50, 150},   // Bottom left vertex
        {100, 50}    // Back to top vertex to close the triangle
    };

    /* 2. Create a line widget directly on the standard active screen */
    lv_obj_t * triangle = lv_line_create(lv_screen_active());

    /* 3. Pass the point array to the line widget */
    lv_line_set_points(triangle, triangle_points, 4);

    /* 4. Style the triangle (color and thickness) */
    lv_obj_set_style_line_width(triangle, 5, LV_PART_MAIN);
    lv_obj_set_style_line_color(triangle, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    lv_obj_set_style_line_rounded(triangle, true, LV_PART_MAIN); // Smooth corners

    /* 5. Optional: Center the bounding box of the line widget on the screen */
    lv_obj_center(triangle);
}

static void set_needle_line_value(void * obj, int32_t v)
{
    lv_scale_set_line_needle_value((lv_obj_t *)obj, needle_line, 60, v);
}
static void set_needle_img_value(void * obj, int32_t v)
{
    lv_scale_set_image_needle_value((lv_obj_t *)obj, needle_img, v);
}
/**
 * @title Round scales with animated needles
 * @brief Two round inner scales driven by looping line and image needles.
 *
 * Two 150 by 150 scales use `LV_SCALE_MODE_ROUND_INNER` with a 270
 * degree range rotated to 135 degrees, 31 ticks, and the range 10 to
 * 40. The left scale attaches an `lv_line` needle driven by
 * `lv_scale_set_line_needle_value`; the right one attaches an
 * `lv_image` needle (`img_hand`) driven by
 * `lv_scale_set_image_needle_value`. Both needles animate between 10
 * and 40 on an infinite 1000 ms forward and 1000 ms reverse loop.
 */
void lv_example_scale_needles(void)
{
    lv_obj_t * scale_line = lv_scale_create(lv_screen_active());
    lv_obj_set_size(scale_line, 150, 150);
    lv_scale_set_mode(scale_line, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale_line, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(scale_line, lv_palette_lighten(LV_PALETTE_RED, 5), 0);
    lv_obj_set_style_radius(scale_line, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale_line, true, 0);
    lv_obj_align(scale_line, LV_ALIGN_LEFT_MID, LV_PCT(2), 0);
    lv_scale_set_label_show(scale_line, true);
    lv_scale_set_total_tick_count(scale_line, 31);
    lv_scale_set_major_tick_every(scale_line, 5);
    lv_obj_set_style_length(scale_line, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale_line, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale_line, 10, 40);
    lv_scale_set_angle_range(scale_line, 270);
    lv_scale_set_rotation(scale_line, 135);
    needle_line = lv_line_create(scale_line);
    lv_obj_set_style_line_width(needle_line, 6, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(needle_line, true, LV_PART_MAIN);
    lv_anim_t anim_scale_line;
    lv_anim_init(&anim_scale_line);
    lv_anim_set_var(&anim_scale_line, scale_line);
    lv_anim_set_exec_cb(&anim_scale_line, set_needle_line_value);
    lv_anim_set_duration(&anim_scale_line, 1000);
    lv_anim_set_repeat_count(&anim_scale_line, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_reverse_duration(&anim_scale_line, 1000);
    lv_anim_set_values(&anim_scale_line, 10, 40);
    lv_anim_start(&anim_scale_line);
    lv_obj_t * scale_img = lv_scale_create(lv_screen_active());
    lv_obj_set_size(scale_img, 150, 150);
    lv_scale_set_mode(scale_img, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale_img, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(scale_img, lv_palette_lighten(LV_PALETTE_RED, 5), 0);
    lv_obj_set_style_radius(scale_img, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale_img, true, 0);
    lv_obj_align(scale_img, LV_ALIGN_RIGHT_MID, LV_PCT(-2), 0);
    lv_scale_set_label_show(scale_img, true);
    lv_scale_set_total_tick_count(scale_img, 31);
    lv_scale_set_major_tick_every(scale_img, 5);
    lv_obj_set_style_length(scale_img, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale_img, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale_img, 10, 40);
    lv_scale_set_angle_range(scale_img, 270);
    lv_scale_set_rotation(scale_img, 135);
    /* image must point to the right. E.g. -O------>*/
    needle_img = lv_image_create(scale_img);
    lv_image_set_src(needle_img, &img_hand);
    lv_obj_align(needle_img, LV_ALIGN_CENTER, 47, -2);
    lv_image_set_pivot(needle_img, 3, 4);
    lv_anim_t anim_scale_img;
    lv_anim_init(&anim_scale_img);
    lv_anim_set_var(&anim_scale_img, scale_img);
    lv_anim_set_exec_cb(&anim_scale_img, set_needle_img_value);
    lv_anim_set_duration(&anim_scale_img, 1000);
    lv_anim_set_repeat_count(&anim_scale_img, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_reverse_duration(&anim_scale_img, 1000);
    lv_anim_set_values(&anim_scale_img, 10, 40);
    lv_anim_start(&anim_scale_img);
}
