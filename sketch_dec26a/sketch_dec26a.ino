#define BLYNK_TEMPLATE_ID "TMPL3EXfgv94J"
#define BLYNK_TEMPLATE_NAME "GPS TRACKER free"
#define BLYNK_AUTH_TOKEN "RO9RHrpYrnJbANbmtk0qybb0Gd19Pp9P"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPSPlus.h> // Correct library name

char auth[] = "RO9RHrpYrnJbANbmtk0qybb0Gd19Pp9P";
char ssid[] = "Avin";
char pass[] = "24680000";

TinyGPSPlus gps;
HardwareSerial SerialGPS(2); // GPS TX->16, RX->17
BlynkTimer timer;

void sendGPSData() {
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (gps.location.isValid()) {
        // Send separate coordinates for free widgets
        Blynk.virtualWrite(V1, gps.location.lat()); 
        Blynk.virtualWrite(V2, gps.location.lng());
        Blynk.virtualWrite(V3, gps.speed.kmph());
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // Use correct ESP32 UART2 pins
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendGPSData); // Send data every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}