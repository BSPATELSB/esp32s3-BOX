#NXON AI PVT. LTD.

# Image Display Example

| Board             | Support Status |
| ----------------- | -------------- |
| ESP32-S3-BOX      | YES            |
| ESP32-S3-BOX-Lite | YES            |

Display PNG image with LVGL.

## How to use example

### Hardware Required

* A ESP32-S3-Box
* An USB-C cable for power supply and programming

Follow detailed instructions provided specifically for this example. 

### Build and Flash

Run `idf.py flash monitor` to build, flash and monitor the project.

Once a complete flash process has been performed, you can use `idf.py app-flash monitor` to reduce the flash time.

(To exit the serial monitor, type `Ctrl-]`. Please reset the development board f you cannot exit the monitor.)

## Example Output

Run this example, you will see the following output log:

```
I (5462) wifi:set rx beacon pti, rx_bcn_pti: 0, bcn_timeout: 0, mt_pti: 25000, mt_time: 10000
I (5472) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (7082) example_connect: Got IPv6 event: Interface "example_netif_sta" address: fe80:0000:0000:0000:7edf:a1ff:feff:40d8, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (7662) wifi:<ba-add>idx:0 (ifx:0, b2:8b:92:61:be:d7), tid:0, ssn:0, winSize:64
I (8462) esp_netif_handlers: example_netif_sta ip: 192.168.1.21, mask: 255.255.255.0, gw: 192.168.1.1
I (8462) example_connect: Got IPv4 event: Interface "example_netif_sta" address: 192.168.1.21
I (8462) example_common: Connected to example_netif_sta
I (8462) example_common: - IPv4 address: 192.168.1.21,
I (8462) example_common: - IPv6 address: fe80:0000:0000:0000:7edf:a1ff:feff:40d8, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (8462) MQTTS_EXAMPLE: [APP] Free memory: 8447328 bytes
I (8462) MQTTS_EXAMPLE: Other event id:7
I (8472) wifi:<ba-add>idx:1 (ifx:0, b2:8b:92:61:be:d7), tid:6, ssn:2, winSize:64
I (9292) MQTTS_EXAMPLE: MQTT_EVENT_CONNECTED
I (9292) MQTTS_EXAMPLE: sent subscribe successful, msg_id=54675
I (10312) MQTTS_EXAMPLE: MQTT_EVENT_SUBSCRIBED, msg_id=54675
I (12412) main: volume '3'
I (12442) main: volume '7'
I (12472) main: volume '13'
I (12502) main: volume '21'
I (12532) main: volume '30'
I (12562) main: volume '42'
I (12592) main: volume '54'
I (12622) main: volume '65'
I (12652) main: volume '75'
I (12682) main: volume '83'
I (12712) main: volume '90'
I (12742) main: volume '96'
I (12772) main: volume '100'
I (11142) main: volume '99'
I (11202) main: volume '98'
I (11262) main: volume '97'
I (11322) main: volume '96'
I (11382) main: volume '95'
I (11562) main: volume '94'
I (11892) main: volume '93'
I (12072) main: volume '92'
I (12252) main: volume '91'
I (12672) main: volume '90'
I (12942) main: volume '89'
I (13332) main: volume '88'
I (13752) main: volume '87'
I (15022) main: volume '86'
I (15322) main: volume '85'
I (15982) main: volume '86'
I (136882) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=test1
DATA={"screen":"WelcomeScreen","data":{"title":"Welcome to Easovation Solutions","voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T142436330Z245431.wav","img":""}}
I (136882) MQTTS_EXAMPLE: screen=WelcomeScreen
I (136882) MQTTS_EXAMPLE: title:Welcome to Easovation Solutions
I (136882) MQTTS_EXAMPLE: voice_data:http://116.202.102.65:9000/downloadttsfile?filename=20230512T142436330Z245431.wav
I (137172) HTTP_CLIENT: Body received in fetch header state, 0x3fcdf757, 101
I (137512) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 11424
I (140092) main: mute setting 1, volume:86
I (142962) main: mute setting 0, volume:86
I (156242) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=test1
DATA={"screen":"DisplayTotalScreen","data":{"TotalAmount":100,"DiscountAmount":20,"TaxAmount":10,"GrandTotal":90,"voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T142454092Z663978.wav","img":""}}
I (156242) MQTTS_EXAMPLE: screen=DisplayTotalScreen
I (156652) HTTP_CLIENT: Body received in fetch header state, 0x3fcb7243, 101
I (157062) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 12672
I (157572) main: mute setting 1, volume:86
I (157572) MQTTS_EXAMPLE: voice_data:http://116.202.102.65:9000/downloadttsfile?filename=20230512T142454092Z663978.wav
I (157572) MQTTS_EXAMPLE: TotalAmount:100 DiscountAmount:20 TaxAmount:10 GrandTotal:90
I (160742) main: mute setting 0, volume:86
I (172122) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=test1
DATA={"screen":"DisplayQRCodeScreen","data":{"QrCodeBase64":"","UPIUrl":"upi://pay?pa=63270083167.payswiff@indus&pn=Bonrix&cu=INR&am=10&pn=Bonrix%20Software%20Systems","Amount":10,"voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T142507671Z505495.wav","CompanyName":"Bonrix Software Systems","ShopName":"Easovation","img":""}}
I (172122) MQTTS_EXAMPLE: screen=DisplayQRCodeScreen
I (172122) MQTTS_EXAMPLE: QrCodeBase64:
I (172122) MQTTS_EXAMPLE: UPIUrl:upi://pay?pa=63270083167.payswiff@indus&pn=Bonrix&cu=INR&am=10&pn=Bonrix%20Software%20Systems
I (172122) MQTTS_EXAMPLE: CompanyName:Bonrix Software Systems
I (172122) MQTTS_EXAMPLE: ShopName:Easovation
I (172122) MQTTS_EXAMPLE: Amount:10
I (172632) HTTP_CLIENT: Body received in fetch header state, 0x3fcb7103, 101
I (173032) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 11232
I (173342) main: mute setting 1, volume:86
I (173342) MQTTS_EXAMPLE: voice_data:http://116.202.102.65:9000/downloadttsfile?filename=20230512T142507671Z505495.wav
I (176302) main: mute setting 0, volume:86
TOPIC=test1
DATA={"screen":"DisplaySuccessQRCodeScreen","data":{"OrderId":123567,"BankRef":21354,"Amount":100,"voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T204028666Z853372.wav","Date":1683924028899,"img":""}}
I (21892) MQTTS_EXAMPLE: screen=DisplaySuccessQRCodeScreen
I (21892) MQTTS_EXAMPLE: payment_date:2147483647
I (21892) MQTTS_EXAMPLE: Amount:0
I (22362) HTTP_CLIENT: Body received in fetch header state, 0x3fcdf82f, 101
I (22982) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 17088
I (24632) MQTTS_EXAMPLE: paymentstauts:0 OrderId:123567, BankRef:21354, Date:2147483647
I (24652) main: mute setting 1, volume:86
I (25332) main: Display image file : S:/spiffs/pass.png
I (30072) main: mute setting 0, volume:86
I (240632) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=test1
DATA={"screen":"DisplayCancelQRCodeScreen","data":{"OrderId":123567,"BankRef":21354,"Amount":1000,"voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T142635390Z254330.wav","Date":1683901595577,"img":""}}
I (257222) MQTTS_EXAMPLE: screen=DisplayCancelQRCodeScreen
I (257222) MQTTS_EXAMPLE: payment_date:2147483647
I (257222) MQTTS_EXAMPLE: Amount:10
I (257612) HTTP_CLIENT: Body received in fetch header state, 0x3fcb6e9a, 102
I (257822) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 8160
I (258942) main: mute setting 1, volume:86
I (258942) MQTTS_EXAMPLE: paymentstauts:1 OrderId:123567, BankRef:21354, Date:2147483647
I (259582) main: Display image file : S:/spiffs/cancel.png
I (262112) main: mute setting 0, volume:86
I (304722) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=test1
DATA={"screen":"DisplayFailQRCodeScreen","data":{"OrderId":123567,"BankRef":21354,"Amount":2000,"voice_data":"http://116.202.102.65:9000/downloadttsfile?filename=20230512T142742608Z687224.wav","Date":1683901662803,"img":""}}
I (322222) MQTTS_EXAMPLE: screen=DisplayFailQRCodeScreen
I (322222) MQTTS_EXAMPLE: payment_date:2147483647
I (322222) MQTTS_EXAMPLE: Amount:10
I (322642) HTTP_CLIENT: Body received in fetch header state, 0x3fcdfb72, 102
I (322882) MQTTS_EXAMPLE: HTTP GET Status = 200, content_length = 7584
I (323252) main: mute setting 1, volume:86
I (323252) MQTTS_EXAMPLE: paymentstauts:2 OrderId:123567, BankRef:21354, Date:2147483647
I (323252) main: Display image file : S:/spiffs/fail.png
I (325702) main: mute setting 0, volume:86
```


