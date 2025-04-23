# Bicycle Vehicle Proximity Detection System  

🚴 **Detekcija približavanja vozila biciklu** 🚗  

LINK NA PROJEKT ->  https://wokwi.com/projects/428865980507846657

Ovaj projekt implementira sustav za detekciju približavanja vozila biciklu koristeći **Arduino Mega**, ultrazvučni senzor, LED indikatore, zvučno upozorenje i LCD ekran.  

---

## 📦 Komponente  
- **Arduino Mega** – Glavni mikrokontroler  
- **Ultrazvučni senzor (HC-SR04)** – Mjerenje udaljenosti  
- **LED lampice** – Vizualna indikacija (zelena, žuta, crvena)  
- **Zvučnik** – Zvučno upozorenje  
- **LCD ekran s I2C modulom** – Prikaz udaljenosti i upozorenja  

---

## 🛠️ Funkcionalnost  
- **✅ Normalan rad (nema bliskog vozila)**  
  - 🔵 **Zelena LED** – Bez opasnosti  
- **⚠️ Vozilo u blizini (unutar određene udaljenosti)**  
  - 🟡 **Žuta LED** – Upozorenje  
  - 📊 **LCD prikazuje udaljenost**  
- **🚨 Vozilo vrlo blizu (manje od 2 metra)**  
  - 🔴 **Crvena LED** – Visoka opasnost  
  - 🔔 **Zvučno upozorenje**  
  - 📟 **LCD prikaz: "PAZI AUTO!"**  

---

## 🔌 Instalacija i upute  
1. **Spojite komponente** prema shemi.  
2. **Učitajte Arduino kôd** na mikrokontroler.  
3. **Pokrenite sustav** i testirajte funkcionalnost.  

---

## 🔮 Buduća poboljšanja  
- 📳 **Vibracijski motor** – Dodatno taktilno upozorenje  
- 🔍 **Napredniji senzori** – Točnija detekcija  
- 📱 **Mobilna integracija** – Prikaz podataka u aplikaciji  

---

## 📜 Licenca  
📌 **Open-Source (MIT)** – Slobodno koristite i modificirajte.  

---

🚀 **Spremni za sigurniju vožnju biciklom?** Spojite, programirajte i vozite oprezno! 🚲💨
