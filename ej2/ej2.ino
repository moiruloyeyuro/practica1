//potenciometro conectado a GPIO 34
volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t*timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}


const int portPin = 34;

// Almacenamiento del valor de puerto (rango de 0-4095)
int potValor;
float x;
void setup() {


  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = timerBegin(0,80, true); 
  //1) tiempo inicial, 2) prescaler 3)true interrupcion es edge, false es level
  //contador inicial a 80MHz por defecto, divido entre 80 (prescaler)
  timerAttachInterrupt(timer, &onTimer,true);
  //Ejecuta cuando se genera la interrupción
  //1) timer global 2)onTimer, se especifica despues 
  //3)true interrupcion es edge, false es level
  timerAlarmWrite(timer,10000000,true);
  //especifica el valor de contador donde se genera la interrupción.
  //primera entrada timer global, segunda entrada numero de microsegundos para que ocurra
  //la interrupcion, true es para que el contador se recargue
  //el tiempo va en microsegundos solo si se pone 80 de prescaler
  //ahora genera una interrupción cada 10 segundos
  timerAlarmEnable(timer);
  class machine.PWM(portPin,5000,512] )
}

void loop() {
  // put your main code here, to run repeatedly:
if (interruptCounter > 0) {
 //si el contador es mayor que 0
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
    //Cuento una interrupcion mas
    Serial.print("Se ha producido una interrupción. Numero de interrupciones: ");
    Serial.println(totalInterruptCounter);
    potValor = analogRead(portPin);
    x = map(potValor, 0, 4095, 0, 3300)
    Serial.println(x);
 //dice cuantas interrupciones han habido y saca el valor por pantalla
  }
}