// #

#include <Wire.h>
  int heaterPin=9;
  union first_union{
    float f[2] ={0.0 , 0.0};
    byte b[8];}
  datamts;
  int jj=0;

 
  union second_union{
    float f;
    byte b[4];}
  datastm;

void setup() 
{ 
    pinMode(heaterPin, OUTPUT);   
    pinMode(13, OUTPUT);
    Wire.begin(0);// Slave ID #0
    Wire.onReceive(receiveEvent);   // receive data from master
    Wire.onRequest(requestEvent);   // send data to master
    Serial.begin(9600); 
} 
float rate = 0;


void loop() 
{ 
  int value;
  Serial.print("datamts.f[0]=");
  Serial.println(datamts.f[0]); 
  Serial.print("datamts.f[1]=");
  Serial.println(datamts.f[1]); 
if (datamts.f[1] >-1.0){
if (datamts.f[0] >=40 && datamts.f[0] <=50){
  digitalWrite(heaterPin,LOW);
  digitalWrite(13, LOW);
  rate=10*(datamts.f[0]-40);
  delay(50*(50-datamts.f[0]));
  digitalWrite(heaterPin,HIGH);
  digitalWrite(13, HIGH);
  delay(50*(datamts.f[0]-40));
} else if (datamts.f[0] > 50.0){
  digitalWrite(heaterPin,HIGH);
  digitalWrite(13, HIGH);
  rate=100;
  delay(500);
} else if (datamts.f[0]<40.0) {
  digitalWrite(heaterPin,LOW);
  digitalWrite(13, LOW);
  rate=0;
  delay(500);
}}
else {
  digitalWrite(heaterPin,HIGH);
  digitalWrite(13, HIGH);
}

}

  void receiveEvent(int howMany)   /*----( LOOP: RUNS CONSTANTLY )----*/
{
    int jj=0;
//  Serial.println("start receiveEvent");
  while (Wire.available()) {
    datamts.b[jj] = Wire.read();
    jj=jj+1;
    if(jj>7) jj=0;
  }
}

void requestEvent() {
  datastm.f=rate;
  //when switch is 0 ,heater is on 
  //when switch is 1 ,heater is off
  Wire.write(datastm.b,4);  // send 2byte data to master
  Serial.print("datastm.f=");
  Serial.println(datastm.f);
}

