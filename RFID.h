#pragma once

#include "MFRC522.h"

class RFID
{
private:
	int _rx, _tx;
	MFRC522 mfrc522;
	MFRC522::MIFARE_Key key;

public:
	byte successRead[4];
	RFID(int rx, int tx);
	~RFID();
	byte readData(void);
	void printSuccessRead(void);
	void clean(void);
	void assingData(uint8_t *b);
	bool available(void);
	void readerInfo(void);
	void init(void);
};
