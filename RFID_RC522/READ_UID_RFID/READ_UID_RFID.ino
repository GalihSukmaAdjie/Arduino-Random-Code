#include <SPI.h>
#include <MFRC522.h>
#include "Keyboard.h"

#define SS_PIN 10
#define RST_PIN 9
#define RED_LED 8
#define GREEN_LED 7
#define BUZZER 6

int interval = 500; // interval setiap pengecekan

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  Keyboard.begin();
  rfid.PCD_Init();
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT),
  pinMode(BUZZER, OUTPUT),
  Serial.println("Silakan tempelkan kartu RFID...");
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BUZZER, 0);
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i]);
    }
    
    Serial.print("UID Kartu: ");
    Serial.println(uid);

    if (uid.startsWith("23") && uid.endsWith("10")) { // hanya kirim data dengan ID berawalan 23 dan 10
      Serial.println("Benar, Kirim data Ke backend");
      Keyboard.println(uid); // send data as keyboard emulator
      LED_TRUE();
      BUZZER_TRUE();
    } else {
      Serial.println("Salah, Jangan kirim data ke backend");
      LED_FALSE();
      BUZZER_FALSE();
    }

    // delay(1000); // delete if use interval
    digitalWrite(RED_LED, 0);
    digitalWrite(GREEN_LED, 0);
    digitalWrite(BUZZER, 0);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void LED_TRUE() {
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 1);
}

void LED_FALSE() {
  digitalWrite(RED_LED, 1);
  digitalWrite(GREEN_LED, 0);
}

void BUZZER_TRUE() {
  int timer_buzzer = interval/4;
  for(int Count = 0; Count <= 2; Count++) {
    digitalWrite(BUZZER, 1);
    delay(timer_buzzer);
    digitalWrite(BUZZER, 0);
    delay(timer_buzzer);
    Count += Count;
  }
}

void BUZZER_FALSE() {
  digitalWrite(BUZZER, 1);
  delay(interval);
}
