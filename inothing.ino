//ino

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

  // Define hardware Serial pins for ESP8266
  #define ESP_RX 3  // GPIO3 (RX)
  #define ESP_TX 1  // GPIO1 (TX)
  
  // ...existing code...
  
   void setup() {
    pinMode(stepPin, OUTPUT);      // Set step pin as output
    pinMode(dirPin, OUTPUT);       // Set direction pin as output
  
    // Define hardware Serial pins for ESP8266
    #define ESP_RX 3  // GPIO3 (RX)
    #define ESP_TX 1  // GPIO1 (TX)
    
    // Initialize hardware Serial for RPi communication    //ino
    
    // For ESP8266 update pin definitions (using NodeMCU pin labels)
    const int dirPin = 5;    // direction control pin for ESP8266
    const int stepPin = 4;   // step control pin for ESP8266
    
    // Define hardware Serial pins for ESP8266
    #define ESP_RX 3  // GPIO3 (RX)
    #define ESP_TX 1  // GPIO1 (TX)
    
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
    
    // ...rest of the existing code remains the same...
    Serial.begin(115200);  // Higher baud rate for more reliable communication
    while (!Serial) {
      ; // Wait for serial port to connect
    }
    
    Serial.println("++++++++ ESP8266-RPi5 Stepper Controller ++++++++");
    Serial.println("Ready for commands from RPi5");
  }
    // Initialize hardware Serial for RPi communication
    Serial.begin(115200);  // Higher baud rate for more reliable communication
    while (!Serial) {
      ; // Wait for serial port to connect
    }
    
    Serial.println("++++++++ ESP8266-RPi5 Stepper Controller ++++++++");
    Serial.println("Ready for commands from RPi5");
  }
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

// Updated: runUsrCmd without CNC hat commands
void runUsrCmd(){
  switch(cmd){ 
    case 'x':  // Set motor rotation direction
      Serial.print("Set Rotation To ");
      if (data == 0){
        digitalWrite(dirPin, HIGH);  // swapped: now HIGH means Counter Clockwise
        Serial.println("Counter Clockwise.");
      } else {
        digitalWrite(dirPin, LOW);   // LOW means Clockwise
        Serial.println("Clockwise.");
      }
      break;
      
    // New case for upward movement
    case 'U': 
      Serial.print("Float Up with steps = ");
      Serial.println(data);
      digitalWrite(dirPin, HIGH);
      runStepper(motorSpeed, data);
      break;
      
    // New case for downward movement
    case 'D': 
      Serial.print("Float Down with steps = ");
      Serial.println(data);
      digitalWrite(dirPin, LOW);
      runStepper(motorSpeed, data);
      break;
      
    case 'z': // Run stepper for a number of steps using set motor speed
      runStepper(motorSpeed, data);
      break;
      
    case 'd': // Set motor step delay speed
      motorSpeed = data;
      Serial.print("Set Motor Speed To ");
      Serial.println(data);
      break;
      
    case '!': // Emergency Stop command
      Serial.println("Emergency Stop!");
      break;
  }
}

void runStepper (int rotationSpeed, int stepNum){
  for(int x = 0; x < stepNum; x++) {
    if (Serial.available() && Serial.peek() == '!') {
      Serial.read();  // consume emergency stop command
      Serial.println("Emergency Stop!");
      break;
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(rotationSpeed);
    yield(); // allow watchdog feeding
    digitalWrite(stepPin, LOW);
    delayMicroseconds(rotationSpeed);
    yield(); // allow watchdog feeding
  }
}
