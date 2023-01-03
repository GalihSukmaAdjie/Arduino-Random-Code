#include <LiquidCrystal.h>

#include <LiquidCrystal.h>          //  FILE HEADER LCD
LiquidCrystal lcd(12,11,10,9,8,7);  //  RS,E,D4,D5,D6,D7

#define bzr 6                       //  PIN DIGITAL 6 SEBAGAI BZR

#define clk 5                       //  PIN DIGITAL 5 SEBAGAI CLK
#define ltc 4                       //  PIN DIGITAL 4 SEBAGAI LTC
#define dta 3                       //  PIN DIGITAL 3 SEBAGAI DTA

#define sw A0                       //  PIN ANALOG 0 SEBAGAI SW
#define sens A1                     //  PIN ANALOG 1 SEBAGAI SENS

byte leda = 1;                      //  
byte ledb = 1;                      //

unsigned char A[17]={0b11111111,    //////////////////
                     0b11111110,    //  DATA ARRAY  //
                     0b11111100,    //  UNTUK       //
                     0b11111000,    //  LED A       //
                     0b11110000,    //              //
                     0b11100000,    //              //
                     0b11000000,    //              //
                     0b10000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000,    //              //
                     0b00000000};   //////////////////

unsigned char B[17]={0b11111111,    //////////////////
                     0b11111111,    //  DATA ARRAY  //
                     0b11111111,    //  UNTUK       //
                     0b11111111,    //  LED B       //
                     0b11111111,    //              //
                     0b11111111,    //              //
                     0b11111111,    //              //
                     0b11111111,    //              //
                     0b11111111,    //              //
                     0b11111110,    //              //
                     0b11111100,    //              //
                     0b11111000,    //              //
                     0b11110000,    //              //
                     0b11100000,    //              //
                     0b11000000,    //              //
                     0b10000000,    //              //
                     0b00000000};   //////////////////
                     
int tombol = 0;                     // VARIABEL UNTUK DIISI NILAI A0/SW
int sensor = 0;                     // VARIABEL UNTUK DIISI NILAI A1/SENS 
float volt = 0.0;                   // VARIABEL UNTUK DIISI NILAI ((SENSOR/1024.0)*5.0)
float cel = 0.0;                    // VARIABEL UNTUK DIISI NILAI (VOLT*100.0)
int ind = 0;                        // VARIABEL UNTUK DIISI JUMLAH LED
byte sp;                            // VARIABEL UNTUK MENGHITUNG JUMLAH TEKAN 
int setPoint;                // VARIABEL UNTUK BATAS SUHU
int awal = 50;                      // VARIABEL UNTUK NILAI AWAL SETPOINT
int sw1,sw2,sw3,sw4,sw5;            // VARIABEL UNTUK DIISI NILAI DARI MASING' SWITCH

