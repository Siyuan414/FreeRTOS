#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


#define RED A0
#define BLUE A1
#define YELLOW 12

typedef int TaskProfiler;

TaskProfiler RedTaskProfiler;
TaskProfiler BlueTaskProfiler;
TaskProfiler YellowTaskProfiler;

SemaphoreHandle_t xBinarySemaphore;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(redLedControllerTask,"red led task",100,NULL,1,NULL);
  xTaskCreate(blueLedControllerTask,"blue led task",100,NULL,1,NULL);
  xTaskCreate(yellowLedControllerTask,"yellow led task",100,NULL,1,NULL);
}
void redLedControllerTask(void *pvParameters){
  pinMode(RED,OUTPUT);
  xSemaphoreGive(xBinarySemaphore);
  while(1){
    xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
    Serial.println("This is red task");
    xSemaphoreGive(xBinarySemaphore);
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE,OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
    Serial.println("This is blue task");
    xSemaphoreGive(xBinarySemaphore);
  }
}
void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW,OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
     Serial.println("This is yellow task");
     xSemaphoreGive(xBinarySemaphore);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
