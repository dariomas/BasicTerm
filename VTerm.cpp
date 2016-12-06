/*
 * BasicTerm.cpp
 * Provides basic ANSI/VT220 terminal control over a serial interface
 * Copyright 2011 Trannie Carter <borys@nottwo.org>
 * Licensed for use under the terms of the GNU Lesser General Public License v3
 */

#include "VTerm.h"
#include "VT100.h"

VTerm::VTerm(Stream *ser) {
    serial = ser;
}

int VTerm::available(void) {
    return serial->available();
}

int VTerm::peek(void) {
    return serial->peek();
}

int VTerm::read(void) {
    return serial->read();
}

void VTerm::flush(void) {
    serial->flush();
}

size_t VTerm::write(uint8_t c) {
    uint8_t ret;

    if(c & BT_ALTCHAR) {
        serial->print(BT_START_ALTCHAR);
        ret = serial->write(c & ~BT_ALTCHAR);
        serial->print(BT_END_ALTCHAR);
        return ret;
    }

    return serial->write(c);
}

void VTerm::init(void) {
   serial->print(RIS); 
}

void VTerm::cls(void) {
    serial->print(CLS);
}

void VTerm::home(void) {
    serial->print(HOME);
}

void VTerm::up(char x) {
    serial->print(CSI);
    serial->print(x,DEC);
    serial->write('A');
}

void VTerm::down(char x) {
    serial->print(CSI);
    serial->print(x,DEC);
    serial->write('B');
}

void VTerm::forward(char x) {
    serial->print(CSI);
    serial->print(x,DEC);
    serial->write('C');
}

void VTerm::backward(char x) {
    serial->print(CSI);
    serial->print(x,DEC);
    serial->write('D');
}

void VTerm::eraseLine(void) {
    serial->print(EL2);
}

void VTerm::eraseScreen(void) {
    serial->print(ED2);
}

void VTerm::fill(char x1, char y1, char x2, char y2) {
    for (char x = x1; x <= x2; x++)
  {
    for (char y = y1; y <= y2; y++)
    {
      position(x,y);
      serial->print(' ');
    }
  }
}
void VTerm::position(uint8_t row, uint8_t col) {
    serial->print(CSI);
    serial->print((uint8_t)row + 1);
    serial->print(F(";"));
    serial->print((uint8_t)col + 1);
    serial->print(F("H"));
}

void VTerm::show_cursor(boolean show) {
    if(show) {
        serial->print(SHOW_CURSOR);
    } else {
        serial->print(HIDE_CURSOR);
    }
}

int16_t VTerm::get_key(void) {
    int16_t key;
    uint16_t when;

    key = serial->read();

    if(key == ESC_CHAR) { /* escape sequence */
        when = millis();
        while(serial->available() < 2) {
            if(((uint16_t) millis() - when) > 1000) {
                return key;
            }
        }

        key = serial->read();

        switch(key) {
            case '[':
                key = serial->read();
                switch(key) {
                    case 'A':
                        return BT_KEY_UP;
                    case 'B':
                        return BT_KEY_DOWN;
                    case 'C':
                        return BT_KEY_RIGHT;
                    case 'D':
                        return BT_KEY_LEFT;
                    default:
                        return BT_KEY_UNKNOWN;
                }
                break;
            case 'O':
                key = serial->read();
                switch(key) {
                    case 'P':
                        return BT_KEY_F(1);
                    case 'Q':
                        return BT_KEY_F(2);
                    case 'R':
                        return BT_KEY_F(3);
                    case 'S':
                        return BT_KEY_F(4);
                    default:
                        return BT_KEY_UNKNOWN;
                }
                break;
            default:
                return BT_KEY_UNKNOWN;
        } 
    }

    return key;
}

void VTerm::set_attribute(uint8_t attr) {
    if(attr & BT_REVERSE) {
        serial->print(REVERSE);
    }
    if(attr & BT_UNDERLINE) {
        serial->print(UNDERLINE);
    }
    if(attr & BT_BOLD) {
        serial->print(BOLD);
    }
    if(attr & BT_BLINK) {
        serial->print(BLINK);
    }
    if(attr == BT_NORMAL) {
        serial->print(OFF);
    }
}

void VTerm::set_color(uint8_t fg, uint8_t bg) {
    serial->print(CSI);
    serial->print(30 + fg);
    serial->print(";");
    serial->print(40 + bg);
    serial->print("m");
}

void VTerm::beep(void) {
    serial->print(BELL_CHAR);
}
