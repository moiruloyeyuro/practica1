//potenciometro
const int portPin = 34; //Pin del potenciómetro
int x;
int potValor; //valor potenciometro
char a;
//pwm
const int pwm = 23;  // GPIO33 salida pwm
const int frecuencia = 5000;//Hz
const int ledChannel = 0; //Canal
const int resolucion = 8; //bits, de 0 a 255

float segundos; //para una lectura
int D; //lectura, duty escalado de 0 a 9
int dutyreal; //duty real, hasta 255
String opcion; //opción de salida
 
void setup(){
  Serial.begin(115200);
  // configuracion pwm
  ledcSetup(ledChannel, frecuencia, resolucion); 
  ledcAttachPin(pwm, ledChannel); //salida pwm
}
 
void loop(){

    if(Serial.available()>0){ //condicion puerto libre
    segundos=0;
    opcion = Serial.readStringUntil('\n'); //lee lo que escribo por pantalla
    
    if (opcion == "ADC"){
      Serial.println(opcion);
      potValor = analogRead(portPin);
      x = map(potValor, 0, 4095 , 0, 3300);
      Serial.println(x); //Envío del valor al puerto serie
      delay(1000);
    }
    
    else if (opcion.startsWith("ADC(")){//si lo escrito empieza por ADC(
      Serial.println(opcion);
      opcion.remove(-1); 
      opcion.remove(0, 4); //esta linea y la anterior borran los caracteres que no son los segundos 
      segundos=opcion.toInt();//cambia de opcion a int
      if(segundos>0){
        Serial.println("Lectura del ADC cada "+String(segundos)+" segundos");
      }     
    }
    
    else if (opcion.startsWith("PWM(")){//si empieza por PWM(
      Serial.println(opcion);
      opcion.remove(-1); 
      opcion.remove(0, 4); // borra caracteres no interesantes
      D=opcion.toInt(); //pasa el numero a int
      dutyreal = map(D, 0, 9 , 0, 255); //escala a 255
      Serial.println(dutyreal);
  }
    }
    
    else if (opcion == 0){
      //no mando datos
    }
    if(segundos>0){        
        potValor = analogRead(portPin);
        x = map(potValor, 0, 4095 , 0, 3300);
        Serial.println(x);
        delay(segundos*1000);//delay de segundos indicados             
  } 
    if (dutyreal>0 && dutyreal<256){
        ledcWrite(ledChannel,dutyreal);    
        delay(1000); //tiempo entre lecturas de 1000 ms (1s)
    }
  }   