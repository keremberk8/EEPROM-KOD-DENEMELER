# EEPROM Kod Denemeleri

Arduino projelerinde **EEPROM üzerinden kalıcı veri saklama ve okuma** mantığını geliştirmek için hazırlanmış deneysel kod koleksiyonudur.

Bu repository özellikle renk sensörü kalibrasyon değerlerinin EEPROM'a kaydedilmesi ve daha sonra başka bir program tarafından okunması sürecini test etmek amacıyla oluşturulmuştur.

## ✨ İçerik

- EEPROM'a `int` değerlerin kaydedilmesi
- EEPROM'dan kalibrasyon değerlerinin okunması
- Renk sensörü için kırmızı, mavi ve yeşil limitlerin saklanması
- Kalibrasyon sırasında çoklu ölçüm alma
- Ortalama ve standart sapma ile ölçüm stabilizasyonu
- Kaydedilen verilerin seri port üzerinden kontrol edilmesi

## 📂 Proje Yapısı

```text
EEPROM-KOD-DENEMELER/
├── alan/
│   └── alan.ino      # EEPROM'daki değerleri okur
├── veren/
│   └── veren.ino     # Renk kalibrasyonu yapar ve EEPROM'a kaydeder
└── README.md
```

## 🔬 `veren` — Kalibrasyon ve Kayıt

`veren.ino`, TCS benzeri bir renk sensöründen kırmızı, mavi ve yeşil kanalları ölçerek kalibrasyon limitleri oluşturur.

Kalibrasyon seri port üzerinden yapılır:

```text
k → Kırmızı
m → Mavi
y → Yeşil
```

Her renk için birden fazla ölçüm alınır ve daha kararlı bir sonuç elde etmek amacıyla istatistiksel filtreleme uygulanır. Sonrasında alt/üst limitler EEPROM'a 4-byte aralıklarla yazılır.

## 📖 `alan` — EEPROM Okuma

`alan.ino`, daha önce kaydedilmiş kalibrasyon değerlerini EEPROM'dan okuyarak Serial Monitor üzerinde gösterir.

Saklanan veri sırası:

| Adres | Veri |
|---:|---|
| `0` | Kırmızı alt limit |
| `4` | Kırmızı üst limit |
| `8` | Mavi alt limit |
| `12` | Mavi üst limit |
| `16` | Yeşil alt limit |
| `20` | Yeşil üst limit |

## 🛠️ Teknolojiler

- Arduino
- C/C++
- `EEPROM.h`
- Renk sensörü
- Serial Monitor

## 🚀 Kullanım

1. `veren/veren.ino` dosyasını Arduino'ya yükleyin.
2. Serial Monitor'ü `9600 baud` ile açın.
3. Kalibrasyon yapmak istediğiniz rengi ilgili komutla başlatın.
4. Kalibrasyon tamamlandıktan sonra değerler EEPROM'a kaydedilir.
5. `alan/alan.ino` ile EEPROM değerlerini okuyup kontrol edin.

## ⚠️ Not

EEPROM sınırlı sayıda yazma döngüsüne sahip kalıcı hafızadır. Kalibrasyon gibi seyrek gerçekleştirilen işlemlerde kullanılması uygundur; döngü içerisinde gereksiz `EEPROM.put()` çağrılarından kaçınılmalıdır.

## 🚧 Geliştirme Durumu

**Deneysel / yardımcı modül**

Bu repository, daha büyük Arduino ve robotik projelerinde kullanılabilecek EEPROM tabanlı veri saklama altyapısının geliştirilmesi için hazırlanmıştır.
