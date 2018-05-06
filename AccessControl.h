#include "Arduino.h"

class AccessControl
{
    private:
        uint8_t _pin;
    public:
        AccessControl(uint8_t p);
        void init(void);
        void open(void);
        void close(void);
};