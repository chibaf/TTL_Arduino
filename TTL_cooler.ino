// #

#include <Wire.h>
  int coolerPin=12;
  
//  union first_union{
//    float f[2] ={0.0 , 0.0};
//    byte b[8];}
//  datamts;

  int jj=0;

 
  union sfirst_union{
    int d[2];
    byte b[4];}
    datastc;

void setup() 
{ 
    pinMode(coolerPin, OUTPUT);   
    pinMode(13, OUTPUT);
    Wire.begin(2);// Slave ID #2
    Wire.onReceive(receiveEvent);   // receive data from master
//    Wire.onRequest(requestEvent);   // send data to master
    Serial.begin(9600); 
} 
float rate = 0;


void loop() 
{ 
  int value;
  Serial.print("datastc.d[0]=");
  Serial.println(datastc.d[0]); 
//  Serial.print("datamts.f[1]=");
//  Serial.println(datamts.f[1]); 
//if (datamts.f[1] >-1.0){
if (datastc.d[0] >0){
  digitalWrite(coolerPin,LOW);
  digitalWrite(13, LOW);
  delay(100);
} else if (datastc.d[0] <1){
  digitalWrite(coolerPin,HIGH);
  digitalWrite(13, HIGH);
//  rate=100;
  delay(100);
}

//}
else {
  digitalWrite(coolerPin,HIGH);
  digitalWrite(13, HIGH);
}

}

  void receiveEvent(int howMany)   /*----( LOOP: RUNS CONSTANTLY )----*/
{
    int jj=0;
//  Serial.println("start receiveEvent");
  while (Wire.available()) {
    datastc.b[jj] = Wire.read();
    jj=jj+1;
    if(jj>3) jj=0;
  }
}

//void requestEvent() {
//  datastm.f=rate;
//  //when switch is 0 ,heater is on 
//  //when switch is 1 ,heater is off
//  Wire.write(datastm.b,4);  // send 2byte data to master
//  Serial.print("datastm.f=");
//  Serial.println(datastm.f);
//}

