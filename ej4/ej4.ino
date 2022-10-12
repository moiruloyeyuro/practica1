//potenciometro
const int portPin = 34; //Pin del potenciómetro
int x;
int potValor; //valor potenciometro

//pwm
const int pwm = 13;  // GPIO13 salida pwm
const int frecuencia = 5000;//Hz
const int ledChannel = 0; //Canal
const int resolucion = 8; //bits, de 0 a 255

int segundos; //para una lectura
int D; //lectura, duty escalado de 0 a 9
int dutyreal; //duty real, hasta 255
string opcion; //opción de salida
 
void setup(){
  Serial.begin(115200);
  // configuracion pwm
  ledcSetup(portPin, frecuencia, resolucion); 
  ledcAttachPin(pwm, portPin); //salida pwm
}
 
void loop(){

    if(Serial.available()>0){ //condicion puerto libre
    segundos=0;
    opcion = Serial.readStringUntil('\n'); //lee lo que escribo por pantalla
    
    if (opcion == "ADC"){
      Serial.println(opcion);
      potValor = analogRead(portPin);
      x = map(potValor), 0, 4095 , 0, 3300);
      Serial.println(x); //Envío del valor al puerto serie
      delay(1000);
      
          
    }
    
    else if (opcion.startsWith("ADC(")){//si lo escrito empieza por ADC(
      Serial.println(opcion);
      opcion.remove(-1); 
      opcion.remove(0, 4); //esta linea y la anterior borran los caracteres que no son los segundos 
      segundos=opcion.toInt();//cambia de opcion a int
      Serial.println("Lectura del ADC cada "+String(segundos)+" segundos");  
      if(segundos>0){        
        potValor = analogRead(portPin);
        x = map(potValor), 0, 4095 , 0, 3300);
        Serial.println(x);
        delay(segundos*1000);//delay de segundos indicados             
  }    
    }
    
    else if (opcion.startsWith("PWM(")){//si empieza por PWM(
      Serial.println(opcion);
      opcion.remove(-1); 
      opcion.remove(0, 4); // borra caracteres no interesantes
      D=opcion.toInt(); //pasa el numero a int
      dutyreal=(255*duty)/9; //escala a 255
      Serial.println(dutyreal);    
      if (dutyreal>0){
        ledcWrite(pwm,dutyreal);    
        delay(1000); //tiempo entre lecturas de 1000 ms (1s)
  }
    }
    else if (opcion == 0){
      //no mando datos
    }
  }  
}







  potValor = analogRead(portPin);
  //lee potenciometro
  x = map(potValor, 0, 4095 , 0, 255); 
  // ajusta a 255 (resolucion)
  ledcWrite(portPin,x);
  delay(20);
 
}   