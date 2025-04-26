# Bicycle Vehicle Proximity Detection System  

🚴 **Detekcija približavanja vozila biciklu** 🚗  

**LINK NA PROJEKT:**  
🔗 [Wokwi Simulator](https://wokwi.com/projects/428865980507846657)  
🔗 [Napredna ESP32 verzija](https://wokwi.com/projects/429025123835618305)  

---

## 📦 Komponente  
### 💻 Osnovna verzija (Arduino Mega)
- **Arduino Mega** – Glavni mikrokontroler  
- **HC-SR04** – Ultrazvučni senzor udaljenosti  
- **LED indikatori** (zelena/žuta/crvena)  
- **Buzzer** – Zvučno upozorenje    
- **LCD1602 s I2C** – Prikaz stanja  

### 🚀 Napredna verzija (ESP32 u Wokwiju)
- **ESP32** – WiFi/BLE sposobnosti  
- **Dodatni HC-SR04** – Za dvije strane  
- **OLED SSD1306** – Grafički displej
- **Vibra Motor** – Haptičko upozorenje

---

## 🛠️ Funkcionalnost  
### 🟢 Normalan režim
- Zelena LED aktivna  
- LCD: "Sustav aktivan"  
- Kontinuirano mjerenje udaljenosti  

### 🟡 Upozorenje (2-3.5m)
- Žuta LED treperi  
- Kratki zvučni signali (0.1s interval)  
- LCD: "OPREZ: Vozilo u blizini"
- Slabe vibracije

### 🔴 Kritično stanje (<2m)
- Crvena LED + buzzer kontinuirano  
- LCD: "PAZI! VOZILO BLIZU!"
- U ESP32 verziji dodatno:  
  - Vibracija  
  - WiFi obavijest  

---

## 🔌 Wokwi Implementacija  
### 📌 Pinout za ESP32 verziju
| Komponenta   | ESP32 Pin |
|-------------|----------|
| HC-SR04 (Front) | Trig:13, Echo:12 |
| HC-SR04 (Rear)  | Trig:14, Echo:27 |
| OLED I2C       | SDA:21, SCL:22 |
| Buzzer         | GPIO2   |
| Vibra motor         | GPI32   |

### 💻 Kôd značajke
```cpp
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
        delay(10);                      
        digitalWrite(VIBRA_PIN, LOW);
        delay(40);
        digitalWrite(LED_ZUTA, LOW);
        delay(50);
      }
    }

    static void criticalMode() {
      digitalWrite(LED_CRVENA, HIGH);
      tone(ZVUCNIK, 262);
      digitalWrite(VIBRA_PIN, HIGH); 
    }
};
```

## 📚 Resursi
1. [Kompletni kod](https://github.com/MarcoMatijevic/RUS_Detekcija/blob/main/Projekt/sketch.ino)
2. [ESP32 Wokwi template](https://wokwi.com/projects/429025123835618305)
3. [Kalibracijski vodič](https://wokwi.com/projects/428865980507846657)  

---

## 📜 Licenca  
📌 **Open-Source (MIT)** – Slobodno koristite i modificirajte.  

---

🚀 **Spremni za sigurniju vožnju biciklom?** Spojite, programirajte i vozite oprezno! 🚲💨

**Autori:** 
👨‍💻 Marco Matijević
👨‍💻 Filip Štiglić
