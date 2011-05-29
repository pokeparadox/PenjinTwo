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
#ifndef ANIMATION_H
#define ANIMATION_H


#include "ImageSheet.h"
#include "Timer.h"
#include "UpdateObject.h"


namespace Penjin
{

    /// Playback modes that the Animation can be played in.
    enum PlayMode
    {
        pmNormal=0,     // Run through frames sequentially
        pmReverse,      // Run through frames in reverse order.
        pmPulse         // Run forward and then back through the frames.
    };

    class Animation : public ImageSheet, public Timer, public UpdateObject
    {
        public:
            Animation();
            virtual ~Animation();

            /** \brief Set the Animation looping playback status.
             * \param loop : if true looping playback, otherwise play once.
             */
            void setLooping(CRbool loop);
            /** \brief Set the Animation looping playback status, specifying a number of loop cycles.
             * \param loops : -1 means loop forever, any other value specify the number of loops.
            */
            void setLooping(CRint loops);
            /** \brief Set the PlayMode of the Animation.
             * \param mode : see PlayMode enum.
             */
            void setPlayMode(const PlayMode& mode);
            PlayMode getPlayMode();
            void setReversePlay(CRbool play);
            void setPulsePlay(CRbool play);
            bool hasFinished();

            void rewind();

            virtual void update();

        protected:
            int numLoops;       // -1 - loop forever, 0 - don't loop, else - number of loops
            int firstLoops;
            PlayMode playMode;
            bool hasFinishedVal;
            bool reachedEnd;        // used for pulse playing mode
    };
}
#endif	//	ANIMATION_H
