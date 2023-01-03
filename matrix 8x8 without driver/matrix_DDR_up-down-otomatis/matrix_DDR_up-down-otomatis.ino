

// PROGRAM UNTUK SCAN BARIS (NYALA BERTAHAP)
unsigned char baris[8] = {0b11111110,     //
                          0b11111101,     //
                          0b11111011,     //  SCANNING
                          0b11110111,     //  UNTUK 
                          0b11101111,     //  MENYALAKAN LED
                          0b11011111,     //  PERBARIS
                          0b10111111,     //
                          0b01111111};    //
                          
// PROGRAM BERISI ANGKA ANGKA
unsigned char nol[8] = {0b00111111,
                        0b00110011,
                        0b00110011,
                        0b00110011,
                        0b00110011,
                        0b00110011,
                        0b00110011,
                        0b00111111};

unsigned char satu[8] = {0b00011100,
                         0b00111100,
                         0b00001100,
                         0b00001100,
                         0b00001100,
                         0b00001100,
                         0b00001100,
                         0b00111111};

unsigned char dua[8] = {0b00111111,
                        0b00000011,
                        0b00000011,
                        0b00001100,
                        0b00110000,
                        0b00110000,
                        0b00110000,
                        0b00111111};

unsigned char tiga[8] = {0b00111111,
                         0b00000011,
                         0b00000011,
                         0b00111111,
                         0b00000011,
                         0b00000011,
                         0b00000011,
                         0b00111111};

unsigned char empat[8] = {0b00000111,
                          0b00001011,
                          0b00010011,
                          0b00100011,
                          0b00111111,
                          0b00000011,
                          0b00000011,
                          0b00000011};

unsigned char lima[8] = {0b00111111,
                         0b00110000,
                         0b00110000,
                         0b00111100,
                         0b00000010,
                         0b00000011,
                         0b00000010,
                         0b00111110};

unsigned char enam[8] = {0b00111111,
                         0b00110000,
                         0b00110000,
                         0b00111111,
                         0b00110011,
                         0b00110011,
                         0b00110011,
                         0b00111111};

unsigned char tujuh[8] = {0b00111111,
                          0b00000011,
                          0b00000011,
                          0b00000110,
                          0b00001100,
                          0b00011000,
                          0b00110000,
                          0b00110000};

unsigned char delapan[8] = {0b00111111,
                            0b00110011,
                            0b00110011,
                            0b00111111,
                            0b00110011,
                            0b00110011,
                            0b00110011,
                            0b00111111};

unsigned char sembilan[8] = {0b00111111,
                             0b00110011,
                             0b00110011,
                             0b00110011,
                             0b00111111,
                             0b00000011,
                             0b00000011,
                             0b00111111};

int t;
int i = 0;
int ii = 0;

int sw1,sw2,sw3;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1,INPUT_PULLUP);   // INPUT DENGAN PULLUP
  pinMode(A2,INPUT_PULLUP);   // INPUT DENGAN PULLUP
  pinMode(A3,INPUT_PULLUP);   // INPUT DENGAN PULLUP
  
  // kolom
  DDRB = B11111111;           // SETTING IC ATMEGA
  PORTB = B00000000;          // SETTING IC ATMEGA

  // baris
  DDRD = B11111111;           // SETTING IC ATMEGA
  PORTD = B00000000;          // SETTING IC ATMEGA
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sw1=digitalRead(A1);
  sw2=digitalRead(A2);
  sw3=digitalRead(A3);

  if(sw1 == LOW)
  {
    countUp();              // JALANKAN FUNGSI
    ii = ii+1;
  }
  if(sw2 == LOW)
  {
    countDown();            // JALANKAN FUNGSI
    ii = ii+1;
  }
  reset();
  if(sw3 == LOW)
  {
    ii = 0;
  }
  
}

void reset() {
  if(ii == 0)
  {
      for (t=0; t < 1000; t++)
    {
     if(i==8)
     {
      i=0;
     }
      PORTD = baris[i];
      PORTB = nol[i];             // NOL
      i=i+1;
      delay(1);
    }
  }
}

void countUp() {
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = nol[i];             // NOL
      i=i+1;
      delay(1);
    }
  
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = satu[i];            // SATU
      i=i+1;
      delay(1);
    }
  
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = dua[i];             // DUA
      i=i+1;
      delay(1);
    }
  

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = tiga[i];            // TIGA
      i=i+1;
      delay(1);
    }
  
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = empat[i];           // EMPAT
      i=i+1;
      delay(1);
    }

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = lima[i];            // LIMA
      i=i+1;
      delay(1);
    }

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = enam[i];            // ENAM
      i=i+1;
      delay(1);
    }

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = tujuh[i];           // TUJUH
      i=i+1;
      delay(1);
    }
  
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = delapan[i];         // DELAPAN
      i=i+1;
      delay(1);
    }
    
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = sembilan[i];        // SEMBILAN
      i=i+1;
      delay(1);
    }

}

void countDown() {
    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = sembilan[i];        // SEMBILAN
      i=i+1;
      delay(1);
    }


    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = delapan[i];         // DELAPAN
      i=i+1;
      delay(1);
    }

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = tujuh[i];           // TUJUH
      i=i+1;
      delay(1);
    }


    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = enam[i];            // ENAM
      i=i+1;
      delay(1);
    }

    for (t=0; t < 1000; t++)
    {
      if(i==8)
      {
        i=0;
      }
      PORTD = baris[i];
      PORTB = lima[i];            // LIMA
      i=i+1;
      delay(1);
    }
  
   for (t=0; t < 1000; t++)
   {
    if(i==8)
    {
     i=0;
    }
    PORTD = baris[i];
    PORTB = empat[i];           // EMPAT
    i=i+1;
    delay(1);
  }

  for (t=0; t < 1000; t++)
  {
    if(i==8)
    {
      i=0;
    }
    PORTD = baris[i];
    PORTB = tiga[i];            // TIGA
    i=i+1;
    delay(1);
  }

  for (t=0; t < 1000; t++)
  {
    if(i==8)
    {
      i=0;
    }
    PORTD = baris[i];
    PORTB = dua[i];             // DUA
    i=i+1;
    delay(1);
  }

  for (t=0; t < 1000; t++)
  {
    if(i==8)
    {
      i=0;
    }
    PORTD = baris[i];
    PORTB = satu[i];            // SATU
    i=i+1;
    delay(1);
  }

  for (t=0; t < 1000; t++)
  {
    if(i==8)
    {
      i=0;
    }
    PORTD = baris[i];
    PORTB = nol[i];             // NOL
    i=i+1;
    delay(1);
  }
  
}
