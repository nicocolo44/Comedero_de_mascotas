#include "sapi.h"
#include "sapi_esp8266.h"
#include <string.h>

#define ESP8266_UART UART_232
#define ESP8266_BAUD_RATE 115200

static char WifiName[30] = "";
static char WifiPass[30] = "";

/* Funciones internas */
static bool_t IsWaitedResponse(void);
static void SetEsp8266Status(uint8_t statusToSend);
static void ExecuteHttpServerFsm(void);
static bool_t ProcessHttpPostRequest(char *httpRequestBody);

/* Variables internas */
static uint8_t Esp8266Status = 0;
static const char *Esp8266ResponseToWait = NULL;
static delay_t Esp8266Delay;

/* Inicia el ESP8266 como Access Point */
bool_t esp8266StartAccessPoint(char *apName, char *apPassword) {
    // Inicializar UART y configurar ESP8266
    uartConfig(ESP8266_UART, ESP8266_BAUD_RATE);
    
    // Configura el ESP8266 en modo Access Point (AP)
    stdioPrintf(ESP8266_UART, "AT+CWMODE=2\r\n");  // Modo AP
    if (!IsWaitedResponse()) {
        return FALSE;
    }

    // Configura el nombre y la contraseña del AP
    stdioPrintf(ESP8266_UART, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", apName, apPassword);
    if (!IsWaitedResponse()) {
        return FALSE;
    }

    // Habilitar múltiples conexiones
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
    ExecuteHttpServerFsm();
    return (Esp8266Status == 1);  // Estado cuando hay una petición HTTP
}

/* Envía una página de configuración de red WiFi */
bool_t esp8266SendConfigPage() {
    // Página de configuración con el formulario HTML
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

    // Verifica si hay una petición POST
    if (esp8266ReadHttpServer()) {
        // Aquí asume que se ha capturado el cuerpo de la solicitud POST
        // y lo almacena en `httpRequestBody`
        char *httpRequestBody = "<simulación>";  // Reemplaza con la forma en que capturas el cuerpo

        if (ProcessHttpPostRequest(httpRequestBody)) {
            // Extrae el SSID y contraseña del cuerpo de la solicitud
            sscanf(httpRequestBody, "ssid=%s&password=%s", ssid, password);

            // Guarda las credenciales WiFi
            strcpy(WifiName, ssid);
            strcpy(WifiPass, password);

            // Enviar respuesta de éxito
            char *responseHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            char *responseBody = "<html><body><h1>WiFi Configurado!</h1></body></html>";
            esp8266WriteHttpServer(responseHeader, responseBody, "");

            return TRUE;
        }
    }

    return FALSE;
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

/* Ejecuta la FSM del servidor HTTP */
static void ExecuteHttpServerFsm(void) {
    // Aquí iría la implementación del manejo de la FSM para el servidor HTTP
}

/* Procesa los datos de la solicitud POST recibida */
static bool_t ProcessHttpPostRequest(char *httpRequestBody) {
    // Aquí se procesaría el cuerpo de la solicitud POST
    return TRUE;
}

