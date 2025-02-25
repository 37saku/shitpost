// ...existing code...

void runStepper(int steps, bool direction) {
  digitalWrite(dirPin, direction);  // Set direction
  
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(motorSpeed);
  }
}

void runUsrCmd() {
  switch(cmd) {
    case 'F':  // Forward
      runStepper(data, HIGH);
      break;
      
    case 'B':  // Backward
      runStepper(data, LOW);
      break;
      
    case 'S':  // Set Speed (delay in microseconds)
      if(data > 0) motorSpeed = data;
      break;
      
    default:
      Serial.println("Invalid command");
      break;
  }
}

// ...existing code...
