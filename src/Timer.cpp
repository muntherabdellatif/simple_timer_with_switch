#include<Timer.h>
#include<other.h>
#include <Arduino.h>
//object 
RtcDS3231<TwoWire> rtcObject(Wire); //Uncomment for version 2.0.0 of the rtc library
// variabils
byte RTCday=0;
byte RTCsec=0;      // display date  
byte lastRTCsec=0;  // display date
byte RTCsec2=0;     // cpunter  
byte lastRTCsec2=0; // counter
bool timedis;
byte seccounter;  
byte RTCmin=0;     
byte lastRTCmin=0; 
byte setyear=21,setmonth=1,setday=16,sethour=2,setmin=0;
byte onHour=0;
byte onPeriod=0;
byte nextProgMin=0;
byte nextProgHour=0;
byte countDownMin=0;
byte countDownSec=0;
// functions 
void displayDate(){
 RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC (new)
   RTCsec=currentTime.Second(); 
  if (!(lastRTCsec==RTCsec)){
  seccounter++;
   if (seccounter==5){timedis=!timedis;seccounter=0;}
   lastRTCsec=RTCsec;
  if (timedis==1){Serial.print("date"); if (currentTime.Day()<10){Serial.print("0");}   Serial.print(currentTime.Day());
                 Serial.print("/");      if (currentTime.Month()<10){Serial.print("0");} Serial.print(currentTime.Month()); 
                 Serial.print("/");      Serial.print(currentTime.Year()); }
  else           {Serial.print("time"); if (currentTime.Hour()<10)  {Serial.print("0");}Serial.print(currentTime.Hour()); 
                  Serial.print(":");     if (currentTime.Minute()<10){Serial.print("0");}Serial.print(currentTime.Minute());
                  Serial.print(":");     if (currentTime.Second()<10){Serial.print("0");}Serial.print(currentTime.Second());}
  readHourSwitchs();
  Serial.print("On hour :"); Serial.print(onHour);
  readPeriodSwitch();
  Serial.print("on period:");Serial.print(onPeriod);
  Serial.print("counter :"); Serial.print(countDownMin);
  Serial.print(":"); Serial.println(countDownSec);
}}
void startRTC(){
  rtcObject.Begin();     //Starts I2C
  RtcDateTime currentTime ; //define date and time object
  currentTime = rtcObject.GetDateTime();    //get the time from the RTC
}
void setTime(){
  rtcObject.Begin();    //Starts I2C
  RtcDateTime currentTime = RtcDateTime(setyear,setmonth,setday,sethour,setmin,0); //define date and time object
  rtcObject.SetDateTime(currentTime); //configure the RTC with object
  currentTime = rtcObject.GetDateTime();    //get the time from the RTC 
}
void setRTCHour (){
   readHourSwitchs();
   readPeriodSwitch();
   if (onPeriod==0){sethour=onHour;setTime();
                    Serial.print("RTC new hour is :");Serial.println(sethour);}
}
void watchTimer(){
 RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC (new)
if (digitalRead(instrument)==0){
   if (currentTime.Hour()==onHour && currentTime.Minute()==0 ){
   digitalWrite(instrument,1);setCounter();
 } }
 if (digitalRead(heater)==1) {
   if (currentTime.Hour()==(onHour-1) && currentTime.Minute()==55 ){
   digitalWrite(heater,0);setCounter();
 } }
}
void setCounter(){
 RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC   
 if ((currentTime.Minute()+onPeriod)<60){
       nextProgMin=0+onPeriod;
       nextProgHour=onHour;}
 else {nextProgMin=(0+onPeriod)%60;
       nextProgHour=onHour+1;} 
     countDownMin=abs(abs((currentTime.Hour()-nextProgHour ))*60 + abs(currentTime.Minute()- nextProgMin)-1) ;
     countDownSec=59;
}
void watchCounter(){
if (digitalRead(instrument)==1){
   RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC (new)
  RTCsec2=currentTime.Second(); 
  if (!(lastRTCsec2==RTCsec2)){
  if (countDownSec>0){countDownSec=countDownSec-1;} else {countDownSec=59;countDownMin=countDownMin-1;}
  lastRTCsec2=RTCsec2;
  }
if (countDownSec==0 && countDownMin==0){
    digitalWrite(instrument,0);digitalWrite(heater,1);
    countDownSec=0;countDownMin=0; } // pump off 
  }
}