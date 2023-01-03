#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

int sens = 0.0;
float volt = 0.0;
float cel = 0.0;

#define mos 2

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(mos, OUTPUT);
  pinMode(A4,  INPUT);

  lcd.setCursor(0,0);
  lcd.print("PENETAS TELUR");
  lcd.setCursor(0,1);
  lcd.print("SMKN 2 SURABAYA");
  delay(3000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  sens=analogRead(A4);
  volt=(sens/1024.0)*5.0;
  cel=volt*100.0;

  if (cel<=37)
  {
     digitalWrite(mos, HIGH);
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("HEATER ON");    
  }

  else if (cel>=40)
  {
    digitalWrite(mos, LOW);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("HEATER OFF"); 
  }

  Serial.print("SUHU = ");
  Serial.println(cel);
  lcd.setCursor(0,0);
  lcd.print("SUHU = ");
  lcd.print(cel);
  lcd.print("\xdf");
  lcd.print("C");
  delay(500);
} 
