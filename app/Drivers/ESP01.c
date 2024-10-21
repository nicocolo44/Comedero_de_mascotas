// ... existing code ...


// Agregar un nuevo estado para configurar el modo AP
typedef enum Esp8266State {
   // ... existing states ...
   ESP_SEND_CWMODE_AP,
   ESP_WAIT_CWMODE_AP,
   ESP_SEND_CWSAP,
   ESP_WAIT_CWSAP,
   // ... other states ...
} Esp8266Status_t;

// ... existing code ...

// Modificar la función esp8266InitHttpServer para incluir parámetros del AP
bool_t esp8266InitAccessPoint(char * apName, char * apPass)
{
   static bool_t parametersReceived = FALSE;

   if (!parametersReceived) {
      strcpy(WifiName, apName);
      strcpy(WifiPass, apPass);
      SetEsp8622Status(ESP_INIT);
      parametersReceived = TRUE;
   }
   ExcecuteAccessPointFsm();

   return (Esp8266Status == ESP_SEND_CIPSTATUS);
}

// Crear una nueva FSM para el modo AP
static void ExcecuteAccessPointFsm(void)
{
   // ... existing code ...

   switch (Esp8266Status) {
      // ... existing cases ...

      case ESP_SEND_CWMODE_AP:
         if (delayRead(&Esp8266Delay)) {
            stdioPrintf(ESP8266_UART, "AT+CWMODE=2\r\n");
            Esp8266ResponseToWait = Response_OK;
            delayConfig(&Esp8266Delay, ESP8266_TMO);
            SetEsp8622Status(ESP_WAIT_CWMODE_AP);
         }
      break;

      case ESP_WAIT_CWMODE_AP:
         if (IsWaitedResponse()) {
            delayConfig(&Esp8266Delay, ESP8266_PAUSE);
            SetEsp8622Status(ESP_SEND_CWSAP);
         }
         if (delayRead(&Esp8266Delay)) {
            delayConfig(&Esp8266Delay, ESP8266_PAUSE);
            SetEsp8622Status(ESP_SEND_AT);
         }
      break;

      case ESP_SEND_CWSAP:
         if (delayRead(&Esp8266Delay)) {
            stdioPrintf(ESP8266_UART, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", WifiName, WifiPass);
            Esp8266ResponseToWait = Response_OK;
            delayConfig(&Esp8266Delay, ESP8266_TMO);
            SetEsp8622Status(ESP_WAIT_CWSAP);
         }
      break;

      case ESP_WAIT_CWSAP:
         if (IsWaitedResponse()) {
            delayConfig(&Esp8266Delay, ESP8266_PAUSE);
            SetEsp8622Status(ESP_CIPMUX_SEND);
         }
         if (delayRead(&Esp8266Delay)) {
            delayConfig(&Esp8266Delay, ESP8266_PAUSE);
            SetEsp8622Status(ESP_SEND_AT);
         }
      break;

      // ... other cases ...
   }
}