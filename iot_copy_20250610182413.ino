#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Membuat objek sensor ADXL345_Unified
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(115200); // Inisialisasi Serial Monitor

  Serial.println("Inisialisasi ADXL345 (Unified) dengan pin I2C kustom...");

  // Inisialisasi komunikasi I2C pada pin GPIO 25 (SDA) dan GPIO 26 (SCL)
  Wire.begin(25, 26); // SDA = GPIO 25, SCL = GPIO 26

  // Coba inisialisasi sensor
  if (!accel.begin()) {
    Serial.println("Tidak dapat menemukan sensor ADXL345. Periksa koneksi atau pin I2C.");
    while (1) yield(); // Berhenti jika sensor tidak ditemukan
  }
  Serial.println("Sensor ADXL345 terdeteksi pada pin kustom!");

  // Mengatur rentang pengukuran (opsional, defaultnya adalah +/- 2G)
  // accel.setRange(ADXL345_RANGE_16_G);

  // Mengatur data rate (opsional, defaultnya 100 Hz)
  // accel.setDataRate(ADXL345_DATARATE_100_HZ);
}

void loop() {
  /* Baca nilai akselerasi dari sensor */
  sensors_event_t event;
  accel.getEvent(&event);

  /* Cetak nilai akselerasi */
  Serial.print("Akselerasi X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  // Logika deteksi getaran
  float threshold = 5.0; // Ganti dengan nilai ambang batas yang sesuai

  if (abs(event.acceleration.x) > threshold ||
      abs(event.acceleration.y) > threshold ||
      abs(event.acceleration.z) > threshold) {
    Serial.println("!!! GETARAN TERDETEKSI !!!");
    // Di sini Anda bisa menambahkan kode untuk memicu tindakan
  }

  delay(1000); // Jeda sebentar sebelum membaca lagi
}