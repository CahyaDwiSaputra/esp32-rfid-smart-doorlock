# 🔐 ESP32 RFID MFRC522 Smart Doorlock Access Control

Sistem kontrol akses pintu pintar (*smart door lock*) berbasis mikrokontroler **ESP32** dan sensor kartu **RFID MFRC522** dengan aktuator motor servo SG90 serta indikator audiovisual Buzzer & LED.

---

## 🚀 Fitur Utama
- **Autentikasi Kartu RFID**: Verifikasi identitas UID kartu/tag 13.56 MHz melalui protokol komunikasi kecepatan tinggi **SPI**.
- **Mekanisme Kunci Otomatis (Servo)**:
  - Posisi default: **0°** (Terkunci / *Locked*).
  - Saat akses terverifikasi: Berputar ke **180°** (Pintu Terbuka / *Unlocked*), menahan selama 5 detik, lalu kembali mengunci secara otomatis.
- **Feedback Audiovisual**:
  - **Akses Diterima**: LED menyala hijau/biru solid + 1x beep konfirmasi.
  - **Akses Ditolak**: LED berkedip cepat + 3x alert buzzer nada rendah.
- **Laporan Praktikum**: PDF laporan praktikum lengkap di folder `docs/`.

---

## 🛠️ Skema Rangkaian & Pinout (ESP32)
| Komponen | Pin Modul | Pin ESP32 (GPIO) | Keterangan |
|---|---|---|---|
| **MFRC522 RFID** | 3.3V | 3V3 | Catu daya **(Jangan hubungkan ke 5V!)** |
| **MFRC522 RFID** | GND | GND | Ground |
| **MFRC522 RFID** | RST | **GPIO 27** | Reset pin |
| **MFRC522 RFID** | SDA / SS | **GPIO 5** | SPI Slave Select |
| **MFRC522 RFID** | SCK | **GPIO 18** | SPI Clock |
| **MFRC522 RFID** | MOSI | **GPIO 23** | SPI Master Out Slave In |
| **MFRC522 RFID** | MISO | **GPIO 19** | SPI Master In Slave Out |
| **Motor Servo SG90** | PWM (Oranye/Kuning) | **GPIO 32** | Sinyal kontrol posisi PWM |
| **Buzzer Aktif** | Positif (+) | **GPIO 25** | Nada peringatan audio |
| **LED Indikator** | Anoda (+) | **GPIO 26** | Resistor 220Ω |

---

## 📦 Kebutuhan Library
- `MFRC522` (oleh GithubCommunity / Miguel Balboa)
- `ESP32Servo` (oleh Kevin Harrington)

---

## 👤 Author
- **Cahya Dwi Saputra**
