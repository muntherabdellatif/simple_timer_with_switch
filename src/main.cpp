#include <Arduino.h>
#include<other.h>
#include<Timer.h>

void setup() {
Serial.begin(9600);
startRTC();
}

void loop() {
displayDate();
}