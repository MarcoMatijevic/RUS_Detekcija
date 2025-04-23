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
- **Dodatni HC-SR04** – Stražnji senzor  
- **OLED SSD1306** – Grafički displej  

---

## 🛠️ Funkcionalnost  
### 🟢 Normalan režim
- Zelena LED aktivna  
- LCD: "Sustav aktivan"  
- Kontinuirano mjerenje udaljenosti  

### 🟡 Upozorenje (2-3.5m)
- Žuta LED treperi  
- Kratki zvučni signali (1s interval)  
- LCD: "OPREZ: Vozilo u blizini"  

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

### 💻 Kôd značajke
```cpp
// Režim rada ovisno o minimalnoj udaljenosti
  if (minUdaljenost >= 350) {
    // Normalan režim
    digitalWrite(LED_ZELENA, HIGH);
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.println("Sustav aktivan");

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
```

## 📚 Resursi
1. [Kompletni kod](https://github.com/MarcoMatijevic/RUS_Detekcija)
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
