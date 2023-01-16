//___________________IMPORT LIBRARY____________________________________________
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//_____DATA STORAGE_____________________________________________
String myString = "" ;
String val1 = "--";
String val2 = "--";
String val3 = "--";
String val4 = "--";
String key[3]={"/","*","+"};
String value[3]={"","",""};

//___________________CREATE ASYNCWEBSERVER OBJECT ON PORT 80___________________
AsyncWebServer server(80);
//___________________READ TEMPERATUR___________________________________________
String readDHTTemperature(int in) {
  if(in==1){
  /*float t1 = random(1,100);
  if (isnan(t1)) {    
    return "--";
    }else {
    return String(t1);
  }*/
  return "--";
  }else if(in==2){
  /*float t2 = random(1,100);
  if (isnan(t2)) {    
    return "--";
  }else {
    return String(t2);
  }*/
  return val1 ;
  }else if(in==3){
  float t3 = random(1,100);
  if (isnan(t3)) {    
    return "--";
  }else {
    return "--";
  }
  }else if(in==4){
  float t4 = random(1,100);
  if (isnan(t4)) {    
    return "--";
  }else {
    return "--";
  }
  }else if(in==5){
  float t5 = random(1,100);
  if (isnan(t5)) {    
    return "--";
  }else {
    return "--";
  }
  }else if(in==6){
  float t6 = random(1,100);
  if (isnan(t6)) {    
    return "--";
  }else {
    return "--";
  }
  }
  
}
//___________________READ HUMIDITY____________________________________________
String readDHTHumidity(int in) {
  if(in==1){
  /*float h1 = random(1,100);
  if (isnan(h1)) {    
    return "--";
    }else {
    return String(h1);
  }*/
    return val4 ;
  }else if(in==2){
  /*float h2 = random(1,100);
  if (isnan(h2)) {    
    return "--";
  }else {
    return String(h2);
  }*/
   return val3;
  }else if(in==3){
  float h3 = random(1,100);
  if (isnan(h3)) {    
    return "--";
  }else {
    return "--";
  }
   
  }else if(in==4){
  float h4 = random(1,100);
  if (isnan(h4)) {    
    return "--";
  }else {
    return "--";
  }
  
  }else if(in==5){
  float h5 = random(1,100);
  if (isnan(h5)) {    
    return "--";
  }else {
    return "--";
  }
  }else if(in==6){
  float h6 = random(1,100);
  if (isnan(h6)) {    
    return "--";
  }else {
    return "--";
  }
  }
}
String readEtat(int in) {
  String mssg ;
  if (in==1) {
  if (digitalRead(D5) == HIGH){
    mssg = "running" ;}else{
    mssg = "off" ;}
   return mssg;
  }else if (in==2){
  if (digitalRead(D3) == HIGH){
    mssg = "running" ;}else{
    mssg = "off" ;}
   return mssg;
  }else if (in==3){
  if (digitalRead(D4) == HIGH){
    mssg = "running" ;}else{
    mssg = "off" ;}
   return mssg;
  }  
}
//_____________________
void myDecomposition(String str){
    int pos1 = str.indexOf("A");
    int pos2 = str.indexOf("B");
    int pos3 = str.indexOf("C");
    int pos4 = str.indexOf("D");
    int pos5 = str.indexOf("E");
    
    val1 = str.substring(pos1+1,pos2);
    val2 = str.substring(pos2+1,pos3);
    val3 = str.substring(pos3+1,pos4);
    val4 = str.substring(pos4+1,pos5);
}
//___________________NETWORK CREDENTIALS_______________________________________
const char* ssid = "HTL-WS";
const char* password = "12345678";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

