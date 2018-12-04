/*
 *  The purpose of this file to put the HC-05 in AT MODE,
 *  We can do this by connecting HC-05 RX,TX,VCC,GND to 
 *  Arduinos pin 11, pin 10, VCC, GND respectively.  Also before connecting VCC,
 *  We need to have EN connected to VCC and hold the button down.  After connecting VCC, we can let
 *  go of the button and disconnect the EN.
 *  This should put us in AT MODE
 *  
 *  
 *  // follow the tutorial http://blog.zakkemble.co.uk/getting-bluetooth-modules-talking-to-each-other/
 *  The following commands are useful
 *  AT
 *  AT+MODE?
 *  AT+MODE=1 (connect to any device)
 *  AT+MODE=0 (connect to paired devices only)
 *  AT+PSWD=1234 (Set password, its all at 1234 for now) same as slave for master
 *  AT+NAME=MYBT
 *  AT+UART=115200,1,0 (baudrate,stopbit,parity)
 *  AT+ORGL default setting
 *  AT+ROLE=1(master = 1, slave = 0)
 *  AT+RESET after changing role
 *  AT+INQM=0,5,5   (standard,stop after 5 devices found, or after 5 seconds)
 *  AT+INIT to initalize any bluetooth transmitting/receive 
 *  AT+INQ start searching
 */


#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
Serial.begin(38400);
Serial.println("Goodnight moon!");
//mySerial.begin(115200);
//mySerial.begin(115200);
mySerial.begin(38400);

}

void loop() // run over and over
{
if (mySerial.available())
Serial.write(mySerial.read());
if (Serial.available())
mySerial.write(Serial.read());
//static int counter = 0;
//delay(100);
//counter++;
//Serial.println(counter);
}

//void setup() {}
//void loop() {}
