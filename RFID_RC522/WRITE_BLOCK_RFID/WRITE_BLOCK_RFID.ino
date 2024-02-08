/* DATA YANG DIINPUTKAN KE DALAM KARTU DISESUAIKAN DIBAWAH INI */
//
/* Panjang MAKS     |||||||||||||||| hanya sepanjang 16 garis vertikal */
char inputText[] = "UJI coba WRITE";
byte data[16]; // Panjang memory maksimal 16
//
/*------------------------------------------------------------*/
//
//
//

#include <SPI.h>
#include <MFRC522.h>

/* Pin yang digunakan Hardware */
#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

void setup() {
  /* Siapkan Serial */
  Serial.begin(9600);    
  /* Preparation Hardware */    
  SPI.begin();               
  mfrc522.PCD_Init();        
  convertTextToBytes(inputText, data);
  Serial.println(F("Telah siap digunakan WRITE : "));
}

void loop() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.setTimeout(20000L);

  /* kode enkripsi kartu di blok 4 */
  byte block4 = 4;
  byte encrypt[] = 
  {0x4e,0x41,0x59,0x41,
  0x4b,0x41,0x20,0x50,
  0x52,0x4f,0x4a,0x45,
  0x43,0x54,0x20,0x20};
  writeBytesToBlock(block4, encrypt);  

  /* DATA pribadi disimpan di blok 5 */
  byte block5 = 5;
  writeBytesToBlock(block5, data);  

  Serial.println(" ");
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

/* Konversikan data char menjadi array HEX */
void convertTextToBytes(const char* text, byte* dataArray) {
  int length = strlen(text);
  
  for (int i = 0; i < length; i++) {
    dataArray[i] = text[i];
  }
  
  /* Menambahkan 0x20 sebagai terminasi string */
  dataArray[length] = 0x20;

  /* Mengisi sisa array dengan spasi (ASCII 32 atau 0x20) */
  for (int i = length + 1; i < 16; i++) {
    dataArray[i] = 0x20;
  }
}

/* write new data to memory Card  */
void writeBytesToBlock(byte block, byte buff[]) {
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("PCD_Authenticate() success: "));
  // Write block
  status = mfrc522.MIFARE_Write(block, buff, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else {
    Serial.print(F("MIFARE_Write() success: IN BLOCK "));
    Serial.println(block);
  }
}