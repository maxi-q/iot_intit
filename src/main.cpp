#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <arduino.h>




const char *ssid = "TP-LINK_89AC"; 
const char *password = "88673592"; 
const char *host = "127.0.0.1:5000";  


void Get(){
  HTTPClient http; 
  String ADCData, station, getData, Link;
  int adcvalue=analogRead(A0); 
  ADCData = String(adcvalue); 
  station = "B";


  
  http.begin("http://127.0.0.1:5000/data");
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
  delay(5000);  //GET Data at every 5 seconds
}

void Post() {
    HTTPClient http; 

  String  ADCData, station, postData, dureni;
 
  //Post Data
  postData = "momonik" ;
  
  http.begin("http://127.0.0.1:5000/data");             
  http.addHeader("Content-Type", "application/json");   

  int httpCode = http.POST(postData);   
  String payload = http.getString();    

  Serial.println(httpCode);   
  Serial.println(payload);  

  http.end();  
  delay(5000);  
}


void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);      
  delay(1000);
  WiFi.mode(WIFI_STA);        
  
  WiFi.begin(ssid, password);     
  Serial.println("");

  Serial.print("Connecting");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.status());
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
}
void loop() {
  Get();
}