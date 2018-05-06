#include "AccessControl.h"
#include "Arduino.h"

AccessControl::AccessControl(uint8_t p)
{
    _pin = p;
};

void AccessControl::init(void)
{
    pinMode(_pin, OUTPUT);
};

void AccessControl::open(void)
{
    digitalWrite(_pin, HIGH); // Make sure green LED is on
    delay(100);
    digitalWrite(_pin, LOW); // Make sure green LED is off
    delay(100);
    digitalWrite(_pin, HIGH); // Make sure green LED is on
    delay(100);
    digitalWrite(_pin, LOW); // Make sure green LED is off
};

void AccessControl::close(void)
{
    digitalWrite(_pin, HIGH); // Make sure green LED is on
    delay(200);
    digitalWrite(_pin, LOW); // Make sure green LED is off
    delay(200);
    digitalWrite(_pin, HIGH); // Make sure green LED is on
    delay(200);
    digitalWrite(_pin, LOW); // Make sure green LED is off};
};