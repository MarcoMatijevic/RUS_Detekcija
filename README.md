# RUS
Detekcija približavanja vozila biciklu

Ovaj projekt implementira sustav za detekciju približavanja vozila biciklu koristeći Arduino Mega, ultrazvučni senzor za mjerenje udaljenosti, LED lampice za vizualni signal, zvučnik za zvučno upozorenje i LCD ekran s I2C modulom za prikaz informacija.

Komponente

Arduino Mega - mikrokontroler
Ultrazvučni senzor - mjerenje udaljenosti (npr. HC-SR04)
LED lampice - Zelena, žuta i crvena za vizualni signal
Zvučnik - zvučno upozorenje
LCD ekran s I2C modulom - prikaz udaljenosti i upozorenja

Funkcionalnost

Kada senzor ne detektira objekt u blizini, svijetli zelena LED lampica.
Kada senzor detektira vozilo na određenoj udaljenosti:
Pali se žuta LED lampica.
Na LCD ekranu se ispisuje trenutna udaljenost vozila od bicikla.
Kada je udaljenost manja od 2 metra:
Pali se crvena LED lampica.
Aktivira se zvučno upozorenje.
Na LCD ekranu se ispisuje: "PAZI AUTO!"

Instalacija i korištenje
Spojite komponente prema shemi povezivanja.
Učitajte Arduino kôd na mikrokontroler.
Pokrenite sustav i testirajte funkcionalnost senzorike.

Buduća poboljšanja
Implementacija vibracijskog motora za dodatno upozorenje.
Korištenje naprednijih senzora za točnija mjerenja.
Integracija s mobilnom aplikacijom za prikaz podataka.

Licence

Ovaj projekt je open-source i možete ga slobodno koristiti i modificirati.

