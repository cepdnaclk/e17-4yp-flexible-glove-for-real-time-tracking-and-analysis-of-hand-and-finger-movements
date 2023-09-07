#include <SPI.h>

const int chipSelectPin = 32;
const int syncPin = 17;

const int misoPin = 19;
const int mosiPin = 23;
const int clkPin = 18;

SPIClass spi(HSPI);

void setup() {
  Serial.begin(115200);

  // Configure the SPI class with custom pins
  spi.begin(clkPin, misoPin, mosiPin, chipSelectPin);
  spi.setClockDivider(SPI_CLOCK_DIV16); // Adjust clock speed as needed

  pinMode(chipSelectPin, OUTPUT);
  pinMode(syncPin, OUTPUT);

  digitalWrite(chipSelectPin, HIGH); // Deselect the chip select pin
  digitalWrite(syncPin, HIGH); // Set sync pin to HIGH initially
}

void loop() {
  int x, y, z;

  // Assuming the acceleration data can be read using a specific command
  // Adjust the readAccelerationData function as necessary to match the MCU's data format
  readAccelerationData(x, y, z);

  // Print the acceleration data to the serial monitor
  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" Z: "); Serial.println(z);

  delay(1000); // Delay before reading the data again
}

void readAccelerationData(int& x, int& y, int& z) {
  digitalWrite(chipSelectPin, LOW); // Select the chip
  digitalWrite(syncPin, LOW); // Set sync pin to LOW to start communication

  delayMicroseconds(10); // Add delay if necessary to stabilize the signal

  // Replace with the actual commands and data format of your MCU
  x = spi.transfer(0x2E); // Send command and read X data
  y = spi.transfer(0x30); // Send command and read Y data
  z = spi.transfer(0x32); // Send command and read Z data

  digitalWrite(syncPin, HIGH); // Set sync pin to HIGH to stop communication
  digitalWrite(chipSelectPin, HIGH); // Deselect the chip
}
