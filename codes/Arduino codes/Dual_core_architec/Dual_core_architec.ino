#define LED1 2
SemaphoreHandle_t mutex;

float sensor1=0;
float sensor2=0;
float sensor3=0;
float sensor4=0;
float sensor5=0;

void sensorDataProcessing(void* param) {
  
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);

    sensor1 = random(1, 100);
    sensor2 = random(1, 100);
    sensor3 = random(1, 100);
    sensor4 = random(1, 100);
    sensor5 = random(1, 100);

    xSemaphoreGive(mutex);
    delay(1000);

  }
}

void dataCommunication(void* param) {
  
  while (1) {
  xSemaphoreTake(mutex, portMAX_DELAY);

  Serial.print("SensorData=[");
  Serial.print(sensor1);
  Serial.print(",");
  Serial.print(sensor2);
  Serial.print(",");
  Serial.print(sensor3);
  Serial.print(",");
  Serial.print(sensor4);
  Serial.print(",");
  Serial.print(sensor5);
  Serial.println("]");

  xSemaphoreGive(mutex);
  delay(1000);
  }
}

void setup() {
  mutex = xSemaphoreCreateMutex();
  Serial.begin(115200);
  // pinMode(LED1, OUTPUT);

  xTaskCreatePinnedToCore(
    sensorDataProcessing,    // Function to run on core 0
    "dataCommunication",  // Task name
    10000,        // Stack size
    NULL,         // Task parameters
    1,            // Priority
    NULL,         // Task handle
    0             // Core number (0 or 1 for core 0 or core 1, respectively)
  );

  xTaskCreatePinnedToCore(
    dataCommunication,    // Function to run on core 1
    "dataCommunication",  // Task name
    10000,        // Stack size
    NULL,         // Task parameters
    1,            // Priority
    NULL,         // Task handle
    1             // Core number (0 or 1 for core 0 or core 1, respectively)
  );

}


void loop() { 
}
