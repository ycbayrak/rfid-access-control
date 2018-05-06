#include "RFID.h"
#include "MFRC522.h"
#include "Arduino.h"

RFID::RFID(int rx, int tx)
{
	MFRC522 mfrc522(rx, tx);
}

RFID::~RFID()
{
	// Destroy RFID object.
}

void RFID::init(void)
{
	mfrc522.PCD_Init();
	mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
}

bool RFID::available()
{
	return true; // hard coded.
}

void RFID::clean(void)
{
	for (byte i = 0; i < 4; i++)
	{
		successRead[i] = 0;
	}
}

void RFID::printSuccessRead(void)
{
	Serial.print("[RFID] ");
	for (byte i = 0; i < 4; i++)
	{
		Serial.print(successRead[i], HEX);
	}
	Serial.println(" ");
}

void RFID::readerInfo(void)
{
	// Get the MFRC522 firmware version
	byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
	Serial.print(F("MFRC522 Software Version: 0x"));
	Serial.print(v, HEX);
	if (v == 0x91)
		Serial.print(F(" = v1.0"));
	else if (v == 0x92)
		Serial.print(F(" = v2.0"));
	else
		Serial.print(F(" (unknown)?"));
	Serial.println("");
	// When 0x00 or 0xFF is returned, communication probably failed
	if ((v == 0x00) || (v == 0xFF))
	{
		Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
		Serial.println(F("SYSTEM HALTED: Check connections."));
		// Turn on red LED
		while (true)
			; // do not go further
	}
}

byte RFID::readData(void)
{
	//yeni bir kart okunmadıysa 0 döndür
	if (!mfrc522.PICC_IsNewCardPresent())
		return 0;
	if (!mfrc522.PICC_ReadCardSerial())
		return 0;
	Serial.print("[RFID] UID -> ");
	for (int i = 0; i < mfrc522.uid.size; i++)
	{
		successRead[i] = mfrc522.uid.uidByte[i];
		Serial.print(successRead[i], HEX);
	}
	Serial.println("");
	//kart okumayı durdur ve 1 döndür (okuma başarılı)
	mfrc522.PICC_HaltA();
	return 1;
}
