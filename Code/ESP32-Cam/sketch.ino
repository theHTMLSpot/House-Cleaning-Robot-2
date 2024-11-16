#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverAddress[] = {0x24, 0x6F, 0x28, 0xXX, 0xXX, 0xXX}; // Replace with receiver's MAC address

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  Serial.println("ESP-NOW initialized");
}

void loop() {
  String command = "STAIRS"; // Change this to "S", "C", or other commands
  esp_now_send(receiverAddress, (uint8_t *)command.c_str(), command.length());
  delay(5000); // Send every 5 seconds
}
