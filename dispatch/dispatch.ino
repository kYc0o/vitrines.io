#include <Wire.h>

/*
Vitrines IO Arduino mega routing software
 Beerware V1337.42
 */

byte inputsVals[12]; //storing array for inputs readings
byte pInputsVals[12]; //storing array for previous inputs values
boolean flags[12]; //flags to be aware of current state
byte outputsVals[12]; //outputs vals

void setup() {

  Wire.begin(); // join i2c bus (address optional for master)
  
  Serial.begin(57600);
  Serial.println("Serial init... done !");

  //Declare 13 inputs pins for interruptors
  //NB : inputs and outputs pins are in face to face pairs
  for(byte i = 22; i < 47; i=i+2) {
    pinMode(i, INPUT);
  }

  //Declare 13 outputs pins for Teensys boards
  for(byte i = 23; i < 49; i=i+2) {
    pinMode(i, OUTPUT);
  }
  
  Serial.println("end of setup");
}

byte x = 0;


void loop() {
  
  byte count;
  
  //Read all inputs pins, store values in one array
  for(byte i = 22; i < 47; i=i+2){
 //   Serial.print(count);
    inputsVals[count] = digitalRead(i);
    count++;
  }
  
  count = 0;

  //Test if inputs are HIGH or LOW, sore the state in outputsVals array, digialwrite it
  for(byte i = 23; i < 49; i=i+2){
    if(inputsVals[count] == 1)
      outputsVals[count] = 1;
    else
      outputsVals[count] = 0;
      
    digitalWrite(i, outputsVals[count]);
    count++;
  }

  memcpy(pInputsVals, inputsVals, 12);
  
  Wire.beginTransmission(4);
  for(uint16_t i = 0; i < 9; i++){
    Wire.write(pInputsVals[i]);
    Serial.print(pInputsVals[i]);
  }
  Serial.println();
  Wire.endTransmission();
  delay(50);
}
