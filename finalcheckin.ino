#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"

/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO5 D1
SDA(SS) = GPIO4 D2
MOSI    = GPIO13 D7
MISO    = GPIO12 D6
SCK     = GPIO14 D5
GND     = GND
3.3V    = 3.3V
*/

#define RST_PIN  5  // RST-PIN für RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  4  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO4 

#define SSID "yourwifiname"      // wifi name
#define PASSWORD "yourwifipassword"   //wifi password
#define HOST "hooks.slack.com"  //slack host
#define URL "/services/T20BFV5KQ/BA2Q5ALCB/YWh45ABYXXbpFaWJZ7BNFEKS"  //get incoming web hook url of your slack channel
String MESSAGE = "Message Post To Slack";  //message you want to post to slack

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
int statuss = 0;


void setup() {
  Serial.begin(115200);
  Serial.println();

  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to wifi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }

  Serial.println();
  Serial.println(WiFi.localIP());

 
}

void loop() {

// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "BD 7D 7A 89") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" Welcome Naman Sisodia");
    delay(1000);
    MESSAGE = "Naman Sisodia check in through rfid";
    post();
    statuss = 1;
  }
  
  else   {
    Serial.println(" Access Denied ");
    delay(3000);
  }
 
}

void post() {

    Serial.println("Connecting to host...");
  WiFiClientSecure client;
  if (!client.connect(HOST, 443)) {
    Serial.println("Connection failed");
    client.stop();
    return;
  }
  Serial.println("Connected to host");

  // Send a POST request to your Slack webhook:
  // {"text": "Someone pushed the big red button."}

  String request = "";
  request += "POST ";
  request += URL;
  request += " HTTP/1.1\r\n";

  request += "Host: ";
  request += HOST;
  request += "\r\n";

  int len = MESSAGE.length() + 12;  // JSON wrapper length
  request += "Content-Length: ";
  request += len;
  request += "\r\n";

  request += "Accept: application/json\r\n";
  request += "Connection: close\r\n";
  request += "Content-Type: application/json\r\n";

  request += "\r\n";
  
  request += "{\"text\": \"";
  request += MESSAGE;
  request += "\"}";

  Serial.print(request);
  Serial.println();
  client.print(request);

  long timeout = millis() + 5000;
  while (!client.available()) {
    if (millis() > timeout) {
      Serial.println("Request timed out");
      client.stop();
      return;
    }
  }
  Serial.println("Response:");
  while (client.available()) {
    Serial.write(client.read());
  }
  Serial.println();
  Serial.println("Request complete");
  delay(4000);
}

