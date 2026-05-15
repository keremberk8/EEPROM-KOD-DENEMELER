#include <EEPROM.h>

#define s0 52
#define s1 50
#define s2 46
#define s3 48
#define out 44

float kirmizi, mavi, yesil;
int kirmizi_veriler[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int mavi_veriler[10] =   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int yesil_veriler[10] =   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int mavi_ust_limit,  mavi_alt_limit;
int kirmizi_alt_limit, kirmizi_ust_limit;
int yesil_alt_limit, yesil_ust_limit;

 bool k =false, m=false, y=false;
 bool tekrar_kalibre_lazimmi = true;


void setup(){

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

Serial.begin(9600);
Serial.println("kalibrasyon için renk girin (k/m/y)");
}

void loop() {
if (Serial.available()) {
    char c = Serial.read();

    if (c == 'k') { kalibrasyon('k');}
    if (c == 'm') { kalibrasyon('m');}
    if (c == 'y') { kalibrasyon('y'); }
}
if(k&&m&&y){
eepromKaydet();
k= false;
m= false;
y= false;
}

}

void kalibrasyon(char renk){

tekrar_kalibre_lazimmi = true;
while(tekrar_kalibre_lazimmi){
int deger = olcum();
Serial.println("deger" + String(deger));

if(renk=='k') { 
kirmizi_alt_limit = deger - 40; 
kirmizi_ust_limit = deger + 40; 

Serial.println("Kirmizi ust Limit: " + String(kirmizi_alt_limit) + " kirmizi alt limit" + String(kirmizi_ust_limit));
int deneme1 = olcum(); // sağlama yapcazzz
delay(100);
int deneme2 = olcum(); // hehrheheh

if((kirmizi_ust_limit >= deneme1 && deneme1 >= kirmizi_alt_limit)  && (kirmizi_ust_limit >= deneme2 && deneme2 >= kirmizi_alt_limit) ){
Serial.println(" kirmizi kalibresi ve testi tamamdir");
Serial.println("Dogrulama degerleri: " + String(deneme1) + " | " + String(deneme2));
tekrar_kalibre_lazimmi = false;
k=true;
}
}

if(renk=='m') { 
mavi_alt_limit = deger - 30; 
mavi_ust_limit = deger + 30; 
Serial.println("mavi ust Limit: " + String(mavi_alt_limit) + " mavi alt limit" + String(mavi_ust_limit));
int deneme1 = olcum(); // sağlama yapcazzz
delay(100);
int deneme2 = olcum();

if((mavi_ust_limit >= deneme1 && deneme1 >= mavi_alt_limit) && (mavi_ust_limit >= deneme2 && deneme2 >= mavi_alt_limit) ){
Serial.println(" mavi kalibresi ve testi tamamdir");
Serial.println("Dogrulama degerleri: " + String(deneme1) + " | " + String(deneme2));
tekrar_kalibre_lazimmi = false;
m=true;
}
}

if(renk=='y') { 
yesil_alt_limit = deger - 40;
yesil_ust_limit = deger + 40;
Serial.println("yesil ust Limit: " + String(yesil_alt_limit) + " yesil alt limit" + String(yesil_ust_limit));
int deneme1 = olcum(); // sağlama yapcazz
delay(100);
int deneme2= olcum();

if((yesil_ust_limit >= deneme1 && deneme1 >= yesil_alt_limit )&& (yesil_ust_limit >= deneme2 && deneme2 >= yesil_alt_limit )){
Serial.println(" yesil kalibresi ve testi tamamdir");
Serial.println("Dogrulama degerleri: " + String(deneme1) + " | " + String(deneme2));
tekrar_kalibre_lazimmi = false;
y=true;
}
}
}
}

int olcum() {
  //verileri güncelliyoruz
  for (int i = 0; i < 10; i++) {
    olc();
    kirmizi_veriler[i] = kirmizi;
    mavi_veriler[i] = mavi;
    yesil_veriler[i] = yesil;
  }

  // 10 TANE VERİ ALIP İÇELERİNDEN TUTARLI HALE GETİRİYORUZ
  // ÖRNEK : 64,65,68,97 ÖLÇMÜŞ OLALIM -> 67 GİBİ BİR SONUÇ DÖNDÜRÜYOR ANLIK DALGALANMALARDAN ETKİLENMEMİŞ OLUYORUZ
  kirmizi = stabilSonucuBul(kirmizi_veriler, 10);
  mavi = stabilSonucuBul(mavi_veriler, 10);
   yesil = stabilSonucuBul(yesil_veriler, 10);

 

  int sonuc = ((float)mavi / (float)kirmizi /(float)yesil) * 10000;
  Serial.println(sonuc);
  
Serial.println("MAVİ");  
Serial.println(mavi);

Serial.println("KIRMIZI");  
Serial.println(kirmizi);

Serial.println("yeşil");  
Serial.println(yesil);


  return sonuc;
}

void olc() {
  //RENK SENSÖRÜ KIRMIZI FİLTRE AYARI
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  delay(20);
  kirmizi = pulseIn(out, LOW);

  //RENK SENSÖRÜ MAVİ FİLTRE AYARI
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  delay(20);
  mavi = pulseIn(out, LOW);

   //RENK SENSÖRÜ YESİL FİLTRE AYARI
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  delay(20);
  yesil = pulseIn(out, LOW);
}

void eepromKaydet() {
  int adres = 0;
  int atlama = 4; // Her veri için 4 byte yer ayırıyoruz (ne olur ne olmaz!)

  // Kırmızı Limitleri
  EEPROM.put(adres, kirmizi_alt_limit); adres += atlama;
  EEPROM.put(adres, kirmizi_ust_limit); adres += atlama;
  
  // Mavi Limitleri
  EEPROM.put(adres, mavi_alt_limit);    adres += atlama;
  EEPROM.put(adres, mavi_ust_limit);    adres += atlama;
  
  // Yeşil Limitleri
  EEPROM.put(adres, yesil_alt_limit);   adres += atlama;
  EEPROM.put(adres, yesil_ust_limit);   adres += atlama;

  Serial.println("------------------------------------------");
  Serial.println("VERILER 4-BYTE ARALIKLARLA GUVENE ALINDI!");
  Serial.println("Son kaydedilen adres: " + String(adres - atlama));
  Serial.println("------------------------------------------");
}




// ***********Ortalama hesaplayan fonksiyon**********
double ortalamaHesapla(const int arr[], int size) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}

