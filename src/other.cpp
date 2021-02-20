#include<other.h>
#include<Timer.h>
#include<Arduino.h>
// variabels
extern byte onHour;
extern byte onPeriod;
extern byte sethour;
// functions
void pinmodefunction (){
pinMode(hoursw1,INPUT_PULLUP);
pinMode(hoursw2,INPUT_PULLUP);
pinMode(hoursw3,INPUT_PULLUP);
pinMode(hoursw4,INPUT_PULLUP);
pinMode(hoursw5,INPUT_PULLUP);
pinMode(periodsw1,INPUT_PULLUP);
pinMode(periodsw2,INPUT_PULLUP);
pinMode(periodsw3,INPUT_PULLUP);
pinMode(periodsw4,INPUT_PULLUP);
pinMode(instrument,OUTPUT);
}
void readHourSwitchs () {
    byte hour=0;
    if (digitalRead(hoursw1)==0){hour=hour+1;}
    if (digitalRead(hoursw2)==0){hour=hour+2;}
    if (digitalRead(hoursw3)==0){hour=hour+4;} 
    if (digitalRead(hoursw4)==0){hour=hour+8;}
    if (digitalRead(hoursw5)==0){hour=hour+16;}
if (hour!=0){onHour=hour;}
}
void readPeriodSwitch(){
      byte period=0;
      byte minPeriod=5;
    if (digitalRead(periodsw1)==0){period=period+minPeriod;}
    if (digitalRead(periodsw2)==0){period=period+minPeriod*2;}
    if (digitalRead(periodsw3)==0){period=period+minPeriod*4;} 
    if (digitalRead(periodsw4)==0){period=period+minPeriod*8;}
onPeriod=period; 
}
