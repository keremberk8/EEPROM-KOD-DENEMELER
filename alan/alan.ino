#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  int deger;

  Serial.println("--- RENK AYARLARI ---");

  // Kırmızı
  EEPROM.get(0, deger);
  Serial.print("Kirmizi Alt: "); Serial.println(deger);
  EEPROM.get(4, deger);
  Serial.print("Kirmizi Ust: "); Serial.println(deger);

  // Mavi
  EEPROM.get(8, deger);
  Serial.print("Mavi Alt: "); Serial.println(deger);
  EEPROM.get(12, deger);
  Serial.print("Mavi Ust: "); Serial.println(deger);

  // Yeşil
  EEPROM.get(16, deger);
  Serial.print("Yesil Alt: "); Serial.println(deger);
  EEPROM.get(20, deger);
  Serial.print("Yesil Ust: "); Serial.println(deger);

  Serial.println("---------------------");
}

void loop() {
  // Burası boş
}