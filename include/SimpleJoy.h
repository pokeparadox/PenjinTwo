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
#ifndef SIMPLEJOY_H
#define SIMPLEJOY_H

#include "Object.h"
#include "Singleton.h"
#include "PenjinTypes.h"
#include "Vector2d.h"
#include "KeyMapper.h"
#include <iostream>

#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
#include <fstream>
#endif
using std::cout;
/*
TODO: Add Wii Controls/GBA/NDS etc
*/
namespace Penjin
{
    class SimpleJoy : public Object
    {
        public:
            enum sjSTATUS
            {
                sjRELEASED = 0,
                sjPRESSED = 1,
                sjHELD = 2
            };
            //  keymapping and a key status for the map.
            struct tKey
            {
                KeyMapKey key;
                sjSTATUS status;
            };
            //  Contains a player's control mapping and pressed buttons.
            struct Player
            {
                //  Control map
                KeyMapper mapper;
                bool mapLoaded;
                //  stored keyboard presses
                vector <tKey> storeKeys;
                //  standard game buttons
                sjSTATUS Start, Select, Up, Down, Left, Right, A, B, X, Y, L, R;
                //  X box check and other quit message checking
                sjSTATUS Quit;

                //  Josystick config and values
                Vector2d<int> deadZone;
                float scaler;
                Vector2d<int> leftStick;
                Vector2d<int> rightStick;

                //  mouse
                Vector2d<int> mouse;
                Vector2d<int> oldMouse;
                sjSTATUS leftClick, rightClick;

                //  GP2X Specific
            #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
                sjSTATUS Click, VolumeUp, VolumeDown,UpLeft, UpRight, DownLeft, DownRight;
            #endif
            };
            SimpleJoy();
            ~SimpleJoy();

            /// Multiplayer options
            /*starting from 1... 1 == 1 player 2 == 2 players*/
            void setNumPlayers(CRuint p);           //  Set how many player controller to track
            /*Player 1 is starting at index 0.*/
            void setPlayer(CRuint p){player = p;}   // set the ownership of inputs to this player
            uint getPlayer()const{return player;}

            Penjin::ERRORS load(CRstring filename)
            {
                Penjin::ERRORS t = players[player].mapper.load(filename);
                if(t == PENJIN_OK)
                    players[player].mapLoaded = true;
                return t;
            }

            Penjin::ERRORS save(CRstring filename)
            {
                return players[player].mapper.save(filename);
            }

            void update();					//	Get current status of keyboard

            // Check button states
            bool isHeld(const sjSTATUS& bstat)const{return (bstat == sjHELD);}
            bool isPressed(const sjSTATUS& bstat)const{return (bstat == sjPRESSED);}
            bool isReleased(const sjSTATUS& bstat)const{return (bstat == sjRELEASED);}

            sjSTATUS isStart()const{return players[player].Start;}
            sjSTATUS isSelect()const{return players[player].Select;}
            sjSTATUS isUp()const{return players[player].Up;}
            sjSTATUS isDown()const{return players[player].Down;}
            sjSTATUS isLeft()const{return players[player].Left;}
            sjSTATUS isRight()const{return players[player].Right;}
            sjSTATUS isA()const{return players[player].A;}
            sjSTATUS isB()const{return players[player].B;}
            sjSTATUS isX()const{return players[player].X;}
            sjSTATUS isY()const{return players[player].Y;}
            sjSTATUS isL()const{return players[player].L;}
            sjSTATUS isR()const{return players[player].R;}
            /// The fabled ANY button.
            sjSTATUS isAny()const
            {
                if((players[player].A || players[player].B || players[player].X || players[player].Y || players[player].L
                || players[player].R || players[player].Start || players[player].Select) == sjPRESSED)
                    return sjPRESSED;
                else if((players[player].A || players[player].B || players[player].X || players[player].Y || players[player].L
                || players[player].R || players[player].Start || players[player].Select) == sjHELD)
                    return sjHELD;
                return sjRELEASED;
            }

            sjSTATUS isQuit()const{return players[player].Quit;}

        #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
            /// GP2X Buttons
            sjSTATUS isClick()const{return players[player].Click;}
            sjSTATUS isVolumeUp()const{return players[player].VolumeUp;}
            sjSTATUS isVolumeDown()const{return players[player].VolumeDown;}
            sjSTATUS isUpLeft()const{return players[player].UpLeft;}
            sjSTATUS isUpRight()const{return players[player].UpRight;}
            sjSTATUS isDownLeft()const{return players[player].DownLeft;}
            sjSTATUS isDownRight()const{return players[player].DownRight;}
        #else
            sjSTATUS isUpLeft()const{return sjRELEASED;}
            sjSTATUS isUpRight()const{return sjRELEASED;}
            sjSTATUS isDownLeft()const{return sjRELEASED;}
            sjSTATUS isDownRight()const{return sjRELEASED;}
        #endif

            /// Keyboard passthrough
            sjSTATUS isKey(CRstring k)
            {
                KeyMapKey t(k);
                for(int i = players[player].storeKeys.size()-1; i>=0;--i)
                {
                    if(t.getKey() == players[player].storeKeys.at(i).key.getKey())
                        return players[player].storeKeys.at(i).status;
                }
            }
            string isKeyLetter();

