#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
//RH_ASK(uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted)
//RH_ASK driver(2000, 12, 13);
RH_ASK driver;

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    uint8_t ret;
    ret = driver.recv(buf, &buflen);
    if (ret) // Non-blocking
    {
      
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
    delay(250);
    
    
}
