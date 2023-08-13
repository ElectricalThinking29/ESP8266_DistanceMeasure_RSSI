/*

If you can, please support me on my Youtube's channel: @ElectricalThinking29
by hitting like, share and subscribe's buttons to my videos.

*** LICENSE ***

Copyright 2023 @ElectricalThinking29

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <cmath>

#define LED 2
const char* ssid = "ESP8266's AP";
const char* password = "ESP8266AP123";
float RSSI_value = 0.0;
float A = -90.71; // dBm
float n = 4.1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, HIGH);
    delay(1000);
    Serial.println("Connecting ...");
    digitalWrite(LED, LOW);
  }
  Serial.println("Connected :");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  
  Serial.println("Please place the 2 boards exactly 1 m apart then press '1' to start the calibration process.");
  delay(1000);
  while (Serial.available()<=0){
    delay(1000);
  }
  
  if (Serial.available()>0){
    char c = Serial.read();
    if (c == '1'){
      // Calculate A = RSSI at 1 m distance
      float sum = 0;
      for (int i = 0; i <= 10; i++){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
        sum += WiFi.RSSI();
        Serial.print(10*i);
        Serial.println("%");
      }
      A = (float)sum/10.0;
    }
}

  Serial.println("Now please place the 2 boards exactly 0.5 m (50 cm) apart then press '1' to continue the calibration process.");
  delay(1000);
  while (Serial.available()<=0){
    delay(1000);
  }
  if (Serial.available()>0){
    char c = Serial.read();
    if (c == '1'){

      // Get RSSI at 0.5 m distance
      float sum = 0;
      for (int i = 0; i <= 10; i++){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
        sum += WiFi.RSSI();
        Serial.print(10*i);
        Serial.println("%");
      }
      RSSI_value = (float)sum/10.0;
      n = (RSSI_value - A)/(-10 * log10(0.5));
    }
  }
  Serial.println("Calibration process completed.");
  Serial.println(n);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float sum = 0;
  for (int i = 0; i <= 10; i++){
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
    sum += WiFi.RSSI();
  } 
  RSSI_value = (float)sum/10.0;
  float distance = pow(10, (RSSI_value - A) / (- 10 * n));
  Serial.print("Distance: ");
  Serial.printf("%.8f", distance);
  Serial.println(" m");
}

/*
void loop() {
  // put your main code here, to run repeatedly:
  int sum = 0;
  for (int i = 0; i <= 10; i++){
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
    sum += WiFi.RSSI();
  }
  RSSI_value = - (float)sum/10.0;
  float distance = 0.005*RSSI_value - 0.002;
  Serial.print("Distance: ");
  Serial.printf("%.4f", distance);
  Serial.println(" m");
}
*/

/*
void loop() {
  // put your main code here, to run repeatedly:
  int sum = 0;
  for (int i = 0; i <= 10; i++){
    digitalWrite(LED, LOW);
    delay(500);
    sum += WiFi.RSSI();
    digitalWrite(LED, HIGH);
    delay(500);
  }
  RSSI_value = (float)sum/10.0;
  Serial.print("Signal strength (RSSI): ");
  Serial.printf("%.4f", RSSI_value);
  Serial.println(" dBm");
}
*/