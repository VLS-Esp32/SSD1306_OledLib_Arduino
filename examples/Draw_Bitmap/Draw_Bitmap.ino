#include "SSD1306_OledLib_Arduino.h"

VLS_DisplayCore display;


const byte PROGMEM Bird[300] ={    // Flappy Bird. Array for avr or esp8266, to work on esp32 please remove "const"
 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,
 0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,
 0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,
 0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,
 0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,
 0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
 0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,
 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  

 const uint8_t PROGMEM C_data[] = { //Bitmap Array for avr or esp8266, to work on esp32 please remove "const"
  B00000000,
  B00000000,
  B00000000,
  B10000011,
  B11000111,
  B11101111,
  B11111111,
  B11111111,
};

void setup(){ 
  Wire.begin(); // Nesesary for manual set display adress
  display.begin(0x3C); // Start display witch adress 0x3C   
  
   display.drawBytePicture(34, 19, Bird, 20, 15); //Draw byte picture. drawBytePicture(Top left x, top left y, Picture array(PROGMEM),Size x,Size y)

  display.drawBitmap(42, 50, C_data, 7, 8); //Draw byte picture. drawBytePicture(Top left x, top left y, Picture array(PROGMEM),Size x,Size y)
  
  display.SetFrame();
  }
  

  void loop(){
   
  }