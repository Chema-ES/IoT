/**********************************
 *  STM32_led_builtin

 *  Identificación del LED builtin
 *
 *  Se asume led ánodo común
 *
  */
#include <Arduino.h>

void setup(){
Serial.begin(115200);
}
void loop()
{
  for(int i=10;i<35;i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    delay(2000);
    Serial.println(i);
  }
}
