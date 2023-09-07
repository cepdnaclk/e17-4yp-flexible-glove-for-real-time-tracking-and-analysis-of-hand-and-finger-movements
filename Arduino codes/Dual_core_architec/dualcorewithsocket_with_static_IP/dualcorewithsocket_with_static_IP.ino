#include <WebSocketsServer.h>

// ----------------------------------------------------- socket init
const char* ssid = "Huawei";
const char* password = "12345678";
WebSocketsServer webSocket = WebSocketsServer(80);
//-------------------------------------------------------


//----------------------------------------------dual core init
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

  
  webSocket.loop();
  // Send data to connected clients
  // char sensor1Str[10];
  // char sensor2Str[10];
  // char sensor3Str[10];
  // char sensor4Str[10];
  // char sensor5Str[10];
 // Convert sensor data to strings
  String sensor1Str = String(sensor1, 2);
  String sensor2Str = String(sensor2, 2);
  String sensor3Str = String(sensor3, 2);
  String sensor4Str = String(sensor4, 2);
  String sensor5Str = String(sensor5, 2);

  // Concatenate all sensor data into one string
  String result = "SensorData=[" + sensor1Str + "," + sensor2Str + "," + sensor3Str + "," + sensor4Str + "," + sensor5Str + "]";

  webSocket.broadcastTXT(result);
  
  // delay(1000); // Delay before sending the next message

  xSemaphoreGive(mutex);

  delay(1000);
  }
}

//----------------------------------------------




void setup() {

  Serial.begin(115200);

//--------------------------------------------------------- socket setup
  


  IPAddress staticIP(192, 168, 43, 55);  // Static IP address
  IPAddress gateway(192, 168, 43, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(192, 168, 43, 1);
  IPAddress secondaryDNS(0,0,0,0);
  
  if(!WiFi.config(staticIP, gateway, subnet, primaryDNS,secondaryDNS)){
    Serial.print("Fail to config");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("subnet ");
  Serial.println(WiFi.subnetMask());
  Serial.println("DNS1 ");
  Serial.println(WiFi.dnsIP(0));
  Serial.println("DNS2 ");
  Serial.println(WiFi.dnsIP(1));
  webSocket.begin();
//---------------------------------------------------------
mutex = xSemaphoreCreateMutex();
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
  // webSocket.loop();

  // // Send data to connected clients
  // String dataToSend = "Hello from ESP8266!";
  // webSocket.broadcastTXT(dataToSend);
  
  // delay(1000); // Delay before sending the next message
}
