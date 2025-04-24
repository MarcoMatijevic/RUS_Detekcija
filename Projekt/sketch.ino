#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/rtc_io.h"
#include "esp_sleep.h"      //dodavanje potrebnih biblioteka

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1      //konfiguracija oled ekrana
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIN_TRIG_LIJEVI 13
#define PIN_ECHO_LIJEVI 12    
#define PIN_TRIG_DESNI 14
#define PIN_ECHO_DESNI 27     // Definiranje pinova za senzore udaljenosti

#define LED_CRVENA 26
#define LED_ZUTA 25
#define LED_ZELENA 33
#define ZVUCNIK 2     // Definiranje pinova za LED-ice i za zvucnik

int udaljenostLijevi, udaljenostDesni;

int izmjeriUdaljenost(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 25000) / 58;  // Max timeout 25ms
}

String interpretiraj(int udaljenost) {
  if (udaljenost >= 350) return "Daleko";
  else if (udaljenost >= 200) return "Srednje";
  else return "Blizu";
}

void setup() {

  pinMode(PIN_TRIG_LIJEVI, OUTPUT);
  pinMode(PIN_ECHO_LIJEVI, INPUT);
  pinMode(PIN_TRIG_DESNI, OUTPUT);
  pinMode(PIN_ECHO_DESNI, INPUT);

  pinMode(LED_CRVENA, OUTPUT);
  pinMode(LED_ZUTA, OUTPUT);
  pinMode(LED_ZELENA, OUTPUT);    // Inicijalizacija pinova

  pinMode(ZVUCNIK, OUTPUT);

  Serial.begin(115200);

  // Inicijalizacija OLED ekrana
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // I2C adresa 0x3C
    Serial.println(F("OLED ekran nije pronađen"));
    while (true);
  }

  // Konfiguracija izvora buđenja (pin echo senzora)
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_ECHO_LIJEVI, 1);  // Budi se na HIGH s ECHO lijevog senzora

  // Prikaz poruke prilikom buđenja
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Aktivacija...");
  display.display();
  delay(1000);
}

void loop() {

  while (true) {
    // Mjerenje udaljenosti
    udaljenostLijevi = izmjeriUdaljenost(PIN_TRIG_LIJEVI, PIN_ECHO_LIJEVI);
    udaljenostDesni = izmjeriUdaljenost(PIN_TRIG_DESNI, PIN_ECHO_DESNI);

    // Odredi bliži senzor
    int minUdaljenost = udaljenostLijevi;
    String najbliziSenzor = "lijevi";
    if (udaljenostDesni < udaljenostLijevi) {
      minUdaljenost = udaljenostDesni;
      najbliziSenzor = "desni";
    }

    // Reset svih LED-ica i zvučnika
    digitalWrite(LED_ZELENA, LOW);
    digitalWrite(LED_ZUTA, LOW);
    digitalWrite(LED_CRVENA, LOW);
    noTone(ZVUCNIK);

    // OLED priprema
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print("Lijevi: ");
    display.print(udaljenostLijevi);
    display.print(" cm");

    display.setCursor(0, 10);
    display.print("Desni: ");
    display.print(udaljenostDesni);
    display.print(" cm");

    // Režim rada ovisno o minimalnoj udaljenosti
    if (minUdaljenost >= 350) {
      // Normalan režim
      digitalWrite(LED_ZELENA, HIGH);
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.println("Sustav aktivan");

      display.display();
      delay(2000);  // Kratko zadržavanje

      // Priprema za sleep
      digitalWrite(LED_ZELENA, LOW);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Spavanje...");
      display.display();
      delay(1000);

      esp_deep_sleep_start();  // Ulazak u duboki san

    } else if (minUdaljenost >= 200) {
      // Upozorenje (2–4 m)
      for (int i = 0; i < 2; i++) {
        digitalWrite(LED_ZUTA, HIGH);
        tone(ZVUCNIK, 262, 100);
        delay(500);
        digitalWrite(LED_ZUTA, LOW);
        delay(500);
      }
      display.setCursor(0, 30);
      display.setTextSize(1);
      display.println("OPREZ: Vozilo u blizini");

    } else {
      // Kritično stanje (< 2 m)
      digitalWrite(LED_CRVENA, HIGH);
      tone(ZVUCNIK, 262);
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.println("PAZI!");
      display.setCursor(0, 50);
      display.setTextSize(1);
      display.print("VOZILO BLIZU! (");
      display.print(najbliziSenzor);
      display.print(")");
    }

    display.display();
    delay(500);  // Kratki delay prije novog očitanja
  }
}
