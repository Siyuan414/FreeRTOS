#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

SemaphoreHandle_t  xMutex;

static const char *pcStringToPrint[] =
{
  "Task 1 ############################## Task1 \r\n",
  "Task 2 ------------------------------ Task2 \r\n",  
};
void setup()
{
  Serial.begin(9600);
  xMutex = xSemaphoreCreateMutex();

  xTaskCreate(OutputTask,"Printer Task 1", 100,(void *)0,1,NULL);
  xTaskCreate(OutputTask,"Printer Task 2", 100,(void *)1,2,NULL);
  
  
}

void OutputTask(void *pvParameters)
{
  char *pcStringToPrint;
  pcStringToPrint = (char *)pvParameters;
  while(1)
  {
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void printer(const char* pcString)
{
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcString);
  xSemaphoreGive(xMutex);
}
void loop(){}
