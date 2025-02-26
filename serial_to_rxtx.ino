#include <SoftwareSerial.h>

// For ESP8266 update pin definitions (using NodeMCU pin labels)
const int dirPin = 5;    // direction control pin for ESP8266
const int stepPin = 4;   // step control pin for ESP8266
const int rxPin = 12;    // RX pin for software serial
const int txPin = 13;    // TX pin for software serial

const int moveSteps = 200;    // test steps
char cmd;
int data;
int motorSpeed = 1000;

SoftwareSerial mySerial(rxPin, txPin);  // Create software serial object

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(9600);  // Initialize software serial
  mySerial.println("++++++++ ESP8266 Single-Stepper Demo ++++++++");
  mySerial.println("Please input motor command:");
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
}

void runUsrCmd() {
  switch(cmd) { 
    case 'x':  // Set motor rotation direction
      mySerial.print("Set Rotation To ");
      if (data == 0) {
        digitalWrite(dirPin, HIGH);  // HIGH means Counter Clockwise
        mySerial.println("Counter Clockwise.");
      } else {
        digitalWrite(dirPin, LOW);   // LOW means Clockwise
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
