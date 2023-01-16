#include <Wire.h>
#include <stdio.h>
#include <DHT.h>

String key[4]={"A","B","C","D"};
String valueSend[4]={"","----","",""};

String valueReceive[4]={"","","",""};

String myString="" ;
String sendVar ="";

String messg1;
String messg2;
String messg3;

float humd1 = 0.0 ,humd2 = 0.0 ,temp1 = 0.0 ,pourC;

unsigned char stat = 0 , usCmd = 0;
//________________________________CONFIGURATION ___________________________________________
#define DHTPIN 5            
#define DHTTYPE DHT21       
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 //_____________________________CONFIGURATION OF GPIOs PINs _______________________________________
  pinMode(A0,INPUT);
  pinMode(5,INPUT);
  pinMode(7,OUTPUT);
  pinMode(9,INPUT);
 //_________join i2c bus with address 8___________________
 Wire.begin(8);
 //_________register receive event # register request event               
 Wire.onReceive(receiveEvent); 
 Wire.onRequest(requestEvent);
 //________start serial for debug________________________ 
 Serial.begin(115200);          
}
void loop() {
 
   
  if (pourC < 50){
    digitalWrite(7,HIGH);
    stat = 1;
  }else{
    digitalWrite(7,LOW);
    stat = 0;
  }
  //-----------------------

 pourC = map(humd2,4,679,0,100) ;
  
 valueSend[0]= String(temp1) ;
 valueSend[1]= String(stat) ;
 valueSend[2]= String(humd1) ;
 valueSend[3]= String(pourC) ;
 Serial.print("temp1 = ");
 Serial.println(temp1);
 Serial.print("humd1 = ");
 Serial.println(humd1);
 Serial.print("humd2 = ");
 Serial.println(pourC);
  readSensor();
  myDecomposition(myString);
  if (messg1.length()>1){
    valueReceive[0] = messg1;
  }else if(messg2.length()>1){
    valueReceive[1] = messg2;
  }else if(messg3.length()>1){
    valueReceive[2] = messg3;
  }
  //Serial.print("messag1= ");
  //Serial.println(valueReceive[0]);
  //Serial.print("messag2= ");
  //Serial.println(valueReceive[1]);
  //Serial.print("messag3= ");
  //Serial.println(valueReceive[2]);
  
}

//____function that executes whenever data is received from master
void receiveEvent(int howMany) {
 myString="" ;
 while (0 <Wire.available()) {
    char c = Wire.read();      
    myString +=c;
  }  
  //Serial.println(myString);           
}

//___function that executes whenever data is requested from master
void requestEvent() {
  for (int i = 0; i <4; i++) {
    sendVar = key[i];
    Wire.print(sendVar);
    sendVar = valueSend[i];
    Wire.print(sendVar);
  }
  sendVar ="E";
  Wire.print(sendVar);
}

void myDecomposition(String str){
    int pos1 = str.indexOf("/");
    int pos2 = str.indexOf("*");
    int pos3 = str.indexOf("+");
    int pos4 = str.indexOf("#");
    
    messg1 = str.substring(pos1+1,pos2);
    messg2 = str.substring(pos2+1,pos3);
    messg3 = str.substring(pos3+1,pos4);
}
void readSensor(){
  float h1 = dht.readHumidity();
  float h2 = analogRead(A0);
  float t1 = dht.readTemperature();
  if (isnan(h1)) {    
    
  }else {
    humd1 = h1;
  }

  if (isnan(h2)) {    
    
  }else {
    humd2 = h2 ;
  }

  if (isnan(t1)) {    
    
  }else {
    temp1 = t1 ;
  }
}