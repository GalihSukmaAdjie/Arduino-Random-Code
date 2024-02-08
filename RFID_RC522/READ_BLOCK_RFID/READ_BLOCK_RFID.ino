#include <SPI.h>
#include <MFRC522.h>
#include "Keyboard.h"

/* Serial komunikasi dari alat */
#define AKTIFKAN_SERIAL // Komentari baris ini untuk menonaktifkan komunikasi
#ifdef AKTIFKAN_SERIAL
#define SERIAL_PRINT(value) Serial.print(value)
#define SERIAL_PRINTLN(value) Serial.println(value)
#else
#define SERIAL_PRINT(value)
#define SERIAL_PRINTLN(value)
#endif

/* Keyboard Emulator */
#define AKTIFKAN_KEYBOARD_EMUL // Komentari baris ini untuk menonaktifkan keyboard
#ifdef AKTIFKAN_KEYBOARD_EMUL
#define KEYBOARD_PRINT(value) Keyboard.print(value)
#define KEYBOARD_PRINTLN(value) Keyboard.println(value)
#else
#define KEYBOARD_PRINT(value)
#define KEYBOARD_PRINTLN(value)
#endif

/* Pin yang digunakan Hardware */
#define RST_PIN      9           
#define SS_PIN       10          
#define RED_LED      8
#define GREEN_LED    7
#define BUZZER       6

/* Variabel yang digunakan */
String device_id = "1021191";
int interval = 500;

MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

void setup() {
  /* Siapkan Serial */
  Serial.begin(9600);                                           
  while(!Serial);
  /* Preparation Hardware */
  SPI.begin();                                                  
  Keyboard.begin();
  mfrc522.PCD_Init();                                              
  delay(7);				
	mfrc522.PCD_DumpVersionToSerial();
  
  /* Configurasi pin */
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT),
  pinMode(BUZZER, OUTPUT),

  /* Reset kondisi pin */
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BUZZER, 0);

  SERIAL_PRINTLN("Ready To Use :");
}

void loop() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    byte encrypt;
    byte data;
    byte len;
  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  SERIAL_PRINTLN(F("Kartu Terdeteksi :"));
  byte buffer[18];
  encrypt = 4;
  data = 5;
  len = 18;

  /* Baca Enskripsi di Memory Sektor 4 */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, encrypt, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    String message = String(F("Authentication failed: Memory ")) + String(encrypt) + String(F(" => "));
    SERIAL_PRINT(message);
    SERIAL_PRINTLN(mfrc522.GetStatusCodeName(status));
    // return;
  }
  status = mfrc522.MIFARE_Read(encrypt, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    String message = String(F("Reading failed: Memory ")) + String(encrypt) + String(F(" => "));
    SERIAL_PRINT(message);
    SERIAL_PRINTLN(mfrc522.GetStatusCodeName(status));
    // return;
  }
  String encryptKey = "";
  for (uint8_t i = 0; i < 16; i++) {
    encryptKey += (char)buffer[i];
  }
  encryptKey.trim();
  SERIAL_PRINTLN(encryptKey);

  /* Baca Data di Memory Sektor 5 */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, data, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    String message = String(F("Authentication failed: Memory ")) + String(data) + String(F(" => "));
    SERIAL_PRINT(message);
    SERIAL_PRINTLN(mfrc522.GetStatusCodeName(status));
    // return;
  }
  status = mfrc522.MIFARE_Read(data, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    String message = String(F("Reading failed: Memory ")) + String(data) + String(F(" => "));
    SERIAL_PRINT(message);
    SERIAL_PRINTLN(mfrc522.GetStatusCodeName(status));
    // return;
  }
  String dataKey = "";
  for (uint8_t i = 0; i < 16; i++) {
    dataKey += (char)buffer[i];
  }
  dataKey.trim();
  SERIAL_PRINTLN(dataKey);

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  if (encryptKey == "NAYAKA PROJECT" && isValidString(dataKey)) {
    /* konkatenasi print */
    SERIAL_PRINTLN("Device ID : " + device_id);
    SERIAL_PRINTLN("Identity  : " + dataKey);
    KEYBOARD_PRINTLN(device_id + ";" + dataKey);
    INDICATOR_LED(true);
    INDICATOR_BUZZER(true);
  } 
  else {
    SERIAL_PRINTLN("Salah, Jangan kirim data ke backend");
    INDICATOR_LED(false);
    INDICATOR_BUZZER(false);
  }
  /* RESET Indicator setelah Pembacaan */
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BUZZER, 0);
}

/* Filter karakter yang bisa dibaca */
bool isValidString(String str) {
  /* Pemeriksaan apakah setiap karakter dalam string adalah karakter yang diizinkan */
  for (int i = 0; i < str.length(); i++) {
    char currentChar = str.charAt(i);
    
    /* Sesuaikan karakter-karakter yang diizinkan sesuai kebutuhan Anda */
    if (!isAlphaNumeric(currentChar) && currentChar != ' ' && currentChar != '.' && currentChar != ',' && currentChar != ':') {
      return false; /* Karakter tidak diizinkan ditemukan */
    }
  }

  return true; /* Semua karakter diizinkan */
}

/* fungsi indicator LED */
void INDICATOR_LED(bool statusLed) {
  if(statusLed){
    digitalWrite(RED_LED, 0);
    digitalWrite(GREEN_LED, 1);
  } else {
    digitalWrite(RED_LED, 1);
    digitalWrite(GREEN_LED, 0);
  }
}

/* fungsi indicator Buzzer */
void INDICATOR_BUZZER(bool statusBuzz) {
  if(statusBuzz){
    int timer_buzzer = interval/4;
    for(int Count = 0; Count <= 2; Count++) {
      digitalWrite(BUZZER, 1);
      delay(timer_buzzer);
      digitalWrite(BUZZER, 0);
      delay(timer_buzzer);
      Count += Count;
    }
  } else {
    digitalWrite(BUZZER, 1);
    delay(interval);
  }
}