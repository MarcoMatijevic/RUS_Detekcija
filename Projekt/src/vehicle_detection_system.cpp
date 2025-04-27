#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/rtc_io.h"
#include "esp_sleep.h"

// ---  OLED konfiguracija --- 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Definicije pinova --- 
#define PIN_TRIG_LIJEVI 13
#define PIN_ECHO_LIJEVI 12    
#define PIN_TRIG_DESNI 14
#define PIN_ECHO_DESNI 27

#define LED_CRVENA 26
#define LED_ZUTA   25
#define LED_ZELENA 33
#define ZVUCNIK    2
#define VIBRA_PIN 32

// --- Apstraktna klasa Senzor ---
class Sensor {
  public:
    virtual void begin() = 0;
    virtual int readDistance() = 0;
};

// --- Ultrazvučni senzor ---
class UltrasonicSensor : public Sensor {
  private:
    int trigPin, echoPin;

  public:
    UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}

    void begin() override {
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    int readDistance() override {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      return pulseIn(echoPin, HIGH, 25000) / 58; // Max timeout 25ms
    }
};

// --- Klasa za prikaz na OLED-u ---
class DisplayManager {
  public:
    static void init() {
      if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("OLED ekran nije pronađen"));
        while (true);
      }
    }

    static void showStartup() {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Aktivacija...");
      display.display();
      delay(1000);
    }

    static void showSpavanje() {
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Spavanje...");
      display.display();
      delay(1000);
    }

    static void showStatus(int leftDist, int rightDist, String status, String sensor = "") {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);

      display.setCursor(0, 0);
      display.print("Lijevi: ");
      display.print(leftDist);
      display.print(" cm");

      display.setCursor(0, 10);
      display.print("Desni: ");
      display.print(rightDist);
      display.print(" cm");

      display.setCursor(0, 30);
      display.setTextSize(status == "PAZI!" ? 2 : 1);
      display.println(status);

      if (sensor != "") {
        display.setCursor(0, 50);
        display.setTextSize(1);
        display.print("VOZILO BLIZU! (");
        display.print(sensor);
        display.print(")");
      }

      display.display();
    }
};

// --- Klasa za upravljanje signalizacijom ---
class AlertManager {
  public:
    static void init() {
      pinMode(LED_CRVENA, OUTPUT);
      pinMode(LED_ZUTA, OUTPUT);
      pinMode(LED_ZELENA, OUTPUT);
      pinMode(ZVUCNIK, OUTPUT);
      pinMode(VIBRA_PIN, OUTPUT);
      digitalWrite(VIBRA_PIN, LOW);
    }

    static void reset() {
      digitalWrite(LED_ZELENA, LOW);
      digitalWrite(LED_ZUTA, LOW);
      digitalWrite(LED_CRVENA, LOW);
      noTone(ZVUCNIK);
      digitalWrite(VIBRA_PIN, LOW);
    }

    static void normalMode() {
      digitalWrite(LED_ZELENA, HIGH);
    }

    static void warningMode() {
      for (int i = 0; i < 2; i++) {
        digitalWrite(LED_ZUTA, HIGH);
        tone(ZVUCNIK, 262, 100);
        digitalWrite(VIBRA_PIN, HIGH); 
        delay(100);                      
        digitalWrite(VIBRA_PIN, LOW);
        delay(400);
        digitalWrite(LED_ZUTA, LOW);
        delay(500);
      }
    }

    static void criticalMode() {
      digitalWrite(LED_CRVENA, HIGH);
      tone(ZVUCNIK, 262);
      digitalWrite(VIBRA_PIN, HIGH); 
    }
};

// --- Globalne instance ---
UltrasonicSensor lijeviSensor(PIN_TRIG_LIJEVI, PIN_ECHO_LIJEVI);
UltrasonicSensor desniSensor(PIN_TRIG_DESNI, PIN_ECHO_DESNI);

// --- Funkcija za interpretaciju udaljenosti ---
String interpretiraj(int udaljenost) {
  if (udaljenost >= 350) return "Daleko";
  else if (udaljenost >= 200) return "Srednje";
  else return "Blizu";
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  
  lijeviSensor.begin();
  desniSensor.begin();
  
  AlertManager::init();
  DisplayManager::init();
  
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_ECHO_LIJEVI, 1);

  DisplayManager::showStartup();
}

// --- Loop ---
void loop() {
  while (true) {
    int udaljenostLijevi = lijeviSensor.readDistance();
    int udaljenostDesni = desniSensor.readDistance();

    int minUdaljenost = udaljenostLijevi;
    String najbliziSenzor = "lijevi";
    if (udaljenostDesni < udaljenostLijevi) {
      minUdaljenost = udaljenostDesni;
      najbliziSenzor = "desni";
    }

    AlertManager::reset();

    if (minUdaljenost >= 350) {
      // Normalno stanje
      AlertManager::normalMode();
      DisplayManager::showStatus(udaljenostLijevi, udaljenostDesni, "Sustav aktivan");
      delay(2000);

      AlertManager::reset();
      DisplayManager::showSpavanje();
      esp_deep_sleep_start();
    } 
    else if (minUdaljenost >= 200) {
      // Upozorenje
      AlertManager::warningMode();
      DisplayManager::showStatus(udaljenostLijevi, udaljenostDesni, "OPREZ: Vozilo u blizini");
    } 
    else {
      // Kritično stanje
      AlertManager::criticalMode();
      DisplayManager::showStatus(udaljenostLijevi, udaljenostDesni, "PAZI!", najbliziSenzor);
    }

    delay(500);
  }
}