            /// Joystick
            void setDeadZone(const Vector2d<int> & zone){players[player].deadZone = zone;}
            void setDeadZoneX(CRint x){players[player].deadZone.x = x;}
            void setDeadZoneY(CRint y){players[player].deadZone.y = y;}
            void setScaler(CRfloat s){players[player].scaler = s;}
            Vector2d<int> getLeftStick()const{return players[player].leftStick;}
            Vector2d<int> getRightStick()const{return players[player].rightStick;}
            int getLeftStickX()const{return players[player].leftStick.x;}
            int getLeftStickY()const{return players[player].leftStick.y;}
            int getRightStickX()const{return players[player].rightStick.x;}
            int getRightStickY()const{return players[player].rightStick.y;}

            /// Joystick logical
            sjSTATUS isLeftStick()const
            {
                if((isLeftStickDown() || isLeftStickLeft() || isLeftStickRight() || isLeftStickUp())==sjHELD)
                    return sjHELD;
                else if((isLeftStickDown() || isLeftStickLeft() || isLeftStickRight() || isLeftStickUp())==sjPRESSED)
                    return sjPRESSED;
                return sjRELEASED;
            }
            sjSTATUS isLeftStickUp()const
            {
                if(getLeftStickY() < -players[player].deadZone.y)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isLeftStickDown()const
            {
                if(getLeftStickY() > players[player].deadZone.y)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isLeftStickLeft()const
            {
                if(getLeftStickX() < -players[player].deadZone.x)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isLeftStickRight()const
            {
                if(getLeftStickX() > players[player].deadZone.x)
                    return sjHELD;
                return sjRELEASED;
            }

            sjSTATUS isRightStick()const
            {
                if((isRightStickDown() || isRightStickLeft() || isRightStickRight() || isRightStickUp())==sjHELD)
                    return sjHELD;
                else if((isRightStickDown() || isRightStickLeft() || isRightStickRight() || isRightStickUp())==sjPRESSED)
                    return sjPRESSED;
                return sjRELEASED;
            }
            sjSTATUS isRightStickUp()const
            {
                if(getRightStickY() < -players[player].deadZone.y)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isRightStickDown()const
            {
                if(getRightStickY() > players[player].deadZone.y)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isRightStickLeft()const
            {
                if(getRightStickX() < -players[player].deadZone.x)
                    return sjHELD;
                return sjRELEASED;
            }
            sjSTATUS isRightStickRight()const
            {
                if(getRightStickX() > players[player].deadZone.x)
                    return sjHELD;
                return sjRELEASED;
            }

            /// Mouse
            Vector2d<int> getMouse()const{return players[player].mouse;}
            int getMouseX()const{return players[player].mouse.x;}
            int getMouseY()const{return players[player].mouse.y;}
            Vector2d<int> getMouseDelta()const{return players[player].mouse-players[player].oldMouse;}
            int getMouseDeltaX()const{return players[player].mouse.x-players[player].oldMouse.x;}
            int getMouseDeltaY()const{return players[player].mouse.y-players[player].oldMouse.y;}

            sjSTATUS isLeftClick()const{return players[player].leftClick;}
            sjSTATUS isRightClick()const{return players[player].rightClick;}
            /// TouchScreen - Just a wrapper to mouse
            Vector2d<int> getTouch()const{return players[player].mouse;}
            int getTouchX()const{return players[player].mouse.x;}
            int getTouchY()const{return players[player].mouse.y;}
            sjSTATUS isTouch()const{return players[player].leftClick;}

            void clearEventQueue();
            void resetKeys();

            void resetDpad();
            void resetUp();

            void resetA();
            void resetB();
            void resetX();
            void resetY();
            void resetL();
            void resetR();

            /// Status
            void joystickStatus();
        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            int getTouchPressure(){return ts_pressure;}
        #endif

        private:
            void mappedDown(const SIMPLEJOY_MAP& map);
            void mappedUp(const SIMPLEJOY_MAP& map);
            void mappedMouseAxes(const SIMPLEJOY_MAP& map,CRuchar axis);
            void mappedJoyAxes(const SIMPLEJOY_MAP& map);

            //  This object stores a keymapping and button status for each Player
            Player* players;
            size_t numPlayers;
            uint player;

        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            #define DEV_NUBL 0
            #define DEV_NUBR 1
            #define DEV_KEYS 2
            #define DEV_GPIO 3
            #define DEV_TOUCH 4
            #define PND_NUBL "nub0"
            #define PND_NUBR "nub1"
            #define PND_KEYS "keypad"
            #define PND_GPIO "gpio-keys"
            #define PND_TOUCH "touchscreen"
            #define NUB_CUTOFF 5
            #define NUB_SCALE  10

            int PND_OpenEventDeviceByName( const char device_name[] );
            void PND_ReadEvents( int fd, int device );
            void PND_CheckEvent( struct input_event *event, int device );

            int fd_nubL, fd_nubR, fd_keys, fd_gpio, fd_touch;
            int rd, version, i;
            int ts_pressure;
            int pointercal[7];  // stores ts cali data
            Point2di rawTS;
            bool haveTSx;
            bool haveTSy;
            struct input_event ev[64];
            uint currentEvent;          //  stores the currently checked event for mapping purposes.
            char event_name[30];
            char dev_name[256]; //= "Unknown";
            unsigned short id[4];
            //Vector2di nubL, nubR;
            // KEV nub code
            //void MappedNubAxes(const SIMPLEJOY_MAP& map, CRint axis);
        #else
            SDL_Joystick **Joy;		//	SDL joysticks
            SDL_Event Event;
        #endif
    };
    typedef Singleton <SimpleJoy> Joy;
}
#endif // SIMPLEJOY_H
