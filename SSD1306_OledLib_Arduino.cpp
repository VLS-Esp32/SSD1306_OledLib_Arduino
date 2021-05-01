//////////////////////////
// Esp 32 Graphics Core. Created by VLS 
// 23.03.21
// v 1.0.0
////////////////////////

#include "SSD1306_OledLib_Arduino.h"

/////////////////////////////////////////////////////////////////////////////////////LOW LEVEL CALLS////////////////////////////////////////////////////////////
 void VLS_DisplayCore::begin(unsigned char address){   //Instantiate library  
	//Wire.begin(-1,-1,2000000); //Setup I2C connection witch frequency  2Mhz. Not here
	DAddr=address;	
 
 dspCmd(0xAE); //Commands to instantiate 
 dspCmd(0xD5); 
 dspCmd(0x80); 
 dspCmd(0xD3); 
 dspCmd(0x0); 
 dspCmd(0x40); 
 dspCmd(0x8D); 
 dspCmd(0x14); 
 dspCmd(0x20); 
 dspCmd(0x02); 
 dspCmd(0xA1);
 dspCmd(0xC8); 
 dspCmd(0xDA); 
 dspCmd(0x12); 
 dspCmd(0x81); 
 dspCmd(0xCF); 
 dspCmd(0xD9); 
 dspCmd(0xF1); 
 dspCmd(0xDB); 
 dspCmd(0x40); 
 dspCmd(0xA4); 
 dspCmd(0xA6); 
 dspCmd(0xAF);
 
 ClrTables();// Clearing buffers 
 dspClr(); // Clearing display
 SetFrame();
 }
 
 void VLS_DisplayCore::begin(){   //Instantiate library
  #ifdef ESP32 
  Wire.begin(-1,-1,2000000); //Setup I2C connection witch frequency  2Mhz
  #else
  Wire.begin(); //Setup I2C connection for atmega
  #endif   
  begin(0x3C);
 }
 
 void VLS_DisplayCore::dspCmd(unsigned char cmd){  //Low level display function
 
 Wire.beginTransmission(DAddr); //Select Device 
 Wire.write(SSD1306_Command_Mode); // Set command mode 
 Wire.write(cmd); // Write cmd 
 Wire.endTransmission();
	 
 }
 
