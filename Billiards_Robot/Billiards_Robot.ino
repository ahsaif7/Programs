#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

#define NUM_SERVOS 6

// Servo Pins
int servoPins[NUM_SERVOS] = {25, 26, 27, 14, 33, 32};

Servo servos[NUM_SERVOS];
int currentAngle[NUM_SERVOS];
int targetAngle[NUM_SERVOS];

// Angle limits (edit if a joint binds)
int minLimit[NUM_SERVOS] = {0, 0, 0, 0, 0, 0};
int maxLimit[NUM_SERVOS] = {180, 180, 180, 180, 180, 180};

// Smooth speed control
const int STEP_SIZE = 2;
const int STEP_DELAY = 5;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_RobotArm_Slider");

  Serial.println("Send: <servoNumber> <angle> (Example: 3 120)");

  for(int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    currentAngle[i] = 90;      // start at 90° neutral position
    targetAngle[i] = 90;
    servos[i].write(90);
  }
}

void loop() {

  // If data received like: "3 120"
  if (SerialBT.available()) {
    int id = SerialBT.parseInt();     // Servo index
    int angle = SerialBT.parseInt();  // Angle value

    if (id >= 1 && id <= 6) {
      int index = id - 1;
      angle = constrain(angle, minLimit[index], maxLimit[index]);
      targetAngle[index] = angle;

      Serial.printf("Servo %d -> %d°\n", id, angle);
      SerialBT.printf("OK %d %d\n", id, angle);
    }
  }

  // Smooth motion section
  for(int i = 0; i < NUM_SERVOS; i++) {
    if(currentAngle[i] != targetAngle[i]) {
      if(targetAngle[i] > currentAngle[i]) currentAngle[i] += STEP_SIZE;
      else currentAngle[i] -= STEP_SIZE;

      servos[i].write(currentAngle[i]);
      delay(STEP_DELAY);
    }
  }
}
