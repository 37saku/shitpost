#include <SoftwareSerial.h>

const int rxPin = 12; // RX pin for Software Serial
const int txPin = 13; // TX pin for Software Serial

SoftwareSerial mySerial(rxPin, txPin); // Create a SoftwareSerial object

void setup() {
  mySerial.begin(9600); // Start SoftwareSerial at 9600 baud
  Serial.begin(9600);   // Start the hardware serial at 9600 baud
  while (!Serial) {
    ; // Wait for the serial port to connect
  }
  Serial.println("ESP8266 Software Serial Echo Ready");
}

void loop() {
  if (mySerial.available() > 0) {
    // Read the incoming byte
    String line = mySerial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(line);  // Print the received line to the Serial Monitor
    mySerial.print("Received: ");
    mySerial.println(line); // Send the response back via Software Serial
  }
}
