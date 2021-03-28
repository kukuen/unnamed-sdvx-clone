
#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  drv.useLRA(); 
  
  drv.selectLibrary(6);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
  
      // set the effect to play
      drv.setWaveform(0, 1);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
    
      // play the effect!
      drv.go();
}


void loop() {

  
  while(Serial.available()){
    
    if(Serial.read()){
      drv.stop();
      delayMicroseconds(1);
      
      // set the effect to play
      drv.setWaveform(0, 1);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
    
      // play the effect!
      drv.go();
    }
   
  }
  
  delay(1);    
}
