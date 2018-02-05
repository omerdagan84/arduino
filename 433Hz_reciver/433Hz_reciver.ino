#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
int light = 2;
int light_state = 0;

void setup()
{
  pinMode(light, OUTPUT);
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[20];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      light_state = !light_state;
      if ( light_state ) {
       digitalWrite(light, HIGH);
      } else {
        digitalWrite(light, LOW);
      }
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
}
