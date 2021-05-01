//////////////////////////
// Esp 32 Graphics Core. Created by VLS 
// 23.03.21
// v 1.0.0
////////////////////////

#pragma once
#include "Arduino.h"
#include "Wire.h"
#include "fonts/main_Font.c" // Include font for text printing

#ifdef __AVR__
#include <avr/pgmspace.h>
#elif ESP8266
#include <pgmspace.h>
#endif

#define SSD1306_X                 128     //Defines commands for SSD1306
#define SSD1306_Y                 64    

#define PAGE_MODE                     01 
#define HORIZONTAL_MODE               02
 
#define SSD1306_Command_Mode          0x80
#define SSD1306_Data_Mode             0x40
#define SSD1306_Display_Off_Cmd       0xAE
#define SSD1306_Display_On_Cmd        0xAF
#define SSD1306_Normal_Display_Cmd    0xA6
#define SSD1306_Inverse_Display_Cmd   0xA7
#define SSD1306_Set_Brightness_Cmd    0x81

#ifdef __AVR__
#define SSD_1306_Wire_Buffer_Size    16  //Do not touch! Or touch, if you know, what is this. 16 is defoult
#elif  ESP32
#define SSD_1306_Wire_Buffer_Size     64 //Do not touch! Or touch, if you know, what is this. 64 is defoult
#elif ESP8266
#define SSD_1306_Wire_Buffer_Size     32 //Do not touch! Or touch, if you know, what is this. 32 is defoult
#endif

#define PRIMITIVES_ENABLED // Enable primitves module


class VLS_DisplayCore{
  public:
  
  void begin (unsigned char address); //System voids
  void begin (); 
  void setBrightness(byte Brightness);
  void switchDisplay(); // Turn of or turn on display
  ////////////////////////////////////////////////////// END OF SYSTEM VOIDS /////////////////////////////////////////////
  
  void drawPixel(int x,int y,bool md);
  bool IsPixelSet(int x, int y);
  void clearDisplay();
       
  void SetFrame();  // Set buffer data on display

  ////////////////////////////////////////////////////////// PRIMITIVES /////////////////////////////////////////////////////////////////
  #ifdef PRIMITIVES_ENABLED
   void drawRect(int x1,int y1, int x2, int y2, bool md);// X1, Y1- Upper left point, X2, Y2- lower right point, md - pixel mode true-on, false - off
   void drawLine(int x1, int y1, int x2, int y2, bool md); // X1, Y1- first point, X2, Y2- second point, md - pixel mode true-on, false - off   
   void drawCircle(int x1, int y1, int r, bool md);  // X, Y - Center, R -radius, md - pixel mode true-on, false - off
   
   void fillRect(int x1,int y1, int x2, int y2, bool md);// X1, Y1- Upper left point, X2, Y2- lower right point, md - pixel mode true-on, false - off
   void fillCircle(int x1, int y1, int r, bool md);  // X, Y - Center, R -radius, md - pixel mode true-on, false - off
   #endif
 ////////////////////////////////////////////////////////// END OF PRIMITIVES /////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////// BITMAP, BYTEMAP /////////////////////////////////////////////////////////////////
  
   void drawBytePicture(int x,int y, byte Picture[],int SizeX, int SizeY); //Drawing a picture from byte array (0 or 1) x,y -Top left coordinate, Picture - array of bytes(0 or 1), SizeX,SizeY - size of picture. FOR AVR Or ESP 8266 only PROGMEM!
   
   void drawBitmap(int x,int y, const uint8_t Picture[],int SizeX, int SizeY); //Drawing  bitmap from byte aray. Supports the same arrays as Adafruit ssd1306. FOR AVR Or ESP 8266 only PROGMEM!
  ////////////////////////////////////////////////////////// END OF BITMAP, BYTEMAP /////////////////////////////////////////////////////////////////

 ////////////////////////////////////////////////////////// TEXT PRINT //////////////////////////////////////////////////////////////////////////
  void print(int x, int y, String data);
  void print(int x, int y, int data);
  void print(int x, int y, float data);
  void print(int x, int y, char data);
  void print(int x, int y, char data[]);
  
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
  private:  
  unsigned char DAddr= 0x3c;
  
  unsigned char BufferP0[(SSD1306_X*SSD1306_Y)/64]; //Page buffers
  unsigned char BufferP1[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP2[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP3[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP4[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP5[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP6[(SSD1306_X*SSD1306_Y)/64];
  unsigned char BufferP7[(SSD1306_X*SSD1306_Y)/64];

  bool IsP0Edited=false; //Page Editing markers
  bool IsP1Edited=false;
  bool IsP2Edited=false;
  bool IsP3Edited=false;
  bool IsP4Edited=false;
  bool IsP5Edited=false;
  bool IsP6Edited=false;
  bool IsP7Edited=false;

  bool IsDisplayEnabled=true;
  
  void dspCmd(unsigned char cmd); 
  void dspDta(unsigned char data);
  
  void drawChar(int x,int y, const uint8_t Picture[],int SizeX, int SizeY);// Draw bitmap witch mods
       
  void dspClr(); // Clear Display 
  void ClrTables();
  
  
  void SetTable(byte id);  //Set table

  
  };

 
