#ifndef __MQTT_H__
#define __MQTT_H__
#include "freertos/event_groups.h"

#define WELCOMESCREEN_EVT   BIT0
#define TOTALSCREEN_EVT     BIT1
#define QRCODESCREEN_EVT    BIT2
#define PAYMENTSTATUS_EVT   BIT3


#define WELCOMESCREEN   "WelcomeScreen"
#define TOTALSCREEN     "DisplayTotalScreen"
#define QRCODESCREEN    "DisplayQRCodeScreen"
#define QRSUCCESSSCREEN "DisplaySuccessQRCodeScreen"
#define QRCANCELSCREEN  "DisplayCancelQRCodeScreen"
#define QRFAILSCREEN    "DisplayFailQRCodeScreen"

extern EventGroupHandle_t event_group;

typedef enum payment_status
{
    PAYMENT_SUCCESS = 0,
    PAYMENT_CANCEL,
    PAYMENT_FAIL,
    PAYMENT_PENDING,
}payment_status_t;

typedef struct welcome_data
{
    char title[512];
    char img[100];
    char voice_url[512];
}welcome_data_t;

typedef struct total_data
{
    int TotalAmount;
    int DiscountAmount;
    int TaxAmount;
    int GrandTotal;
    char img[100];
    char voice_url[512];
}total_data_t;

typedef struct QR_code_data
{
    int Amount;
    char QrCodeBase64[32];
    char UPIUrl[512];
    char CompanyName[100];
    char ShopName[100];
    char img[100];
    char voice_url[512];
}QR_code_data_t;

typedef struct payment_status_data
{
    payment_status_t status;
    int OrderId;
    int BankRef;
   // char Date[100];
    int Date;
    int Amount;
    char img[100];
    char voice_url[512];
}payment_status_data_t;
void get_welcome_screen_data(welcome_data_t *data);
void get_total_screen_data(total_data_t *data);
void get_payment_status_data(payment_status_data_t *data);
void get_QR_code_screen_data(QR_code_data_t *data);

#endif
