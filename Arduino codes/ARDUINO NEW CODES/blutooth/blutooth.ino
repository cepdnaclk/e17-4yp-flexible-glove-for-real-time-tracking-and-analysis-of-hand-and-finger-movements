#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool testRunning = false;
const char *dataToSend = "Hello from ESP32!";
unsigned long startTime = 0;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
    Serial.println("Connected to BLE client");
  }

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    Serial.println("Disconnected from BLE client");
    testRunning = false;
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32_BLE_Speed_Test");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(BLEUUID("0000XXXX-0000-1000-8000-00805F9B34FB"));

  pCharacteristic = pService->createCharacteristic(
      BLEUUID("0000YYYY-0000-1000-8000-00805F9B34FB"),
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();

  Serial.println("BLE server started");
}

void loop() {
  if (deviceConnected && !testRunning) {
    Serial.println("BLE client connected");
    testRunning = true;
    startTime = millis();

    // Send test data to the BLE client
    pCharacteristic->setValue(dataToSend);
    pCharacteristic->notify();
  }

  if (testRunning && millis() - startTime > 5000) {  // Adjust the time according to your needs (5 seconds in this example)
    // Stop the test after a certain period (5 seconds in this example)
    Serial.println("BLE client disconnected");
    testRunning = false;

    // Calculate and print the speed
    unsigned long endTime = millis();
    unsigned long dataSize = strlen(dataToSend) * 8;  // Size of data in bits
    float speed = (dataSize / ((float)(endTime - startTime) / 1000.0)) / 1000.0;  // Speed in kbps
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" kbps");
  }

  delay(10);
}