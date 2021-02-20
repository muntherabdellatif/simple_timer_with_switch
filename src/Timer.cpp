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
byte setyear=21,setmonth=1,setday=16,sethour=12,setmin=30; 
byte onHour=10;
byte onMin=30;
byte onPeriod=2;
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
                 Serial.print("/");      Serial.println(currentTime.Year()); }
  else           {Serial.print("time"); if (currentTime.Hour()<10)  {Serial.print("0");}Serial.print(currentTime.Hour()); 
                  Serial.print(":");     if (currentTime.Minute()<10){Serial.print("0");}Serial.print(currentTime.Minute());
                  Serial.print(":");     if (currentTime.Second()<10){Serial.print("0");}Serial.println(currentTime.Second());}
  }
}
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