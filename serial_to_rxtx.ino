#include <SoftwareSerial.h>

// For ESP8266 pin definitions
const int dirPin = 5;    
const int stepPin = 4;   
const int rxPin = 12;    
const int txPin = 13;    

const int moveSteps = 200;
char cmd;
int data;
int motorSpeed = 1000;

SoftwareSerial mySerial(rxPin, txPin);

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  mySerial.println("++++++++ ESP8266 Single-Stepper Demo ++++++++");
  mySerial.println("Please input motor command:");
  Serial.println("ESP8266 Software Serial Echo Ready");
}

void loop() {
  if (mySerial.available()) {
    cmd = mySerial.read();
    mySerial.print("cmd = ");
    mySerial.print(cmd);
    mySerial.print(" , ");
    data = mySerial.parseInt();
    mySerial.print("data = ");
    mySerial.println(data);
    runUsrCmd();
  }

  if (mySerial.available() > 0) {
    // Read the incoming byte
    String line = mySerial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(line);  // Print the received line to the Serial Monitor
    mySerial.print("Received: ");
    mySerial.println(line); // Send the response back via Software Serial
  }
}

void runUsrCmd() {
  switch(cmd) { 
    case 'x':
      mySerial.print("Set Rotation To ");
      if (data == 0) {
        digitalWrite(dirPin, HIGH);
        mySerial.println("Counter Clockwise.");
      } else {
        digitalWrite(dirPin, LOW);
        mySerial.println("Clockwise.");
      }
      break;
      
    case 'U':
      mySerial.print("Float Up with steps = ");
      mySerial.println(data);
      digitalWrite(dirPin, HIGH);
      runStepper(motorSpeed, data);
      break;
      
    case 'D':
      mySerial.print("Float Down with steps = ");
      mySerial.println(data);
      digitalWrite(dirPin, LOW);
      runStepper(motorSpeed, data);
      break;
      
    case 'z':
      runStepper(motorSpeed, data);
      break;
      
    case 'd':
      motorSpeed = data;
      mySerial.print("Set Motor Speed To ");
      mySerial.println(data);
      break;
      
    case '!':
      mySerial.println("Emergency Stop!");
      break;
  }
}

void runStepper(int rotationSpeed, int stepNum) {
  for(int x = 0; x < stepNum; x++) {
    if (mySerial.available() && mySerial.peek() == '!') {
      mySerial.read();
      mySerial.println("Emergency Stop!");
      break;
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(rotationSpeed);
    yield();
    digitalWrite(stepPin, LOW);
    delayMicroseconds(rotationSpeed);
    yield();
  }
}
