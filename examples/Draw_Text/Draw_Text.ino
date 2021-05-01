#include "SSD1306_OledLib_Arduino.h"

VLS_DisplayCore display; 

void setup(){ 
  
  display.begin(); // Start display witch defoult settings 
  }

  void loop(){
    display.print(25,22,"Test text"); // print string print(Top left x, Top left y, data)
    display.SetFrame(); // Send data to display
    delay(5000);

    display.clearDisplay();// Clear display
    display.SetFrame();

    display.print(25,22,1.25f); // print float print(Top left x, Top left y, data)
    display.SetFrame(); // Send data to display
    delay(5000);

    display.clearDisplay();// Clear display
    display.SetFrame();

    display.print(25,22, 256); // print int print(Top left x, Top left y, data)
    display.SetFrame(); // Send data to display
    delay(5000);

    display.clearDisplay();// Clear display
    display.SetFrame();


    char tst[7]={'D','i','s','p','l','a','y'};
    display.print(25,22, tst); // print char array print(Top left x, Top left y, data)
    display.SetFrame(); // Send data to display
    delay(5000);

    display.clearDisplay();// Clear display
    display.SetFrame();
    }
