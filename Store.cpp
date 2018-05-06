#include "Store.h"
#include "EEPROM.h"
#include "Arduino.h"

Store::Store()
{
}

byte Store::findIDSLOT(byte find[])
{
  uint8_t count = EEPROM.read(0); // Read the first Byte of EEPROM that
  for (uint8_t i = 1; i <= count; i++)
  {            // Loop once for each EEPROM entry
    readID(i); // Read an ID from EEPROM, it is stored in storedCard[4]
    if (matched(find, storedCard))
    { // Check to see if the storedCard read from EEPROM
      // is the same as the find[] ID card passed
      return i; // The slot number of the card
      break;    // Stop looking we found it
    }
  }
}

void Store::eraseAll(void)
{
  Serial.println(F("Starting Wiping EEPROM"));
  for (uint16_t x = 0; x < EEPROM.length(); x = x + 1)
  { //Loop end of EEPROM address
    if (EEPROM.read(x) == 0)
    { //If EEPROM address 0
      // do nothing, already clear, go to the next address in order to save time and reduce writes to EEPROM
    }
    else
    {
      EEPROM.write(x, 0); // if not write 0 to clear, it takes 3.3mS
    }
  }
}

bool Store::matched(byte a[], byte b[])
{
  bool match;
  if (a[0] != 0)  // Make sure there is something in the array first
    match = true; // Assume they match at first
  for (uint8_t k = 0; k < 4; k++)
  {                   // Loop 4 times
    if (a[k] != b[k]) // IF a != b then set match = false, one fails, all fail
      match = false;
  }
  if (match)
  {              // Check to see if if match is still true
    return true; // Return true
  }
  else
  {
    return false; // Return false
  }
}

boolean Store::isMaster(byte test[])
{
  if (matched(test, masterCard))
  {
    Serial.println("[STORE] Master Found");
    return true;
  }
  else
    return false;
}

boolean Store::findID(byte find[])
{
  uint8_t count = EEPROM.read(0); // Read the first Byte of EEPROM that
  for (uint8_t i = 1; i <= count; i++)
  {            // Loop once for each EEPROM entry
    readID(i); // Read an ID from EEPROM, it is stored in storedCard[4]
    if (matched(find, storedCard))
    { // Check to see if the storedCard read from EEPROM
      Serial.println("[STORE] ID Found");
      return true;
      break; // Stop looking we found it
    }
    else
    { // If not, return false
    }
  }
  Serial.println("[STORE] ID Not Found!");
  return false;
}

void Store::readID(uint8_t number)
{
  uint8_t start = (number * 4) + 2; // Figure out starting position
  for (uint8_t i = 0; i < 4; i++)
  {                                         // Loop 4 times to get the 4 Bytes
    storedCard[i] = EEPROM.read(start + i); // Assign values read from EEPROM to array
  }
}

void deleteID(byte a[])
{
  uint8_t num = EEPROM.read(0); // Get the numer of used spaces, position 0 stores the number of ID cards
  uint8_t slot;                 // Figure out the slot number of the card
  uint8_t start;                // = ( num * 4 ) + 6; // Figure out where the next slot starts
  uint8_t looping;              // The number of times the loop repeats
  uint8_t j;
  uint8_t count = EEPROM.read(0); // Read the first Byte of EEPROM that stores number of cards
  slot = 1;                       // Figure out the slot number of the card to delete
  start = (slot * 4) + 2;
  looping = ((num - slot) * 4);
  num--;                // Decrement the counter by one
  EEPROM.write(0, num); // Write the new count to the counter
  for (j = 0; j < looping; j++)
  {                                                      // Loop the card shift times
    EEPROM.write(start + j, EEPROM.read(start + 4 + j)); // Shift the array values to 4 places earlier in the EEPROM
  }
  for (uint8_t k = 0; k < 4; k++)
  { // Shifting loop
    EEPROM.write(start + j + k, 0);
  }
  Serial.println(F("Succesfully removed ID record from EEPROM"));
}

void Store::writeID(byte a[])
{
  if (!findID(a))
  {                                // Before we write to the EEPROM, check to see if we have seen this card before!
    uint8_t num = EEPROM.read(0);  // Get the numer of used spaces, position 0 stores the number of ID cards
    uint8_t start = (num * 4) + 6; // Figure out where the next slot starts
    num++;                         // Increment the counter by one
    EEPROM.write(0, num);          // Write the new count to the counter
    for (uint8_t j = 0; j < 4; j++)
    {                                // Loop 4 times
      EEPROM.write(start + j, a[j]); // Write the array values to EEPROM in the right position
    }
    Serial.println(F("Succesfully added ID record to EEPROM"));
  }
  else
  {
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
  }
}