const char* PARAM_INPUT_4 = "output";
const char* PARAM_INPUT_5 = "state";
//__________________HTML - CSS - BOOTSTRAP - JAVASCRIPT________________________
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:,">
    <!--<link rel="stylesheet" href="StyleCss.css">-->
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <style>

          #Logo1{margin-left: 40px;margin-bottom: 10px;margin-top: 10px;border-color: rgb(14, 36, 233);border-radius: 8px;box-shadow: 0 0 2px 1px rgba(27, 7, 201, 0.5);}
          #Logo2{margin-left: 110px;margin-bottom: 10px;margin-top: 10px; border-color: rgb(14, 36, 233);border-radius: 8px;box-shadow: 0 0 2px 1px rgba(27, 7, 201, 0.5);}
          #Area{text-align: center;margin-top:15px;margin-bottom: 15px;margin-left: 15px;margin-right: 15px;border-radius: 15px;}
          .dht-labels{font-style:inherit;font-family: 'Times New Roman', Times, serif;font-size: large;font-weight: 100;margin-left: 5px;margin-right: 5px;}
          .units{font-family: 'Times New Roman', Times, serif;font-size: large;margin-left: 5px;}
          .var{ border-color: rgb(10, 119, 207); box-shadow: 0 0 2px 3px rgba(10, 177, 228, 0.5); }
          .etat{font-size: large; font-family: 'Times New Roman', Times, serif;text-align: start;}
          .titel1{border-radius: 6px;width: 110px; margin-top: 10px;margin-left: 101px;}
          .switch {position: relative; display: inline-block; width: 60px; height: 30px} 
          .switch input {display: none}
          .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: rgb(238, 27, 20); border-radius: 6px}
          .slider:before {position: absolute; content: ""; height: 20px; width: 22px; left: 3px; bottom: 5px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
          input:checked+.slider {background-color: #2dca18}
          input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(29px)}

          @media screen and (max-width: 900px) {
              #Area{ margin-left: 30px; margin-right: 30px; width: 350px;}
              #Logo1{ margin-left: 2px; width:70px ;}
              #Logo2{margin-left: 0px;width: 80px;}
          }

    </style>
    <title>Irrigation System</title>
</head>
<body>
    <div class="content">
        <div class="row justify-content-center bg-secondary" style="height: 100px;">
            <div class="col-3 align-left "> <img id="Logo1" src="https://st2.depositphotos.com/8645502/11508/v/950/depositphotos_115088076-stock-illustration-water-irrigation-logo.jpg" alt="Connexion Faild!" width="100" height="80"></div>
            <div class="col-6 text-light" style="text-align:center; font-size: x-large; font-family: 'Times New Roman', Times, serif; margin-top: 20px;">Automatic Irrigation System</div>
            <div class="col-3 " ><img id="Logo2" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR6GMGVKPpIqG3hUI7t5kKVxgyaZ2e1RzliYU7O1zCW5cfYCv89w8aCjDBfw8eslZ3wVA&usqp=CAU" alt="Connexion Faild!" width="190" height="80"></div>
        </div><br>
        <div class="row justify-content-center bg-info">
            <!--------------------The area 1----------------->
            <div class="col-xl-3 col-lg-3 col-md-4  col-sm-5 bg-light" id="Area" >
                <h6 class="titel1 text-light bg-info">The area 1</h6><br>
                <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a; margin-right: 5px;"></i> Temperature</h6>
                <div class=" col-12 " style="text-align: start;">
                    <p>
                        <i class="fas fa-thermometer-half" style="color:#f3900e;"></i> 
                        <span class="dht-labels text-primary ">Soil Temperature:</span> 
                        <span class=" var text-danger" id="temperature1">%TEMPERATURE1%</span>
                        <sup class="units  text-danger">&deg;C</sup>
                    </p>
                    <p>
                        <i class="fas fa-thermometer-half" id="Icon" style="color:#00FFFF;"></i> 
                        <span class="dht-labels text-primary">Air Temperature:&nbsp;</span> 
                        <span class="var text-danger" id="temperature2">%TEMPERATURE2%</span>
                        <sup class="units  text-danger">&deg;C</sup>
                    </p>
                </div><br>
                <h6 class="text-warning"> <i class="fas fa-tint" style="color:#00add6; margin-right: 5px;"></i>Humidity</h6>
                <div class="col-12" style="text-align: start;">
                    <p>
                        <i class="fas fa-tint" style="color:#f3900e;"></i> 
                        <span class="dht-labels text-primary">Soil Humidity:&nbsp;&nbsp;&nbsp;</span>
                        <span class="var  text-danger" id="humidity1">%HUMIDITY1%</span>
                        <sup class="units  text-danger">&percnt;</sup>
                    </p>
                    <p>
                        <i class="fas fa-tint" style="color: #00FFFF;"></i> 
                        <span class="dht-labels text-primary">Air Humidity:&nbsp;&nbsp;&nbsp;&nbsp;</span>
                        <span class=" var text-danger" id="humidity2">%HUMIDITY2%</span>
                        <sup class="units text-danger">&percnt;</sup>
                    </p>
                </div><br>
                <h6 class="text-warning"> Pump Control</h6>
                <div class="row justify-content-center">
                  <div class="col-4"> 
                    <label class="switch" >
                      <input type=checkbox onchange=toggleCheckbox(this) id=14  + outputState(14) +>
                      <span class=slider></span>
                  </label></div>
                  <div class="col-8"><p>
                      <span class="text-primary etat ">The pump 1 is</span>
                      <span class="text-primary etat" id="etat1" >%ETAT1%</span>
                    </p></div>
                </div><br>
                <h6 class="text-warning">Send A Message</h6>
                <form action="/get">
                     <input class="bg-warning text-primary" type="text" name="input1" style="width: 220px;" placeholder="send message to the area 1">
                    <input class="bg-success" type="submit" value="Send">
                </form><br><br>
            </div>
            <!--------------------The area 2----------------->
            <div class="col-xl-3 col-lg-3  col-md-4 col-sm-5 bg-light" id="Area" >
              <h6 class=" titel1 text-light bg-info">The area 2</h6><br>
              <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a; margin-right: 5px;"></i> Temperature</h6>
              <div class=" col-12 " style="text-align: start;"><p>
                      <i class="fas fa-thermometer-half" style="color:#f3900e;"></i> 
                      <span class="dht-labels text-primary ">Soil Temperature:</span> 
                      <span class=" var text-danger" id="temperature3">%TEMPERATURE3%</span>
                      <sup class="units  text-danger">&deg;C</sup>
                  </p>
                  <p>
                      <i class="fas fa-thermometer-half" id="Icon" style="color:#00FFFF;"></i> 
                      <span class="dht-labels text-primary">Air Temperature:&nbsp;</span> 
                      <span class="var text-danger" id="temperature4">%TEMPERATURE4%</span>
                      <sup class="units  text-danger">&deg;C</sup>
                  </p></div><br>
              <h6 class="text-warning"> <i class="fas fa-tint" style="color:#00add6; margin-right: 5px;"></i>Humidity</h6>
              <div class="col-12" style="text-align: start;"><p>
                      <i class="fas fa-tint" style="color:#f3900e;"></i> 
                      <span class="dht-labels text-primary">Soil Humidity:&nbsp;&nbsp;&nbsp;</span>
                      <span class="var  text-danger" id="humidity3">%HUMIDITY3%</span>
                      <sup class="units  text-danger">&percnt;</sup>
                  </p>
                  <p>
                     <i class="fas fa-tint" style="color: #00FFFF;"></i> 
                      <span class="dht-labels text-primary">Air Humidity:&nbsp;&nbsp;&nbsp;&nbsp;</span>
                      <span class=" var text-danger" id="humidity4">%HUMIDITY4%</span>
                      <sup class="units text-danger">&percnt;</sup>
                  </p></div><br>
              <h6 class="text-warning"> Pump Control</h6>
              <div class="row justify-content-center">
                <div class="col-4"> 
                  <label class="switch" >
                    <input type=checkbox onchange=toggleCheckbox(this) id=0  + outputState(0) +>
                    <span class=slider></span>
                </label></div>
                <div class="col-8"><p>
                    <span class="text-primary etat ">The pump 2 is</span>
                    <span class="text-primary etat" id="etat2" >%ETAT2%</span>
                  </p></div>
              </div><br>
              <h6 class="text-warning">Send A Message</h6>
              <form action="/get">
               
                   <input class="bg-warning text-primary" type="text" name="input2" style="width: 220px;" placeholder="send message to the area 2">
                  <input class="bg-success" type="submit" value="Send">
              </form><br><br>
            </div>
              <!--------------------The area 3----------------->
            <div class="col-xl-3 col-lg-3  col-md-4 col-sm-5 bg-light" id="Area">
              <h6 class=" titel1 text-light bg-info" >The area 3</h6><br>
              <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a; margin-right: 5px;"></i> Temperature</h6>
              <div class=" col-12 " style="text-align: start;"><p>
                      <i class="fas fa-thermometer-half" style="color:#f3900e;"></i> 
                      <span class="dht-labels text-primary ">Soil Temperature:</span> 
                      <span class=" var text-danger" id="temperature5">%TEMPERATURE5%</span>
                      <sup class="units  text-danger">&deg;C</sup>
                  </p>
                  <p>
                      <i class="fas fa-thermometer-half" id="Icon" style="color:#00FFFF;"></i> 
                      <span class="dht-labels text-primary">Air Temperature:&nbsp;</span> 
                      <span class="var text-danger" id="temperature6">%TEMPERATURE6%</span>
                      <sup class="units  text-danger">&deg;C</sup>
                  </p>
              </div><br>
              <h6 class="text-warning"> <i class="fas fa-tint" style="color:#00add6; margin-right: 5px;"></i>Humidity</h6>
              <div class="col-12" style="text-align: start;"><p>
                      <i class="fas fa-tint" style="color:#f3900e;"></i> 
                      <span class="dht-labels text-primary">Soil Humidity:&nbsp;&nbsp;&nbsp;</span>
                      <span class="var  text-danger" id="humidity5">%HUMIDITY5%</span>
                      <sup class="units  text-danger">&percnt;</sup>
                  </p>
                  <p>
                      <i class="fas fa-tint" style="color: #00FFFF;"></i> 
                      <span class="dht-labels text-primary">Air Humidity:&nbsp;&nbsp;&nbsp;&nbsp;</span>
                      <span class=" var text-danger" id="humidity6">%HUMIDITY6%</span>
                      <sup class="units text-danger">&percnt;</sup>
                  </p></div><br>
              <h6 class="text-warning"> Pump Control</h6>
              <div class="row justify-content-center">
                <div class="col-4"> <label class="switch" >
                    <input type=checkbox onchange=toggleCheckbox(this) id=2  + outputState(2) +>
                    <span class=slider></span></label></div>
                <div class="col-8"><p>
                    <span class="text-primary etat ">The pump 3 is</span>
                    <span class="text-primary etat" id="etat3" >%ETAT3%</span>
                  </p></div>
              </div>
              <br>
              <h6 class="text-warning">Send A Message</h6>
              <form action="/get">
                   <input class="bg-warning text-primary" type="text" name="input3" style="width: 220px;" placeholder="send message to the area 3">
                  <input class="bg-success" type="submit" value="Send">
              </form><br><br>
            </div>
        </div>
      </div>
<script>function toggleCheckbox(element) {
        var xhr = new XMLHttpRequest();
        if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
        else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
        xhr.send();} </script>

<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
</body>
<script>
//_________________temperature1_temperature2_temperature3_temperature4_temperature5_temperature6_____________________________________
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature1", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature2", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature3").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature3", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature4").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature4", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature5").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature5", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature6").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature6", true);
  xhttp.send();
}, 10000 ) ;
//_________________humidity1_humidity2_humidity3_humidity4_humidity5_humidity6_____________________________________
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity1", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity2", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity3").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity3", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity4").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity4", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity5").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity5", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity6").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity6", true);
  xhttp.send();
}, 10000 ) ;
//_________________etat1_etat2_etat3_____________________________________
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("etat1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/etat1", true);
  xhttp.send();
}, 1000 );
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("etat2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/etat2", true);
  xhttp.send();
}, 1000 );
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("etat3").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/etat3", true);
  xhttp.send();
}, 1000 );

