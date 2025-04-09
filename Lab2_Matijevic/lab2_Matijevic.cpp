/**
 * @file SleepModeWithWatchdog.ino
 * @brief Arduino program koji demonstrira sleep mode s buđenjem preko tipkala i watchdog timera
 * @details Program periodično pali LED na 5 sekundi, zatim ulazi u sleep mode iz kojeg se može probuditi
 *          tipkalom ili watchdog timerom.
 */

#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define LED_PIN     13  ///< Pin na kojem je spojena LED dioda
#define BUTTON_PIN  2   ///< Pin na kojem je spojeno tipkalo

volatile bool wakeUpByButton = false;      ///< Flag za buđenje tipkalom
volatile bool wakeUpByWatchdog = false;    ///< Flag za buđenje watchdog timerom
unsigned long lastWakeTime = 0;            ///< Vrijeme zadnjeg buđenja (za debounce)

/**
 * @brief Inicijalizacija hardvera
 * 
 * Postavlja pinove, serijsku komunikaciju, watchdog timer i prekid za tipkalo.
 */
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  while (!Serial); // Čekaj da se Serial port otvori
  
  configureWatchdog();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUpISR, FALLING);
}

/**
 * @brief Glavna programska petlja
 * 
 * Upravlja LED diodom, provjerava uzrok buđenja i upravlja sleep mode-om.
 */
void loop() {
  if (millis() - lastWakeTime > 100) { // Debounce period
    if (wakeUpByButton) {
      Serial.println("Probudio se tipkalom!");
      wakeUpByButton = false;
    }
    else if (wakeUpByWatchdog) {
      Serial.println("Probudio se watchdog timerom!");
      wakeUpByWatchdog = false;
    }

    Serial.println("LED ON (5s)");
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    digitalWrite(LED_PIN, LOW);
    Serial.println("Entering sleep...");
    Serial.flush();
    
    enterSleep();
    lastWakeTime = millis();
  }
}

/**
 * @brief Ulazi u sleep mode
 * 
 * Postavlja najdublji sleep mode (PWR_DOWN) i čeka na prekid za buđenje.
 */
void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // Omogući prekide prije spavanja
  sei();
  sleep_cpu();
  
  sleep_disable();
}

/**
 * @brief Konfigurira watchdog timer
 * 
 * Postavlja watchdog timer sa željenim intervalom (default 2 sekunde) u interrupt modu.
 * Timer neće resetirati MCU, samo će generirati prekid.
 */
void configureWatchdog() {
  MCUSR &= ~(1<<WDRF); // Resetuj watchdog reset flag
  
  WDTCSR |= (1<<WDCE) | (1<<WDE); // Omogući promjenu postavki
  // Postavi novi prescaler (2 sekunde)
  WDTCSR = (1<<WDP2) | (1<<WDP1); // 2.0s
  // WDTCSR = (1<<WDP2) | (1<<WDP1) | (1<<WDP0); // 4.0s
  // WDTCSR = (1<<WDP3) | (1<<WDP0); // 8.0s
  
  WDTCSR |= (1<<WDIE); // Omogući watchdog interrupt
}

/**
 * @brief Prekidna rutina za tipkalo
 * 
 * Postavlja flag za buđenje tipkalom.
 */
void wakeUpISR() {
  wakeUpByButton = true;
}

/**
 * @brief Prekidna rutina za watchdog timer
 * 
 * Postavlja flag za buđenje watchdog timerom.
 */
ISR(WDT_vect) {
  wakeUpByWatchdog = true;
}