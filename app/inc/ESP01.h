#ifndef _ESP8266_CONFIG_H_
#define _ESP8266_CONFIG_H_

#include "sapi.h"

/* Inicia el ESP8266 en modo Access Point */
bool_t esp8266StartAccessPoint();

/* Lee si hay solicitudes HTTP en el servidor */
bool_t esp8266ReadHttpServer(void);

/* Env�a una p�gina de configuraci�n de red WiFi */
bool_t esp8266SendConfigPage(void);

/* Procesa una solicitud POST con las credenciales WiFi */
bool_t esp8266ProcessPostRequest(void);

/* Conecta el ESP8266 a la red WiFi */
bool_t esp8266ConnectToWifi(void);

#endif /* _ESP8266_CONFIG_H_ */