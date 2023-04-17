/* MQTT over SSL Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_tls.h"
#include "cJSON.h"
#include "mqtt.h"

static const char *TAG = "MQTTS_EXAMPLE";

static welcome_data_t welcome_screen_data;
static total_data_t total_screen_data;
static QR_code_data_t QR_code_screen_data;
static payment_status_data_t payment_status_scr_data;

void get_welcome_screen_data(welcome_data_t *data)
{
    strcpy(data->title, welcome_screen_data.title);
}
void get_total_screen_data(total_data_t *data)
{
    data->TotalAmount = total_screen_data.TotalAmount;
    data->DiscountAmount = total_screen_data.DiscountAmount;
    data->TaxAmount = total_screen_data.TaxAmount;
    data->GrandTotal = total_screen_data.GrandTotal;
}

void get_payment_status_data(payment_status_data_t *data)
{
    data->status = payment_status_scr_data.status;
    data->BankRef = payment_status_scr_data.BankRef;
    data->OrderId = payment_status_scr_data.OrderId;
    strcpy(data->Date, payment_status_scr_data.Date);
}
void get_QR_code_screen_data(QR_code_data_t *data)
{
    data->Amount = QR_code_screen_data.Amount;
    strcpy(data->UPIUrl, QR_code_screen_data.UPIUrl);
    strcpy(data->QrCodeBase64, QR_code_screen_data.QrCodeBase64);
    strcpy(data->CompanyName, QR_code_screen_data.CompanyName);
    strcpy(data->ShopName, QR_code_screen_data.ShopName);
}
void parse_json_payload(char *data)
{
    cJSON *root = cJSON_Parse(data);
    if (cJSON_GetObjectItem(root, "screen")) 
    {
		char *screen = cJSON_GetObjectItem(root,"screen")->valuestring;
		ESP_LOGI(TAG, "screen=%s",screen);
        if(strcmp(screen,WELCOMESCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
            char *title = cJSON_GetObjectItem(data,"title")->valuestring;
            strcpy(welcome_screen_data.title, title);
            ESP_LOGI(TAG,"title:%s",welcome_screen_data.title);
            xEventGroupSetBits(event_group, WELCOMESCREEN_EVT);
        }
        else if(strcmp(screen,TOTALSCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
            total_screen_data.TotalAmount = cJSON_GetObjectItem(data,"TotalAmount")->valueint;
            total_screen_data.DiscountAmount = cJSON_GetObjectItem(data,"DiscountAmount")->valueint;
            total_screen_data.TaxAmount = cJSON_GetObjectItem(data,"TaxAmount")->valueint;
            total_screen_data.GrandTotal = cJSON_GetObjectItem(data,"GrandTotal")->valueint;
            ESP_LOGI(TAG,"TotalAmount:%d DiscountAmount:%d TaxAmount:%d GrandTotal:%d",
            total_screen_data.TotalAmount, total_screen_data.DiscountAmount,total_screen_data.TaxAmount,total_screen_data.GrandTotal);
            xEventGroupSetBits(event_group, TOTALSCREEN_EVT);
        }
        else if(strcmp(screen,QRCODESCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
            char *QrCodeBase64 = cJSON_GetObjectItem(data,"QrCodeBase64")->valuestring;
            strcpy(QR_code_screen_data.QrCodeBase64, QrCodeBase64);
            ESP_LOGI(TAG,"QrCodeBase64:%s",QR_code_screen_data.QrCodeBase64);
            char *UPIUrl = cJSON_GetObjectItem(data,"UPIUrl")->valuestring;
            strcpy(QR_code_screen_data.UPIUrl, UPIUrl);
            ESP_LOGI(TAG,"UPIUrl:%s",QR_code_screen_data.UPIUrl);
            char *CompanyName = cJSON_GetObjectItem(data,"CompanyName")->valuestring;
            strcpy(QR_code_screen_data.CompanyName, CompanyName);
            ESP_LOGI(TAG,"CompanyName:%s",QR_code_screen_data.CompanyName);
            char *ShopName = cJSON_GetObjectItem(data,"ShopName")->valuestring;
            strcpy(QR_code_screen_data.ShopName, ShopName);
            ESP_LOGI(TAG,"ShopName:%s",QR_code_screen_data.ShopName);
            QR_code_screen_data.Amount = cJSON_GetObjectItem(data,"Amount")->valueint;
            ESP_LOGI(TAG,"Amount:%d",QR_code_screen_data.Amount);
            xEventGroupSetBits(event_group, QRCODESCREEN_EVT);
        }
        else if(strcmp(screen,QRSUCCESSSCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
           // char *payment_date = cJSON_GetObjectItem(data,"Date")->valuestring;
           // strcpy(payment_status_scr_data.Date, payment_date);
           // ESP_LOGI(TAG,"payment_date:%s",payment_status_scr_data.Date);
            payment_status_scr_data.OrderId = cJSON_GetObjectItem(data,"OrderId")->valueint;
            payment_status_scr_data.BankRef = cJSON_GetObjectItem(data,"BankRef")->valueint;
            payment_status_scr_data.status = PAYMENT_SUCCESS;
            ESP_LOGI(TAG,"paymentstauts:%d OrderId:%d, BankRef:%d",
            payment_status_scr_data.status, payment_status_scr_data.OrderId, payment_status_scr_data.BankRef);
            xEventGroupSetBits(event_group, PAYMENTSTATUS_EVT);
        }
        else if(strcmp(screen,QRCANCELSCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
            //char *payment_date = cJSON_GetObjectItem(data,"Date")->valuestring;
            //strcpy(payment_status_scr_data.Date, payment_date);
            //ESP_LOGI(TAG,"payment_date:%s",payment_status_scr_data.Date);
            payment_status_scr_data.OrderId = cJSON_GetObjectItem(data,"OrderId")->valueint;
            payment_status_scr_data.BankRef = cJSON_GetObjectItem(data,"BankRef")->valueint;
            payment_status_scr_data.status = PAYMENT_CANCEL;
            ESP_LOGI(TAG,"paymentstauts:%d OrderId:%d, BankRef:%d",
            payment_status_scr_data.status, payment_status_scr_data.OrderId, payment_status_scr_data.BankRef);
            xEventGroupSetBits(event_group, PAYMENTSTATUS_EVT);
        }
        else if(strcmp(screen,QRFAILSCREEN) == 0)
        {
            cJSON *data = cJSON_GetObjectItem(root,"data");
            //char *payment_date = cJSON_GetObjectItem(data,"Date")->valuestring;
            //strcpy(payment_status_scr_data.Date, payment_date);
            //ESP_LOGI(TAG,"payment_date:%s",payment_status_scr_data.Date);
            payment_status_scr_data.OrderId = cJSON_GetObjectItem(data,"OrderId")->valueint;
            payment_status_scr_data.BankRef = cJSON_GetObjectItem(data,"BankRef")->valueint;
            payment_status_scr_data.status = PAYMENT_FAIL;
            ESP_LOGI(TAG,"paymentstauts:%d OrderId:%d, BankRef:%d",
            payment_status_scr_data.status, payment_status_scr_data.OrderId, payment_status_scr_data.BankRef);
            xEventGroupSetBits(event_group, PAYMENTSTATUS_EVT);
        }
        else
        {
            ESP_LOGE(TAG,"Received invalid screen: %s",screen);
        }
	}
    else
    {
        ESP_LOGE(TAG,"Invalid payload unable to find screen");
    }
    cJSON_Delete(root);
}
/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
                msg_id = esp_mqtt_client_subscribe(client, "test1", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            //msg_id = esp_mqtt_client_publish(client, "test1", "data", 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            parse_json_payload(event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
}


void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://nodered-mqtt.bonrix.in:21883",
        .credentials.authentication.password = "nxon1234",
        .credentials.username = "nxon",
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void wifi_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
}
