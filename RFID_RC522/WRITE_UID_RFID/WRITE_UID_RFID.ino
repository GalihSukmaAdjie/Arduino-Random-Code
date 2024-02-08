#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

// ================================================ SET NEW UID =============================================================
/* 12 digit decimal */
// Mengonversi nilai menjadi array menggunakan #define
#define CONVERT_TO_ARRAY(value) {(value / 1000000000) % 1000, (value / 1000000) % 1000, (value / 1000) % 1000, value % 1000} 
// Mendefinisikan UID ···········||||||||||||
#define NEW_UID CONVERT_TO_ARRAY(102119100107) 

// /* 8 digit decimal */
// // Mengonversi nilai menjadi array menggunakan #define
// #define CONVERT_TO_ARRAY(value) {value / 1000000, (value / 100) % 100, (value / 100) % 100, value % 100} 
// // Mendefinisikan UID ···········||||||||
// #define NEW_UID CONVERT_TO_ARRAY(10211911) 

// /* Manual input decimal */
// #define NEW_UID {102, 119, 100, 107}
// ==========================================================================================================================

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  Serial.println(F("Warning!!! UID akan berubah"));
  
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

// But of course this is a more proper approach
void loop() {
  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  
  // Dump UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], DEC);
  } 
  Serial.println();

  // Set new UID
  byte newUid[] = NEW_UID;
  if ( mfrc522.MIFARE_SetUid(newUid, (byte)4, true) ) {
    Serial.println(F("Wrote new UID to card."));
  }
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  // Dump the new memory contents
  Serial.println(F("New UID and contents:"));
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  delay(2000);
}
