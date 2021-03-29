
#include <stdio.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void selectBus(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup() {  
  Wire.begin();  
  Serial.begin(9600);
  Serial.println("Started");

  selectBus(2);
  initDrv();
  
  selectBus(3);
  initDrv();    
}

void initDrv() {
  drv.begin();
  drv.useLRA(); 
  drv.selectLibrary(6);
  drv.setMode(DRV2605_MODE_INTTRIG); 
}


void loop() {
  
  selectBus(2);
  play();

 delay(100);
  
  selectBus(3);
  play();
  
 delay(100);
}

void play(){
      drv.stop();
      delayMicroseconds(1);
      
      // set the effect to play
      drv.setWaveform(0, 1);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
    
      // play the effect!
      drv.go();  
}

void __loop() {

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
  delay(100);    
}
