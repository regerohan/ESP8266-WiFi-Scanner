#include "ESP8266WiFi.h"

const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm

const int displayEnc=1;// set to 1 to display Encryption or 0 not to display

void setup() {
  Serial.begin(115200);
  Serial.println("Wifi Signal Scan");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("Wifi scan started");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Wifi scan ended");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(") ");
      Serial.print(WiFi.SSID(i));// SSID
      Serial.print(" ");
      Serial.print(WiFi.RSSI(i));//Signal strength in dBm
      Serial.print("dBm");
      if (WiFi.RSSI(i) <= RSSI_MIN) {
        Serial.print(" 0%");
      }
      if (WiFi.RSSI(i) >= RSSI_MAX) {
        Serial.print(" 100%");
      }
      else
      {
        Serial.print(" ");
        Serial.print(2*(WiFi.RSSI(i)+100));
        Serial.print("%");
      }
      

      if(WiFi.encryptionType(i) == ENC_TYPE_NONE)
      {
          Serial.println(" <<***OPEN***>>");        
      }else{
          Serial.println();        
      }

      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
  WiFi.scanDelete();  
}
