/*
  Fecha 14/02/2018
  Marco Antonio Moreno Cortés

  Programa que controla mediante un botón pulsador un semáforo temporizado
  con un potenciometro, el programa consiste en:

  Que el peatón presiona el botón solicitando el paso, por dicha acción el 
  semáforo contara el paso a los automóviles "El semáforo de los automoviles
  cambiara de estado de verde, ambar y quedara en rojo por un tiempo", y dara
  el paso a los peatones "El semáforo de los peatones cambiara de estado de rojo
  pasara al verde y queda en rojo por un tiempo", y con el potenciometro se
  controlara el tiempo de espera para paso a los peatones.

   Lista de componentes

  2  Led Rojo.
  2  Led Verde.
  1  Led Ambar.
  5  Resistencias de 330 ohmios.
  1  Pulsador normalmente abierto.
  1  Potenciómetro de 10K.
  9  Cables.
  1  Placa Arduino Uno.
  1  Placa Protoboard.
  1 Cable de impresora.
   
*/

/* Definición de constantes y asignación a los pines */ 

int verde_auto = 13;
int ambar_auto = 12;
int rojo_auto = 11;
int verde_peaton = 10;
int rojo_peaton = 9;
int pulsador = 8;
 
//Se define el tiempo mínimo que el semáforo verde permanecerá para que los automóviles pasen.
int tiempo_minimo_verde_auto = 7000;
 
 
//   FUNCIONES DEL PROGRAMA
 
// Inicializa semáforo. Verde para automóviles

void semaforo_init(void) {
   // Enciende el led verde para automóviles. Apaga los demás leds
   digitalWrite(verde_auto, HIGH);
   digitalWrite(rojo_auto, LOW);
   digitalWrite(ambar_auto, LOW);
 
   // Enciende el led rojo para peatones. Apaga los demás leds
   digitalWrite(rojo_peaton, HIGH);
   digitalWrite(verde_peaton, LOW);
}
 
 

// Cambia el semáforo de automóviles a rojo
void semaforo_auto_rojo(void) {
   
   // Apaga el led verde para coches
   digitalWrite(verde_auto,  LOW);
 
   // Enciende el led ambar para coches y parpadea 3 veces
   for(int i=4; i>0; i--) {
      delay(500);
      digitalWrite(ambar_auto, HIGH);
      delay(500);
      digitalWrite(ambar_auto, LOW);
   }
 
   // Enciende el led rojo para coches
   digitalWrite(rojo_auto, HIGH);
}
 
// Espera a que se presione el pulsador

void semaforo_espera_pulsador(void) {
   int presionado;
   long time;
   
   // Espera a que se presione el pulsador
   // Debe permanecer esperando un tiempo mínimo
   time = millis() + tiempo_minimo_verde_auto; 
   presionado = 0;
   while(1) {
      // Se lee el estado del pulsador
      if (digitalRead(pulsador) == LOW)
         presionado = 1;
         
      // Si ha pasado el tiempo de verde para coches y se ha presionado el pulsador, salir
      if ((millis() > time) && (presionado == 1))
         break;
   }
}
 
 
// Espera un tiempo que depende del potenciómetro
void semaforo_delay(void) {
   int tiempo_peatones;
   
   // Calcula el tiempo de espera, 8 segundos más el tiempo que añada el potenciómetro
   tiempo_peatones = 8000 + 5 * analogRead(A0);
   // Envía por el puerto serie el tiempo de espera
   Serial.print("Tiempo para los peatones es : ");
   Serial.println(tiempo_peatones);
    // Espera
   delay(tiempo_peatones);
}
 
// Cambia el semáforo de peatones a rojo
void semaforo_peatones_rojo(void) {
 // Parpadea el led verde 3 veces
   for(int i=3; i>0; i--) {
      digitalWrite(verde_peaton, LOW);
      delay(500);
      digitalWrite(verde_peaton, HIGH);
      delay(500);
   }
 // Enciende el led rojo para peatones y apaga el verde
   digitalWrite(verde_peaton, LOW);
   digitalWrite(rojo_peaton, HIGH);
}
 

// Inicialización del programa y definicion de salidas de arduino.
void setup() {
   pinMode(verde_auto, OUTPUT);
   pinMode(ambar_auto, OUTPUT);
   pinMode(rojo_auto, OUTPUT);
   pinMode(verde_peaton, OUTPUT);
   pinMode(rojo_peaton, OUTPUT);
   // Define las entradas con resistencia de Pull-up
   pinMode(pulsador, INPUT_PULLUP);
   // Inicializa el puerto de comunicaciones
   Serial.begin(9600);
   Serial.println("Semáforo en marcha");
}
 

// Programa principal que llama a las funciones creadas anteriormente creadas.
void loop() {
    // Inicializa semáforo. Verde para automóviles
   semaforo_init();
   // Espera a que se presione el pulsador
   semaforo_espera_pulsador();
   // Cambia el semáforo de automóviles a rojo
   semaforo_auto_rojo();
   // Espera antes de permitir paso a peatones
   delay(1500);
   // Enciende el led verde para peatones
   digitalWrite(rojo_peaton, LOW);
   digitalWrite(verde_peaton, HIGH);
   // Espera un tiempo que depende del potenciómetro
   semaforo_delay();
   // Cambia el semáforo de peatones a rojo
   semaforo_peatones_rojo();
   // Espera antes de permitir el paso a los automóviles
   delay(2000);
 }
