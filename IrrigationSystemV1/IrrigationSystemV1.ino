//_________________________________IMPORT LIBRARY____________________________________________
#include<Arduino.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
//__________________________GPIOs PINs ARCHITECTURE _______________________________________
/* A0 ==> ANALOG INPUT
   16 ==> TEST OF CONNECTION TO WIFI
   5 ==> CHIP SELECT TO READ ------------ 
   4 ==> CHIP SELECT TO READ SIOL HUMIDITY
   0 ==> INPUT OF DHT21 SENSOR
   2 ==> CONTROLE OF POMPE OF IRRIGATION
*/
//_________________________________DECLARATION OF VARIABLES__________________________________
FirebaseData firebaseData ;
int temp1, hum1, hum2;
unsigned char stat = 0;
String sr="" ;

//________________________________NETWORK CREDENTIALS_______________________________________
const char* ssid = "HTL-WS";
const char* password = "12345678";
#define FIREBASE_HOST "https://irrigation-system-2f1bb-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "JenK4kn8SJMFPBYFvfP1KAU55KuG1x1VZOmJTqPd"

//_--_--_--_--_--_--_--_--_-- setup -_--_--_--_--_--_--_--_--_--_--_--_--_--_--
void setup() {
  //_____________________________SERIAL PORT FOR DEBUGGING PURPOSES_____________________________
  Serial.begin(115200);
  //_____JOIN I2C BUS WITH SDA=D1 AND SCL=D2_______________________
   Wire.begin(D1, D2); 
  //_____________________________CONFIGURATION OF GPIOs PINs _______________________________________
 
  pinMode(16,OUTPUT);  //D0
  pinMode(13,OUTPUT); //D7

  //___________________________CONNECT TO Wi-Fi_______________________________________________
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(16,HIGH);
    delay(1000);
    digitalWrite(16,LOW);
    delay(1000); 
  }
  //_________________________ PRINTESP LOCAL IP ADDRESS _____________________________________
  Serial.print("The IP  device : ");
  Serial.println(WiFi.localIP());
  //__________________________START THE Firebase_______________________________________________
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

//_--_--_--_--_--_--_--_--_-- loop -_--_--_--_--_--_--_--_--_--_--_--_--_--_--_

void loop() {  
  
  //_________________TEST OF CONNECTION TO WIFI _______________________________
  digitalWrite(16,HIGH);
   while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(16,HIGH);
    delay(300);
    digitalWrite(16,LOW);
    delay(300);
  }
  //_____SEND DATA TO DEVICE ADDRESS 8___________________________
 Wire.beginTransmission(8); 
 //Wire.write("Hello Arduino");  
 Wire.endTransmission();    

 delay(1000);
 //_____RECEIVE DATA FROM DEVICE ADDRESS 8___________________________
 Wire.requestFrom(8, 26); 
 
 while(Wire.available()){
   char c = Wire.read();
   sr +=c;
 }

temp1 = (sr.substring(sr.indexOf("A")+1,sr.indexOf("B"))).toInt();
stat = (sr.substring(sr.indexOf("B")+1,sr.indexOf("C"))).toInt();
hum1 = (sr.substring(sr.indexOf("C")+1,sr.indexOf("D"))).toInt();
hum2 = (sr.substring(sr.indexOf("D")+1,sr.indexOf("E"))).toInt();
  
 Serial.print("temp1=");
 Serial.println(temp1);
 Serial.print("Pompe state=");
 Serial.println(stat);
 Serial.print("humd1=");
 Serial.println(hum1);
 Serial.print("humd2=");
 Serial.println(hum2);

 //_______________________SEND DATA TO FIREBASE FUNCTION____________________
  Firebase.setString(firebaseData,"irrigationSystem/zone-1/t1" ,(String)temp1);
  Firebase.setString(firebaseData,"irrigationSystem/zone-1/h1" ,(String)hum1);
  Firebase.setString(firebaseData,"irrigationSystem/zone-1/h2" ,(String)hum2);
  Firebase.setString(firebaseData,"irrigationSystem/zone-1/stat" ,(String)stat);
}
