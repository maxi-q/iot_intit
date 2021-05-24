#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>
#include <arduino.h>

const char *ssid = "TP-LINK_89AC"; 
const char *password = "88673592"; 
const char *host = "192.168.0.106:5000";  
String payload;

LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

void LiquidCristal(){
  lcd.begin(16, 2);
  lcd.print("Hello world");
}
String Get(){
  HTTPClient http; 
  String ADCData, station;
  int adcvalue=analogRead(A0); 
  ADCData = String(adcvalue); 
  station = "B";
  
  http.begin("http://127.0.0.1:5000/data");
  
  int httpCode = http.GET();
  payload = http.getString();

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();
  return payload;
  
}
void Post() {
  HTTPClient http; 

  String postData;
  postData = "momonik" ;
  
  http.begin("http://192.168.0.105:5000/");             
  http.addHeader("Content-Type", "application/json");   

  http.POST(postData);   

  String payload = http.getString();    
  Serial.println(payload);  

  http.end();  
}
void ReadJson(){


  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
 
  const char *DISLAY = doc["sensor"];


  Serial.print(DISLAY);

}
void setup() {
  Serial.begin(9600);
  delay(1000);
  
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
  ReadJson();
 

  delay(5000);
}