#ifndef VT100_h
#define VT100_h
//
//    FILE: VT100.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: VT100 codes, to be sent by serial.print() et al.
//    DATE: 2013-09-30
//     URL:
//
// Released to the public domain
//

// Sources of VT100 codes:
// http://ascii-table.com/ansi-escape-sequences-vt-100.php
// http://hackipedia.org/Protocols/Terminal,%20DEC%20VT100/html/VT100%20Escape%20Codes.html
// https://sourceforge.net/projects/arduino-si4735/

//control chars and sequences
#define BELL_CHAR '\x07'
#define ESC_CHAR '\x1B'
#define CSI_CHAR '\x9B'   //single char version of CSI
#define CSI      F("\x1B[")  //two char version of CSI

#define RIS          F("\x1B\x63")   // RIS	Reset to Initial State			ESC c
#define EL           F("\x1B[K")  // cleareol              Erase to end of current line           ^[K
#define EL2           F("\x1B[2K")  // Esc[2K 	Clear entire line 	EL2
#define ERASE_TO_END_OF_SCREEN F("\x1B[J")  // cleareos              Erase to end of screen                 ^[J
#define ED2 F("\x1B[2J")  // Esc[2J 	Clear entire screen 	ED2
#define SHOW_CURSOR     F("\x1B[?25h")
#define HIDE_CURSOR     F("\x1B[?25l")

// CHAR MODES
#define OFF             F("\x1B[0m")    // modesoff SGR0         Turn off character attributes          ^[[0m
#define NORMAL          F("\x1B[m")     // modesoff SGR0         Turn off character attributes          ^[[m
#define BOLD            F("\x1B[1m")    // bold SGR1             Turn bold mode on                      ^[[1m
#define LOWINTENS       F("\x1B[2m")    // lowint SGR2           Turn low intensity mode on             ^[[2m
#define UNDERLINE       F("\x1B[4m")    // underline SGR4        Turn underline mode on                 ^[[4m
#define BLINK           F("\x1B[5m")    // blink SGR5            Turn blinking mode on                  ^[[5m
#define REVERSE         F("\x1B[7m")    // reverse SGR7          Turn reverse video on                  ^[[7m

// POSITIONING
#define CLS             F("\x1B[2J")       // clearscreen ED2      Esc[2J Clear entire screen
#define HOME            F("\x1B[H")       // cursorhome            Move cursor to upper left corner       ^[[H
//#define POSX(x)      CSI #x "G"         
//#define GOTOXY(x,y)    "\033[x;yH"     // Esc[Line;ColumnH
// #define POS(x,y)     CSI #y ";" #x "H" // cursorpos(v,h) CUP    Move cursor to screen location v,h     ^[[<v>;<h>H
// #define CUD(x)          "\033[xB"      // cursordn(n) CUD       Move cursor down n lines               ^[[<n>B
// Esc[ValueA 	Move cursor up n lines 	    CUU
// Esc[ValueB 	Move cursor down n lines 	CUD
// Esc[ValueC 	Move cursor right n lines 	CUF
// Esc[ValueD 	Move cursor left n lines 	CUB