</script>
</html>
)rawliteral";

//____________PROCESSOR FOR REPLACE VARIABEL IN WEB PAGE_______________________
String processor(const String& var){
  if(var == "TEMPERATURE1"){
    return readDHTTemperature(1);
  }else if(var == "TEMPERATURE2"){
    return readDHTTemperature(2);
  }else if(var == "TEMPERATURE3"){
    return readDHTTemperature(3);
  }else if(var == "TEMPERATURE4"){
    return readDHTTemperature(4);
  }else if(var == "TEMPERATURE5"){
    return readDHTTemperature(5);
  }else if(var == "TEMPERATURE6"){
    return readDHTTemperature(6);
  }
  else if(var == "HUMIDITY1"){
    return readDHTHumidity(1);
  }else if(var == "HUMIDITY2"){
    return readDHTHumidity(2);
  }else if(var == "HUMIDITY3"){
    return readDHTHumidity(3);
  }else if(var == "HUMIDITY4"){
    return readDHTHumidity(4);
  }else if(var == "HUMIDITY5"){
    return readDHTHumidity(5);
  }else if(var == "HUMIDITY6"){
    return readDHTHumidity(6);
  }
  else if (var == "ETAT1"){
    return readEtat(1);
  };
  return String();
}
//_______________
String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}
//____________SEND 'Page Not found' IF CONNEXION FAILDE________________________
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}
//___________SETUP() FUNCTION__________________________________________________
void setup() {
  //____________SERIAL PORT FOR DEBUGGING PURPOSES_____________________________
  Serial.begin(115200);
  //_____JOIN I2C BUS WITH SDA=D1 AND SCL=D2_______________________
   Wire.begin(D1, D2);
  //________GPIO SETUP_________________________________________________________
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  
 
  //____________CONNECT TO Wi-Fi_______________________________________________
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(16,HIGH);
    delay(300);
    digitalWrite(16,LOW);
    delay(300);
    Serial.println("Connecting to WiFi..");
  }
  //___________ PRINTESP LOCAL IP ADDRESS _____________________________________
  Serial.println(WiFi.localIP());
  //_______________SEND WEB PAGE[index_html AND processor]_____________________
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(1).c_str());
  });
  server.on("/temperature2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(2).c_str());
  });
   server.on("/temperature3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(3).c_str());
  });
  server.on("/temperature4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(4).c_str());
  });
   server.on("/temperature5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(5).c_str());
  });
  server.on("/temperature6", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature(6).c_str());
  });

  server.on("/humidity1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(1).c_str());
  });
  server.on("/humidity2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(2).c_str());
  });
  server.on("/humidity3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(3).c_str());
  });
  server.on("/humidity4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(4).c_str());
  });
  server.on("/humidity5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(5).c_str());
  });
  server.on("/humidity6", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity(6).c_str());
  });

  server.on("/etat1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readEtat(1).c_str());
  });
  server.on("/etat2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readEtat(2).c_str());
  });
  server.on("/etat3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readEtat(3).c_str());
  });
  //___________SEND A GET REQUEST______________________________________________
  //________________ REQUEST-1 ________________________________________________
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    String inputMessage3;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
      inputMessage3 = "No message sent";
      inputParam = "none";
    }
    value[0] = inputMessage1;
    value[1] = inputMessage2;
    value[2] = inputMessage3;
    Serial.println(inputMessage1);
    Serial.println(inputMessage2);
    Serial.println(inputMessage3);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage1 +
                                     "<br><a href=\"/\">Return to Home Page</a>");

  });
  //________________ REQUEST-2 ________________________________________________
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage4;
    String inputMessage5;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_4) && request->hasParam(PARAM_INPUT_5)) {
      inputMessage4 = request->getParam(PARAM_INPUT_4)->value();
      inputMessage5 = request->getParam(PARAM_INPUT_5)->value();
      digitalWrite(inputMessage4.toInt(), inputMessage5.toInt());
    }
    else {
      inputMessage4 = "No message sent";
      inputMessage5 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage4);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage5);
    request->send(200, "text/plain", "OK");
  });

  //________________START THE SERVER___________________________________________
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
 //_____SEND DATA TO DEVICE ADDRESS 8___________________________
 Wire.beginTransmission(8); 
 Wire.write("Hello Arduino");  
 Wire.endTransmission();    

 delay(1000);
 //_____RECEIVE DATA FROM DEVICE ADDRESS 8___________________________
 Wire.requestFrom(8, 26); 
 myString="" ;
 while(Wire.available()){
   char c = Wire.read();
   myString +=c;
 }
 //Serial.println(myString);
 myDecomposition(myString);
  
 Serial.print("A=");
 Serial.println(val1);
 Serial.print("B=");
 Serial.println(val2);
 Serial.print("C=");
 Serial.println(val3);
 Serial.print("D=");
 Serial.println(val4);
  
}
