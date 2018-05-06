#include "Arduino.h"
#include "SPI.h"
#include "EEPROM.h"

#include "Main.h"
#include "Store.h"
#include "AccessControl.h"
#include "State.h"
#include "RFID.h"

RFID rfid(53, 5);
Store store;
State state;
AccessControl accessControl(RELAY);

byte success;
Type program_mode;
void prog_init(void);
void program_info(void);

void setup(void)
{
  Serial.begin(BAUD_RATE);
  delay(50);
  SPI.begin();
  delay(50);
  accessControl.init();
  rfid.init();
  rfid.readerInfo();
  program_info();
  prog_init();
}

void loop(void)
{
  success = rfid.readData();
  if (!success)
  {
    return;
  }
  else if (success && store.isMaster(rfid.successRead)) // Check if card is master card
  {
    state.setMode(MASTER);
    do
    {
      success = rfid.readData();
      if (!success)
      {
        continue;
      }
      else if (store.isMaster(rfid.successRead))
      {
        state.setMode(Type::ACCESS);
        break;
      }
      else if (store.findID(rfid.successRead))
      {
        DEBUGLN("ID already registered. Passing");
        success = 0;
        continue;
      }
      else
      {
        store.writeID(rfid.successRead);
        DEBUG("New ID registered -> ");
        success = 0;
        continue;
      }
    } while (!success);
  }
  else if (store.findID(rfid.successRead)) // Check if card is registered in database;
  {
    state.setMode(Type::ACCESS);
    accessControl.open();
  }
  else
  {
    //    DEBUGLN("YOU SHALL NOT PASS");
    accessControl.close();
    //    rfid.printSuccessRead();
  }
}

void prog_init(void)
{
  if (EEPROM.read(1) != 143)
  {
    Serial.println(F("No Master Card Defined"));
    Serial.println(F("Scan A PICC to Define as Master Card"));
    do
    {
      uint8_t success = rfid.readData(); // sets successRead to 1 when we get read from reader otherwise 0
      DEBUGLN("[Main] WAITING FOR SUCCESS!");
      delay(500);
    } while (!success); // Program will not go further while you not get a successful read
    for (uint8_t j = 0; j < 4; j++)
    {                                           // Loop 4 times
      EEPROM.write(2 + j, rfid.successRead[j]); // Write scanned PICC's UID to EEPROM, start from address 3
      DEBUGLN("[Main] WRITE SUCCESSFUL!");
    }
    EEPROM.write(1, 143); // Write to EEPROM we defined Master Card.
    Serial.println(F("Master Card Defined"));
  }
  Serial.println(F("-------------------"));
  Serial.println(F("Master Card's UID"));
  for (uint8_t i = 0; i < 4; i++)
  {                                           // Read Master Card's UID from EEPROM
    store.masterCard[i] = EEPROM.read(2 + i); // Write it to masterCard
    Serial.print(store.masterCard[i], HEX);
  }
  Serial.println("");
  Serial.println(F("-------------------"));
  Serial.println(F("Program initialized"));
}

void program_info(void)
{
  Serial.println("RFID Access Control v.12");
  Serial.println("Bor Teknik, 2018");
}