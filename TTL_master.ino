#include "max6675.h" // SPI
#include <Wire.h> // = I2C

const int SENSOR1 = A1;   // use A1

int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;
// int ktcCS2 = 11;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

float temp1,temp2;

void setup() {
  Serial.begin(9600);
  Wire.begin();// I2C setting
  delay(500);
}

  union first_union{  // read float x 2 : max6674
    float f=0;
    byte b[4];}
    datastm;

  union second_union{  // read float x 2 : max6674
    float f[2]={0.0 , 0.0};
    byte b[8];}
    datamts;

  union third_union{  // send integer to slave
    int z[2]={0,0};
    byte b[4];}
    datamtm;

  union fiurth_union{  // send integer to slave
    int z[2]={0,0};
    byte b[4];}
    datamtc;
  
    int i=0,j=0;

void loop() { 
   datamts.f[0]=ktc.readCelsius();
   datamts.f[1] = analogRead(SENSOR1);
   datamts.f[1]=0;  // test 171226
   Wire.beginTransmission(0); // transmit to device #0: heater
   Wire.write(datamts.b[0]);    // send one byte
   Wire.write(datamts.b[1]);    // send one byte 
   Wire.write(datamts.b[2]);    // send one byte 
   Wire.write(datamts.b[3]);    // send one byte 
   Wire.write(datamts.b[4]);    // send one byte
   Wire.write(datamts.b[5]);    // send one byte
   Wire.write(datamts.b[6]);    // send one byte
   Wire.write(datamts.b[7]);    // send one byte
   Wire.endTransmission();    // stop transmitting
   if(i>=0 && i<75) datamtm.z[0]=50.0+205.0*float(i)/75.0;
   if(i>=75 && i<150) datamtm.z[0]=255;
   if(i>=150 && i<225) datamtm.z[0]=255.0-205.0*(float(i)-150.0)/75.0;
   datamtm.z[1]=datamtm.z[0];   // we do not use another moter
   Wire.beginTransmission(1);   // transmit to device #1: motor
   Wire.write(datamtm.b[0]);    // send one byte
   Wire.write(datamtm.b[1]);    // send one byte 
   Wire.write(datamtm.b[2]);    // send one byte 
   Wire.write(datamtm.b[3]);    // send one byte 
   Wire.endTransmission();      // stop transmitting
   if(i>=0 && i<112) datamtc.z[0]=0;
   if(i>=112 && i<225) datamtc.z[0]=1;
   datamtc.z[1]=datamtc.z[0];   // we do not use another cooler   
   Wire.beginTransmission(2);   // transmit to device #2: motor
   Wire.write(datamtc.b[0]);    // send one byte
   Wire.write(datamtc.b[1]);    // send one byte 
   Wire.write(datamtc.b[2]);    // send one byte 
   Wire.write(datamtc.b[3]);    // send one byte 
   Wire.endTransmission();      // stop transmitting

  Wire.requestFrom(0,2);// request 2 bytes from Slave ID #0
  int jj=0;
  while (Wire.available()) {
    datastm.b[jj]= Wire.read();
    jj=jj+1;
    if(jj>3) jj=0;  
    }
    
   Serial.print(datamts.f[0]);
   Serial.print(" ");
   Serial.print(datastm.f); //  on/off switch for heater
   Serial.print(" ");
   Serial.print(datamts.f[1]); //  voltage of heater
   Serial.print(" ");
   Serial.print(datamtm.z[0]); //  PWM output for motor slave
   Serial.print(" ");
   Serial.println(datamtc.z[0]); //  PWM output for motor slave
   delay(200); 
   i=i+1;
   if(i>224) i=0;
}
