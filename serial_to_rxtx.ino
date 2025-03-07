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
    St    #include <SoftwareSerial.h>
    
    // For ESP8266 update pin definitions (using NodeMCU pin labels)
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
      Serial.println("DEBUG: Serial ports initialized");
      mySerial.println("++++++++ ESP8266 Single-Stepper Demo ++++++++");
      mySerial.println("Please input motor command:");
      Serial.println("ESP8266 Software Serial Echo Ready");
    }
    
    void loop() {
      if (mySerial.available()) {
        String line = mySerial.readStringUntil('\n');
        Serial.print("DEBUG: Raw input received: ");
        Serial.println(line);
        
        mySerial.print("Received: ");
        mySerial.println(line);
    
        if (line.length() > 1) {
          cmd = line.charAt(0);
          data = line.substring(1).toInt();
          Serial.print("DEBUG: Parsed command: ");
          Serial.print(cmd);
          Serial.print(", data: ");
          Serial.println(data);
          
          mySerial.print("cmd = ");
          mySerial.print(cmd);
          mySerial.print(" , ");
          mySerial.print("data = ");
          mySerial.println(data);
          runUsrCmd();
        } else {
          Serial.println("DEBUG: Invalid command length");
        }
      }
    }
    
    void runUsrCmd() {
      Serial.print("DEBUG: Executing command: ");
      Serial.println(cmd);
      
      switch(cmd) { 
        case 'x':
          Serial.println("DEBUG: Setting rotation direction");
          mySerial.print("Set Rotation To ");
          if (data == 0) {
            digitalWrite(dirPin, HIGH);
            mySerial.println("Counter Clockwise.");
            Serial.println("DEBUG: Direction set to Counter Clockwise");
          } else {
            digitalWrite(dirPin, LOW);
            mySerial.println("Clockwise.");
            Serial.println("DEBUG: Direction set to Clockwise");
          }
          break;
          
        case 'U':
          Serial.print("DEBUG: Moving Up steps: ");
          Serial.println(data);
          mySerial.print("Float Up with steps = ");
          mySerial.println(data);
          digitalWrite(dirPin, HIGH);
          runStepper(motorSpeed, data);
          break;
          
        case 'D':
          Serial.print("DEBUG: Moving Down steps: ");
          Serial.println(data);
          mySerial.print("Float Down with steps = ");
          mySerial.println(data);
          digitalWrite(dirPin, LOW);
          runStepper(motorSpeed, data);
          break;
          
        case 'z':
          Serial.println("DEBUG: Running stepper directly");
          runStepper(motorSpeed, data);
          break;
          
        case 'd':
          Serial.print("DEBUG: Setting motor speed to: ");
          Serial.println(data);
          motorSpeed = data;
          mySerial.print("Set Motor Speed To ");
          mySerial.println(data);
          break;
          
        case '!':
          Serial.println("DEBUG: Emergency Stop triggered");
          mySerial.println("Emergency Stop!");
          break;
          
        default:
          Serial.print("DEBUG: Unknown command received: ");
          Serial.println(cmd);
          break;
      }
    }
    
    void runStepper(int rotationSpeed, int stepNum) {
      Serial.print("DEBUG: Starting stepper movement. Steps: ");
      Serial.print(stepNum);
      Serial.print(", Speed: ");
      Serial.println(rotationSpeed);
      
      for(int x = 0; x < stepNum; x++) {
        if (mySerial.available() && mySerial.peek() == '!') {
          mySerial.read();
          mySerial.println("Emergency Stop!");
          Serial.println("DEBUG: Emergency stop during stepper movement");
          break;
        }
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(rotationSpeed);
        yield();
        digitalWrite(stepPin, LOW);
        delayMicroseconds(rotationSpeed);
        yield();
        
        if (x % 50 == 0) {  // Log every 50 steps
          Serial.print("DEBUG: Steps completed: ");
          Serial.println(x);
        }
      }
      Serial.println("DEBUG: Stepper movement completed");
    }
    mySerial.println(line); // Send the response back via Software Serial

    // Parse the command and data from the received line
    if (line.length() > 1) {
      cmd = line.charAt(0);
      data = line.substring(1).toInt();
      mySerial.print("cmd = ");
      mySerial.print(cmd);
      mySerial.print(" , ");
      mySerial.print("data = ");
      mySerial.println(data);
      runUsrCmd();
    }
  }
}

void runUsrCmd() {
  switch (cmd) { 
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
  for (int x = 0; x < stepNum; x++) {
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
