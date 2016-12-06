/*
  VTSerial.cpp - Serial library for inputing numbers and text via
  VT100 compatible terminal software - Version 1
  Copyright (c) 2010 www.hobbytronics.co.uk  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VTSerial.h"

VTSerial::VTSerial()
{
}

// Special version of strtoi 
long vt_strtoi (char *a){
  unsigned char i=0; 
  char neg=1;
  char w;
  long intval=0, inttemp;
  i=0;
  if(a[0]=='-') {
    neg=-1;
    i++;
  }  
  do{ 
    w=a[i];
    inttemp=(long) w;
    inttemp=inttemp-48;
    if((inttemp >=0) && (inttemp <=9)){
      intval*=10;
      intval+=inttemp;
    }
    i++;
  } while(a[i]);
  intval*=neg;
  return intval;
}

void backspace(void) {
  unsigned char esc = 27; 						// Escape character (27)
  #if ARDUINO >= 100  
  Serial.write(esc); 							// Move back 1 char
  Serial.write("[D");   
  Serial.write(" ");    						// print space
  Serial.write(esc);								// Move back 1 char
  Serial.write("[D");   
  #else
  Serial.print(esc); 							// Move back 1 char
  Serial.print("[D");   
  Serial.print(" ");    						// print space
  Serial.print(esc);								// Move back 1 char
  Serial.print("[D");     
  #endif
}

void VTSerial::clearscreen(void) {
  unsigned char esc = 27; 						// Escape character (27)
  #if ARDUINO >= 100    
  Serial.write(esc); 							// Clear screen
  Serial.write("[2J");    
  Serial.write(esc); 							// Move to Home
  Serial.write("[H");  
  #else
  Serial.print(esc); 							// Clear screen
  Serial.print("[2J");    
  Serial.print(esc); 							// Move to Home
  Serial.print("[H"); 
  #endif 
}

void VTSerial::clearline(void) {
  unsigned char esc = 27; 						// Escape character (27)
  #if ARDUINO >= 100    
  Serial.write(esc); 							// Clear line
  Serial.write("[2K");    
  Serial.write(esc); 							// Move to beginning of line
  Serial.write("[80D");   
  #else
  Serial.print(esc); 							// Clear line
  Serial.print("[2K");    
  Serial.print(esc); 							// Move to beginning of line
  Serial.print("[80D");  
  #endif 
}

// Read signed long integer
// - sign can only be at the beginning
// Max 10 numeric digits
long VTSerial::ReadLong(void) {
  int x;
  long val;
  char inByte;
  char inStr[12];
  //while (Serial.available() == 0) ;       // wait for user input
  x=0;
  inByte='0';
  do{
    if(Serial.available()) {
      inByte = Serial.read();    // read the data bytes
      if((inByte >=48 && inByte <= 57) || (inByte == 45 && x==0)) {
		  if((x < 11 && inStr[0] == '-') || (x < 10 && inStr[0] != '-')) {
          Serial.print(inByte);   // if byte is an allowed character echo it back and store it
          inStr[x] = inByte;
          x++;
          inStr[x] = '\0';        // Make sure end of string marker set
		  }	 
      }  
      else if(inByte == 8 && x >0) {
        // Backspace
		  backspace();
        x--;   
        inStr[x] = '\0';        // Make sure end of string marker set        
      }  
    }      
  } while (inByte != '\n' && inByte != '\r');    // Keep looping until New Line or Return received
  val = vt_strtoi(inStr);
  return(val);
}

// Read float
// - sign can only be at the beginning
// Only one . allowed, must be a number before it
// Max 10 numeric digits
float VTSerial::ReadFloat(void) {
  int x;
  float val;
  char inByte;
  char isDot;
  char inStr[12];
  x=0;
  isDot=0;
  inByte='0';
  do{
    if(Serial.available()) {
      inByte = Serial.read();    // read the data bytes
      if((inByte >=48 && inByte <= 57) || (inByte == 45 && x==0) || (inByte == 46 && x > 0)) {
		  // inByte is a number, or its a minus sign at the beginning, or its a dot not at the beginning
		  if((x < 11 && inStr[0] == '-') || (x < 10 && inStr[0] != '-')) {
		    if((inByte != 46) || (inByte == 46 && isDot == 0 && inStr[x-1] != '-' && x>0)) {
		  
            Serial.print(inByte);   // if byte is an allowed character echo it back and store it
            inStr[x] = inByte;
            x++;
            inStr[x] = '\0';        // Make sure end of string marker set
			   if(inByte == 46) isDot=1;
			 }	
		  }	 
      }  
      else if(inByte == 8 && x >0) {
        // Backspace
		  backspace();	           		// Send VT backspace sequence
        x--;   
		  if(inStr[x] == '.') isDot=0;  // Removed character is a dot, so reset isDot
        inStr[x] = '\0';        		// Make sure end of string marker set        
      }  
    }      
  } while (inByte != '\n' && inByte != '\r');    // Keep looping until CR received
  val = atof(inStr);  					// or strtof()
  return(val);
}

// Read text
// Max strsize characters
void VTSerial::ReadText(char* inStr, unsigned char strsize ) {
  int x;
  char inByte;
  x=0;
  inByte='0';
  do{
    if(Serial.available()) {
      inByte = Serial.read();    // read the data bytes
      if((inByte >=32 && inByte <= 127)) {
		  if(x < strsize) {
          Serial.print(inByte);   // if byte is an allowed character echo it back and store it
          inStr[x] = inByte;
          x++;
          inStr[x] = '\0';        // Make sure end of string marker set
		  }	 
      }  
      else if(inByte == 8 && x >0) {
        // Backspace
		  backspace();
        x--;   
        inStr[x] = '\0';        // Make sure end of string marker set        
      }  
    }      
  } while (inByte != '\n' && inByte != '\r');    // Keep looping until CR received
}


/*
Here is an example program showing the use of the VTSerial library

 

#include <VTSerial.h>

VTSerial vtSerial;

long mynum = 0;
float myfloat = 0;
char mytext[21];

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:    
  Serial.println("Example VTSerial program");  // prints a label  
  Serial.println("------------------------");  // prints carriage return    
}

void loop() {  

  // print labels 
  Serial.print("Enter a Number: ");  // prints a label
  mynum = vtSerial.ReadLong();      // read integer
  Serial.print("  Val=");
  Serial.print(mynum);               // echo the number received to screen
  Serial.println("");                // prints carriage return
  
  Serial.print("Enter a Float: ");   // prints a label
  myfloat = vtSerial.ReadFloat();   // read float
  Serial.print("  Val=");
  Serial.print(myfloat,4);           // echo the number received, to 4 DP
  Serial.println("");                // prints another carriage return  
  
  Serial.print("Enter Text: ");      // prints a label
  vtSerial.ReadText(mytext,20);     // Read text
  Serial.print("  Val=");
  Serial.print(mytext);              // echo the text received to screen
  Serial.println("");                // prints another carriage return    

}
*/
