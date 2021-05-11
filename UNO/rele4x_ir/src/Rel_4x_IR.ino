/*     telecoAsorey, Cambados
*      FogarDixital
*      Plataforma Atom Platformio
*
*      RELE4X_IR
*      V1.1 2021
*
*      CONTROL DE BLOQUE RELÉ MEDIANTE MANDO IR
*      CON REPORT DE ESTADO POR PUERTO SERIE
*      1-4 CONMUTA RELÉ 1-4
*      0: ESCENA TODOS OFF
*      9: ESCENAS TODOS ON
*      ....
*/


#include <IRremote.h>
const int  IR_PIN=7; //constante PIN IR
const int RELE[]={8,9,10,11};

bool estadoReles[]={0,0,0,0};  // array booleano que almacena el estado 4 contactores NA : 1= cerrado / 0=abierto.

// Las dos líneas que siguen son "enlatadas. El que hizo IRremote.h dicta esta estructura.

IRrecv ir(IR_PIN);  //se crea un objeto del tipo IRrecv y se le asocia el PIN de entrada del diodo IR
decode_results resultado; //se declara una variable resultado del tipo decode_results que tendrá el valor decimal devuelto por IR
void setup()
{
int i;
Serial.begin(9600);
//declara pin IR_PIN de entrada y los pines 8-11 de salida
for(i=0;i<=3;i++){
    pinMode(RELE[i],OUTPUT);
}
pinMode(IR_PIN,INPUT);
todoOFF(); //abre todos los contactos NA de los 4 canales.
ir.enableIRIn(); //Habilita el PIN ir asociado al led IR
}

void loop() {
if (ir.decode(&resultado))  //Si decodificación IR es exitosa. IMPORTANTE el &!!!
{
  decodrele();  // controla ON/OFF relés
  delay(200);  //Una parada de 0.2s para dar tiempo a recibir nuevos datos.
  ir.resume(); //final decodificación. vacía el buffer de recepción
 }
}

//decoficador y actuación sobre relés
//cada tecla del mando genera una secuencia numérica que previamente hay que averiguar!!!!!!
void decodrele(){
  switch (resultado.value){
    case 16593103: if(estadoReles[0]==0){         //Si el relé número 1 (índice 0) está en valor 0 (abierto)
                   digitalWrite(RELE[0],LOW);     //escribir en puerto 8 (relay[0]) el valor 0 (cerrar NA)
                   estadoReles[0]=1;              //actualizar el nuevo estado del relé (cerrado)
                  }
                  else{                           //En caso cotrario, es decirm si relé 1 está en valor 0
                   digitalWrite(RELE[0],HIGH);    //escribir en puerto 8 (relay[0]) el valor 0
                   estadoReles[0]=0;               //actualizar el nuevo estado del relé (cerrado)
                  }
                  mostrarEstado();                //Devuelve por USB/Serie el estado de los contactores
                  break;
    case 16625743: if(estadoReles[1]==0){
                   digitalWrite(RELE[1],LOW);
                   estadoReles[1]=1;
                  }
                  else{
                   digitalWrite(RELE[1],HIGH);
                   estadoReles[1]=0;
                  }
                  mostrarEstado();
                  break;

   case 16609423: if(estadoReles[2]==0){
                   digitalWrite(RELE[2],LOW);
                   estadoReles[2]=1;
                  }
                  else{
                   digitalWrite(RELE[2],HIGH);
                   estadoReles[2]=0;
                  }
                  mostrarEstado();
                  break;
   case 16582903: if(estadoReles[3]==0){
                   digitalWrite(RELE[3],LOW);
                   estadoReles[3]=1;
                  }
                  else{
                   digitalWrite(RELE[3],HIGH);
                   estadoReles[3]=0;
                  }
                  mostrarEstado();
                  break;
   case 16584943: todoOFF();
                  mostrarEstado();
                  break;
   case 16607383: todoON();
                  mostrarEstado();
                  break;
  }
}

void todoON(void ){
  int ch;
  for(ch=RELE[0];ch<=RELE[3];ch++){              // desde ch=8 hasta 11
    digitalWrite(ch,LOW);
    estadoReles[ch-RELE[0]]=1;      //Fija estado del CH1-CH4 en 1
  }
}

void todoOFF(void ){
  int ch;
 for(ch=RELE[0];ch<=RELE[3];ch++){
    digitalWrite(ch,HIGH);
    estadoReles[ch-RELE[0]]=0;      //Fija estado del CH1-CH4 en 0
 }
}

void mostrarEstado(){
 int i;
 Serial.print("CH1-CH4:");
 for(i=0;i<=3;i++)
    Serial.print(estadoReles[i]);
Serial.println(" Ok!");
}
