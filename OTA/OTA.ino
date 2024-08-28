#include <WiFi.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "COL"
#define STAPSK ""
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void setup() {
  delay(500);
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
	
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    led.show(255, 0, 0);
	  delay(500);
  }
  led.show(0, 0, 254);

  // Port defaults to 2040
  // ArduinoOTA.setPort(2040);

  // Hostname defaults to pico-[ChipID]
  ArduinoOTA.setHostname("acreditacionLargo");

  // No authentication by default
  ArduinoOTA.setPassword("credLargo");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  ArduinoOTA.handle();
}
