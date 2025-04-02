ESP32 Interrupt-Based Safety Alert System
🚴 Sustav za upozorenje na približavanje vozila biciklistima 🚗

Ovaj projekt implementira inteligentni sustav upozorenja koristeći ESP32, PIR senzor, mehaničke tipke i LED indikatore, s naprednim upravljanjem prekidima i prioritetima.

📦 Komponente
ESP32 – Glavni mikrokontroler s Wi-Fi/Bluetooth

PIR senzor (HC-SR501) – Detekcija pokreta vozila

Mehaničke tipke (x3) – Ručno upravljanje sustavom

LED indikatori (x4) – Vizualna upozorenja (zeleno/žuto/crveno)

Serijska konzola – Prikaz događaja u realnom vremenu

🛠️ Funkcionalnost
🔄 Automatski rad
✅ Normalan režim

🟢 LED_TIMER – Periodično treperi (1Hz)

⚠️ Detekcija pokreta (PIR senzor)

🟡 LED_BTN0 – Kratko upozorenje

📟 Serijski izlaz: "Pokret detektiran!"

🚨 Ručno aktiviranje upozorenja

🔴 LED_BTN1/LED_BTN2 – Dugotrajno upozorenje (1s)

⚡ Prioriteti prekida
BUTTON1 (GPIO4) – Najviši prioritet (hitno upozorenje)

PIR senzor (GPIO33) – Srednji prioritet

BUTTON0 (GPIO2) – Niži prioritet

BUTTON2 (GPIO5) – Osnovni prioritet

Tajmer – Najniži prioritet

🔧 Instalacija
Spojite komponente prema shemi:

Copy
BUTTON0 → GPIO2   (Pull-up 10kΩ)  
BUTTON1 → GPIO4  
BUTTON2 → GPIO5  
PIR → GPIO33  
LED_TIMER → GPIO13  
LED_BTN0 → GPIO12  
LED_BTN1 → GPIO14  
LED_BTN2 → GPIO27  
Preuzmite i kompajlirajte kod u Arduino IDE/PlatformIO

Otvortie serijski monitor (115200 baud)

🚀 Napredne mogućnosti
Preklapanje prekida – Visokoprioritetni prekidi mogu prekinuti nižeprioritetne

Zaštita resursa – Semafori za sigurno dijeljenje varijabli između prekida

Konfigurabilni prioriteti – Lako podešavanje prema potrebama

🔮 Buduća unapređenja
📶 Wi-Fi povezivanje – Slanje upozorenja na mobilni uređaj

🔊 Zvučna upozorenja – Integracija buzzer modula

📊 LCD ekran – Vizualni prikaz stanja

📜 Licenca
📌 MIT Licenca – Slobodna upotreba i modifikacija

🚲 Spremni za sigurniju vožnju? Implementirajte sustav i vozite s povjerenjem!
🔗 Dostupno za simulaciju na Wokwi platformi