📝 ESP32 Sustav upravljanja prekidima
<img src="https://img.shields.io/badge/Platform-ESP32-blue" alt="Platform"> <img src="https://img.shields.io/badge/Framework-Arduino-green" alt="Framework">

Sustav za demonstriranje upravljanja prekidima na ESP32 mikrokontroleru sa strogo definiranim prioritetima.

📋 Sadržaj
Hardverska konfiguracija

Upravljanje prekidima

Obrada u glavnoj petlji

Napomene o implementaciji

Usklađenost sa zahtjevima

Instalacija

Korištenje

Autor

## 📦 Hardverske komponente
| Komponenta       | GPIO Pin | Opis                |
|------------------|----------|---------------------|
| ESP32 ploča      | -        | Glavni kontroler    |
| PIR senzor       | 33       | Detekcija pokreta   |
| Tipka 0          | 2        | Prekid prioritet 3  |
| Tipka 1          | 4        | Prekid prioritet 4  |
| Tipka 2          | 5        | Prekid prioritet 1  |
| LED tajmer       | 13       | Crveni indikator rada      |
| LED tipka 0      | 12       | Plava indikacija     |
| LED tipka 1      | 14       | Žuta indikacija   |
| LED tipka 2      | 27       | Roza indikacija    |

## 🔌 Shema spojeva
| ESP32 Pin | Komponenta     | Dodatni elementi  |
|-----------|----------------|-------------------|
| GPIO2     | Tipka0         | 10kΩ → GND        |
| GPIO4     | Tipka1         | 10kΩ → GND        |
| GPIO5     | Tipka2         | 10kΩ → GND        |
| GPIO33    | PIR OUT        | -                 |
| GPIO12    | LED0 (Plava)    | 220Ω → GND        |
| GPIO13    | LED_TIMER (Crvena)     | 220Ω → GND        |
| GPIO14    | LED1 (Žuta)  | 220Ω → GND        |
| GPIO27    | LED2 (Roza)   | 220Ω → GND        |

## ⚙️ Upravljanje prekidima
- **3.1 Izvori prekida i prioriteti**
- Sustav upravlja s četiri vrste prekida sa sljedećim prioritetima (veći broj = veći prioritet):


| Izvor prekida | Razina prioriteta  | Opis  |
|---------------|--------------------|-------------------|
|Timer	        | 0 	             | (Najviši)Periodični timer (1s)  |
| BUTTON0       | 3                  | Tipka visokog prioriteta        |
| PIR senzor    | 2                  | Detekcija pokreta        |
| BUTTON1       | 4                  | Tipka srednjeg prioriteta         |
| BUTTON2       | 1                  | (Najniži)	Tipka niskog prioriteta |

- **3.2 Rutine za obradu prekida (ISR)**
- Svaki prekid ima svoju ISR rutinu koja postavlja zastavicu za obradu u glavnoj petlji:

**Timer ISR:

- Aktivira se svake 1 sekunde**

- Postavlja timerFlag za promjenu stanja LED_TIMER

- Najviši prioritet (0)

**BUTTON0 ISR:

- Aktivira se na silazni brid (pritisak tipke)

- Postavlja zastavicu btn0Pressed

- Razina prioriteta 3

**BUTTON1 ISR:

- Aktivira se na silazni brid

- Postavlja zastavicu btn1Pressed

- Razina prioriteta 4

**BUTTON2 ISR:

- Aktivira se na silazni brid

- Postavlja zastavicu btn2Pressed

- Razina prioriteta 1

**PIR senzor ISR:

- Aktivira se na uzlazni brid (detekcija pokreta)

- Postavlja zastavicu pirDetected

- Razina prioriteta 2

## 🔄 Obrada u glavnoj petlji
Glavna petlja provjerava zastavice prekida po redu prioriteta i obrađuje ih:

**Timer:

- Mijenja stanje LED_TIMER

- Ispisuje "[TIMER] Aktiviran" na serijski izlaz

**BUTTON0:

- Paljenje LED_BTN0 na 1 sekundu

- Ispis "[BUTTON0] Pritisnut"

**BUTTON1:

- Paljenje LED_BTN1 na 1 sekundu

- Ispis "[BUTTON1] Pritisnut"

**BUTTON2:

Paljenje LED_BTN2 na 1 sekundu

- Ispis "[BUTTON2] Pritisnut"

**PIR senzor:

- Ispis "[PIR] Pokret detektiran!"

## 📝 Napomene o implementaciji
- Sustav koristi ESP32 GPIO prekidne servise

- Timer je implementiran koristeći ESP32 hardverski timer (esp_timer)

- Sve ISR rutine označene su s `IRAM_ATTR` za ispravno smještanje u IRAM

- Odskakanje tipki riješeno je 1-sekundnim trajanjem LED diode

- Glavna petlja uključuje malu pauzu od 10ms za stabilnost

## ✔️ Usklađenost sa zahtjevima
- Implementacija ispunjava sve navedene zahtjeve:

- Detektira pritiske tipki i aktivira odgovarajuće LED diode (FR-1, FR-2)

- Implementira prioritete prekida (FR-8)

- Koristi prekide timera (FR-4)

- Obradjuje ulaz s PIR senzora (FR-5)

- Obradjuje prekide ispravnim redoslijedom prioriteta `(TIMER1 > INT0 > PIR > INT1 > INT2)`

**Napomena:** Funkcionalnost HC-SR04 senzora udaljenosti (FR-5, FR-6, FR-7) nije implementirana u ovoj verziji koda.

## 📥 Instalacija
- Klonirajte repozitorij:
git clone https://github.com/vas_repozitorij/esp32-interrupt-system.git

- Otvorite projekt u Arduino IDE

- Postavite prave pinove u config.h

- Uploadajte na ESP32

## 🖥️ Korištenje
- Povežite ESP32 na računalo preko USB

- Otvorite Serial Monitor (115200 baud)

- Pritisnite tipke za testiranje

- Pokret u blizini PIR senzora će biti detektiran

**Primjer koda za konfiguraciju prekida:**
```cpp
gpio_set_intr_type(BUTTON0, GPIO_INTR_NEGEDGE);
gpio_isr_handler_add(BUTTON0, handleBtn0, (void*)PRIORITY_BTN0);
```

## 👨💻 Autor
Marco Matijević
📧 mmatijevi@tvz.hr
