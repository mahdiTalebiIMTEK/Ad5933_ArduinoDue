
#include "Wire.h"
#include "Math.h"
#include "Micro40Timer.h" // Timer function for notifications
#include "AD5933.h" //Library for AD5933 functions (must be installed)

// ================================================================
// Constants
// ================================================================



// ================================================================
// Dynamic variables
// ================================================================



byte Z_Value_byte[4];
double Z_Value = 0;          // Initialize impedance magnitude.

void setup() {

  // Begin I2C
  Wire.begin();
  Wire.setClock(400000);

  // Begin serial at 115200 baud for output
  Serial.begin(115200);
  Serial.println("AD5933 Test Started! M. Talebi IMTEK KvM May2019");
  
  // Perform initial configuration. Fail if any one of these fail.
  if (!(AD5933::reset() &&
        AD5933::setInternalClock(true) &&
        AD5933::setStartFrequency(START_FREQ) &&
        AD5933::setIncrementFrequency(FREQ_INCR) &&
        AD5933::setNumberIncrements(NUM_INCR) &&
        AD5933::setPGAGain(PGA_GAIN_X1)))
        {
            Serial.println("FAILED in initialization!");
            while (true) ;
        }

}
//Each single Measurement, we write 4 bytes
#define BYTESPERLOOP  4
#define BUFFERSIZE    1000
byte fifo[BYTESPERLOOP*BUFFERSIZE];
bool RecordingFlg = true;
unsigned int inpos=0;
unsigned int outpos=0;

void loop() {
  //delay(2); // Delay because Arduino serial buffer will return 1 if queried too quickly.
 // Micro40Timer::start(); 
  
 

//  while(recording){
//    AD5933.singleMesurement(&fifo[inpos]);
//    inpos= (inpos+BYTESPERLOOP);  //increment to the next adress, if we reached the end, we start
//    if(inpos>=BYTESPERLOOP*BUFFERSIZE){
//      inpos=0;
//      RecordingFlg = false;
//    }
//  }
//  while(inpos>outpos){
//    Serial.write(fifo[outpos]);
//    outpos++;
//  }
 //AD5933.singleMesurement(&Z_Value_byte[0]);
 //AD5933.getComplexOnce(gain_factor, systemPhaseShift, realimp, imgimp, Z_Value, phaseAngle);
AD5933.getComplex(gain_factor, systemPhaseShift, Z_Value, phaseAngle);

 // AD5933.setCtrMode(REPEAT_FREQ);

 //AD5933.singleMesurement(Z_Value_byte);
  //start logging 
  Serial.print("T measurement : ");
  Serial.println(millis());

//  while(1){
//    
//     }
  }
