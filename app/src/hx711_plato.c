#include "HX711_plato.h"

static uint8_t HX711_SCK_PIN;
static uint8_t HX711_DOUT_PIN;
static int32_t valor_base;
static int32_t factor_de_conversion;


// Función para inicializar los pines del HX711
void HX711_plato_Init(uint8_t sck_pin, uint8_t dout_pin) {
    HX711_SCK_PIN = sck_pin;
    HX711_DOUT_PIN = dout_pin;
    gpioConfig(sck_pin, GPIO_OUTPUT);
    gpioConfig(dout_pin, GPIO_INPUT);
}

// Función para leer datos de 24 bits del HX711
int8_t HX711_plato_Read(int32_t* data) {
    *data = 0;

    // Asegurarse de que el HX711 está listo
    if(gpioRead(HX711_DOUT_PIN)){
        return FALSE;
    }

    // Leer 24 bits de datos
    for (int i = 0; i < 24; i++) {
        gpioWrite(HX711_SCK_PIN, true); // Genera un pulso alto en SCK
        delayUs(1); 
        *data = (*data << 1) | gpioRead(HX711_DOUT_PIN); // Leer el bit de DOUT
        gpioWrite(HX711_SCK_PIN, false); // Pulso bajo en SCK
        delayUs(1); 
    }

    // Recibir el pulso extra para seleccionar el canal y ganancia
    gpioWrite(HX711_SCK_PIN, true);
    delayUs(1); 
    gpioWrite(HX711_SCK_PIN, false);
    delayUs(1); 

    // Asegurarse de que el valor sea signo extendido de 24 a 32 bits
    if (*data & 0x800000) {
        *data |= 0xFF000000;
    }

    return TRUE;
}


int32_t HX711_plato_GetWeight(int32_t lectura) {
   return (float)(lectura - valor_base) / factor_de_conversion;
}

void HX711_plato_Tare(int8_t muestras) {
    int32_t sumatoria = 0;
    int32_t lectura;
    for (int i = 0; i < muestras; i++) {
        HX711_plato_Read(&lectura);
        sumatoria += lectura;
    }
    valor_base = sumatoria / muestras;
}

int32_t HX711_plato_Calibrate(int32_t peso_conocido) {
    int32_t lectura;
    HX711_plato_Read(&lectura);
    factor_de_conversion = lectura - valor_base;
    factor_de_conversion /= peso_conocido;
    return factor_de_conversion;
}