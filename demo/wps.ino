#include <ESP8266WiFi.h>

bool startWPSPBC() {
  Serial.println("WPS config start");
  bool wpsSuccess = WiFi.beginWPSConfig();
  if(wpsSuccess) {
      // Well this means not always success :-/ in case of a timeout we have an empty ssid
      String newSSID = WiFi.SSID();
      if(newSSID.length() > 0) {
        // WPSConfig has already connected in STA mode successfully to the new station. 
        Serial.printf("WPS finished. Connected successfull to SSID '%s'\n", newSSID.c_str());
      } else {
        wpsSuccess = false;
      }
  }
  return wpsSuccess; 
}

void reset() {
  WiFi.disconnect();
  delay(2000);
  ESP.reset();
}

void setup() {
  Serial.begin(115200);
  delay(1000);


  Serial.printf("\nTry connecting to WiFi with SSID '%s'\n", WiFi.SSID().c_str());


  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi.SSID().c_str(),WiFi.psk().c_str()); // reading data from EPROM, last saved credentials
  while (WiFi.status() == WL_DISCONNECTED) {
    delay(500);
    Serial.print(".");
  }

  wl_status_t status = WiFi.status();
  if(status == WL_CONNECTED) {
    Serial.printf("\nConnected successfull to SSID '%s'\n", WiFi.SSID().c_str());
  } else {
    Serial.printf("\nCould not connect to WiFi. state='%d'", status); 
    Serial.println("Please press WPS button on your router.\n Press any key to continue...");
    while(!Serial.available()) { ; }
    if(!startWPSPBC()) {
       Serial.println("Failed to connect with WPS :-(");  
    }
  } 
}


void loop() {
  // put your main code here, to run repeatedly:

}