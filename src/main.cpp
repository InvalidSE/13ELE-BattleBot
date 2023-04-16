
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

    if(bearing >= 0 && bearing <= 90) {
      // Turn right
      left = amplitude;
      right = amplitude - (amplitude * (bearing / 90.0));
      // Set both motors to forward
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    } else if(bearing > 90 && bearing <= 180) {
      // Turn left
      left = amplitude - (amplitude * ((bearing - 90) / 90.0));
      right = amplitude;
      // Set both motors to forward
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    } else if(bearing > 180 && bearing <= 270) {
      // Turn left
      left = amplitude - (amplitude * ((bearing - 180) / 90.0));
      right = amplitude;
      // Set both motors to reverse
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    } else if(bearing > 270 && bearing <= 360) {
      // Turn right
      left = amplitude;
      right = amplitude - (amplitude * ((bearing - 270) / 90.0));
      // Set both motors to reverse
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }

    if(amplitude == 0) {
      // Stop motors
      left = 0;
      right = 0;
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }

    // Set motor speeds
    analogWrite(PWMA, left);
    analogWrite(PWMB, right);

  }
}