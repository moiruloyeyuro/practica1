
#include <Wire.h> //librería para conectar por I2C
#include "MPU9250_asukiaaa.h"
#define MPU 0x68 //Direccion I2C
int i=0;
const int pinSDA= 22;
const int pinSCL= 23;
int cont;
int16_t AcX;
int16_t AcY;
int16_t AcZ;


void I2Cread(uint8_t Direccion, uint8_t Registro, uint8_t Nbytes)
{
   Wire.beginTransmission(Direccion); //direccion del esclavo
   Wire.write(Registro); //registro con el que me comunico
   Wire.endTransmission(false);
   Wire.requestFrom(Direccion, Nbytes,true);//leo N bytes del esclavo
}

void I2CwriteByte(uint8_t Direccion, uint8_t Registro)
{
   Wire.beginTransmission(Direccion);  //Inicio comunicacion
   Wire.write(Registro);//Accedo al registro para escribir
   Wire.endTransmission(true);
}


void setup(){
  // config I2C
  Wire.begin(pinSDA, pinSCL);
  
  // comm serie
  I2CwriteByte(MPU, 0x6B);
   Serial.begin(115200);
  }

void loop(){
  for( cont = 0; cont < 10; cont ++){
    I2Cread(MPU, 0x6B, 6);
    i++; 
    AcX = Wire.read()<<8|Wire.read();
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();
    delay(100); //muestreo cada 100ms
  }

  //mando porr UART
  if( cont == 10){
    
    Serial.println(String(AcX) + "," + String(AcY)+ "," + String(AcZ)); 
    cont = 0; // reseteo el contador
  }
}

