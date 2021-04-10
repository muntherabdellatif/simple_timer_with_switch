#include <Arduino.h>
#include<other.h>
#include<Timer.h>

void setup() {
pinmodefunction ();
Serial.begin(9600);
startRTC();
setRTCHour();
// setTime();  // need to delet
}
void loop() {
displayDate();
watchTimer();
watchCounter();
}