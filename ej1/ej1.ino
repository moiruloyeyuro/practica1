//potenciometro conectado a GPIO 34
const int portPin = 34;
// Almacenamiento del valor de puerto (rango de 0-4095)
int potValor;
float x;
void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  potValor = analogRead(portPin);
  x = map(potValor), 0, 4095 , 0, 3300);
  Serial.println(x); //Envío del valor al puerto serie
  delay(1000);
}