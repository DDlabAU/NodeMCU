#include <ESP8266WiFi.h>

uint8_t MAC_array[6];
char MAC_char[18];

void setup() {
    Serial.begin(115200);
    Serial.println();

    WiFi.persistent(false);
    WiFi.macAddress(MAC_array);
    for (int i = 0; i < sizeof(MAC_array); ++i){
      sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    }
	MAC_char[17]='\0'; //get rid of last colon... :)

    Serial.println(MAC_char);
}

void loop() {
	delay(5000);
	Serial.print("MAC address is still: ");
	Serial.println(MAC_char);
}