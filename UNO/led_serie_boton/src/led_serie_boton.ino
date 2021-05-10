/* CONTROL DE LED POR SERIE Y PULSADOR
 *  '0': apaga led
 *  '1': enciende led
 *  PULSAR: Conmuta estado del diodo
 */

int led = 13;
int estado=0;
int pulsador = 12;
int pulsaciones=0;

void setup() {

pinMode(led, OUTPUT);
pinMode(pulsador, INPUT);
Serial.begin(9600);
}

void loop(){
   if(Serial.available() > 0) {
       char ledState = Serial.read();
       if(ledState == '1'){
          digitalWrite(led, HIGH);
          estado=1;
       }
       if(ledState == '0'){
          digitalWrite(led, LOW);
          estado=0;
        }
   }
  int estadopulsador = digitalRead(pulsador);
  if ( estadopulsador == LOW){
      pulsaciones++;
      Serial.print("Pulsación:");
      Serial.println(pulsaciones);

      if(estado==0){
        digitalWrite(led, HIGH);
        estado=!estado;
      }
      else{
         digitalWrite(led,LOW);
         estado=!estado;
      }
   delay(1000);
  }
}
