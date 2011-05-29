/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "KeyMapKey.h"

KeyMapKey::KeyMapKey()
{
    //ctor
    device = DEV_KEYBOARD;
    setDeviceID(0);
    target = SJ_UNMAPPED;
}

KeyMapKey::KeyMapKey(CRstring k)
{
    device = DEV_KEYBOARD;
    setDeviceID(0);
    target = SJ_UNMAPPED;
    setKey(k);
}

#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
    KeyMapKey::KeyMapKey(__u16 k)
#else
    KeyMapKey::KeyMapKey(SDLKey k)
#endif
{
    device = DEV_KEYBOARD;
    setDeviceID(0);
    target = SJ_UNMAPPED;
    key= k;
}

KeyMapKey::~KeyMapKey()
{
    //dtor
}

bool KeyMapKey::isMapValid()
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        return (target != SJ_UNMAPPED && key != KEY_UNKNOWN && player != 0);
    #elif defined(PENJIN_SDL_INPUT) || defined(PENJIN_SDL)
        return (target != SJ_UNMAPPED && key != SDLK_UNKNOWN && player != 0);
    #endif
}

void KeyMapKey::setKey(CRstring k)
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
    // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
        if(k == "0")
            key=KEY_0;
        else if(k == "1")
            key=KEY_1;
        else if(k == "2")
            key=KEY_2;
        else if(k == "3")
            key=KEY_3;
        else if(k == "4")
            key=KEY_4;
        else if(k == "5")
            key=KEY_5;
        else if(k == "6")
            key=KEY_6;
        else if(k == "7")
            key=KEY_7;
        else if(k == "8")
            key=KEY_8;
        else if(k == "9")
            key=KEY_9;
        else if(k == "a" || k == "A")
            key=KEY_A;
        /*else if(k == "&")
            key=SDLK_AMPERSAND;*/
        else if(k == "*")
            key=KEY_KPASTERISK;
        /*else if(k == "@")
            key=SDLK_AT;*/
        else if(k == "b" || k == "B")
            key=KEY_B;
        /*else if(k == "`")
            key=SDLK_BACKQUOTE;*/
        else if(k == "\\")
            key=KEY_BACKSLASH;
        else if(k == "Backspace")
            key=KEY_BACKSPACE;
        else if(k == "Break")
            key=KEY_BREAK;
        else if(k == "c" || k == "C")
            key=KEY_C;
        else if(k == "CapsLock")
            key=KEY_CAPSLOCK;
        /*else if(k == "^")
            key=KEY_CARET;*/
        else if(k == "Clear")
            key=KEY_CLEAR;
        /*else if(k == "COLON")
            key=KEY_COLON;*/
        else if(k == "Comma")
            key=KEY_COMMA;
        else if(k == "Compose")
            key=KEY_COMPOSE;
        else if(k == "d" || k == "D")
            key=KEY_D;
        else if(k == "Delete")
            key=KEY_DELETE;
// TODO: this should compile just fine, but doesn't for some reason.  Perhaps my input.h is out of date
//        else if(k == "$")
//            key=KEY_DOLLAR;
        else if(k == "Down")
            key=KEY_DOWN;
        else if(k == "e" || k == "E")
            key=KEY_E;
        else if(k == "End")
            key=KEY_END;
        /*else if(k == "=")
            key=KEY_EQUALS;*/
        else if(k == "Escape")
            key=KEY_ESC;
