#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h" // Knihovna, kterou jsme právě stáhli

// --- NASTAVENÍ VAŠÍ WIFI ---
const char* ssid = "Zabnet_kostel2";
const char* password = "7b03874v";

// --- NASTAVENÍ I2S PINŮ PRO ESP32-S3 ---
#define I2S_BCLK      4
#define I2S_LRC       5
#define I2S_DOUT      6

// Vytvoření objektu pro audio knihovnu
Audio audio;

void setup() {
  // Zapnutí sériového portu pro výpis hlášek do PC
  Serial.begin(115200);
  delay(1000); // Počkáme sekundu na ustálení

  Serial.println("\n--- Test Zvuku Start ---");

  // 1. Připojení k Wi-Fi
  Serial.printf("Pripojuji k WiFi %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" PRIPOJENO!");

  // 2. Nastavení Audio knihovny a I2S pinů
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(10); // Nastavení hlasitosti 0 až 21

  // 3. Spuštění přehrávání (např. MP3 stream Evropy 2)
  Serial.println("Zacinam prehravat radio...");
  audio.connecttohost("http://icecast2.play.cz/radiobeat128.mp3");
}

void loop() {
  // Tato funkce se musí točit pořád dokola, aby knihovna 
  // stíhala stahovat a posílat zvukové balíčky do zesilovače
  audio.loop();
}

// Tyto funkce nám v Serial Monitoru vypíšou informace z rádia (název písničky atd.)
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     "); Serial.println(info);
}