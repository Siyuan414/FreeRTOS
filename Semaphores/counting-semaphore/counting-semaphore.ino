#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


#define RED A0
#define BLUE A1
#define YELLOW 12

SemaphoreHandle_t xCountingSemaphore;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(YELLOW,OUTPUT);

  Serial.begin(9600);
  xCountingSemaphore = xSemaphoreCreateCounting(1,0);
  xTaskCreate(redLEDCrontrollerTask,"Red task",100,NULL,1,NULL);
  xTaskCreate(blueLEDCrontrollerTask,"blue task",100,NULL,1,NULL);
  xTaskCreate(yellowLEDCrontrollerTask,"yellow task",100,NULL,1,NULL);
  xSemaphoreGive(xCountingSemaphore);
}
void redLEDCrontrollerTask(void *pvParameters){
  
  while(1){
    xSemaphoreTake(xCountingSemaphore,portMAX_DELAY);
    digitalWrite(RED,HIGH);
    Serial.println("RED TASK");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void blueLEDCrontrollerTask(void *pvParameters){
  
  while(1){
    xSemaphoreTake(xCountingSemaphore,portMAX_DELAY);
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    Serial.println("BLUE TASK");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void yellowLEDCrontrollerTask(void *pvParameters){
 
  while(1){
    xSemaphoreTake(xCountingSemaphore,portMAX_DELAY);
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    Serial.println("YELLOW TASK");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
