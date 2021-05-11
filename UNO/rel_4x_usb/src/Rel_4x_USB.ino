/***************   telecoAsorey  **************
*                  PlatformIO
*                 Fogar Dixital
*
*               RELE4x_USB
*               V2.0, 2021
*
* Control relés desde PC vía USB
* Control salida cuádruple binaria a relé 4CH
*
* Formato trama control: decimal de 2 posiciones: d1: canal (1-4); d2: estado (0/1)
*                        Ej: 11: enciende canal 1
*                            10: apaga canal1
* Tramas especiales:
*                      99: todo ON
*                      66: todo OFF
*                      33: 1-3 ON; 2-4 OFF
* Ej: 99 activa los 4CH;
* NOTA: los estados de los relés usan lógica negativa (ON: LOW OFF: HIGH)
*/

#include <stdlib.h>

#define ch1 8   // CH1 - Relé 1
#define ch2 9   // CH2 - Relé2
#define ch3 10  // CH3 - Relé3
#define ch4 11  // CH4 - Relé4


// Setup:
void setup(){

Serial.begin(9600); // Para debug cód
  // Relés:
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  pinMode(ch4, OUTPUT);

  todoOFF(); //abre todos los relés

}

void loop(){

  String inString;              //cadena alfanumérica  que almacenará la secuencia recibida por USB
  int inChar;                   //inChar: caracter leído del canal USB.
  int trama;                    //trama: número entero obtenido a partir de la cadena recibida.

  while(Serial.available()>0){  // comprueba que el canal USB presenta datos nuevos
    inChar=Serial.read();       // lee un caracter (1 byte)
    if(isDigit(inChar)){        // comprueba que es un número
     inString+=(char)inChar;    // en caso afirmativo se lo añade a la cadena
    }
    if(inChar =='\n'){          // Si se detecta caracter retorno de carro = ENTER
      trama=inString.toInt();   // realiza la conversión de la cadena a número entero.
      Serial.write("Eco:");     // Envía comprobación de la secuencia recibida
      Serial.println(trama);    // .... valor decimal
    }

  // decodificación de la trama
    switch(trama){
      case 11: digitalWrite(ch1,LOW);   // En el supuesto 11 abrir CH1 del relé.
               break;                   // break es necesario para que no siga decodificando.
      case 21: digitalWrite(ch2,LOW);
               break;
      case 31: digitalWrite(ch3,LOW);
               break;
      case 41: digitalWrite(ch4,LOW);
               break;
      case 10: digitalWrite(ch1,HIGH);
               break;
      case 20: digitalWrite(ch2,HIGH);
               break;
      case 30: digitalWrite(ch3,HIGH);
               break;
      case 40: digitalWrite(ch4,HIGH);
               break;
      case 66: todoOFF();               // Llama a una función que abre todos los relés.
               break;
      case 99: todoON();                // Llama a una función que cierra todos los relés.
               break;
      case 33: digitalWrite(ch1,LOW);
               digitalWrite(ch3,LOW);
               digitalWrite(ch2,HIGH);
               digitalWrite(ch4,HIGH);
               break;
     }
    delay(100);                         // parada de 0.1s para dar tiempo a recibir el siguiente byte por USB
   }
}

void todoON(void ){
  int ch;
  for(ch=ch1;ch<=ch4;ch++)              // desde ch=8 hasta 11 (ya que ch1=8 y ch4=11)
    digitalWrite(ch,LOW);
}

void todoOFF(void ){
  int ch;
  for(ch=ch1;ch<=ch4;ch++)
    digitalWrite(ch,HIGH);
}
