# 🚀 ESP32 Demo Projekt s Prekidima

![Shema projekta](https://wokwi.com/projects/427051732721736705/thumbnail.png)

## 📝 Opis projekta
Demonstracijski projekt za ESP32 koji prikazuje:
- Upravljanje višestrukim prekidima
- Različite prioritete prekida
- Rad s PIR senzorom i tipkama
- Vizualizaciju stanja pomoću LED dioda

## 📦 Hardverske komponente
| Komponenta       | GPIO Pin | Opis                |
|------------------|----------|---------------------|
| ESP32 ploča      | -        | Glavni kontroler    |
| PIR senzor       | 33       | Detekcija pokreta   |
| Tipka 0          | 2        | Prekid prioritet 3  |
| Tipka 1          | 4        | Prekid prioritet 4  |
| Tipka 2          | 5        | Prekid prioritet 1  |
| LED tajmer       | 13       | Indikator rada      |
| LED tipka 0      | 12       | Žuta indikacija     |
| LED tipka 1      | 14       | Crvena indikacija   |
| LED tipka 2      | 27       | Plava indikacija    |

## ⚙️ Konfiguracija prekida
```mermaid
pie
    title Raspodjela prioriteta
    "Tajmer (0)" : 10
    "Tipka2 (1)" : 15
    "PIR (2)" : 25
    "Tipka0 (3)" : 20
    "Tipka1 (4)" : 30
🔌 Shema spojeva
plaintext
Copy
ESP32 GPIO2  → Tipka0 → 10kΩ → GND
ESP32 GPIO4  → Tipka1 → 10kΩ → GND
ESP32 GPIO5  → Tipka2 → 10kΩ → GND
ESP32 GPIO33 → PIR OUT
ESP32 GPIO12 → LED0 (žuta) → 220Ω → GND
ESP32 GPIO13 → LED_TIMER (zelena) → 220Ω → GND
ESP32 GPIO14 → LED1 (crvena) → 220Ω → GND
ESP32 GPIO27 → LED2 (plava) → 220Ω → GND
💻 Upute za pokretanje
Spojite komponente prema shemi


📋 Primjer izlaza
plaintext
Copy
[SYSTEM] Inicijalizacija završena
[TAJMER] Aktiviran (1000ms)
[PIR] Detektiran pokret!
[TIPKA1] Visok prioritet aktiviran
🛠️ Glavni kodovi
cpp
Copy
// Primjer prekidne rutine
void IRAM_ATTR handleButton1() {
  portENTER_CRITICAL_ISR(&btnMux);
  btn1Pressed = true;
  portEXIT_CRITICAL_ISR(&btnMux);
}

// Postavljanje tajmera
void setupTimer() {
  esp_timer_create_args_t timerArgs = {
    .callback = &timerISR,
    .name = "system_timer"
  };
  esp_timer_create(&timerArgs, &timerHandle);
  esp_timer_start_periodic(timerHandle, 1000000);
}
📜 Licenca
text
Copy
MIT Licenca
Dozvoljeno slobodno korištenje i modifikacija
🚀 Simulacija: Wokwi Link - https://wokwi.com/projects/427051732721736705