
#include <Arduino.h>
#include <SoftwareSerial.h>

// Bluetooth control pins
const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

// Motor control pin  s
#define PWMA 5
#define AIN1 3
#define AIN2 4
#define PWMB 6
#define BIN1 10
#define BIN2 9

// Setup bluetooth serial
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
char incomingData[20];
int bearing, amplitude, left, right;

float convert(float angle) {
  // Convert angle to a value between -1 and 1
  if(angle < 0) {
    angle += 360;
  }
  if(0 <= angle && angle < 90) {
    return 1;
  } else if(180 <= angle && angle < 270) {
    return -1;
  } else if(90 <= angle && angle < 180) {
    return 1 - (angle - 90) / 45;
  } else if(270 <= angle && angle <= 360) {
    return -1 + (angle - 270) / 45;
  } else {
    return 0;
  }
}


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {
  // Bluetooth data comes in ')360,100)360,100' format where the first number is the bearing and the second is the amplitude.
  if(bluetooth.available() > 0) {
    while (bluetooth.available() > 0) {
      // read max 10 bytes
      bluetooth.readBytesUntil(')', incomingData, 10);
    } 
    Serial.println(incomingData);

    sscanf(incomingData, "%d,%d", &bearing, &amplitude);
    Serial.print("Bearing: ");
    Serial.println(bearing);
    Serial.print("Amplitude: ");
    Serial.println(amplitude);

    // Reset incoming data
    memset(incomingData, 0, sizeof(incomingData));
  }

  // Move motors
  if (amplitude > 0) {
    // 0 degrees is at the right of the joystick
    // 90 degrees is at the top of the joystick

    // at 0 degrees, left motor is at full speed and right motor is at full reverse
    // at 90 degrees, both motors are at full speed
    // at 180 degrees, left motor is at full reverse and right motor is at full speed
    // at 270 degrees, both motors are at full reverse

    // Calculate motor speeds from -100 to 100
    left = 2.55 * amplitude * convert(bearing);
    right = 2.55 * amplitude * convert(bearing - 90);

    // Set motor directions
    if (left > 0) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
    } else {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
    }

    if (right > 0) {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    } else {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }

    // Set motor speeds
    analogWrite(PWMA, left);
    analogWrite(PWMB, right);

    // Write motor speeds to serial
    Serial.print("Left: ");
    Serial.println(left);
    Serial.print("Right: ");
    Serial.println(right);

  } else {
    // Stop motors
    left = 0;
    right = 0;
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
}

