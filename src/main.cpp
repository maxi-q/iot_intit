#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <arduino.h>
#include <LiquidCrystal.h>
#include <string>
#include <TroykaDHT.h>

#define DHTPIN 8
#define led 6

class DHT dht(DHTPIN, DHT11);
LiquidCrystal lcd(D6, D7, D4, D3, D2, D1);

const char* ssid = "Lexa";
const char* password = "brawltop";
const char* host = "192.168.29.174:5000";
const char* GetURL = "http://192.168.29.174:5000/input_elements/state/";
const char* PostURL = "http://192.168.29.174:5000/output_elements/state/";
const char* DISPLAY_TEXT;
const char* LED;
 char* Json;
int Humidity = 4;
int Temperature = 2;
int DHT,temp;
String payload;


void DHTCLONE(){
    dht.read();
    if (dht.getState() == DHT_OK){
    Temperature = dht.getTemperatureC();
    Humidity = dht.getHumidity();
    }else 
        Serial.print("DHT_ERROR");
}
void ReadJson(){
StaticJsonDocument<200> doc;
deserializeJson(doc, payload);

DISPLAY_TEXT = doc["DISPLAY"];
LED = doc["LED"];
Serial.print(DISPLAY_TEXT);
Serial.print(LED);
}
char* PostJson(int Temperature, int Humidity){
    DynamicJsonDocument Qow(1024);

    Qow[DHT] = Temperature;
    Qow[temp] = Humidity;

    serializeJson(Qow, Json);

    return Json;
}
String Get(){
HTTPClient http;
String ADCData, station;
int adcvalue=analogRead(A0);
ADCData = String(adcvalue);
station = "B";

http.begin(GetURL);

int httpCode = http.GET();
payload = http.getString();

//Serial.println(payload);

http.end();
return payload;

}
void Post(char* data) {
HTTPClient http;

String postData;
postData = payload;

http.begin(PostURL);
http.addHeader("Content-Type", "application/json");

http.POST(data);

http.end();
}
void LCD_WRITE(const char* text) {
lcd.clear();
lcd.setCursor(1, 0);
lcd.print(text);
}
void setup() {
lcd.begin(16, 2);
Serial.begin(9600);
dht.begin();
WiFi.mode(WIFI_OFF);

WiFi.mode(WIFI_STA);

WiFi.begin(ssid, password);
Serial.println("");

Serial.print("Connecting");

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
}

void loop() {
Get();
ReadJson();
LCD_WRITE(DISPLAY_TEXT);
DHTCLONE();
PostJson(Temperature,Humidity);
Post(Json);
delay(500);
}