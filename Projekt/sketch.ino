#include <LiquidCrystal_I2C.h>  //Upotreba I2C biblioteke

#define PIN_TRIG 3
#define PIN_ECHO 2    //definiranje pinova za senzor udaljenosti

#define LED_CRVENA 4
#define LED_ZUTA 5
#define LED_ZELENA 6
#define ZVUCNIK 7     //definiranje pinova za LED-ice i za zvucnik

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4   //definiranje podataka za LCD_I2C

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

int udaljenost;

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(LED_CRVENA, OUTPUT);
  pinMode(LED_ZUTA, OUTPUT);
  pinMode(LED_ZELENA, OUTPUT);    //inicijalizacija pinova

  lcd.init();
  lcd.backlight();    //inicijalizacija LCD-a

  lcd.setCursor(0, 0);
  lcd.print("Udaljenost:");
  lcd.setCursor(4, 1);
  lcd.print("cm");    //postavljanje teksta LCD-a

}

void loop() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);    //slanje signala senzora


  int trajanje = pulseIn(PIN_ECHO, HIGH);   //primanje ECHO signala i spremanje u varijablu
  udaljenost = trajanje / 58;


  lcd.setCursor(1, 1);
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print(udaljenost);    //Ispis udaljenost na LCD-u

  if(udaljenost >= 350){
    digitalWrite(LED_ZELENA, HIGH);
    digitalWrite(LED_ZUTA, LOW);
    digitalWrite(LED_CRVENA, LOW);    
  }

  if(udaljenost < 350  && udaljenost >= 200){
    digitalWrite(LED_ZELENA, LOW);
    digitalWrite(LED_ZUTA, HIGH);             //logika LED-ica za udaljenost
    digitalWrite(LED_CRVENA, LOW);
  }

  if(udaljenost < 200){
    digitalWrite(LED_ZELENA, LOW);
    digitalWrite(LED_ZUTA, LOW);
    digitalWrite(LED_CRVENA, HIGH);
    tone(7, 262, 1000);
  }


  delay(1000);

}
