#pragma once
#include "Arduino.h"

class Store
{
private:
	byte findIDSLOT( byte find[] );
public:
	Store();
	byte storedCard[4];   // Stores an ID read from EEPROM
	byte readCard[4];   // Stores scanned ID read from RFID Module
	byte masterCard[4];   // Stores master card's ID read from EEPROM
	void eraseAll(void);
	bool matched(byte a[], byte b[]);
	void readID( uint8_t number );
	void writeID( byte a[]);
	void deleteID( byte a[] );
	boolean findID( byte find[] );
	boolean isMaster( byte test[] );
};