const int ledPin = 32; // Define the GPIO pin for the LED

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Print a message to the serial monitor
  Serial.println("GPIO 26 is blinking.");
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);

  // Wait for a second
  delay(5000);

  // Turn the LED off
  digitalWrite(ledPin, LOW);

  // Wait for a second
  delay(5000);
}