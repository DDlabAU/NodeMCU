#NodeMCU og Arduino
NodeMCU er et arduino-kompatibelt board med indygget wifi. Dette er en kort guide til hvordan du hurtigt får boardet op og køre i dit arduino IDE.

###Kendte problemer


###Installation
Sørg for at du har den nyeste version af [arduino](https://www.arduino.cc/en/Main/Software) installeret før du går i gang.
For at anvende dette board skal du have installeret en pakke af custom boards i dit arduino IDE. Det gør du ved at åbne arduino og navigere til dine indstillinger: "File" -> "Preferences". I tekstboksen ud for "Additional Boards Manager URLs:" indsætter du dette link: http://arduino.esp8266.com/stable/package_esp8266com_index.json og trykker på "OK" knappen nederst i vinduet.
Efter det skal du ind i din "Board Manager" og installere pakken. Det gør du ved at navigere til "Tools" -> "Board: " -> "Boards Manager...". Du scroller så ned indtil du finder "esp8266 by ESP8266 Community, trykker på denne boks og trykker så på "Install". Når installationen er færdig, vil du se en mængde nye boards at vælge imellem, når du bevæger dig til "Tools" -> "Board: ". Vælg enten "NodeMCU 0.9 (ESP-12 Module)" eller "NodeMCU 1.0 (ESP-12E Module)".

###GPIO
Pinout for NodeMCU boardet:
![Pinout for NodeMCU V0.9](http://ddlab.dk/Node-MCU-Pin-Out-Diagram1.png)
Det er GPIOx numrene som man bruger når man koder det i Arduino IDE'en.

###Eksempler![Image of Yaktocat](https://octodex.github.com/images/yaktocat.png)
Har du adgang til et trådløst netværk kan du bruge dette eksempel, der forbinder til netværket og printer den tildelte ip-adresse. Husk selv at indsætte netværksnavn og kode. Dette kan også gøres med et hotspot som du opretter med din smartphone.

```
#include <ESP8266WiFi.h>

// Insert network id and password here

const char* ssid     = "******";
const char* password = "******";


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
  } else {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  delay(5000);
}
```

Har du ikke adgang til et trådløst netværk, kan du i stedet bruge denne kode, der periodisk scanner efter og printer omkringværende netværk.

```
#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
```

Vær i begge tilfælde opmærksom på at boardet ikke resetter når du åbner din "Serial Monitor", så hvis du vil være sikker på at alle dens print med, skal du åbne denne inden du uploader din kode. Husk også at indstille baudraten til "115200".
Som altid kan du finde flere eksempler under "File" -> "Examples". Størstedelen af alle ESP8266 eksemplerne burde kunne anvendes med boardet.

