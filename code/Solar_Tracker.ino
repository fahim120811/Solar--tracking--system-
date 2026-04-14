#include <Servo.h>

Servo servoX;  // Horizontal movement (East-West)
Servo servoY;  // Vertical movement (North-South)

const int ldrTL = A0;  // Top-Left LDR
const int ldrTR = A1;  // Top-Right LDR
const int ldrBL = A2;  // Bottom-Left LDR
const int ldrBR = A3;  // Bottom-Right LDR

int tolerance = 40;    // Adjust this value if needed

void setup() {
  servoX.attach(9);    // Pin 9 for horizontal servo
  servoY.attach(10);   // Pin 10 for vertical servo
  
  servoX.write(90);    // Start at middle position
  servoY.write(90);
  
  Serial.begin(9600);
  Serial.println("Solar Tracker Started!");
}

void loop() {
  int tl = analogRead(ldrTL);
  int tr = analogRead(ldrTR);
  int bl = analogRead(ldrBL);
  int br = analogRead(ldrBR);

  int avgTop = (tl + tr) / 2;
  int avgBottom = (bl + br) / 2;
  int avgLeft = (tl + bl) / 2;
  int avgRight = (tr + br) / 2;

  // Vertical control
  if (avgTop - avgBottom > tolerance) {
    servoY.write(constrain(servoY.read() + 2, 0, 180));
  } else if (avgBottom - avgTop > tolerance) {
    servoY.write(constrain(servoY.read() - 2, 0, 180));
  }

  // Horizontal control
  if (avgLeft - avgRight > tolerance) {
    servoX.write(constrain(servoX.read() + 2, 0, 180));
  } else if (avgRight - avgLeft > tolerance) {
    servoX.write(constrain(servoX.read() - 2, 0, 180));
  }

  delay(50);  // Small delay for smooth movement
}
