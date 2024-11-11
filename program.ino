include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h> 
#include <NewPing.h> 
// Konfigurasi Pin 
#define TRIG_PIN 12        // Pin Trig sensor ultrasonik 
#define ECHO_PIN 14        // Pin Echo sensor ultrasonik 
#define LED_MERAH 26       // Pin LED merah 
#define LED_KUNING 27      // Pin LED kuning 
#define LED_HIJAU 25       // Pin LED hijau 
#define MAX_DISTANCE 200   // Jarak maksimal sensor ultrasonik (cm) 
#define SERVO_PIN 13       // Pin Servo 
// Objek untuk LCD, Servo, dan Sensor Ultrasonik 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C untuk LCD 6x2 
Servo servoMotor; 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
void setup() { 
  // Inisialisasi LCD 
    lcd.begin(16, 2); 
      lcd.backlight(); 
        // Inisialisasi pin LED sebagai output 
          pinMode(LED_MERAH, OUTPUT); 
            pinMode(LED_KUNING, OUTPUT); 
              pinMode(LED_HIJAU, OUTPUT); 
                // Inisialisasi Servo 
                  servoMotor.attach(SERVO_PIN); 
                    servoMotor.write(0);  // Palang dalam posisi tertutup 
                      // Menampilkan pesan awal di LCD 
                        lcd.setCursor(0, 0); 
                          lcd.print("Palang Otomatis"); 
                            lcd.setCursor(0, 1); 
                              lcd.print("Sistem Siap"); 
                                delay(2000);  // Tunggu 2 detik sebelum memulai 
                                  lcd.clear(); 
                                  } 
                                  void loop() { 
                                    // Baca jarak dari sensor ultrasonik 
                                      int distance = sonar.ping_cm(); 
                                        if (distance > 0 && distance <= 20) {  // Kendaraan terdeteksi dalam jarak 20 cm 
                                            lcd.clear(); 
                                                lcd.setCursor(0, 0); 
                                                    lcd.print("Menunggu..."); 
                                                        digitalWrite(LED_MERAH, HIGH);  // LED Merah nyala 
                                                            digitalWrite(LED_HIJAU, LOW);   // LED Hijau mati 
                                                                delay(2000);  // Tunggu 2 detik 
                                                                    // Buka palang pintu 
                                                                        servoMotor.write(90);  // Servo buka ke posisi 90 derajat 
                                                                            digitalWrite(LED_MERAH, LOW);   // LED Merah mati 
                                                                                digitalWrite(LED_HIJAU, HIGH);  // LED Hijau nyala 
                                                                                    lcd.clear(); 
                                                                                        lcd.setCursor(0, 0); 
                                                                                            lcd.print("Silakan Masuk"); 
                                                                                                delay(3000);  // Tunggu 3 detik agar kendaraan bisa lewat 
                                                                                                    // Tutup palang pintu 
                                                                                                        servoMotor.write(0);  // Servo kembali ke posisi 0 derajat 
                                                                                                            digitalWrite(LED_HIJAU, LOW);  // LED Hijau mati 
                                                                                                                digitalWrite(LED_MERAH, HIGH); // LED Merah nyala 
                                                                                                                    lcd.clear(); 
                                                                                                                        lcd.setCursor(0, 0); 
                                                                                                                            lcd.print("Sistem Siap"); 
                                                                                                                                delay(1000);  // Tunggu 1 detik sebelum kembali ke awal 
                                                                                                                                  } else { 
                                                                                                                                      // Jika tidak ada kendaraan, tampilkan sistem siap 
                                                                                                                                          lcd.setCursor(0, 0); 
                                                                                                                                              lcd.print("Sistem Siap   "); 
                                                                                                                                                  digitalWrite(LED_MERAH, HIGH); // LED Merah nyala 
                                                                                                                                                      digitalWrite(LED_HIJAU, LOW);  // LED Hijau mati 
                                                                                                                                                        } 
                                                                                                                                                          delay(100);  // Delay kecil untuk mengurangi pembacaan berulang terlalu cepat 
                                                                                                                                                          }