void VLS_DisplayCore::switchDisplay(){
  if(IsDisplayEnabled){
    dspCmd(0xAE);
    IsDisplayEnabled=false;
  }else{
    dspCmd(0xAF);
    IsDisplayEnabled=true;
  }  
}
 
 void VLS_DisplayCore::dspDta(unsigned char dta){   //Low level display function
 Wire.beginTransmission(DAddr); //Select Device 
 Wire.write(SSD1306_Data_Mode); // Set data mode 
 Wire.write(dta); //Write dta
 Wire.endTransmission();	 
 }
 
 void VLS_DisplayCore::dspClr(){ // Clear screen
   ClrTables();  
   IsP0Edited=true; 
   IsP1Edited=true;
   IsP2Edited=true;
   IsP3Edited=true;
   IsP4Edited=true;
   IsP5Edited=true;
   IsP6Edited=true;
   IsP7Edited=true;
   //SetFrame();  // Useless
 }
 

 void VLS_DisplayCore::SetFrame(){ //Send data to display

    if(IsP0Edited){
      SetTable(0);
      IsP0Edited=false; // Clearing page edited markers
    }
    if(IsP1Edited){
      SetTable(1);
      IsP1Edited=false;
    }
     if(IsP2Edited){
      SetTable(2);
      IsP2Edited=false;
    }
     if(IsP3Edited){
      SetTable(3);
      IsP3Edited=false;
    }
     if(IsP4Edited){
      SetTable(4);
      IsP4Edited=false;
    }
     if(IsP5Edited){
      SetTable(5);
      IsP5Edited=false;
    }
     if(IsP6Edited){
      SetTable(6);
      IsP6Edited=false;
    }
     if(IsP7Edited){
      SetTable(7);
     IsP7Edited=false; 
    }             
 }

  void VLS_DisplayCore::setBrightness(byte Brightness){    //Set Brightness
     dspCmd(SSD1306_Set_Brightness_Cmd);
     dspCmd(Brightness);
  }

 void VLS_DisplayCore::SetTable(byte id){     
  unsigned char Buffer[(SSD1306_X*SSD1306_Y)/64];     
  switch(id){ //Switch table
    case 0:
    memcpy(Buffer,BufferP0, sizeof(BufferP0));  
    break;  
     case 1:
   memcpy(Buffer, BufferP1, sizeof(BufferP1));
    break;  
     case 2:
    memcpy(Buffer, BufferP2, sizeof(BufferP2));
    break;  
     case 3:
    memcpy(Buffer, BufferP3, sizeof(BufferP3));
    break;  
     case 4:
    memcpy(Buffer, BufferP4, sizeof(BufferP4));
    break;  
     case 5:
    memcpy(Buffer, BufferP5, sizeof(BufferP5));
    break;  
     case 6:
    memcpy(Buffer, BufferP6, sizeof(BufferP6));
    break;  
    case 7:
    memcpy(Buffer, BufferP7, sizeof(BufferP7));
    break;    
  }
  
 dspCmd(0x22); //Header
 dspCmd(id); //Begin 
 dspCmd(id); // end 

 byte _TransmittesCount=SSD1306_X/SSD_1306_Wire_Buffer_Size; //Calculate a transmittions count
 byte _outBytes=0; 

 for(int i=0;i<_TransmittesCount;i++){  
  
  Wire.beginTransmission(DAddr); //Select Device
  Wire.write(0x40); // SSD1306_Data_Mode
       
  for(int b=0;b<SSD_1306_Wire_Buffer_Size;b++){   //Set data on wire buffer
     Wire.write(Buffer[_outBytes]); //Send data 
    _outBytes++;
    
  }
  Wire.endTransmission();  // End transmittion
 }
 }

 void VLS_DisplayCore::ClrTables(){ //Clr Pages
  
  
  memset(BufferP0, 0x00,(SSD1306_X*SSD1306_Y)/64); // Clearing page buffers
  memset(BufferP1, 0x00,(SSD1306_X*SSD1306_Y)/64);
  memset(BufferP2, 0x00,(SSD1306_X*SSD1306_Y)/64);
  memset(BufferP3, 0x00,(SSD1306_X*SSD1306_Y)/64);
  memset(BufferP4, 0x00,(SSD1306_X*SSD1306_Y)/64);
  memset(BufferP5, 0x00,(SSD1306_X*SSD1306_Y)/64);
  memset(BufferP6, 0x00,(SSD1306_X*SSD1306_Y)/64);  
  memset(BufferP7, 0x00,(SSD1306_X*SSD1306_Y)/64);
  

  // memset(pixelBuffer, 0x00,(SSD1306_X*SSD1306_Y));  //Clearing user pixel buffer 
 }
  
 void VLS_DisplayCore::drawPixel(int x,int y,bool md) // Draving a pixel
 {
  if(x<SSD1306_X && y<SSD1306_Y){  // Foolproof 
  int Page= (y/8);  //Select current page
  byte inpageY=(y-((8*Page-1)))-1; //Select bit number in current page    
  unsigned char tmp; //temp byte val
 
  switch(Page){  //Select page buffer
    case 0:
   
    tmp=BufferP0[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP0[x]=tmp; 
    IsP0Edited=true;     
    break;
    
    case 1:
    
    tmp=BufferP1[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP1[x]=tmp; 
    IsP1Edited=true;     
    break;  
    
    case 2:
   
    tmp=BufferP2[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP2[x]=tmp;    
    IsP2Edited=true;  
    break; 
     
    case 3:
    
    tmp=BufferP3[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP3[x]=tmp;  
    IsP3Edited=true;    
    break;
      
    case 4:
    
    tmp=BufferP4[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP4[x]=tmp;
     IsP4Edited=true;         
    break;
    
    case 5:
   
    tmp=BufferP5[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP5[x]=tmp; 
     IsP5Edited=true;        
    break; 
     
    case 6:
   
    tmp=BufferP6[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);}  //Set bit value    
    BufferP6[x]=tmp; 
     IsP6Edited=true;        
    break; 
     
    case 7:
    
    tmp=BufferP7[x]; //Execute from buffer 
    if(md){bitWrite(tmp, inpageY, 1);}else{bitWrite(tmp, inpageY, 0);} //Set bit value    
    BufferP7[x]=tmp;
    IsP7Edited=true;         
    break;      
  }
  
  } 
 }


 

  bool VLS_DisplayCore::IsPixelSet(int x, int y){ // Checking: is the pixel enabled (x, y); 
  
  byte Result=0;  // Bit value, defoult is false
  
  if(x<SSD1306_X && y<SSD1306_Y){  // Foolproof

  int Page= (y/8);  //Select current page
  byte inpageY=(y-((8*Page-1)))-1; //Select bit number in current page 
  
  
  unsigned char tmp; //temp byte val
   
 switch(Page){  //Select page buffer   
    case 0:   
    tmp=BufferP0[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 1:   
    tmp=BufferP1[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 2:   
    tmp=BufferP2[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 3:   
    tmp=BufferP3[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 4:   
    tmp=BufferP4[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 5:   
    tmp=BufferP5[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 6:   
    tmp=BufferP6[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;
    
    case 7:   
    tmp=BufferP7[x]; //Execute from buffer 
    Result=bitRead(tmp, inpageY); // Get bit value
    break;    
  }
 
  }
  return Result;  //Return current value
 }

 
 void VLS_DisplayCore::clearDisplay(){
  dspClr();
 }

/////////////////////////////////////////////////////////////////////////////////////HIGH LEVEL CALLS////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////// PRIMITIVES /////////////////////////////////////////////////////////////////
#ifdef PRIMITIVES_ENABLED 
void VLS_DisplayCore::drawRect(int x1,int y1, int x2, int y2, bool md) { 
   if(x2<SSD1306_X && y2<SSD1306_Y && x2>x1 && y2>y1){  // Foolproof
    
   int currentX=x1; 
   int currentY=y1;

  int cyclessCount=(((x2-x1)+1)*((y2-y1)+1)); //Count of cyclless on rect
  //Serial.println(pixelCount);
   for(int i=0; i<cyclessCount; i++){    //Magic cycle 
     
    if(currentY==y1 || currentY==y2 || currentX==x1 || currentX==x2){ // Is this pixel or space?
    drawPixel(currentX,currentY,md); //Set current pixel
    }  
        
   if(currentX==x2){ // if tis end of line    
   currentX=x1;
   currentY++;   
   }else{currentX++;} 
           
    }                      //End of magic cycle 
      
  }
 }

 void VLS_DisplayCore::drawLine(int x1, int y1, int x2, int y2, bool md){   //Bresenhem algorithm for line
 
  if(x2<SSD1306_X && y2<SSD1306_Y && x1<SSD1306_X && y1<SSD1306_Y){  // Foolproof

    if(x1!=x2){  //If is no vertical line
      
    int deltaX=abs(x2-x1); // deltax 
    int deltaY=abs(y2-y1); //deltay
    int err=0;  // Error of match
    int dr= y2-y1; //diary
    int y=y1; // Current ordinate
    int deltaerr= deltaY+1; 

    if(dr>0){ //Calculate diary
      dr=1;
    }
    if(dr<0){
      dr=-1;
    }

    for(int currX=x1; currX<x2; currX++){ //Magick cycle
    drawPixel(currX,y,md); //Set pixel

    err += deltaerr;
    if(err >= (deltaX + 1)){ //If need add diary
      y+=dr;
      err -= (deltaX+1);
    }
    
    } //End of magic cycle 
    
    }else{
      int dir=0;
      
      if(y1<y2){ //Calculate direction
        dir=1;
        
         for(int i=y1;i<=y2;i+=dir){
             drawPixel(x1,i,md);
            }
      }
            
      if(y1>y2){
        dir=-1;
         for(int i=y1;i>=y2;i+=dir){ 
             drawPixel(x1,i,md);  
          }
      }   

       //END           
    }      
  }
 } 

 void VLS_DisplayCore::drawCircle(int x, int y, int r, bool md){  //Bresenhem algorithm for circle (No coments)
   if(x+r <128 && x+r>=0 && x-r <128 && x-r>=0 && y+r<64 && y+r>=0 && y-r<64 && y-r>=0){  // Foolproof
    int currentX=0; 
    int currentY=r;
    int delta= 1- (2*r);
    int err=0; //Error
    
    while (currentY >= 0){ //Magic cycle #2
     drawPixel(currentX+x,currentY+y,md); // Draw current pixels
     drawPixel(x-currentX,currentY+y,md);
     drawPixel(currentX+x,y-currentY,md);
     drawPixel(x-currentX,y-currentY,md);
     
     err = (2 * (delta + currentY)) - 1;
     
     if(delta<=0 && err<=0){
      currentX++;
      delta += 2* currentX +1; 
      continue;     
     }
     
     if(delta>0 && err>0){
      currentY--;
       delta -= 2 * currentY + 1;
       continue;
     }
     
     currentX++;
     delta += 2 * (currentX - currentY);       
     currentY--; 
    }    
   }
 }

 void VLS_DisplayCore::fillRect(int x1,int y1, int x2, int y2, bool md) {
  if(x2<SSD1306_X && y2<SSD1306_Y && x2>x1 && y2>y1){  // Foolproof
    
   int currentX=x1; 
   int currentY=y1;

  int cyclessCount=(((x2-x1)+1)*((y2-y1)+1)); //Count of cyclless on rect
  //Serial.println(pixelCount);
   for(int i=0; i<cyclessCount; i++){    //Drawing cycle    
    
    drawPixel(currentX,currentY,md); //Set current pixel      
        
   if(currentX==x2){ // if tis end of line    
   currentX=x1;
   currentY++;   
   }else{currentX++;} 
           
    }                      //End of magic cycle 
      
  }
}

void VLS_DisplayCore::fillCircle(int x, int y, int r, bool md){  //Bresenhem algorithm for circle (No coments)
   if(x+r <128 && x+r>=0 && x-r <128 && x-r>=0 && y+r<64 && y+r>=0 && y-r<64 && y-r>=0){  // Foolproof
    int currentX=0; 
    int currentY=r;
    int delta=1- 2*r;
    int err=0; //Error
    
   while (currentY >= 0){ //Magic cycle #2
     drawPixel(currentX+x,currentY+y,md); // Draw current pixels
     drawPixel(x-currentX,currentY+y,md);
     drawPixel(currentX+x,y-currentY,md);
     drawPixel(x-currentX,y-currentY,md);
     
     err = (2 * (delta + currentY)) - 1;
     
     if(delta<=0 && err<=0){
      currentX++;
      delta += 2* currentX +1; 
      continue;     
     }
     
     if(delta>0 && err>0){
      currentY--;
       delta -= 2 * currentY + 1;
       continue;
     }
     
     currentX++;
     delta += 2 * (currentX - currentY);       
     currentY--; 
    }    

     int TmpX=(x-(r+1)); // Start of fill cycle. 
     int TmpY=(y-r); 
     
     
     for(int i=0;i<r*2;i++){ // Cycle for y
       bool startMarkerFinded=false; // Doesn't work differently. Why?     
       for(int b=0;b<(r+1)*2;b++){ // Cycle for x
        
        
        if(IsPixelSet(TmpX,TmpY)==md){  //Start and end marker detection           
          if(!startMarkerFinded){ // Very bad part
            startMarkerFinded=true;
          }else if(TmpX>x){break;}// End marker finded. Even worse         
        }
        
        if(startMarkerFinded){
           drawPixel(TmpX,TmpY,md); // Draw a pixel in circle            
        }           
                
        TmpX++;        
        }
        
       TmpX=(x-(r+1));
       TmpY+=1;
       Serial.println(i);
     }        
   }
 }
 #endif
////////////////////////////////////////////////////////// END OF PRIMITIVES /////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////// PICTURES ///////////////////////////////////////////////////////////////////////////

void VLS_DisplayCore::drawBytePicture(int x,int y, byte Picture[],int SizeX, int SizeY)
{
if(x+SizeX<SSD1306_X && y+SizeY<SSD1306_Y){  // Foolproof
    
int sz=SizeX*SizeY;

int currentX=0;
int currentY=0;

for(int i=0;i<sz;i++){ // The cycle of art :)  

  #ifdef __AVR__    //Variant of PROGMEM using
  if(pgm_read_byte(&Picture[i])==1){  // For AVR controllers
  #elif ESP32
  if(Picture[i]==1){  // For ESP 32 or 8266 controllers 
  #elif ESP8266
  if(pgm_read_byte(&Picture[i])==1){    //Not working now
  #endif
         
 // if(Picture[i]==1){      
  drawPixel(currentX+x,currentY+y,1);  
  }else{drawPixel(currentX+x,currentY+y,0);}
    
  currentX++;
  if(currentX==SizeX){ // Next line    
    currentY++;
    currentX=0;
  }    
}
  } 
}

 void VLS_DisplayCore::drawBitmap(int x,int y,const uint8_t Picture[],int SizeX, int SizeY){ // Draw a bitmap from byte array  
  if(x+SizeX<SSD1306_X && y+SizeY<SSD1306_Y){  // Foolproof    
  //int pixels_count=SizeX*SizeY;
  int currY=y;
  int currX=x;  
  
  int current_byteInArray=0; // This variables needed to calculate need byte and bit in array
  
  int current_bitInByte=7;
  
  #ifdef __AVR__    //Variant of PROGMEM using
  uint8_t currentByte=pgm_read_byte(&Picture[current_byteInArray]); // For AVR controllers
  #elif ESP32
  uint8_t currentByte=Picture[current_byteInArray];   // For ESP 32 or 8266 controllers 
  #elif ESP8266
  uint8_t currentByte=pgm_read_byte(&Picture[current_byteInArray]);  //Not working now
  #endif
  
 // uint8_t currentByte=Picture[current_byteInArray];
  
  for(int i=0;i<SizeY;i++){ // Cycle for y axis
    
  for(int b=0;b<SizeX;b++){ // Cycle for x axis
  
  if(bitRead(currentByte, current_bitInByte)==1){ //Read bit in bitmap
    drawPixel(currX,currY,0); // pixel off        
  }else {drawPixel(currX,currY,1);}  // pixel on
    
    if(current_bitInByte==0||b==(SizeX-1)){ // Set next byte or drop current byte
      current_byteInArray++;
      current_bitInByte=7;
      
  #ifdef __AVR__    //Variant of PROGMEM using
  currentByte=pgm_read_byte(&Picture[current_byteInArray]); // For AVR controllers
  #elif ESP32
  currentByte=Picture[current_byteInArray];  // For ESP 32 or 8266 controllers 
  #elif ESP8266
  currentByte=pgm_read_byte(&Picture[current_byteInArray]);  //Not working now
  #endif     
      
    }else{ current_bitInByte--;} //Select next bit   
    
    currX++;
  } 
   
  currX=x; 
  currY++; //Next line
  }
  
  }
 }
  ///////////////////////////////////////////////////////// END OF PICTURES ///////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////// TEXT PRINT //////////////////////////////////////////////////////////////////////////
  
  void VLS_DisplayCore::drawChar(int x,int y,const uint8_t Picture[],int SizeX, int SizeY){ // Draw a bitmap from byte array  
  if(x+SizeX<SSD1306_X && y+SizeY<SSD1306_Y){  // Foolproof    
  //int pixels_count=SizeX*SizeY;
  int currY=y+SizeY;
  int currX=x;  
  int current_byteInArray=0; // This variables needed to calculate need byte and bit in array
  int current_bitInByte=7;
  
  #ifdef __AVR__    //Variant of PROGMEM using
  uint8_t currentByte=pgm_read_byte(&Picture[current_byteInArray]); // For AVR controllers
  #elif ESP32
  uint8_t currentByte=Picture[current_byteInArray];   // For ESP 32 or 8266 controllers 
  #elif ESP8266
  uint8_t currentByte=pgm_read_byte(&Picture[current_byteInArray]);  //Not working now
  #endif 
  
  for(int i=SizeY;i>0;i--){ // Cycle for y axis
    
  for(int b=0;b<SizeX;b++){ // Cycle for x axis
  
  if(bitRead(currentByte, current_bitInByte)==0){ //Read bit in bitmap
    drawPixel(currX,currY,0); // pixel off        
  }else {drawPixel(currX,currY,1);}  // pixel on
    
    if(current_bitInByte==0||b==(SizeX-1)){ // Set next byte or drop current byte
      current_byteInArray++;
      current_bitInByte=7;
      
  #ifdef __AVR__    //Variant of PROGMEM using
    currentByte=pgm_read_byte(&Picture[current_byteInArray]); // For AVR controllers
  #elif ESP32
  currentByte=Picture[current_byteInArray];  // For ESP 32 or 8266 controllers 
  #elif ESP8266
   currentByte=pgm_read_byte(&Picture[current_byteInArray]);  //Not working now
  #endif       
      
    }else{ current_bitInByte--;} //Select next bit   
    
    currX++;
  } 
   
  currX=x; 
  currY--; //Next line
  }
  
  }
 }
 
    
  void VLS_DisplayCore::print(int x, int y, String data){
   if(x+7<SSD1306_X && y+13<SSD1306_Y){  // Foolproof     
    char buff[data.length()]; //Char buffer
   // Serial.println(data.length());// Debug!!
    data.toCharArray(buff,data.length()+1); //Conwerting string to char array
   
    for(int i=0;i<(data.length());i++){ //print cycle
    byte tmp=buff[i]; //Select char
    Serial.println(buff[i]); //Debug
    if(tmp>32&&tmp<126){ // Foolproof  #2
      
      drawChar(x,y,mainFont[(tmp-32)],7,13); //Draw char
    }
      x+=9; //Next char
    }
        
   }
  }

  void VLS_DisplayCore::print(int x, int y, int data){
    String tmp = String(data);
    print(x,y, tmp);
   }
   
   void VLS_DisplayCore::print(int x, int y, float data){
    String tmp = String(data);
    print(x,y, tmp);
   }
   
   void VLS_DisplayCore::print(int x, int y, char data){
    String tmp = String(data);
    print(x,y, tmp);
   }
   
    void VLS_DisplayCore::print(int x, int y, char data[]){
    String tmp = String(data);
    print(x,y, tmp);
   }
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
