/*
  VTSerial.h - Serial library for inputing numbers and text via
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
/* 
  
  This library allows integer and floating point numbers and text to be input via a serial terminal
  program supporting the VT100 escape sequences.
  (We recommend the free TeraTerm software available at http://en.sourceforge.jp/projects/ttssh2/releases/)
  This library allows easy data entry of numbers and text into a program and also allows correction
  via the backspace key. 
  Numbers are entered as a string and converted to an actual number before being returned
  to the calling program. Invalid characters entered are discarded.
  The Backspace key only works back to start of data entry not to the start of the line so
  any previous text displayed is not erased.
  
  ReadLong()
    Read a signed long integer
    - only one minus sign (-) can be input and it must be the first character
    - maximum of 10 numeric characters
	 - no other characters allowed
  ReadFloat()
    Read a float
    - only one minus sign (-) can be input and it must be the first character
	 - Only one dot (.) can be input and it must be preceeded by a number character
    - maximum of 10 numeric characters
	 - no other characters allowed
  ReadText(char* inStr, unsigned char strsize )
    - Allows input of any characters between 32 (space) and 127
    - Char array must be passed to function along with max length allowed	 
  clearscreen()
    Clears the complete screen of text and leaves cursor in top left corner
  clearline()
    Clears the current line and leaves cursor at the beginning of the line	 
	 Useful for displaying changing output values without the screen scrolling

  Example use
  -----------
  
  char inStr[11];		// must be 1 digit more than max characters allowed
  
  longval = vtSerial.ReadLong();
  floatval = vtSerial.ReadFloat();
  vtSerial.ReadText(inStr, 10);
  
  Limitations
  -----------
  No bounds checking is done on the long integer number entered.
  A long integer has a range between -2,147,483,648 and 2,147,483,647 
  Entering a number outside these bounds (e.g. 3,000,000,000) will give an
  inaccurate result
  
  Example Program
  ---------------
  
  #include <VTSerial.h>

  VTSerial vtSerial;

  long mynum = 0;
  float myfloat = 0;
  char mytext[21];

  void setup() {
    Serial.begin(9600);      // open the serial port at 9600 bps:    
  }

  void loop() {  
    // print labels 
    Serial.print("Enter a Number: ");  // prints a label
    mynum = vtSerial.ReadLong();       // read integer
    Serial.print("  Val=");
    Serial.print(mynum);               // echo the number received to screen
    Serial.println("");                // prints carriage return
  
    Serial.print("Enter a Float: ");   // prints a label
    myfloat = vtSerial.ReadFloat();    // read float
    Serial.print("  Val=");
    Serial.print(myfloat);             // echo the number received to screen
    Serial.println("");                // prints another carriage return  
  
    Serial.print("Enter Text: ");      // prints a label
    vtSerial.ReadText(mytext,20);      // Read text
    Serial.print("  Val=");
    Serial.print(mytext);              // echo the text received to screen
    Serial.println("");                // prints another carriage return    

  }  
  
*/

#ifndef VTSerial_h
#define VTSerial_h

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class VTSerial
{
  public:
    VTSerial(void);
    long ReadLong();
	 float ReadFloat();
	 void ReadText(char* inStr, unsigned char strsize ); 
	 void clearscreen();
	 void clearline();
  private:

};

#endif
