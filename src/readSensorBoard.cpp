/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <HardwareSerial.h>

char raw[3];
char data[3];
char uartbuf[32];
signed char frame[4];
int cnt,i;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(PC13, OUTPUT);
  Serial1.begin(57600,SERIAL_9N1);
//  Serial1.begin(26320,SERIAL_9N1);
  Serial2.begin(115200);
  Serial2.write("Copy Data from Serial1 to Serial2");
}
// LS closed
// A5 = 1010 0101
// B5 = 1011 0101

// LS open
// 4A = 0100 1010
// 5A = 0101 1010

void loop()
{
  if(Serial1.available()) {
    Serial1.readBytes(data,2);
    if(*data == 0xb8 ) {
      digitalWrite(PC13, LOW);
      for(i=0;i<4;i++) {
        while(!Serial1.available());
        Serial1.readBytes(data,2);
        frame[i] = (int)*data;
      }
      sprintf(uartbuf,"%04d_%04d_%04d_%04d|", frame[0],frame[1],frame[2],frame[3]);
      Serial2.write(uartbuf);
      if(cnt++ % 4 == 0 ) {
        Serial2.write("\r\n");
      }
      digitalWrite(PC13, HIGH);
    }
  }
}

