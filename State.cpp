#include "State.h"
#include "Arduino.h"

State::State()
{
    red = 9;
    green = 10;
    yellow = 11;
    _type = ACCESS;
}

Type State::getMode(void)
{
    switch (_type)
    {
    case Type::ACCESS:
        Serial.println("[STATE] -> Access");
        break; //Optional
    case Type::MASTER:
        Serial.println("[STATE] -> Master");
        break; //optional
    case Type::DELETE:
        Serial.println("[STATE] -> Delete");
        break;
    }
    return _type;
}

void State::setMode(Type t)
{
    _type = t;
    switch (_type)
    {
    case Type::ACCESS:
        Serial.print("[STATE] -> Access");
        break; //Optional
    case Type::MASTER:
        Serial.println("[STATE] -> Master");
        break; //optional
    case Type::DELETE:
        Serial.println("[STATE] -> Delete");
        break;
    }
    switch (t)
    {
    case (ACCESS):
        digitalWrite(green, HIGH);

    case (MASTER):
        digitalWrite(yellow, HIGH);
    case (DELETE):
        digitalWrite(red, HIGH);
    }
}