//potenciometro
const int portPin = 34; //Pin del potenciómetro
int duty; 
int x;
int potValor; //valor potenciometro

//pwm
const int pwm = 33;  // GPIO33 salida pwm
const int frecuencia = 5000;//Hz
const int ledChannel = 0; //Canal
const int resolucion = 8; //bits, de 0 a 255
 
void setup(){
  Serial.begin(115200);
  // configuracion pwm
  ledcSetup(ledChannel, frecuencia, resolucion); 
  ledcAttachPin(pwm, ledChannel); //salida pwm
}
 
void loop(){
  potValor = analogRead(portPin);
  //lee potenciometro
  duty = map(potValor, 0, 4095 , 0, 255); //da un valor de duty proporcional al estado del potenciometro
  Serial.println(duty); //Envío del valor al puerto serie
  ledcWrite(ledChannel,duty); //salida pin y duty
}   