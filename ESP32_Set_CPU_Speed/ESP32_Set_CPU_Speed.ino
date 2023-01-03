#include "esp32-hal-cpu.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setCpuFrequencyMhz(240);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Frekuensi CPU :");
  Serial.print(getCpuFrequencyMhz());
  Serial.println(" Mhz");
  Serial.println("______________________________________");
  delay(1000);
}
