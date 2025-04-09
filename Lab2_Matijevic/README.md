#📝 Lab2: Upravljanje Energijom i Watchdog Timer u Ugradbenim Sustavima
**Opis zadatka**
U ovom zadatku potrebno je koristiti mikrokontroler za demonstraciju naprednih tehnika upravljanja energijom i pouzdanosti sustava korištenjem sleep modova i watchdog timera. Implementirati:

- Duboki sleep mode (PWR_DOWN) za minimalnu potrošnju energije

- Buđenje sustava pomoću vanjskog prekida (tipkalo)

- Automatsko buđenje pomoću watchdog timera

- Prioritetnu obradu različitih izvora buđenja

- Koristiti Wokwi simulator za razvoj i ispitivanje koda.

#Projekt uključuje
- Implementaciju sleep modova za smanjenje potrošnje energije

- Konfiguraciju watchdog timera kao dodatnog mehanizma buđenja

- Upravljanje prioritetima izvora buđenja (tipkalo vs. watchdog)

- LED indikaciju stanja sustava

- Serijsku komunikaciju za debuggiranje

#Cilj zadatka
**Proučiti tehnike upravljanja energijom**
- Detaljno analizirati različite sleep mode-ove mikrokontrolera i njihov utjecaj na potrošnju energije.

**Implementirati watchdog timer**
- Osmisliti sustav koji koristi WDT kao mehanizam za periodično buđenje i kao sigurnosni mehanizam.

**Upravljanje izvorima buđenja**
- Implementirati prioritetnu obradu različitih izvora buđenja (vanjski prekid vs. watchdog timer).

**Simulacija i analiza**
- Ispitati rad sustava u Wokwi simulatoru i analizirati vremenske karakteristike.

**Tehničke specifikacije**
- Mikrokontroler: ATmega328P (Arduino Uno)

- Sleep mode: SLEEP_MODE_PWR_DOWN

**Izvori buđenja:**

- Vanjski prekid (FALLING) na pin 2 (tipkalo)

- Watchdog timer (interval: 2 sekunde)

**Indikacija:**

- LED na pinu 13 (5 sekundi nakon buđenja)

- Serijski izlaz (9600 baud)

#Uporaba GitHub platforme
**Verzioniranje koda:** Praćenje razvoja kroz Git commitove

**Wokwi integracija:** Pokretanje simulacija direktno iz GitHub repozitorija

**Wiki dokumentacija:** Detaljna dokumentacija implementacije

**Doxygen:** Automatska generacija dokumentacije iz koda

## 📝Metodologija testiranja
**Simulacija u Wokwiju:**

- Provjera ispravnog ulaska u sleep mode

- Testiranje buđenja tipkalom

- Verifikacija periodičnog buđenja watchdog timerom

**Logička analiza:**

- Snimanje vremenskih karakteristika pomoću logičkog analizatora

- Analiza odziva na prekide

- Mjerenje potrošnje energije u različitim modovima


## 📥Automatizacija dokumentacije
- Koristi se Doxygen za automatsko generiranje dokumentacije iz izvornog koda. Dokumentacija uključuje:

- Opis svih funkcija i globalnih varijabli

- Detalje konfiguracije watchdog timera

- Shemu prioriteta prekida

- Vremenske dijagrame rada sustava

## 📥 Instalacija
- Klonirajte repozitorij:
git clone https://github.com/MarcoMatijevic/RUS.git

## Autor
Marco Matijević
📧 mmatijevi@tvz.hr
