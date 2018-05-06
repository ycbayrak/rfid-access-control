#define RST_PIN 9
#define SS_PIN 8
#define RELAY 13
#define BAUD_RATE 9600
#define _DEBUG

#ifdef _DEBUG
#define DEBUG(...) Serial.print(__VA_ARGS__)
#define DEBUGLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG(...)
#define DEBUGLN(...)
#endif