// TODO: this should compile just fine, but doesn't for some reason.  Perhaps my input.h is out of date
//        else if(k == "EURO")
//            key=KEY_EURO;
        /*else if(k == "!")
            key=KEY_EXCLAIM;*/
        else if(k == "f" || k == "F")
            key=KEY_F;
        else if(k == "F1")
            key=KEY_F1;
        else if(k == "F10")
            key=KEY_F10;
        else if(k == "F11")
            key=KEY_F11;
        else if(k == "F12")
            key=KEY_F12;
        else if(k == "F13")
            key=KEY_F13;
        else if(k == "F14")
            key=KEY_F14;
        else if(k == "F15")
            key=KEY_F15;
        else if(k == "F2")
            key=KEY_F2;
        else if(k == "F3")
            key=KEY_F3;
        else if(k == "F4")
            key=KEY_F4;
        else if(k == "F5")
            key=KEY_F5;
        else if(k == "F6")
            key=KEY_F6;
        else if(k == "F7")
            key=KEY_F7;
        else if(k == "F8")
            key=KEY_F8;
        else if(k == "F9")
            key=KEY_F9;
        else if(k == "g" || k == "G")
            key=KEY_G;
        /*else if(k == ">")
            key=KEY_GREATER;*/
        else if(k == "h" || k == "H")
            key=KEY_H;
        /*else if(k == "#")
            key=KEY_HASH;*/
        else if(k == "Help")
            key=KEY_HELP;
        else if(k == "Home")
            key=KEY_HOME;
        else if(k == "i" || k == "I")
            key=KEY_I;
        else if(k == "Insert")
            key=KEY_INSERT;
        else if(k == "j" || k == "J")
            key=KEY_J;
        else if(k == "k" || k == "K")
            key=KEY_K;
        else if(k == "KP_0")
            key=KEY_KP0;
        else if(k == "KP_1")
            key=KEY_KP1;
        else if(k == "KP_2")
            key=KEY_KP2;
        else if(k == "KP_3")
            key=KEY_KP3;
        else if(k == "KP_4")
            key=KEY_KP4;
        else if(k == "KP_5")
            key=KEY_KP5;
        else if(k == "KP_6")
            key=KEY_KP6;
        else if(k == "KP_7")
            key=KEY_KP7;
        else if(k == "KP_8")
            key=KEY_KP8;
        else if(k == "KP_9")
            key=KEY_KP9;
        else if(k == "KP_/")
            key=KEY_SLASH;
        else if(k == "KP_Enter")
            key=KEY_KPENTER;
        else if(k == "KP_=")
            key=KEY_KPEQUAL;
        else if(k == "KP_-")
            key=KEY_KPMINUS;
        else if(k == "KP_*")
            key=KEY_KPASTERISK;
        else if(k == "KP_.")
            key=KEY_KPDOT;
        else if(k == "KP_+")
            key=KEY_KPPLUS;
        else if(k == "l" || k == "L")
            key=KEY_L;
        else if(k == "LeftAlt")
            key=KEY_LEFTALT;
        else if(k == "LeftCtrl")
            key=KEY_LEFTCTRL;
        else if(k == "Left")
            key=KEY_LEFT;
        else if(k == "[")
            key=KEY_LEFTBRACE;
        /*else if(k == "(")
            key=KEY_LEFTPAREN;*/
        /*else if(k == "<")
            key=KEY_LESS;*/
        else if(k == "LeftMeta")
            key=KEY_LEFTMETA;
        else if(k == "LeftShift")
            key=KEY_LEFTSHIFT;
        else if(k == "m" || k == "M")
            key=KEY_M;
        else if(k == "Menu")
            key=KEY_MENU;
        else if(k == "-")
            key=KEY_MINUS;
        else if(k == "Mode")
            key=KEY_MODE;
        else if(k == "n" || k == "N")
            key=KEY_N;
        else if(k == "NumLock")
            key=KEY_NUMLOCK;
        else if(k == "o" || k == "O")
            key=KEY_O;
        else if(k == "p" || k == "P")
            key=KEY_P;
        else if(k == "PageDown")
            key=KEY_PAGEDOWN;
        else if(k == "PageUp")
            key=KEY_PAGEUP;
        else if(k == "Pause")
            key=KEY_PAUSE;
        else if(k == ".")
            key=KEY_DOT;
        /*else if(k == "+")
            key=KEY_PLUS;*/
        else if(k == "Power")
            key=KEY_POWER;
        else if(k == "Print")
            key=KEY_PRINT;
        else if(k == "q" || k == "Q")
            key=KEY_Q;
        else if(k == "?")
            key=KEY_QUESTION;
        else if(k == "'")
            key=KEY_APOSTROPHE;
        /*else if(k == "\"")
            key=KEY_QUOTEDBL;*/
        else if(k == "r" || k == "R")
            key=KEY_R;
        else if(k == "RightAlt")
            key=KEY_RIGHTALT;
        else if(k == "RightCtrl")
            key=KEY_RIGHTCTRL;
        else if(k == "Return")
            key=KEY_ENTER;
        else if(k == "Right")
            key=KEY_RIGHT;
        else if(k == "]")
            key=KEY_RIGHTBRACE;
        /*else if(k == ")")
            key=KEY_RIGHTPAREN;*/
        else if(k == "RightMeta")
            key=KEY_RIGHTMETA;
        else if(k == "RightShift")
            key=KEY_RIGHTSHIFT;
        else if(k == "s" || k == "S")
            key=KEY_S;
        /*else if(k == "SCROLL_LOCK")
            key=KEY_SCROLLOCK;*/
        else if(k == "SemiColon")
            key=KEY_SEMICOLON;
        else if(k == "/")
            key=KEY_SLASH;
        else if(k == "Space")
            key=KEY_SPACE;
        /*else if(k == "SYSTEM_REQUEST")
            key=KEY_SYSREQ;*/
        else if(k == "t" || k == "T")
            key=KEY_T;
        else if(k == "Tab")
            key=KEY_TAB;
        else if(k == "u" || k == "U")
            key=KEY_U;
        /*else if(k == "_")
            key=KEY_UNDERSCORE;*/
        else if(k == "Undo")
            key=KEY_UNDO;
        else if(k == "Up")
            key=KEY_UP;
        else if(k == "v" || k == "V")
            key=KEY_V;
        else if(k == "w" || k == "W")
            key=KEY_W;
        else if(k == "x" || k == "X")
            key=KEY_X;
        else if(k == "y" || k == "Y")
            key=KEY_Y;
        else if(k == "z" || k == "Z")
            key=KEY_Z;
        else
            key=KEY_UNKNOWN;
    #else
        if(k == "0")
            key=SDLK_0;
        else if(k == "1")
            key=SDLK_1;
        else if(k == "2")
            key=SDLK_2;
        else if(k == "3")
            key=SDLK_3;
        else if(k == "4")
            key=SDLK_4;
        else if(k == "5")
            key=SDLK_5;
        else if(k == "6")
            key=SDLK_6;
        else if(k == "7")
            key=SDLK_7;
        else if(k == "8")
            key=SDLK_8;
        else if(k == "9")
            key=SDLK_9;
        else if(k == "a" || k == "A")
            key=SDLK_a;
        else if(k == "&")
            key=SDLK_AMPERSAND;
        else if(k == "*")
            key=SDLK_ASTERISK;
        else if(k == "@")
            key=SDLK_AT;
        else if(k == "b" || k == "B")
            key=SDLK_b;
        else if(k == "`")
            key=SDLK_BACKQUOTE;
        else if(k == "\\")
            key=SDLK_BACKSLASH;
        else if(k == "BackSpace")
            key=SDLK_BACKSPACE;
        else if(k == "Break")
            key=SDLK_BREAK;
        else if(k == "c" || k == "C")
            key=SDLK_c;
        else if(k == "CapsLock")
            key=SDLK_CAPSLOCK;
        else if(k == "^")
            key=SDLK_CARET;
        else if(k == "Clear")
            key=SDLK_CLEAR;
        else if(k == "Colon")
            key=SDLK_COLON;
        else if(k == "Comma")
            key=SDLK_COMMA;
        else if(k == "Compose")
            key=SDLK_COMPOSE;
        else if(k == "d" || k == "D")
            key=SDLK_d;
        else if(k == "Delete")
            key=SDLK_DELETE;
        else if(k == "$")
            key=SDLK_DOLLAR;
        else if(k == "Down")
            key=SDLK_DOWN;
        else if(k == "e" || k == "E")
            key=SDLK_e;
        else if(k == "End")
            key=SDLK_END;
        else if(k == "=")
            key=SDLK_EQUALS;
        else if(k == "Escape")
            key=SDLK_ESCAPE;
        else if(k == "Euro")
            key=SDLK_EURO;
        else if(k == "!")
            key=SDLK_EXCLAIM;
        else if(k == "f" || k == "F")
            key=SDLK_f;
        else if(k == "F1")
            key=SDLK_F1;
        else if(k == "F10")
            key=SDLK_F10;
        else if(k == "F11")
            key=SDLK_F11;
        else if(k == "F12")
            key=SDLK_F12;
        else if(k == "F13")
            key=SDLK_F13;
        else if(k == "F14")
            key=SDLK_F14;
        else if(k == "F15")
            key=SDLK_F15;
        else if(k == "F2")
            key=SDLK_F2;
        else if(k == "F3")
            key=SDLK_F3;
        else if(k == "F4")
            key=SDLK_F4;
        else if(k == "F5")
            key=SDLK_F5;
        else if(k == "F6")
            key=SDLK_F6;
        else if(k == "F7")
            key=SDLK_F7;
        else if(k == "F8")
            key=SDLK_F8;
        else if(k == "F9")
            key=SDLK_F9;
        else if(k == "g" || k == "G")
            key=SDLK_g;
        else if(k == ">")
            key=SDLK_GREATER;
        else if(k == "h" || k == "H")
            key=SDLK_h;
        else if(k == "#")
            key=SDLK_HASH;
        else if(k == "Help")
            key=SDLK_HELP;
        else if(k == "Home")
            key=SDLK_HOME;
        else if(k == "i" || k == "I")
            key=SDLK_i;
        else if(k == "Insert")
            key=SDLK_INSERT;
        else if(k == "j" || k == "J")
            key=SDLK_j;
        else if(k == "k" || k == "K")
            key=SDLK_k;
        else if(k == "KP_0")
            key=SDLK_KP0;
        else if(k == "KP_1")
            key=SDLK_KP1;
        else if(k == "KP_2")
            key=SDLK_KP2;
        else if(k == "KP_3")
            key=SDLK_KP3;
        else if(k == "KP_4")
            key=SDLK_KP4;
        else if(k == "KP_5")
            key=SDLK_KP5;
        else if(k == "KP_6")
            key=SDLK_KP6;
        else if(k == "KP_7")
            key=SDLK_KP7;
        else if(k == "KP_8")
            key=SDLK_KP8;
        else if(k == "KP_9")
            key=SDLK_KP9;
        else if(k == "KP_/")
            key=SDLK_KP_DIVIDE;
        else if(k == "KP_Enter")
            key=SDLK_KP_ENTER;
        else if(k == "KP_=")
            key=SDLK_KP_EQUALS;
        else if(k == "KP_-")
            key=SDLK_KP_MINUS;
        else if(k == "KP_*")
            key=SDLK_KP_MULTIPLY;
        else if(k == "KP_.")
            key=SDLK_KP_PERIOD;
        else if(k == "KP_+")
            key=SDLK_KP_PLUS;
        else if(k == "l" || k == "L")
            key=SDLK_l;
        else if(k == "LeftAlt")
            key=SDLK_LALT;
        else if(k == "LeftCtrl")
            key=SDLK_LCTRL;
        else if(k == "Left")
            key=SDLK_LEFT;
        else if(k == "[")
            key=SDLK_LEFTBRACKET;
        else if(k == "(")
            key=SDLK_LEFTPAREN;
        else if(k == "<")
            key=SDLK_LESS;
        else if(k == "LeftMeta")
            key=SDLK_LMETA;
        else if(k == "LeftShift")
            key=SDLK_LSHIFT;
        else if(k == "m" || k == "M")
            key=SDLK_m;
        else if(k == "Menu")
            key=SDLK_MENU;
        else if(k == "-")
            key=SDLK_MINUS;
        else if(k == "Mode")
            key=SDLK_MODE;
        else if(k == "n" || k == "N")
            key=SDLK_n;
        else if(k == "NumLock")
            key=SDLK_NUMLOCK;
        else if(k == "o" || k == "O")
            key=SDLK_o;
        else if(k == "p" || k == "P")
            key=SDLK_p;
        else if(k == "PageDown")
            key=SDLK_PAGEDOWN;
        else if(k == "PageUp")
            key=SDLK_PAGEUP;
        else if(k == "Pause")
            key=SDLK_PAUSE;
        else if(k == ".")
            key=SDLK_PERIOD;
        else if(k == "+")
            key=SDLK_PLUS;
        else if(k == "Power")
            key=SDLK_POWER;
        else if(k == "Print")
            key=SDLK_PRINT;
        else if(k == "q" || k == "Q")
            key=SDLK_q;
        else if(k == "?")
            key=SDLK_QUESTION;
        else if(k == "'")
            key=SDLK_QUOTE;
        else if(k == "\"")
            key=SDLK_QUOTEDBL;
        else if(k == "r" || k == "R")
            key=SDLK_r;
        else if(k == "RightAlt")
            key=SDLK_RALT;
        else if(k == "RightCtrl")
            key=SDLK_RCTRL;
        else if(k == "Return")
            key=SDLK_RETURN;
        else if(k == "Right")
            key=SDLK_RIGHT;
        else if(k == "]")
            key=SDLK_RIGHTBRACKET;
        else if(k == ")")
            key=SDLK_RIGHTPAREN;
        else if(k == "RightMeta")
            key=SDLK_RMETA;
        else if(k == "RightShift")
            key=SDLK_RSHIFT;
        else if(k == "s" || k == "S")
            key=SDLK_s;
        else if(k == "ScrollLock")
            key=SDLK_SCROLLOCK;
        else if(k == "SemiColon")
            key=SDLK_SEMICOLON;
        else if(k == "/")
            key=SDLK_SLASH;
        else if(k == "Space")
            key=SDLK_SPACE;
        else if(k == "SystemRequest")
            key=SDLK_SYSREQ;
        else if(k == "t" || k == "T")
            key=SDLK_t;
        else if(k == "Tab")
            key=SDLK_TAB;
        else if(k == "u" || k == "U")
            key=SDLK_u;
        else if(k == "_")
            key=SDLK_UNDERSCORE;
        else if(k == "Undo")
            key=SDLK_UNDO;
        else if(k == "Up")
            key=SDLK_UP;
        else if(k == "v" || k == "V")
            key=SDLK_v;
        else if(k == "w" || k == "W")
            key=SDLK_w;
        else if(k == "x" || k == "X")
            key=SDLK_x;
        else if(k == "y" || k == "Y")
            key=SDLK_y;
        else if(k == "z" || k == "Z")
            key=SDLK_z;
        else
            key=SDLK_UNKNOWN;
    #endif
}
