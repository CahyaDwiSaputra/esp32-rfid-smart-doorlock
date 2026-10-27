#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define SS_PIN 5
#define RST_PIN 27
#define SERVO_PIN 32
#define BUZZER_PIN 25
#define LED_PIN 26

// Masukkan UID Kartu yang diizinkan (Authorized Tag)
byte authorizedUID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // Ganti sesuai UID kartu Anda

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0); // Posisi terkunci (0 derajat)

  Serial.println("=== SISTEM SMART DOORLOCK RFID ESP32 AKTIF ===");
  Serial.println("Silakan dekatkan kartu RFID Anda...");
}

void loop() {
  // Cek apakah ada kartu baru terdeteksi
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID Kartu Terdeteksi: ");
  String content = "";
  bool accessGranted = true;

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < 4 && rfid.uid.uidByte[i] != authorizedUID[i]) {
      accessGranted = false;
    }
  }
  Serial.println();

  if (accessGranted) {
    Serial.println(">>> STATUS: AKSES DITERIMA! Pintu Terbuka.");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000, 200); // Beep pendek

    myServo.write(180); // Buka pintu (180 derajat)
    delay(5000);        // Pintu terbuka selama 5 detik

    myServo.write(0);   // Kunci kembali
    digitalWrite(LED_PIN, LOW);
    Serial.println(">>> Pintu Terkunci Kembali.");
  } else {
    Serial.println(">>> STATUS: AKSES DITOLAK! Kartu Tidak Dikenal.");
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 500, 150);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