void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2);                 // KONFIGURASI LCD

  pinMode(bzr,OUTPUT);              // PIN BZR SEBAGAI OUTPUT

  pinMode(clk,OUTPUT);              // PIN CLK SEBAGAI OUTPUT
  pinMode(ltc,OUTPUT);              // PIN LTC SEBAGAI OUTPUT
  pinMode(dta,OUTPUT);              // PIN DTA SEBAGAI OUTPUT

  pinMode(sens,INPUT);              // PIN SENS SEBAGAI INPUT
  pinMode(sw,INPUT);                // PIN SW SWBAGAI INPUT

  leda = 0xFF;                      // LED OFF SEMUA
  ledb = 0xFF;                      // LED OFF SEMUA

  lcd.setCursor(1,0);               // 
  lcd.print("LKS Jatim 2019");      //
  lcd.setCursor(3,1);               //
  lcd.print("Soal Fase 3");         //

  digitalWrite(bzr,HIGH);           //////////////////////
  delay(300);                       // BUZZER           //
  digitalWrite(bzr,LOW);            // BEEP SEBANYAK    //
  delay(300);                       // 2 KALI PADA      //
  digitalWrite(bzr,HIGH);           // SAAT PERTAMAKALI //
  delay(300);                       // ON/UPLOAD        //
  digitalWrite(bzr,LOW);            //////////////////////
  
  delay(1000);                      //
  lcd.clear();                      // BERSIHKAN LCD

  setPoint = awal;                  // NILAI AWAL SETPOINT
}
void loop() {
  // put your main code here, to run repeatedly:
  sensor = analogRead(sens);        // MEMBACA NILAI ANALOG SENS
  volt = (sensor/1024.0)*5.0;       // MENGKONVERSI NILAI ANALOG KE VOLT
  cel = volt*100.0;                 // MENGKONVERSI NILAI VOLT KE CEL
  
  tombol = analogRead(sw);          // MEMBACA NILAI ANALOG SW
  sw1 = constrain(tombol,5,10);     // MENGISI SW1 DENGAN NILAI TOMBOL
  sw2 = constrain(tombol,246,251);  // MENGISI SW2 DENGAN NILAI TOMBOL
  sw3 = constrain(tombol,511,516);  // MENGISI SW3 DENGAN NILAI TOMBOL
  sw4 = constrain(tombol,783,788);  // MENGISI SW4 DENGAN NILAI TOMBOL
  sw5 = constrain(tombol,911,916);  // MENGISI SW5 DENGAN NILAI TOMBOL
  
  ind = constrain(ind,0,16);        // BATAS BAWAH DAN ATAS LED

  ind = map(cel,0,setPoint,0,16);   // MESKALA JARAK SUHU DENGAN LED

  lcd.setCursor(0,0);               //
  lcd.print("P=");                  //
  lcd.print(setPoint);              //
  lcd.print("\xdf");                //
  lcd.print("C ");                  //
  lcd.setCursor(7,0);               //
  lcd.print("T=");                  //
  lcd.print(cel);                   //
  lcd.print("\xdf");                //
  lcd.print("C ");                  //

  leda = A[ind];                    //
  ledb = B[ind];                    //

  digitalWrite(ltc,HIGH);           //
  shiftOut(dta,clk,MSBFIRST,ledb);  //
  shiftOut(dta,clk,MSBFIRST,leda);  //
  digitalWrite(ltc,LOW);            //

  if(cel >setPoint)                 // JIKA CEL DIATAS SETPOINT
  {                                 //
    lcd.setCursor(0,1);             //
    lcd.print("BUZZER ON ");        //
    digitalWrite(bzr,HIGH);         //
  }                                 //
  if(cel <setPoint)                 // JIKA CEL DIBAWAH SETPOINT
  {                                 //
    lcd.setCursor(0,1);             //
    lcd.print("BUZZER OFF");        //
    digitalWrite(bzr,LOW);          //
  }                                 //

  if(sw1 == 5)                      // IF SW1 DI TEKAN
  {                                 //
    setPoint = awal;                // SETPOINT = AWAL
    delay(300);                     //
  }                                 //

  stombol();                        // MENGAKTIFKAN STOMBOL
  delay(100);                       //
}                                   //

void stombol() {                    // RUANG UNTUK STOMBOL
  if(sw5 == 911 && sw4 == 788)      // JIKA SW5 DITEKAN
  {                                 //
    lcd.clear();                    //
    lcd.setCursor(0,0);             //
    lcd.print("SETING POINT");      //
    delay(1000);                    //
    lcd.clear();                    // BERSIHKAN LCD

    do                              // LOOPING
    {                               //
      if(sw5 == 911 && sw4 == 788)  // JIKA SW5 DITEKAN
      {                             //
        sp++;                       // SP + 1
        delay(300);                 //
      }                             //
      if(sw3 == 511 && sw1 == 10 )  // JIKA SW3 DITEKAN
      {                             //
        setPoint = setPoint+1;      // SETPOINT + 1
        delay(300);                 //
      }                             //
      if(sw4 == 783 && sw3 == 516)  // JIKA SW4 DITEKAN
      {                             //
        if(setPoint >0)             // HARUS DI ATAS NOL
        {                           //
        setPoint = setPoint-1;      // SETPOINT - 1
        }                           //
        delay(300);                 //
      }                             //
      
      if(sw1 == 5)                  // JIKA SW1 DITEKAN
      {                             // 
        setPoint = awal;            // SETPOINT = AWAL
        delay(300);                 //
      }                             //
      
      tombol = analogRead(sw);         /////////////
      sw1 = constrain(tombol,5,10);    // MEMBACA //
      sw2 = constrain(tombol,246,251); // KEMBALI //
      sw3 = constrain(tombol,511,516); // NILAI   //
      sw4 = constrain(tombol,783,788); // SW      //
      sw5 = constrain(tombol,911,916); /////////////

      lcd.setCursor(0,0);           ///////////////////
      lcd.print("Set point = ");    // TAMPILAN SAAT //
      lcd.print(setPoint);          // SETTING POIN  //
      lcd.print("   ");             ///////////////////

    }                               //
    while(sp ==1);                  // JIKA SALAH, KEMBALI KE VOID LOOP
    sp = 0;                         // SP KEMBALI NOL
    lcd.clear();                    // BERSIHKAN LCD
    lcd.setCursor(0,0);             //
    lcd.print("SETTING OKE");       // TAMPILAN SAAT DI TEKAN KEDUA
    delay(1000);                    //
    lcd.clear();                    // BERSIHKAN LCD
  }
}
