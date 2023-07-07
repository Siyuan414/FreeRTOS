#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define RED    A0
#define YELLOW A3
#define BLUE   8

// QueueHandle_t q1;
// QueueHandle_t q2;

// QueueSetHandle_t xQueueSet;

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(RED,OUTPUT);
//   Serial.begin(2000000);
//   q1 = xQueueCreate(1,sizeof(char *));
//   q2 = xQueueCreate(1,sizeof(char *));

//   xQueueSet = xQueueCreateSet(1*2);
//   xQueueAddToSet(q1,xQueueSet);
//   xQueueAddToSet(q2,xQueueSet);

//   xTaskCreate(vSenderTask1, "sender task 1", 100, NULL, 1, NULL);
//   xTaskCreate(vSenderTask2, "sender task 2", 100, NULL, 1, NULL);

//   xTaskCreate(vReceiveTask, "receiver task",100,NULL,2,NULL);

// }

// void vSenderTask1(void *pvParameters){
//   const TickType_t xBlockTime = pdMS_TO_TICKS(100);
//   const char * const messageTosend = "message from sender 1";
//   while(1){
//     vTaskDelay(xBlockTime);
//     xQueueSend(q1,&messageTosend,0);
//   }
// }

// void vSenderTask2(void *pvParameters){
//   const TickType_t xBlockTime = pdMS_TO_TICKS(100);
//   const char * const messageTosend = "message from sender 2";
//   while(1){
//     vTaskDelay(xBlockTime);
//     xQueueSend(q2,&messageTosend,0);
//   }
// }
// void vReceiveTask(void *pvParameters){
//   QueueHandle_t Q_data;
//   char *pcReceiveString;
//   while(1){
//     Q_data = (QueueHandle_t)xQueueSelectFromSet(xQueueSet,portMAX_DELAY);
//     xQueueReceive(Q_data, &pcReceiveString,0);
//     Serial.println(pcReceiveString);
//   }
// }
void loop() {
  // put your main code here, to run repeatedly:

}
