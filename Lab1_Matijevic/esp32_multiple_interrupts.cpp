#include <Arduino.h>
#include "driver/gpio.h"
#include "esp_timer.h"

#define LED_TIMER 13
#define LED_BTN0 12
#define LED_BTN1 14
#define LED_BTN2 27
#define PIR_PIN GPIO_NUM_33
#define BUTTON0 GPIO_NUM_2
#define BUTTON1 GPIO_NUM_4
#define BUTTON2 GPIO_NUM_5

// Stanja prekida
volatile bool btn0Pressed = false;
volatile bool btn1Pressed = false;
volatile bool btn2Pressed = false;
volatile bool pirDetected = false;
volatile bool timerFlag = false;

// Prioriteti prekida
#define PRIORITY_TIMER 0
#define PRIORITY_BTN0 3
#define PRIORITY_BTN1 4
#define PRIORITY_BTN2 1
#define PRIORITY_PIR 2

// Tajmer varijabla
esp_timer_handle_t timerHandle;

// ISR rutine (mora primati void* arg)
void IRAM_ATTR handleBtn0(void* arg) { btn0Pressed = true; }
void IRAM_ATTR handleBtn1(void* arg) { btn1Pressed = true; }
void IRAM_ATTR handleBtn2(void* arg) { btn2Pressed = true; }
void IRAM_ATTR handlePIR(void* arg) { pirDetected = true; }

// Tajmer ISR (poziva se svake 1 sekunde)
void IRAM_ATTR timerISR(void* arg) {
    timerFlag = true;
}

void setup() {
    Serial.begin(115200);

    // Konfiguracija izlaza
    esp_rom_gpio_pad_select_gpio((gpio_num_t)LED_TIMER);
    esp_rom_gpio_pad_select_gpio((gpio_num_t)LED_BTN0);
    esp_rom_gpio_pad_select_gpio((gpio_num_t)LED_BTN1);
    esp_rom_gpio_pad_select_gpio((gpio_num_t)LED_BTN2);
    
    gpio_set_direction((gpio_num_t)LED_TIMER, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)LED_BTN0, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)LED_BTN1, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)LED_BTN2, GPIO_MODE_OUTPUT);

    // Konfiguracija ulaza
    gpio_set_direction(BUTTON0, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON1, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON2, GPIO_MODE_INPUT);
    gpio_set_direction(PIR_PIN, GPIO_MODE_INPUT);

    // Konfiguracija prekida
    gpio_set_intr_type(BUTTON0, GPIO_INTR_NEGEDGE);
    gpio_set_intr_type(BUTTON1, GPIO_INTR_NEGEDGE);
    gpio_set_intr_type(BUTTON2, GPIO_INTR_NEGEDGE);
    gpio_set_intr_type(PIR_PIN, GPIO_INTR_POSEDGE);

    // Inicijalizacija ISR servisa
    gpio_install_isr_service(0);

    // Dodavanje ISR funkcija
    gpio_isr_handler_add(BUTTON0, handleBtn0, (void*)PRIORITY_BTN0);
    gpio_isr_handler_add(BUTTON1, handleBtn1, (void*)PRIORITY_BTN1);
    gpio_isr_handler_add(BUTTON2, handleBtn2, (void*)PRIORITY_BTN2);
    gpio_isr_handler_add(PIR_PIN, handlePIR, (void*)PRIORITY_PIR);

    // Konfiguracija tajmera (1 sekunda)
    esp_timer_create_args_t timerArgs = {};
    timerArgs.callback = &timerISR;
    timerArgs.name = "TIMER1";
    esp_timer_create(&timerArgs, &timerHandle);
    esp_timer_start_periodic(timerHandle, 1000000); // 1 sekunda

    Serial.println("Sustav inicijaliziran.");
}

void loop() {
    // Obrada prekida prema prioritetima
    if (timerFlag) {
        timerFlag = false;
        gpio_set_level((gpio_num_t)LED_TIMER, !gpio_get_level((gpio_num_t)LED_TIMER));
        Serial.println("[TIMER] Aktiviran");
    }

    if (btn0Pressed) {
        btn0Pressed = false;
        gpio_set_level((gpio_num_t)LED_BTN0, 1);
        delay(1000);
        gpio_set_level((gpio_num_t)LED_BTN0, 0);
        Serial.println("[BUTTON0] Pritisnut");
    }

    if (btn1Pressed) {
        btn1Pressed = false;
        gpio_set_level((gpio_num_t)LED_BTN1, 1);
        delay(1000);
        gpio_set_level((gpio_num_t)LED_BTN1, 0);
        Serial.println("[BUTTON1] Pritisnut");
    }

    if (btn2Pressed) {
        btn2Pressed = false;
        gpio_set_level((gpio_num_t)LED_BTN2, 1);
        delay(1000);
        gpio_set_level((gpio_num_t)LED_BTN2, 0);
        Serial.println("[BUTTON2] Pritisnut");
    }

    if (pirDetected) {
        pirDetected = false;
        Serial.println("[PIR] Pokret detektiran!");
    }

    delay(10); // Mala pauza za stabilnost
}