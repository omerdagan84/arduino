#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

/*constants*/
const char *detect_msg = "motion detected\0";
const char *nodetect_msg = "motion not detected\0";

RH_ASK driver;

int PIR_out = 0;
volatile struct pir_sensor {
  int pir_pin;
  int pir_state;  
  int pir_change;
} pir = {2,0,0};

void setup()
{
    pinMode(pir.pir_pin, INPUT);
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    attachInterrupt(digitalPinToInterrupt(pir.pir_pin), pir_detect, CHANGE);
    pir.pir_state = 0;//digitalRead(pir.pir_pin);
    interrupts();  
}

void pir_detect ()
{
  noInterrupts();
  pir.pir_change = 1; 
}

void loop()
{
  
    /*
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
    */
   if ( pir.pir_change ) {
      Serial.print("pir state: ");
      Serial.println(pir.pir_state);
      pir.pir_state = digitalRead(pir.pir_pin);
      if ( pir.pir_state == HIGH ) {
        driver.send((uint8_t *)detect_msg, strlen(detect_msg));
        driver.waitPacketSent();
      } else {
        driver.send((uint8_t *)nodetect_msg, strlen(nodetect_msg));
        driver.waitPacketSent();
      }
      pir.pir_change = 0;
      delay(100); 
      interrupts(); 
      
   }
    

    
  
}
