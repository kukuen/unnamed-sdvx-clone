
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
  play();
  
  selectBus(3);
  initDrv();  
  play();  
}

void initDrv() {
  drv.begin();
  drv.useLRA(); 
  drv.selectLibrary(6);
  drv.setMode(DRV2605_MODE_INTTRIG); 
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




void loop() {
  char buf[32];

  while(Serial.available()) {
    size_t count = Serial.readBytesUntil('\0', buf, 32);

    if(buf[0] == 1) {
      selectBus(2);      
    } else {
      selectBus(3);
    }
    
    play();
  }
  delay(1);    
}


void __loop() {
  
  selectBus(2);
  play();

 delay(100);
  
  selectBus(3);
  play();
  
 delay(100);
}
