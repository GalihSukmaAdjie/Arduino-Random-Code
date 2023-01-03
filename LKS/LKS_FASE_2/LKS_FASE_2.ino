#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

#define bzr 6

#define clk 5
#define ltc 4
#define dta 3

#define sw A0

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

int tombol;
int led;
int sw1,sw2,sw3,sw4,sw5;
int buzzer;
int i =0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);

  pinMode(bzr,OUTPUT);

  pinMode(clk,OUTPUT);
  pinMode(ltc,OUTPUT);
  pinMode(dta,OUTPUT);

  pinMode(sw,INPUT);

  lcd.setCursor(1,0);
  lcd.print("UP DOWN COUNTER");
  lcd.setCursor(0,1);
  lcd.print("CNT:0");
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
  tombol = analogRead(sw);

  sw1 = constrain(tombol,5,10);
  sw2 = constrain(tombol,246,251);
  sw3 = constrain(tombol,511,516);
  sw4 = constrain(tombol,783,788);
  sw5 = constrain(tombol,911,916);

  led = constrain(led,0,16);

  lcd.setCursor(1,0);
  lcd.print("UP DOWN COUNTER");
  lcd.setCursor(0,1);
  lcd.print("CNT:");
  lcd.print(led);
  lcd.print(" ");

  if(led <=8 && buzzer == 0)
  {
    lcd.setCursor(9,1);
    lcd.print("BZR OFF");
    digitalWrite(bzr,LOW);
  }
  
    if(led ==9 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=1;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(500);
        digitalWrite(bzr,LOW);
        delay(500);
      }
    }
    if(led ==10 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=2;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(250);
        digitalWrite(bzr,LOW);
        delay(250);
      }
    }
    if(led ==11 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=4;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(125);
        digitalWrite(bzr,LOW);
        delay(125);
      }
    }
    if(led ==12 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=8;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(62);
        digitalWrite(bzr,LOW);
        delay(62);
      }
    }
    if(led ==13 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=16;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(31);
        digitalWrite(bzr,LOW);
        delay(31);
      }
    }
    if(led ==14 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=32;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(15);
        digitalWrite(bzr,LOW);
        delay(15);
      }
    }
    if(led ==15 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=64;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(8);
        digitalWrite(bzr,LOW);
        delay(8);
      }
    }
    if(led ==16 && buzzer ==1)
    {
      lcd.setCursor(9,1);
    lcd.print("BZR ON ");
      for(i=0;i<=128;i++)
      {
        digitalWrite(bzr,HIGH);
        delay(4);
        digitalWrite(bzr,LOW);
        delay(4);
      }
    }

  if(sw2 == 246 && sw1 ==10)
  {
    buzzer = 0;  
    lcd.setCursor(9,1);
    lcd.print("BZR OFF");
  }

  if(sw1 ==5)
  {
    led=0;
    delay(300);
  }

  if(sw3 ==511 && sw2 ==251)
  {
    led = led+1;
    buzzer = 1;
    delay(300);
  }
  if(sw4 ==783 && sw3 ==516)
  {
    if(led <=8)
    {
      buzzer =0;
      led = led-1;
      delay(300);
    }
    else
    {
    buzzer = 1; 
    led = led-1;
    delay(300);
    }
  }

  leda = A[led];
  ledb = B[led];

  digitalWrite(ltc,LOW);
  shiftOut(dta,clk,MSBFIRST,ledb);
  shiftOut(dta,clk,MSBFIRST,leda);
  digitalWrite(ltc,HIGH);

  delay(33);
}
