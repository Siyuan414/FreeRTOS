
#include <DHT.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define RED_LED_PIN 13
#define BLUE_LED_PIN 12
#define DHT_PIN 27
#define DHT_TYPE DHT22

// Initialize DHT sensor
DHT dht(DHT_PIN,DHT_TYPE);

//Queue to send sensor data 
QueueHandle_t sensorDataQueue;
SemaphoreHandle_t xMutex; //mutex for sharing memory

//struct data
struct SensorData{
  float temp;
  float humidity;
};
//LED TASK 1
void blind_red_led(void *pvParameter){
  while(true){
    digitalWrite(RED_LED_PIN,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(RED_LED_PIN,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

//LED TASK2
void blind_blue_led(void *pvParameter){
  while(true){
    digitalWrite(BLUE_LED_PIN,HIGH);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    digitalWrite(BLUE_LED_PIN,LOW);
    vTaskDelay(2000/portTICK_PERIOD_MS);
  }
}

// Task to read DHT32 sensor
void read_dht32(void *pvParameter){
  SensorData data;
  while(1){
    if(xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE){
      data.temp = dht.readTemperature();
      data.humidity = dht.readHumidity();

      //check if sensor data reading successfully
      if (isnan(data.temp)){
        Serial.println("Failed to read temp");
      }else{
        Serial.print("Temperature: ");
        Serial.print(data.temp);
      }
      if(isnan(data.humidity)){
        Serial.println("Failed to read humidity");
      }else{
        Serial.print(" °C, Humidity: ");
        Serial.print(data.humidity);
        Serial.println(" %");
      }

      //send sensor data to queue for another task
      xQueueSend(sensorDataQueue,&data,portMAX_DELAY);

      //release mutex 
      xSemaphoreGive(xMutex);

      // Delay before next reading
      vTaskDelay(1000 / portTICK_PERIOD_MS);  // Read every 5 seconds
    }
  }
}

// Task to process sensor data
void process_sensor_data(void *pvParameter){
  SensorData data;
  
  while(1){
    if(xQueueReceive(sensorDataQueue,&data,portMAX_DELAY) == pdTRUE){
        Serial.print("Processing Sensor Data: Temperature: ");
        Serial.print(data.temp);
    }
    
    if(xQueueReceive(sensorDataQueue,&data,portMAX_DELAY) == pdTRUE){
        Serial.print(" °C, Humidity: ");
        Serial.print(data.humidity);
        Serial.println(" %");
    }
  }
}
void setup() {
  Serial.begin(115200);
  
  // Initialize GPIO for LEDs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Initialize DHT sensor
  dht.begin();

  //Initialize Mutex for task synchronization
  xMutex = xSemaphoreCreateMutex();

  //Inititalize queue for sensor data
  sensorDataQueue = xQueueCreate(10,sizeof(SensorData));

  //create freertos task
  xTaskCreate(blind_red_led,"Blink RED LED",2048,NULL,3,NULL);
  xTaskCreate(blind_blue_led,"Blink BLUE LED",2048,NULL,4,NULL);
  xTaskCreate(read_dht32,"READ SENSOR DATA",2048,NULL,1,NULL);
  xTaskCreate(process_sensor_data,"PROCESS SENSOR DATA",2048,NULL,2,NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
