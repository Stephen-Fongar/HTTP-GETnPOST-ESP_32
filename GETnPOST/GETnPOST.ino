#include <WiFi.h>
#include <HTTPClient.h>
#include <Ticker.h>
Ticker periodicTicker;

const char* ssid = "Vonia";
const char* password = "08062005";

//Your Domain name with URL path or IP address with path
String serverTarget1 = "http://192.168.1.10:3000/api/control/getled2";
const char* serverTarget2 = "http://192.168.1.10:3000/api/telemetry/device1";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 1 seconds (1000)
unsigned long timerDelay = 1000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 1 seconds (timerDelay variable), it will take 1 seconds before publishing the first reading.");
  periodicTicker.attach_ms(10000, POST);

}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClient client;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverTarget1.c_str());

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    http.addHeader("Accept", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MjQyODMyNTdjNjJlYTViZGMxY2FkN2YiLCJpYXQiOjE2NTAwOTQwMDB9.BbZxYIj4MMwW-J9ALau7Fdxc2Z2G9hDptrCR8nruczc");
      // Send HTTP GET request
      int httpResponseCode1 = http.GET();
        if (httpResponseCode1>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode1);
          String payload = http.getString();
          Serial.println(payload);
        }
        
        else {
        Serial.print("HTTP Response code1: ");
        Serial.println(httpResponseCode1);
        }
        http.end();
        }
      else {
        Serial.println("WiFi Disconnected");
      }
}

void POST(){
   HTTPClient http;
    WiFiClient client;
    http.begin(client, serverTarget2);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    http.addHeader("Accept", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MjQyODMyNTdjNjJlYTViZGMxY2FkN2YiLCJpYXQiOjE2NTAwOTQwMDB9.BbZxYIj4MMwW-J9ALau7Fdxc2Z2G9hDptrCR8nruczc");
               // Data to send with HTTP POST
      float dataa= random(10.0, 100.0);
      String packet = "{\"data\": \"" + String(dataa) + "\"" + "}";
     
      //packet.concat((",\"TDS\":"));
      //packet.concat(tdsValue);
      
      Serial.println(packet);
      // Send HTTP POST request
      int httpResponseCode2 = http.POST(packet);
      
      Serial.print("HTTP Response code2: ");
      Serial.println(httpResponseCode2);
      
      // Free resources
      http.end();
      
   
}
