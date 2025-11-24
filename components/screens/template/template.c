#include "lvgl.h"

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target_obj(e);
    if (code == LV_EVENT_CLICKED)
    {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);

        /* Get display from the button's screen */
        lv_display_t *disp = lv_obj_get_display(btn);
        if (cnt % 2 == 0)
            lv_display_set_rotation(disp, LV_DISP_ROTATION_0);
        else
            lv_display_set_rotation(disp, LV_DISP_ROTATION_270);
    }
}

void template_screen_create(void)
{
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t *screen = lv_screen_active();
    lv_obj_t *label_screen = lv_label_create(screen);
    lv_label_set_text(label_screen, "Hello world");
    lv_obj_set_style_text_color(screen, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label_screen, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *btn = lv_button_create(lv_screen_active());       /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                                /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                              /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

    lv_obj_t *label_btn = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label_btn, "Button");     /*Set the labels text*/
    lv_obj_center(label_btn);
}