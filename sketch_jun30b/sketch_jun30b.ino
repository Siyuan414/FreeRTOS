#include "freertos/FreeRTOS.h"

#define RED A0
#define BLUE A1
#define YELLOW 12

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

TaskHandle_t blue_handle, red_handle, yellow_handle;

void setup(){
  
  xTaskCreate(redControllerTask,"red led task",100,NULL,1,&red_handle);
  xTaskCreate(blueControllerTask,"blue led task", 100, NULL, 1, &blue_handle);
  xTaskCreate(yellowControllerTask,"yellow led task", 100, NULL, 1, &yellow_handle);
}
void redControllerTask(void *pvParameters){
  pinMode(RED,OUTPUT);
  while(1){
    digitalWrite(RED,digitalRead(RED)^1);
    delay(50);
  }
}
void blueControllerTask(void *pvParameters){
  pinMode(BLUE,OUTPUT);
  while(1){
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    delay(50);
  }
}
void yellowControllerTask(void *pvParameters){
  pinMode(YELLOW,OUTPUT);
  while(1){
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskPrioritySet(yellow_handle,2);
    delay(50);
  }
}
void loop(){

}