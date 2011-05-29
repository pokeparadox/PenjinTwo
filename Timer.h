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
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
    #include <SDL/SDL.h>
#else
    #include <ctime>
#endif


#include "PenjinTypes.h"

namespace Penjin
{
    enum TimerScalers
    {
        //	Various modes that the timer can be put in.
        MILLI_SECONDS=1000,
        CENTI_SECONDS=100,
        SIXTY_FRAMES=60,
        FIFTY_FRAMES=50,
        THIRTY_FRAMES=30,
        FIFTEEN_FRAMES=15,
        DECI_SECONDS=10,
        SECONDS=1,
        MINUTES,
        HOURS,
        CUSTOM
    };

    #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
        const static int MY_CLOCKS = 1000 ;
    #else
        const static int MY_CLOCKS = CLOCKS_PER_SEC;
    #endif
    class Timer
    {
        public:
            Timer()
            {
                startTicks = 0;
                pausedTicks = 0;
                is_Paused = false;
                is_Started = false;
                timeMode = MILLI_SECONDS;   // default value
                #ifdef PENJIN_FIXED
                    scaler = 1;
                #else
                    scaler = 1.0f;
                #endif
                offset = 0;
            }
            Timer(const TimerScalers& scale)
            {
                startTicks = 0;
                pausedTicks = 0;
                is_Paused = false;
                is_Started = false;
                timeMode = scale;
                scaler = calcScaler(scale);
                offset = 0;
            }

            void setMode(const TimerScalers& mode)       // Set the timer scaler
            {
                timeMode = mode;
                scaler = calcScaler(mode);
            }
            TimerScalers getMode()const{return timeMode;}

            void setOffset(CRint o) {offset = o * scaler;};
            void setOffset(CRint o, const TimerScalers& mode) {offset = o * calcScaler(mode);};
            int getOffset() const {return offset / scaler;};
            int getOffset(const TimerScalers& mode) {return offset / calcScaler(mode);};

            int getScaledTicks(const TimerScalers& mode)
            {
                #ifdef PENJIN_FIXED
                    return Fixed(getTicks() / calcScaler(mode)).intValue>>16;
                #else
                    return (int)((float)getTicks() / calcScaler(mode));
                #endif
            }
            int getScaledTicks() const              // Return the scaled elapsed time
            {
                #ifdef PENJIN_FIXED
                    return Fixed(getTicks()/scaler).intValue>>16;
                #else
                    return (int)((float)getTicks() / scaler);
                #endif
            }
            int getTicks() const
            {
                //If the timer is running
                if(is_Started)
                {
                    //If the timer is paused
                    if(is_Paused)
                    {
                        //Return the number of ticks when the the timer was paused
                        return pausedTicks;
                    }
                    else
                    {
                        //Return the current time minus the start time
                        #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
                            return SDL_GetTicks() - startTicks + offset;
                        #else
                            return clock() - startTicks + offset;
                        #endif
                    }
                }
                //If the timer isn't running
                return 0;
            }

            void delay(const int& sleepTime)
            {
                #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
                        SDL_Delay(sleepTime);  // Release CPU briefly
                #else
                        sleep(sleepTime);  // Release CPU briefly
                #endif
            }

            void start()
            {
                //Start the timer
                is_Started = true;
                //Unpause the timer
                is_Paused = false;
                //Get the current clock time
                #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
                    startTicks = SDL_GetTicks();
                #else
                    startTicks = clock();
                #endif
            }
            void stop()
            {
                is_Started = false;
                is_Paused = false;
            }
            void pause()
            {
                //If the timer is running and isn't already paused
                if(  is_Started && !is_Paused )
                {
                    //Pause the timer
                    is_Paused = true;
                    //Calculate the paused ticks
                    #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
                        pausedTicks = SDL_GetTicks() - startTicks;
                    #else
                        pausedTicks = clock() -startTicks;
                    #endif
                }
            }
            void unpause()
            {
                //If the timer is paused
                if( is_Paused == true )
                {
                    //Unpause the timer
                    is_Paused = false;
                    //Reset the starting ticks
                    #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
                        startTicks = SDL_GetTicks() - pausedTicks;
                    #else
                        startTicks = clock() - pausedTicks;
                    #endif
                    //Reset the paused ticks
                    pausedTicks = 0;
                }
            }

            bool isPaused()const{return is_Paused;};
            bool isStarted()const{return is_Started;};

            /// Set a custom timer resolution.
            #ifdef PENJIN_FIXED
                void setScaler(CRFixed scale){setMode(CUSTOM);scaler = scale;}
                Fixed getScaler() const {return scaler;}
            #else
                void setScaler(CRfloat scale){setMode(CUSTOM);scaler = scale;}
                float getScaler() const {return scaler;}
            #endif
            // Set timerScaler in terms of frames per second
            void setFramesPerSecond(CRuint fps){setScaler(1000/(float)fps);}
        protected:
            #ifdef PENJIN_FIXED
            Fixed calcScaler(const TimerScalers& mode);   // Calculate the resolution of timer updates
            #else
            float calcScaler(const TimerScalers& mode);
            #endif

            TimerScalers timeMode;
            int startTicks;
            int pausedTicks;
            int offset;
            bool is_Paused;
            bool is_Started;
            #ifdef PENJIN_FIXED
                Fixed scaler;
            #else
                float scaler;
            #endif
    };
}
#endif // TIMER_H_INCLUDED
