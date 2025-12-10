#include <Conveyor_inferencing.h>



  ledcSetup(chA1, 20000, 8);
  ledcSetup(chA2, 20000, 8);
  ledcSetup(chB1, 20000, 8);
  ledcSetup(chB2, 20000, 8);

  // Attach channels to pins
  ledcAttachPin(AIN1, chA1);
  ledcAttachPin(AIN2, chA2);
  ledcAttachPin(BIN1, chB1);
  ledcAttachPin(BIN2, chB2);

  Serial.begin(115200);
  Serial.println("Motor test starting...");
}

// helper function
void stopMotor() {
  ledcWrite(chA1, 0);
  ledcWrite(chA2, 0);
  ledcWrite(chB1, 0);
  ledcWrite(chB2, 0);
}

void forward() {
  // Motor A forward
  ledcWrite(chA1, 255);
  ledcWrite(chA2, 0);

  // Motor B forward
  ledcWrite(chB1, 255);
  ledcWrite(chB2, 0);
}

void reverse() {
  // Motor A reverse
  ledcWrite(chA1, 0);
  ledcWrite(chA2, 255);

  // Motor B reverse
  ledcWrite(chB1, 0);
  ledcWrite(chB2, 255);
}

void loop() {
  Serial.println("Forward...");
  forward();
  delay(2000);

  Serial.println("Stop...");
  stopMotor();
  delay(1000);

  Serial.println("Reverse...");
  reverse();
  delay(2000);

  Serial.println("Stop...");
  stopMotor();
  delay(1000);
}
