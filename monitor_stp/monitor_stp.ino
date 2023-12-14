#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
//#include <MFRC522DriverI2C.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <HTTPClient.h>
#include <WiFi.h>


MFRC522DriverPinSimple ss_pin(21); // Configurable, see typical pin layout above.

MFRC522DriverSPI driver{ss_pin}; // Create SPI driver.
//MFRC522DriverI2C driver{}; // Create I2C driver.
MFRC522 mfrc522{driver};  // Create MFRC522 instance.
int curVis = 0;

const char* ssid = "Tenant Only";
const char* password = "stpinkubator";
const char* serverUrl = "https://iscalab.000webhostapp.com/api.php";

String uids = 


void setup() {
  Serial.begin(115200);  // Initialize serial communications with the PC for debugging.
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  mfrc522.PCD_Init();  // Init MFRC522 board.
  // MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);	// Show details of PCD - MFRC522 Card Reader details.
	Serial.println(F("Scan PICC to see UID..."));
}

String getSimpleUID() {
  String uidString = "";
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidString += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
  }
  return uidString;
}

void loop() {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String sentUid, sendThis;
  String uid = getSimpleUID();
  if (uid.length() > 0) {
    Serial.println("Local Status : ");
    Serial.println("UID tag: " + uid);
    Serial.println("Current Visitor : " + String(curVis));
    curVis++;
    sendThis = "uid=" +uid + "&curVis=" +String(curVis);
    int httpResp = http.POST(sendThis);
    String payload = http.getString();
    Serial.println("----------------");
    Serial.println("Server Status : ");
    Serial.println(httpResp);
    Serial.println(payload);
  }
  delay(1000); // Adjust the delay as needed
}