// Standart sapmayı hesaplayan fonksiyon
double standartSapmaHesapla(const int arr[], int size, double mean) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += pow(arr[i] - mean, 2);
  }
  return sqrt(sum / size);
}

// Uç değerleri filtreleyerek en istikrarlı değeri bul
int stabilSonucuBul(const int arr[], int size) {
  // Dizinin ortalamasını hesapla
  double mean = ortalamaHesapla(arr, size);

  // Dizinin standart sapmasını hesapla
  double stdDev = standartSapmaHesapla(arr, size, mean);

  // Standart sapmanın 1.5 katından daha uzak olan değerleri göz ardı et
  const double threshold = 1.5 * stdDev;

  // Filtrelenmiş dizinin ortalamasını ve en yakın değeri bul
  double filteredSum = 0;
  int filteredCount = 0;
  int closestValue = arr[0];
  double minDifference = 1e6;  // çok büyük bir sayı kullanıyoruz

  for (int i = 0; i < size; i++) {
    if (fabs(arr[i] - mean) <= threshold) {
      filteredSum += arr[i];
      filteredCount++;

      // Ortalamaya en yakın değeri bl
      double diff = fabs(arr[i] - mean);
      if (diff < minDifference) {
        minDifference = diff;
        closestValue = arr[i];
      }
    }
  }

  return closestValue;
}