//ino

// Define hardware Serial pins for ESP8266
#define ESP_RX 3  // GPIO3 (RX)
#define ESP_TX 1  // GPIO1 (TX)

// For ESP8266 update pin definitions (using NodeMCU pin labels)
const int dirPin = 5;    // direction control pin for ESP8266
const int stepPin = 4;   // step control pin for ESP8266

const int moveSteps = 200;    // test steps
char cmd;
int data;
int motorSpeed = 1000;

void setup() {
  pinMode(stepPin, OUTPUT);      // Set step pin as output
  pinMode(dirPin, OUTPUT);       // Set direction pin as output
  
  // Initialize hardware Serial for RPi communication
  Serial.begin(115200);  // Higher baud rate for more reliable communication
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("++++++++ ESP8266-RPi5 Stepper Controller ++++++++");
  Serial.println("Ready for commands from RPi5");
}

void loop() {
  if (Serial.available()) {
    cmd = Serial.read();
    Serial.print("cmd = ");
    Serial.print(cmd);
    Serial.print(" , ");
    data = Serial.parseInt();
    Serial.print("data = ");
    Serial.println(data);
    runUsrCmd();
  }
}

// ...existing code for runUsrCmd() and runStepper() functions...
