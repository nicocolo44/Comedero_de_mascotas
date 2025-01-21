
#include "buzzer.h"


uint8_t BUZZER_PIN = -1; // Pin del buzzer


// Inicializa el buzzer con el pin especificado y lo prende
void Buzzer_Init(uint8_t pin){
    BUZZER_PIN = pin;
    gpioConfig(BUZZER_PIN, GPIO_OUTPUT);
    Buzzer_Off();
}

// Prende el buzzer
void Buzzer_On(void){
    gpioWrite(BUZZER_PIN, true);
}

// Apaga el buzzer
void Buzzer_Off(void){
    gpioWrite(BUZZER_PIN, false);
}