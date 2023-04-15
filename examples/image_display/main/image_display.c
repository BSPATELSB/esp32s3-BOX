/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <dirent.h>

#include "bsp/esp-bsp.h"
#include "esp_log.h"
#include "mqtt.h"
#define IMAGE_DISPLAY_QUEUE_SIZE 5
static const char *TAG = "main";

QueueHandle_t image_display_queue = NULL;
EventGroupHandle_t event_group = NULL;
void mqtt_app_start(void);
void wifi_main(void);

typedef struct display_data
{
    char data[512];
    int datasize;
}display_data_t;

void display_qrcode(char *data)
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * qr = lv_qrcode_create(lv_scr_act(), 150, lv_color_black(), lv_color_white());
    /*Set data*/
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_align(qr, LV_ALIGN_CENTER, 0, 0);
}

void display_welcome_screen(char *data)
{
    lv_obj_clean(lv_scr_act());
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, data);
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void display_total_screen(total_data_t total)
{
    
}
void display_payment_status(payment_status_data_t payment)
{

}
static void image_display_task(void *arg)
{
    while(1)
    {
        EventBits_t event_bit = xEventGroupWaitBits(event_group, WELCOMESCREEN_EVT | TOTALSCREEN_EVT | QRCODESCREEN_EVT | PAYMENTSTATUS_EVT, true, false, portMAX_DELAY); 
        if(event_bit & WELCOMESCREEN_EVT)
        {
            welcome_data_t data;
            get_welcome_screen_data(&data);
            display_welcome_screen(data.title);
        }
        if(event_bit & TOTALSCREEN_EVT)
        {

        }
        if(event_bit & QRCODESCREEN_EVT)
        {
            QR_code_data_t data;
            get_QR_code_screen_data(&data);
            display_qrcode(data.UPIUrl);
        }
        if(event_bit & PAYMENTSTATUS_EVT)
        {
            
        }
    }
}
void image_display_init(void)
{
    BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
    // image_display_queue = xQueueCreate(IMAGE_DISPLAY_QUEUE_SIZE, sizeof(display_data_t));
    // if (NULL == image_display_queue)
    // {
    //     ESP_LOGE(TAG, "image_display_queue queue create fail");
    //     abort();
    // }
    /* create event groups */
    event_group = xEventGroupCreate();
    if (NULL == event_group)
    {
        ESP_LOGE(TAG, "event_group create fail");
        abort();
    }
	xReturned = xTaskCreate(image_display_task, "image_display_task", 4096, NULL, 5, &xHandle);
	if (pdPASS != xReturned)
	{
		ESP_LOGE(TAG, "image_display_task create fail");
		abort();
	}
}
void audio_init(void);

void app_main(void)
{
    /* Initialize I2C (for touch and audio) */
    bsp_i2c_init();

    /* Initialize display and LVGL */
    bsp_display_start();

    /* Set display brightness to 100% */
    bsp_display_backlight_on();

    /* Mount SPIFFS */
    bsp_spiffs_mount();
    
    wifi_main();
    image_display_init();

    mqtt_app_start();
    //audio_init();
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

