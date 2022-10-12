//potenciometro
const int portPin = 34; //Pin del potenciómetro
int x;
int potValor; //valor potenciometro

//pwm
const int pwm = 13;  // GPIO13 salida pwm
const int frecuencia = 5000;//Hz
const int ledChannel = 0; //Canal
const int resolucion = 8; //bits, de 0 a 255
 
void setup(){
  Serial.begin(115200);
  // configuracion pwm
  ledcSetup(portPin, frecuencia, resolucion); 
  ledcAttachPin(pwm, portPin); //salida pwm
}
 
void loop(){
  potValor = analogRead(portPin);
  //lee potenciometro
  x = map(potValor, 0, 4095 , 0, 255); 
  // ajusta a 255 (resolucion)
  ledcWrite(portPin,x);
  delay(20);
 
}   