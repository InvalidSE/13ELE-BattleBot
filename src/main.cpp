
#include <Arduino.h>
#include <SoftwareSerial.h>

// Bluetooth TX -> Arduino D8
// Bluetooth RX -> Arduino D7
const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  // Begin serial communication at 9600 bps
  Serial.begin(9600);

  // Begin serial communication with HM 10 at 9600 bps 
  bluetooth.begin(9600);

  // delay in case the HM 10 needs time to respond
  delay(100);
  
  Serial.println("Setup Complete");
}


void loop() {
  if(bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  if(Serial.available()) {
    bluetooth.write(Serial.read());
  }
}