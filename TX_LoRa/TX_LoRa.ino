#include "SX1278.h"
#include <SPI.h>

#define LORA_MODE  4
#define LORA_CHANNEL  CH_6_BW_125
#define LORA_ADDRESS  2

#define LORA_SEND_TO_ADDRESS  4

#define LORA_LED  9

int e;

char message1 [] = "Packet 1, wanting to see if received packet is the same as sent packet";
char message2 [] = "Packet 2, broadcast test";

void setup()
{
  pinMode(LORA_LED, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Print a start message
  Serial.println(F("sx1278 module and Arduino: send two packets (One to an addrees and another one in broadcast)"));

  // Power ON the module
  if (sx1278.ON() == 0) {
    Serial.println(F("Setting power ON: SUCCESS "));
  } else {
    Serial.println(F("Setting power ON: ERROR "));
  }

  // Set transmission mode and print the result
  if (sx1278.setMode(LORA_MODE) == 0) {
    Serial.println(F("Setting Mode: SUCCESS "));
  } else {
    Serial.println(F("Setting Mode: ERROR "));
  }

  // Set header
  if (sx1278.setHeaderON() == 0) {
    Serial.println(F("Setting Header ON: SUCCESS "));
  } else {
    Serial.println(F("Setting Header ON: ERROR "));
  }

  // Select frequency channel
  if (sx1278.setChannel(LORA_CHANNEL) == 0) {
    Serial.println(F("Setting Channel: SUCCESS "));
  } else {
    Serial.println(F("Setting Channel: ERROR "));
  }

  // Set CRC
  if (sx1278.setCRC_ON() == 0) {
    Serial.println(F("Setting CRC ON: SUCCESS "));
  } else {
    Serial.println(F("Setting CRC ON: ERROR "));
  }

  // Select output power (Max, High, Intermediate or Low)
  if (sx1278.setPower('M') == 0) {
    Serial.println(F("Setting Power: SUCCESS "));
  } else {
    Serial.println(F("Setting Power: ERROR "));
  }

  // Set the node address and print the result
  if (sx1278.setNodeAddress(LORA_ADDRESS) == 0) {
    Serial.println(F("Setting node address: SUCCESS "));
  } else {
    Serial.println(F("Setting node address: ERROR "));
  }

  // Print a success message
  Serial.println(F("sx1278 configured finished"));
  Serial.println();
}

void loop(void)
{
  // Send message1 and print the result
  e = sx1278.sendPacketTimeout(LORA_SEND_TO_ADDRESS, message1);
  Serial.print(F("Packet sent, state "));
  Serial.println(e, DEC);

  if (e == 0) {
      digitalWrite(LORA_LED, HIGH);
      delay(500);
      digitalWrite(LORA_LED, LOW);
  }

  delay(4000);  

  // Send message2 broadcast and print the result
  e = sx1278.sendPacketTimeout(0, message2);
  Serial.print(F("Packet sent, state "));
  Serial.println(e, DEC);

  if (e == 0) {
      digitalWrite(LORA_LED, HIGH);
      delay(500);
      digitalWrite(LORA_LED, LOW);
  }

  delay(4000);  
}

