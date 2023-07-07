#include "freertos/FreeRTOS.h"
#define RED    A0
#define YELLOW A3
#define BLUE   8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler; 
TaskProfiler YellowLEDProfiler; 
TaskProfiler BlueLEDProfiler; 


void setup(){
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "RED LED TASK",
              100,
              NULL,
              1,
              NULL
              );
  xTaskCreate(blueLedControllerTask,
              "RED LED TASK",
              100,
              NULL,
              1,
              NULL
              );
  xTaskCreate(yellowLedControllerTask,
              "RED LED TASK",
              100,
              NULL,
              1,
              NULL
              );
}

void redLedControllerTask(void *pvParameters){
  pinMode(RED,OUTPUT);
  while(1){
    Serial.printf("This is RED");
  }
}

void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE,OUTPUT);
  while(1){
    Serial.printf("This is blue");
  }
}

void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW,OUTPUT);
  while(1){
    Serial.printf("This is yellow");
  }
}

void loop(){

}