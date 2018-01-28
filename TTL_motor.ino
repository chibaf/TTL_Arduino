// # Editor     : Lauren from DFRobot
// # Date       : 17.02.2012

// # Product name: L298N motor driver module DF-MD v1.3
// # Product SKU : DRI0002
// # Version     : 1.0

// # Description:
// # The sketch for using the motor driver L298N
// # Run with the PWM mode

// # Connection:
// #        M1 pin  -> Digital pin 4
// #        E1 pin  -> Digital pin 5
// #        M2 pin  -> Digital pin 7
// #        E2 pin  -> Digital pin 6
// #        Motor Power Supply -> Centor blue screw connector(5.08mm 3p connector)
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// # 
// # Note: You should connect the GND pin from the DF-MD v1.3 to your MCU controller. They should share the GND pins.
// #

#include <Wire.h>

int E1 = 5;
int M1 = 4;
int E2 = 6;                         
int M2 = 7;                           

  union first_union{
    int z[2];
    byte b[4];}
  datamtm;
  int jj=0;
  char b2[4];
  char b1;

void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
    Wire.begin(1);// Slave ID #1
    Wire.onReceive(receiveEvent);
    Serial.begin(9600);
} 

void loop() 
{ 
  int value;

    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, datamtm.z[0]);   //PWM Speed Control
    analogWrite(E2, datamtm.z[1]);   //PWM Speed Control
    Serial.print("datamtm.z[0]=");
    Serial.println(datamtm.z[0]);
    Serial.print("datamtm.z[1]=");
    Serial.println(datamtm.z[1]);
//    delay(30); 
// we do not use another moter 
// so we do not use datamtmz[1]
}
  void receiveEvent(int howMany)   /*----( LOOP: RUNS CONSTANTLY )----*/
{
    int jj=0;
//  Serial.println("start receiveEvent");
  while (Wire.available()) {
    datamtm.b[jj] = Wire.read();
    jj=jj+1;
    if(jj>3) jj=0;
  }
    Serial.print("datamtm.z[0]=");
    Serial.println(datamtm.z[0]);
    Serial.print("datamtm.z[1]=");
    Serial.println(datamtm.z[1]);

}
