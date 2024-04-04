#include <wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime RTCdata;

void setup() {
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__)
  Serial.begin(9600); //debug
  Serial.println("initialized RTC module"); //debug
}

void loop() {
  RTCdata = clock.getDateTime(); // Note for whoever is writing the LCD CODE:
                                 //    Call the data of the the rtc by using 
                                 //    RTCdata.year, .month, .day, .hour, and so on
  Serial.print("TIME: %i-%i %i:%i:%i\n", RTCdata.year, RTCdata.month, RTCdata.day,
                       RTCdata.hour, RTCdata.minute, RTCdata.minute, RTCdata.second); //debug
  int hours   = RTCdata.hour;
  int mins    = RTCdata.minute;
  int seconds = RTCdata.second;
}
