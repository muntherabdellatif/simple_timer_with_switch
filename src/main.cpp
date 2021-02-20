#include <Arduino.h>
#include<other.h>
#include<Timer.h>

void setup() {
pinmodefunction ();
Serial.begin(9600);
startRTC();
setRTCHour();
}
void loop() {
displayDate();
watchTimer();
watchCounter();
}