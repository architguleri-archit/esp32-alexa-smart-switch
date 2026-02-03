#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// -------- WiFi Credentials --------
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASS     "YOUR_WIFI_PASSWORD"

// -------- Sinric Pro Credentials --------
#define APP_KEY       "YOUR_SINRIC_APP_KEY"
#define APP_SECRET    "YOUR_SINRIC_APP_SECRET"

// -------- Device IDs --------
#define DEVICE_ID_1   "YOUR_DEVICE_ID_1"
#define DEVICE_ID_2   "YOUR_DEVICE_ID_2"
#define DEVICE_ID_3   "YOUR_DEVICE_ID_3"
#define DEVICE_ID_4   "YOUR_DEVICE_ID_4"

// -------- Relay Pins --------
#define RELAY1 14
#define RELAY2 27
#define RELAY3 26
#define RELAY4 25

bool onPowerState1(const String &deviceId, bool &state) {
  digitalWrite(RELAY1, state ? LOW : HIGH);
  return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
  digitalWrite(RELAY2, state ? LOW : HIGH);
  return true;
}

bool onPowerState3(const String &deviceId, bool &state) {
  digitalWrite(RELAY3, state ? LOW : HIGH);
  return true;
}

bool onPowerState4(const String &deviceId, bool &state) {
  digitalWrite(RELAY4, state ? LOW : HIGH);
  return true;
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // All relays OFF at startup (LOW-trigger relay)
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  SinricProSwitch &sw1 = SinricPro[DEVICE_ID_1];
  SinricProSwitch &sw2 = SinricPro[DEVICE_ID_2];
  SinricProSwitch &sw3 = SinricPro[DEVICE_ID_3];
  SinricProSwitch &sw4 = SinricPro[DEVICE_ID_4];

  sw1.onPowerState(onPowerState1);
  sw2.onPowerState(onPowerState2);
  sw3.onPowerState(onPowerState3);
  sw4.onPowerState(onPowerState4);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}

