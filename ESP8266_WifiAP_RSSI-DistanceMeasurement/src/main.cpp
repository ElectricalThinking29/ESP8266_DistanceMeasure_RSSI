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

const char* ssid = "ESP8266's AP";
const char* password = "ESP8266AP123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
}

void loop() {
  // put your main code here, to run repeatedly:
}
