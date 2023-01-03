#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

#define bzr 6

#define clk 5
#define ltc 4
#define dta 3

#define pot A2

byte leda = 1;
byte ledb = 1;

unsigned char A[17] ={0b11111111,
                      0b11111110,
                      0b11111100,
                      0b11111000,
                      0b11110000,
                      0b11100000,
                      0b11000000,
                      0b10000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000,
                      0b00000000};

unsigned char B[17] ={0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111111,
                      0b11111110,
                      0b11111100,
                      0b11111000,
                      0b11110000,
                      0b11100000,
                      0b11000000,
                      0b10000000,
                      0b00000000};

int trimpot;
int led;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);

  pinMode(bzr,OUTPUT);

  pinMode(clk,OUTPUT);
  pinMode(ltc,OUTPUT);
  pinMode(dta,OUTPUT);

  pinMode(pot,INPUT);

  lcd.setCursor(1,0);
  lcd.print("V.ANALOG LEVEL");
  lcd.setCursor(0,1);
  lcd.print("Lvl:0");
  lcd.setCursor(9,1);
  lcd.print("BZR OFF");

  digitalWrite(bzr,HIGH);
  delay(100);
  digitalWrite(bzr,LOW);
  delay(100);
  digitalWrite(bzr,HIGH);
  delay(100);
  digitalWrite(bzr,LOW);
  
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  trimpot = analogRead(pot);

  led = map(trimpot,0,1010,0,16);
  led = constrain(led,0,16);

  lcd.setCursor(1,0);
  lcd.print("V.ANALOG LEVEL");
  lcd.setCursor(0,1);
  lcd.print(led);
  lcd.print(" ");

  if(led <=8)
  {
    lcd.setCursor(9,1);
    lcd.print("BZR OFF");
    digitalWrite(bzr,LOW);
  }
  else
  {
    lcd.setCursor(9,1);
    lcd.print("BZR ON ");
    digitalWrite(bzr,HIGH);
  }

  leda = A[led];
  ledb = B[led];

  digitalWrite(ltc,LOW);
  shiftOut(dta,clk,MSBFIRST,ledb);
  shiftOut(dta,clk,MSBFIRST,leda);
  digitalWrite(ltc,HIGH);

  delay(33);
}
