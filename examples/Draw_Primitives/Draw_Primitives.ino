#include "SSD1306_OledLib_Arduino.h"

VLS_DisplayCore display; 

void setup(){ 
  Wire.begin(); // Nesesary for manual set display adress
  display.begin(0x3C); // Start display witch adress 0x3C   
  }

void loop(){
    display.drawLine(10, 5, 32, 18, true); //Draw line test. drawLine(x1,y1,x2,y2, bool pixelMode)
       display.drawPixel(39,18,true); //Draw pixel test. drawPixel(x,y,bool pixelMode) 
       display.SetFrame(); // Send data to display

        delay(10000);
        
        display.clearDisplay();// Clear display
        display.SetFrame();
        
        display.drawRect(34, 19, 40, 40, 1); //Draw rect test. drawRect(Top left x,top left y,bottom right x, bottom right y, bool pixel mode)       
        display.fillCircle(80, 32, 18, 1); //Fill circle test. fillCircle/drawCircle(Center x, Center y, Radius, bool pixel mode);

        display.SetFrame();

        delay(10000);
        
        display.clearDisplay();
        display.SetFrame();
}
