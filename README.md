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
- **Vibra motor** – Haptički feedback  

---

## 🛠️ Funkcionalnost  
### 🟢 Normalan režim
- Zelena LED aktivna  
- LCD: "Sustav aktivan"  
- Kontinuirano mjerenje udaljenosti  

### 🟡 Upozorenje (2-4m)
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
| Buzzer         | GPIO4   |
| Vibra motor    | GPIO5   |

### 💻 Kôd značajke
```cpp
// Detekcija vozila s dva senzora
void checkVehicles() {
  float frontDist = getDistance(FRONT_TRIG, FRONT_ECHO);
  float rearDist = getDistance(REAR_TRIG, REAR_ECHO);
  
  if(frontDist < 2.0 || rearDist < 2.0) {
    triggerAlarm(CRITICAL);
  }
  else if(frontDist < 4.0 || rearDist < 4.0) {
    triggerAlarm(WARNING);
  }
}
```

## 📚 Resursi
1. [Kompletni kod](https://github.com/MarcoMatijevic/RUS_Detekcija)
2. [ESP32 Wokwi template](https://wokwi.com/projects/429847891799736321)
3. [Kalibracijski vodič](https://wokwi.com/projects/428865980507846657)  

---

## 📜 Licenca  
📌 **Open-Source (MIT)** – Slobodno koristite i modificirajte.  

---

🚀 **Spremni za sigurniju vožnju biciklom?** Spojite, programirajte i vozite oprezno! 🚲💨

**Autori:** 
👨‍💻 Marco Matijević
👨‍💻 Filip Štiglić