// ADDITIONAL CODES depend on terminal if supported.
/*
Esc[20h 	Set new line mode 	LMN
Esc[?1h 	Set cursor key to application 	DECCKM
none 	Set ANSI (versus VT52) 	DECANM
Esc[?3h 	Set number of columns to 132 	DECCOLM
Esc[?4h 	Set smooth scrolling 	DECSCLM
Esc[?5h 	Set reverse video on screen 	DECSCNM
Esc[?6h 	Set origin to relative 	DECOM
Esc[?7h 	Set auto-wrap mode 	DECAWM
Esc[?8h 	Set auto-repeat mode 	DECARM
Esc[?9h 	Set interlacing mode 	DECINLM

Esc[20l 	Set line feed mode 	LMN
Esc[?1l 	Set cursor key to cursor 	DECCKM
Esc[?2l 	Set VT52 (versus ANSI) 	DECANM
Esc[?3l 	Set number of columns to 80 	DECCOLM
Esc[?4l 	Set jump scrolling 	DECSCLM
Esc[?5l 	Set normal video on screen 	DECSCNM
Esc[?6l 	Set origin to absolute 	DECOM
Esc[?7l 	Reset auto-wrap mode 	DECAWM
Esc[?8l 	Reset auto-repeat mode 	DECARM
Esc[?9l 	Reset interlacing mode 	DECINLM

Esc= 	Set alternate keypad mode 	DECKPAM
Esc> 	Set numeric keypad mode 	DECKPNM

Esc(A 	Set United Kingdom G0 character set 	setukg0
Esc)A 	Set United Kingdom G1 character set 	setukg1
Esc(B 	Set United States G0 character set 	setusg0
Esc)B 	Set United States G1 character set 	setusg1
Esc(0 	Set G0 special chars. & line set 	setspecg0
Esc)0 	Set G1 special chars. & line set 	setspecg1
Esc(1 	Set G0 alternate character ROM 	setaltg0
Esc)1 	Set G1 alternate character ROM 	setaltg1
Esc(2 	Set G0 alt char ROM and spec. graphics 	setaltspecg0
Esc)2 	Set G1 alt char ROM and spec. graphics 	setaltspecg1

EscN 	Set single shift 2 	SS2
EscO 	Set single shift 3 	SS3

Esc[m 	Turn off character attributes 	SGR0
Esc[0m 	Turn off character attributes 	SGR0
Esc[1m 	Turn bold mode on 	SGR1
Esc[2m 	Turn low intensity mode on 	SGR2
Esc[4m 	Turn underline mode on 	SGR4
Esc[5m 	Turn blinking mode on 	SGR5
Esc[7m 	Turn reverse video on 	SGR7
Esc[8m 	Turn invisible text mode on 	SGR8

Esc[Line;Liner 	Set top and bottom lines of a window 	DECSTBM

Esc[ValueA 	Move cursor up n lines 	CUU
Esc[ValueB 	Move cursor down n lines 	CUD
Esc[ValueC 	Move cursor right n lines 	CUF
Esc[ValueD 	Move cursor left n lines 	CUB
Esc[H 	Move cursor to upper left corner 	cursorhome
Esc[;H 	Move cursor to upper left corner 	cursorhome
Esc[Line;ColumnH 	Move cursor to screen location v,h 	CUP
Esc[f 	Move cursor to upper left corner 	hvhome
Esc[;f 	Move cursor to upper left corner 	hvhome
Esc[Line;Columnf 	Move cursor to screen location v,h 	CUP
EscD 	Move/scroll window up one line 	IND
EscM 	Move/scroll window down one line 	RI
EscE 	Move to next line 	NEL
Esc7 	Save cursor position and attributes 	DECSC
Esc8 	Restore cursor position and attributes 	DECSC

EscH 	Set a tab at the current column 	HTS
Esc[g 	Clear a tab at the current column 	TBC
Esc[0g 	Clear a tab at the current column 	TBC
Esc[3g 	Clear all tabs 	TBC

Esc#3 	Double-height letters, top half 	DECDHL
Esc#4 	Double-height letters, bottom half 	DECDHL
Esc#5 	Single width, single height letters 	DECSWL
Esc#6 	Double width, single height letters 	DECDWL

Esc[K 	Clear line from cursor right 	EL0
Esc[0K 	Clear line from cursor right 	EL0
Esc[1K 	Clear line from cursor left 	EL1
Esc[2K 	Clear entire line 	EL2

Esc[J 	Clear screen from cursor down 	ED0
Esc[0J 	Clear screen from cursor down 	ED0
Esc[1J 	Clear screen from cursor up 	ED1
Esc[2J 	Clear entire screen 	ED2

Esc5n 	Device status report 	DSR
Esc0n 	Response: terminal is OK 	DSR
Esc3n 	Response: terminal is not OK 	DSR

Esc6n 	Get cursor position 	DSR
EscLine;ColumnR 	Response: cursor is at v,h 	CPR

Esc[c 	Identify what terminal type 	DA
Esc[0c 	Identify what terminal type (another) 	DA
Esc[?1;Value0c 	Response: terminal type code n 	DA

Escc 	Reset terminal to initial state 	RIS

Esc#8 	Screen alignment display 	DECALN
Esc[2;1y 	Confidence power up test 	DECTST
Esc[2;2y 	Confidence loopback test 	DECTST
Esc[2;9y 	Repeat power up test 	DECTST
Esc[2;10y 	Repeat loopback test 	DECTST

Esc[0q 	Turn off all four leds 	DECLL0
Esc[1q 	Turn on LED #1 	DECLL1
Esc[2q 	Turn on LED #2 	DECLL2
Esc[3q 	Turn on LED #3 	DECLL3
Esc[4q 	Turn on LED #4 	DECLL4


Codes for use in VT52 compatibility mode
Esc< 	Enter/exit ANSI mode (VT52) 	setansi

Esc= 	Enter alternate keypad mode 	altkeypad
Esc> 	Exit alternate keypad mode 	numkeypad

EscF 	Use special graphics character set 	setgr
EscG 	Use normal US/UK character set 	resetgr

EscA 	Move cursor up one line 	cursorup
EscB 	Move cursor down one line 	cursordn
EscC 	Move cursor right one char 	cursorrt
EscD 	Move cursor left one char 	cursorlf
EscH 	Move cursor to upper left corner 	cursorhome
EscLineColumn 	Move cursor to v,h location 	cursorpos(v,h)
EscI 	Generate a reverse line-feed 	revindex

EscK 	Erase to end of current line 	cleareol
EscJ 	Erase to end of screen 	cleareos

EscZ 	Identify what the terminal is 	ident
Esc/Z 	Correct response to ident 	identresp




VT100 Special Key Codes

These are sent from the terminal back to the computer when the particular key is pressed.
Note that the numeric keypad keys send different codes in numeric mode than in alternate mode.
See escape codes above to change keypad mode.



Function Keys:
EscOP	PF1
EscOQ	PF2
EscOR	PF3
EscOS	PF4



Arrow Keys:
    Reset 	Set
up 	EscA	EscOA
down 	EscB	EscOB
right 	EscC	EscOC
left 	EscD	EscOD



Numeric Keypad Keys:
EscOp	0
EscOq	1
EscOr	2
EscOs	3
EscOt	4
EscOu	5
EscOv	6
EscOw	7
EscOx	8
EscOy	9
EscOm	-(minus)
EscOl	,(comma)
EscOn	.(period)
EscOM	^M



Printing:
Esc[i 	Print Screen 	Print the current screen
Esc[1i	Print Line 	Print the current line
Esc[4i	Stop Print Log 	Disable log
Esc[5i	Start Print Log	Start log; all received text is echoed to a printer


VT100 escape codes

This document describes how to control a VT100 terminal. The entries are of the form "name, description, escape code".

The name isn't important, and the description is just to help you find what you're looking for. What you have to do is send the "escape code" to the screen. These codes are often several characters long, but they all begin with ^[. This isn't the two characters ^ and [, but rather a representation of the ASCII code ESC (which is why these are called escape codes).

ESC has the decimal value 27 and should be sent before the rest of the code, which is simply an ASCII string.

As an example of how to use this information, here's how to clear the screen in C, using the VT100 escape codes:

    #define ASCII_ESC 27
    printf( "%c[2J", ASCII_ESC );

   or

    puts( "\033[2J" );

Name                  Description                            Esc Code
setnl LMN             Set new line mode                      ^[[20h
setappl DECCKM        Set cursor key to application          ^[[?1h
setansi DECANM        Set ANSI (versus VT52)                 none
setcol DECCOLM        Set number of columns to 132           ^[[?3h
setsmooth DECSCLM     Set smooth scrolling                   ^[[?4h
setrevscrn DECSCNM    Set reverse video on screen            ^[[?5h
setorgrel DECOM       Set origin to relative                 ^[[?6h
setwrap DECAWM        Set auto-wrap mode                     ^[[?7h
setrep DECARM         Set auto-repeat mode                   ^[[?8h
setinter DECINLM      Set interlacing mode                   ^[[?9h

setlf LMN             Set line feed mode                     ^[[20l
setcursor DECCKM      Set cursor key to cursor               ^[[?1l
setvt52 DECANM        Set VT52 (versus ANSI)                 ^[[?2l
resetcol DECCOLM      Set number of columns to 80            ^[[?3l
setjump DECSCLM       Set jump scrolling                     ^[[?4l
setnormscrn DECSCNM   Set normal video on screen             ^[[?5l
setorgabs DECOM       Set origin to absolute                 ^[[?6l
resetwrap DECAWM      Reset auto-wrap mode                   ^[[?7l
resetrep DECARM       Reset auto-repeat mode                 ^[[?8l
resetinter DECINLM    Reset interlacing mode                 ^[[?9l

altkeypad DECKPAM     Set alternate keypad mode              ^[=
numkeypad DECKPNM     Set numeric keypad mode                ^[>

setukg0               Set United Kingdom G0 character set    ^[(A
setukg1               Set United Kingdom G1 character set    ^[)A
setusg0               Set United States G0 character set     ^[(B
setusg1               Set United States G1 character set     ^[)B
setspecg0             Set G0 special chars. & line set       ^[(0
setspecg1             Set G1 special chars. & line set       ^[)0
setaltg0              Set G0 alternate character ROM         ^[(1
setaltg1              Set G1 alternate character ROM         ^[)1
setaltspecg0          Set G0 alt char ROM and spec. graphics ^[(2
setaltspecg1          Set G1 alt char ROM and spec. graphics ^[)2

setss2 SS2            Set single shift 2                     ^[N
setss3 SS3            Set single shift 3                     ^[O

modesoff SGR0         Turn off character attributes          ^[[m
modesoff SGR0         Turn off character attributes          ^[[0m
bold SGR1             Turn bold mode on                      ^[[1m
lowint SGR2           Turn low intensity mode on             ^[[2m
underline SGR4        Turn underline mode on                 ^[[4m
blink SGR5            Turn blinking mode on                  ^[[5m
reverse SGR7          Turn reverse video on                  ^[[7m
invisible SGR8        Turn invisible text mode on            ^[[8m

setwin DECSTBM        Set top and bottom line#s of a window  ^[[<v>;<v>r

cursorup(n) CUU       Move cursor up n lines                 ^[[<n>A
cursordn(n) CUD       Move cursor down n lines               ^[[<n>B
cursorrt(n) CUF       Move cursor right n lines              ^[[<n>C
cursorlf(n) CUB       Move cursor left n lines               ^[[<n>D
cursorhome            Move cursor to upper left corner       ^[[H
cursorhome            Move cursor to upper left corner       ^[[;H
cursorpos(v,h) CUP    Move cursor to screen location v,h     ^[[<v>;<h>H
hvhome                Move cursor to upper left corner       ^[[f
hvhome                Move cursor to upper left corner       ^[[;f
hvpos(v,h) CUP        Move cursor to screen location v,h     ^[[<v>;<h>f
index IND             Move/scroll window up one line         ^[D
revindex RI           Move/scroll window down one line       ^[M
nextline NEL          Move to next line                      ^[E
savecursor DECSC      Save cursor position and attributes    ^[7
restorecursor DECSC   Restore cursor position and attributes ^[8

tabset HTS            Set a tab at the current column        ^[H
tabclr TBC            Clear a tab at the current column      ^[[g
tabclr TBC            Clear a tab at the current column      ^[[0g
tabclrall TBC         Clear all tabs                         ^[[3g

dhtop DECDHL          Double-height letters, top half        ^[#3
dhbot DECDHL          Double-height letters, bottom half     ^[#4
swsh DECSWL           Single width, single height letters    ^[#5
dwsh DECDWL           Double width, single height letters    ^[#6

cleareol EL0          Clear line from cursor right           ^[[K
cleareol EL0          Clear line from cursor right           ^[[0K
clearbol EL1          Clear line from cursor left            ^[[1K
clearline EL2         Clear entire line                      ^[[2K

cleareos ED0          Clear screen from cursor down          ^[[J
cleareos ED0          Clear screen from cursor down          ^[[0J
clearbos ED1          Clear screen from cursor up            ^[[1J
clearscreen ED2       Clear entire screen                    ^[[2J

devstat DSR           Device status report                   ^[5n
termok DSR               Response: terminal is OK            ^[0n
termnok DSR              Response: terminal is not OK        ^[3n

getcursor DSR         Get cursor position                    ^[6n
cursorpos CPR            Response: cursor is at v,h          ^[<v>;<h>R

ident DA              Identify what terminal type            ^[[c
ident DA              Identify what terminal type (another)  ^[[0c
gettype DA               Response: terminal type code n      ^[[?1;<n>0c

reset RIS             Reset terminal to initial state        ^[c

align DECALN          Screen alignment display               ^[#8
testpu DECTST         Confidence power up test               ^[[2;1y
testlb DECTST         Confidence loopback test               ^[[2;2y
testpurep DECTST      Repeat power up test                   ^[[2;9y
testlbrep DECTST      Repeat loopback test                   ^[[2;10y

ledsoff DECLL0        Turn off all four leds                 ^[[0q
led1 DECLL1           Turn on LED #1                         ^[[1q
led2 DECLL2           Turn on LED #2                         ^[[2q
led3 DECLL3           Turn on LED #3                         ^[[3q
led4 DECLL4           Turn on LED #4                         ^[[4q

#
#  All codes below are for use in VT52 compatibility mode.
#

setansi               Enter/exit ANSI mode (VT52)            ^[<

altkeypad             Enter alternate keypad mode            ^[=
numkeypad             Exit alternate keypad mode             ^[>

setgr                 Use special graphics character set     ^[F
resetgr               Use normal US/UK character set         ^[G

cursorup              Move cursor up one line                ^[A
cursordn              Move cursor down one line              ^[B
cursorrt              Move cursor right one char             ^[C
cursorlf              Move cursor left one char              ^[D
cursorhome            Move cursor to upper left corner       ^[H
cursorpos(v,h)        Move cursor to v,h location            ^[<v><h>
revindex              Generate a reverse line-feed           ^[I

cleareol              Erase to end of current line           ^[K
cleareos              Erase to end of screen                 ^[J

ident                 Identify what the terminal is          ^[Z
identresp             Correct response to ident              ^[/Z

<hr>

#
# VT100 Special Key Codes
#
# These are sent from the terminal back to the computer when the
# particular key is pressed.  Note that the numeric keypad keys
# send different codes in numeric mode than in alternate mode.
# See escape codes above to change keypad mode.
#

# Function Keys:

PF1     ^[OP
PF2     ^[OQ
PF3     ^[OR
PF4     ^[OS


# Arrow Keys:
        Reset    Set
        -----    ---
up      ^[A ^[OA
down        ^[B ^[OB
right       ^[C ^[OC
left        ^[D ^[OD


# Numeric Keypad Keys:

        Keypad Mode
        -----------------
Keypad Key  Numeric Alternate
----------  ------- ---------
0       0   ^[Op
1       1   ^[Oq
2       2   ^[Or
3       3   ^[Os
4       4   ^[Ot
5       5   ^[Ou
6       6   ^[Ov
7       7   ^[Ow
8       8   ^[Ox
9       9   ^[Oy
- (minus)   -   ^[Om
, (comma)   ,   ^[Ol
. (period)  .   ^[On
ENTER       ^M  ^[OM


VT220 Keyboard Codes

In VT220 terminal emulation modes, the following additional keys are defined:

PC			Equivalent	   Cursor key mode
KEY			VT220 key	Reset		Set
Up-arrow		up-arrow	ESC [ A		ESC O A
Down-arrow		down-arrow	ESC [ B		ESC O B
Right-arrow		right-arrow	ESC [ C		ESC O C
Left-arrow		left-arrow	ESC [ D		ESC O D

PC			Equivalent		   
KEY			VT220 key	TRANSMITS
Shift-F1		PF1 key		ESC O P
Shift-F2		PF2 key		ESC O Q
Shift-F3		PF3 key		ESC O R
Shift-F4		PF4 key		ESC O S
Shift-F6		F6 key		ESC [ 1 7 ~
Shift-F7		F7 key		ESC [ 1 8 ~
Shift-F8		F8 key		ESC [ 1 9 ~
Shift-F9		F9 key		ESC [ 2 0 ~
Shift-F10		F10 key		ESC [ 2 1 ~
Numeric Keypad

When NumLock is OFF, the keypad sends functions as labelled alongside the digits (Home, UpArrow, etc). When NumLock is ON and the terminal is in Keypad Numeric Mode, the keypad sends the labelled digit. When NumLock is ON and the terminal is in Keypad Application Mode, the keypad sends the listed Escape sequences. The following table describes this.


				      Keypad mode
PC		   Equivalent		     [w/NumLock ON]
KEYPAD KEY	   VT220 keypad key	Numeric		Application
 0			0		0		ESC O p
 1			1		1		ESC O q
 2			2		2		ESC O r
 3			3		3		ESC O s
 4			4		4		ESC O t
 5			5		5		ESC O u
 6			6		6		ESC O v
 7			7		7		ESC O w
 8			8		8		ESC O x
 9			9		9		ESC O y
 +			,		+		ESC O l
 -			-		-		ESC O m
 .			.		.		ESC O n
 *			Enter		*		ESC O M
Enter			Enter				
VT220 DISPLAY CODES

This table describes the actions taken upon receipt of special control characters.

Character	Action
BELL (7)	Beeps the terminal.
BS (8)		Moves the cursor back one column.
HT (9)		Moves the cursor to the next tab stop.
		 (tabstops are set by the TABS config file command)
LF (10)		Moves the cursor down one row.
CR (13)		Moves the cursor to column one.
CAN (24)	Cancels an Escape sequence.
ESC (27)	Starts an Escape Sequence.
Escape Sequences recognized are:

NAME	DESCRIPTION				CODE SEQUENCE
CUU	Cursor Up				ESC [ Pn A
CUD	Cursor Down				ESC [ Pn B
CUF	Cursor Forward				ESC [ Pn C
CUB	Cursor Backward				ESC [ Pn D
CUP	Cursor Position				ESC [ Pn ; Pn H
HVP	Horizontal and Vertical Position	ESC [ Pn ; Pn f

IND	Index 					ESC D
NEL	Next Line				ESC E
HTS	Horizontal Tabulation Set		ESC H
RI	Reverse Index				ESC M

DECSTBM	Set Top and Bottom Margin		ESC [ Pn ; Pn r
DECSAVC	Save Cursor and attributes		ESC 7
DECRESC	Restore Cursor and attributes		ESC 8

ED	Erase in Display			ESC [ Ps J
	0	cursor to EOD
	1	BOD to cursor
	2	full display
EL	Erase in Line				ESC [ Ps K
	0	cursor to EOL
	1	BOL to cursor
	2	full line

DCH	Delete CHaracter			ESC [ Pn P
DL	Delete Line				ESC [ Pn M
ICH	Insert CHaracter			ESC [ Pn @
IL	Insert Line				ESC [ Pn L
ECH	Erase CHaracter				ESC [ Pn X

TBC	Tab Clear				ESC [ Ps g
	0	clear tab at current position
	3	clear all tab stops

DECKPAM Keypad Numeric Mode			ESC >
DECKPNM Keypad Application Mode			ESC =

RM	Reset Mode				ESC [ Ps l
SM	Set Mode				ESC [ Ps h
	IRM	4	Insert/Replacement mode
	LNM	20	Line feed/New line Mode
	DECCKM	? 1	Cursor/application Keypad Mode
	DECOM	? 6	Origin/absolute Mode
	DECAWM	? 7	AutoWrap at end-of-line Mode

SCS	Select Character Set			ESC ( Px
	A	ASCII Set
	B	ASCII Set
	0	Special Graphics

SGR	Select Graphic Rendition		ESC [ Ps m
	0	normal
	1	bold
	4	underlined
	5	blinking
	7	reverse video

RIS	Reset to Initial State			ESC c
DECSTR	Soft Reset				ESC [ ! p

DA	Device Attributes (primary)		ESC [ c
	terminal responds with "ESC [ ? 62 c"

DA	Device Attributes (secondary)		ESC [ > c
	terminal responds with "ESC [ > 1 ; 10 ; 0 c"
	
	
Notes about the control codes present in VT220, VT240, VT3x0, VT420, and later
DEC terminals.  These models all implement supersets of the VT100's features.

 -====-====-====-====-====-====-====-====-====-====-====-====-====-====-====-

By special request, here are the controls for 
"Visual Character and Line Attributes" in DEC terminals.

The sequence  CSI Ps;Ps;Ps m  (or 7-bit ESC [ Ps;Ps;Ps m)
allow visual attributes to be set for some characters.
The VT100 and/or VT102 could perform only a few attributes;
models beginning with the VT300 series could do more.

The values of "Ps" follow:

  Ps      Attribute             Mode
 ----   ------------------     ------ 
   0    all attributes off      all
   1    bold                    all
   4    underline               all
   5    blinking                all
   7    negative image          all
   8    invisible              VT300+
  22    bold off               VT300+
  24    underline off          VT300+
  25    blinking off           VT300+
  27    negative image off     VT300+
  28    invisible off          VT300+


Line attributes were set as follows:

Sequence    Attribute                         Mnemonic    Special
--------  ---------------------------------   --------  ------------ 
 ESC # 5   single-width, single-height line    DECSWL
 ESC # 6   double-width, single-height line    DECDWL

 ESC # 3   double-width, double-height line    DECDHL   (top half)
 ESC # 4   double-width, double-height line    DECDHL   (bottom half)


Please observe that the VT320 is *not* a color terminal.  It has only
a monochrome screen.  The VT340 is a color terminal, but does not obey
the ISO-6249/ECMA-48 color controls (it can do ReGIS graphics colors,
as can the VT241).

As far as I know, the only DEC terminal to implement and actually be
able to display ISO-6249/ECMA-48 color controls is the VT525 (which
was actually made for DEC by Boundless).

Of course, many contemporary "VT320-emulator" software products do
implement ISO-6249/ECMA-48 color, as an enhancement.  (This has led
to incorrect folklore that a real VT320 was a color terminal.)

These color controls are the 30-37 foreground, 40-47 background
arguments to the SGR control sequence.

*/

#endif
