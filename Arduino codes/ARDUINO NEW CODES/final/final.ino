#include <WebSocketsServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// ----------------------------------------------------- socket init
const char* ssid = "SLT_FIBRE";
const char* password = "ge2250276";
WebSocketsServer webSocket = WebSocketsServer(80);
//-------------------------------------------------------


//----------------------------------------------dual core init
float t_x=0;
float t_y=0;
float t_z=0;

int speed=25;
SemaphoreHandle_t mutex;
sensors_event_t a, g, temp;



void sensorDataProcessing(void* param) {
  
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    mpu.getEvent(&a, &g, &temp);
    xSemaphoreGive(mutex);
    compareAndSetSpeed(t_x,t_y,t_z,g.gyro.x,g.gyro.y,g.gyro.z);
    t_x=g.gyro.x;
    t_y=g.gyro.y;
    t_z=g.gyro.z;
    delay(speed);

  }
}

void dataCommunication(void* param) {
  while (1) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  String a_x = String(a.acceleration.x, 2);
  String a_y = String(a.acceleration.y, 2);
  String a_z = String(a.acceleration.z, 2);
  String r_x = String(g.gyro.x, 2);
  String r_y = String(g.gyro.y, 2);
  String r_z = String(g.gyro.z, 2);
  // Concatenate all sensor data into one string
  String result = "[[" + a_x + "," + a_y + "," + a_z + "],["+r_x+","+r_y+","+r_z + "]]";
  String total = "["+result+","+result+","+result+","+result+","+result+","+result+","+result+","+result+","+result+"]";

  // Serial.println(speed);  //for debug
  webSocket.loop();
  webSocket.broadcastTXT(total);
  xSemaphoreGive(mutex);

  delay(speed);
  }
}

//----------------------------------------------




void setup() {

  Serial.begin(115200);
  //-----------------------------------------------------------------------
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);


  //-----------------------------------------------------------------------
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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

}


void compareAndSetSpeed(float val1, float val2, float val3, float val4, float val5, float val6) {
  // Serial.print(val1);
  // Serial.print(val2);
  // Serial.println(val3);
  // Serial.print(val4);
  // Serial.print(val5);
  // Serial.print(val6);
  // if (val1 == val4 && val2 == val5 && val3 == val6) {
  //   // Inputs match, keep speed at 100
  //   speed = 100;

  if (val1-val4<0.01 && val1-val4>-0.01) {
    // Inputs match, keep speed at 100
    // Serial.println("stable");
    speed = 100;
  }
    else {
    // Inputs are different, set speed to 25
    // Serial.println("not stable");
    speed = 25;
  }

}

