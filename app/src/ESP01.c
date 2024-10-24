#include "sapi.h"
#include "sapi_esp8266.h"
#include <string.h>

#define ESP8266_UART UART_232
#define ESP8266_BAUD_RATE 115200
#define BUFFER_SIZE 1024


static char WifiName[30] = "";
static char WifiPass[30] = "";

/* Funciones internas */
static bool_t IsWaitedResponse(void);
static void SetEsp8266Status(uint8_t statusToSend);
static void ExecuteHttpServerFsm(void);
static bool_t ProcessHttpPostRequest(char *httpRequestBody);
void UART_Read(char* buffer);

/* Variables internas */
static uint8_t Esp8266Status = 0;
static const char *Esp8266ResponseToWait = NULL;
static delay_t Esp8266Delay;

/* Inicia el ESP8266 como Access Point */
bool_t esp8266StartAccessPoint() {
    // Inicializar UART y configurar ESP8266
    uartConfig(ESP8266_UART, ESP8266_BAUD_RATE);
    
    // Configura el ESP8266 en modo Access Point (AP)
    stdioPrintf(ESP8266_UART, "AT+CWMODE=2\r\n");  // Modo AP
    if (!IsWaitedResponse()) {
        return FALSE;
    }

    // Configura el nombre y la contrase�a del AP
    stdioPrintf(ESP8266_UART, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", "ComederoPerro", "NicoyAx");
    if (!IsWaitedResponse()) {
        return FALSE;
    }

    // Habilitar m�ltiples conexiones
    stdioPrintf(ESP8266_UART, "AT+CIPMUX=1\r\n");
    if (!IsWaitedResponse()) {
        return FALSE;
    }
    
    stdioPrintf(ESP8266_UART, "AT+CIPAP=\"192.168.4.1\"\r\n");  // IP fija
        if (!IsWaitedResponse()) {
        return FALSE;
    }

    // Iniciar el servidor HTTP en el puerto 80
    stdioPrintf(ESP8266_UART, "AT+CIPSERVER=1,80\r\n");
    return IsWaitedResponse();
}

/* Lee las solicitudes HTTP que llegan al servidor */
bool_t esp8266ReadHttpServer() {

    UART_Read(buffer);
    char *ipdPos = strstr(uartBuffer, "+IPD");
    if (ipdPos != NULL) {
        // Si se encontró "+IPD", procesamos la request
        processRequest(ipdPos);
        return true;
    }
    return (Esp8266Status == 1);  // Estado cuando hay una petici�n HTTP
}

void UART_Read(char* buffer) {
    uint16_t index = 0;
    uint8_t character;
    bool endOfHeaders = false;
    
    // Leer un byte inicial
    uartReadByte(ESP8266_UART, &character);
    
    // Bucle de lectura
    while (index < BUFFER_SIZE - 1) {
        // Guardar el carácter leído en el buffer
        buffer[index++] = character;
        
        // Verificar si hemos encontrado el final de los headers HTTP (una línea vacía)
        if (index >= 4 && 
            buffer[index-4] == '\r' && buffer[index-3] == '\n' &&
            buffer[index-2] == '\r' && buffer[index-1] == '\n') {
            
            endOfHeaders = true;
            break;
        }
        
        // Leer el siguiente byte
        uartReadByte(ESP8266_UART, &character);
    }

    // Si es una petición POST, necesitamos leer el cuerpo (si lo hay)
    if (endOfHeaders) {
        char* contentLengthStr = strstr(buffer, "Content-Length:");
        if (contentLengthStr != NULL) {
            int contentLength = atoi(contentLengthStr + 15);  // 15 es la longitud de "Content-Length: "
            
            // Leer el cuerpo del mensaje
            for (int i = 0; i < contentLength && index < BUFFER_SIZE - 1; i++) {
                uartReadByte(ESP8266_UART, &character);
                buffer[index++] = character;
            }
        }
    }
    
    // Finalizar la cadena con un terminador nulo de nuevo (por si se añadió contenido)
    buffer[index] = '\0';
}


/* Env�a una p�gina de configuraci�n de red WiFi */
bool_t esp8266SendConfigPage() {
    // P�gina de configuraci�n con el formulario HTML
    char *webHttpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    char *webHttpBody = "<html><body><h1>Configurar WiFi</h1>"
                        "<form action=\"/configure\" method=\"POST\">"
                        "SSID: <input type=\"text\" name=\"ssid\"><br>"
                        "Password: <input type=\"password\" name=\"password\"><br>"
                        "<input type=\"submit\" value=\"Guardar\">"
                        "</form></body></html>";
    char *webHttpEnd = "\r\n";

    return esp8266WriteHttpServer(webHttpHeader, webHttpBody, webHttpEnd);
}

/* Procesa una solicitud POST con las credenciales WiFi ingresadas */
bool_t esp8266ProcessPostRequest() {
    char ssid[30], password[30];
    // Extrae el SSID y contrase�a del cuerpo de la solicitud
    sscanf(httpRequestBody, "ssid=%s&password=%s", ssid, password);

    // Guarda las credenciales WiFi
    strcpy(WifiName, ssid);
    strcpy(WifiPass, password);

    // Enviar respuesta de �xito
    char *responseHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    char *responseBody = "<html><body><h1>WiFi Configurado!</h1></body></html>";
    esp8266WriteHttpServer(responseHeader, responseBody, "");

    return TRUE;
}

/* Conecta el ESP8266 a la red WiFi */
bool_t esp8266ConnectToWifi() {
    // Usa las credenciales obtenidas para conectarse a la red WiFi
    stdioPrintf(ESP8266_UART, "AT+CWJAP=\"%s\",\"%s\"\r\n", WifiName, WifiPass);
    return IsWaitedResponse();
}

/* Funciones internas */

/* Espera la respuesta esperada del ESP8266 */
static bool_t IsWaitedResponse(void) {
    uint8_t byteReceived;
    bool_t responseReceived = FALSE;

    while (uartReadByte(ESP8266_UART, &byteReceived)) {
        if (byteReceived == Esp8266ResponseToWait[0]) {
            responseReceived = TRUE;
            break;
        }
    }
    return responseReceived;
}


/* Procesa los datos de la solicitud POST recibida */
static bool_t ProcessHttpPostRequest(char *httpRequestBody) {
    // Aqu� se procesar�a el cuerpo de la solicitud POST
    return TRUE;
}

