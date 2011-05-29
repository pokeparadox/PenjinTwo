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
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Animation.h"

namespace Penjin
{
    class AnimatedSprite : public Animation
    {
        public:
            AnimatedSprite();
            virtual ~AnimatedSprite();

            /** \brief Function to load an image sheet from file.
             * \param fileName : The file to load.
             * \param xTiles : The number of horizontal tiles.
             * \param yTiles : The number of vertical tiles.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load(const string& fileName, CRuint xTiles, CRuint yTiles);

            /** \brief Function to load an image sheet from SDL_Surface*.
             * \param surface : SDL_Surface* to load.
             * \param xTiles : The number of horizontal tiles.
             * \param yTiles : The number of vertical tiles.
             * \return PENJIN_OK if surface was loaded successfully.
             */
            virtual Penjin::ERRORS load(SDL_Surface* surface, CRuint xTiles, CRuint yTiles);

            Penjin::ERRORS setTransparentColour(const Colour& c);
            Penjin::ERRORS setTransparentColour(const Vector2d<int>& v);
            void disableTransparentColour();

/*            #ifndef PENJIN_SDL
                #ifdef PENJIN_3D
                    AnimatedSprite(CRfloat x,CRfloat y,CRfloat z);
                #endif
                AnimatedSprite(CRfloat x,CRfloat y);
            #else
                AnimatedSprite(CRint x,CRint y);
            #endif

            Penjin::ERRORS loadFrame(SDL_Surface* s);
            virtual Penjin::ERRORS loadFrame(CRstring fileName);     // adds a frame of animation for this sprite
            virtual Penjin::ERRORS loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles); // loads a spritesheet for animations
            Penjin::ERRORS loadFrames(SDL_Surface* s,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles,CRbool transparent=true); // loads a spritesheet from a shared image
            //void setAlpha(const uchar& alpha){image.setAlpha(alpha);}
            Penjin::ERRORS setTransparentColour(const Colour& c){return image.setTransparentColour(c);}
            Penjin::ERRORS setTransparentColour(const Vector2d<int>& v){return image.setTransparentColour(v);};
            Penjin::ERRORS setTransparentColour(const COLOURS& c){return setTransparentColour(Colour(c));}
            #ifdef PENJIN_SDL
                void disableTransparentColour(){image.disableTransparentColour();}
            #endif
            Colour getTransparentColour() const {return image.getTransparentColour();}
            uchar getAlpha()const{return image.getAlpha();}

            void setPosition(const Vector2d<int>& pos){position.x = pos.x;position.y=pos.y;}
            void setPosition(const Vector2d<float>& pos){position.x=pos.x;position.y=pos.y;}
            #ifndef PENJIN_FIXED
                void setPosition(const Vector2d<Fixed>& pos){setPosition(pos.x,pos.y);}
            #endif
            void setPosition(CRFixed x, CRFixed y){position.x = fixedpoint::fix2float(x);position.y = fixedpoint::fix2float(y);}
            void setPosition(CRint x,CRint y){setPosition(Vector2d<int>(x,y));}
            float getX()const{return position.x;}
            float getY()const{return position.y;}
            #ifndef PENJIN_3D
                Vector2d<float> getPosition()const{return position;}
                void setX(CRint x){position.x = x;}
                void setY(CRint y){position.y = y;}
            #endif
            #ifdef PENJIN_SDL
                void render(SDL_Surface* screen);         // Draws the image onto the scre
                void render(){render(screen);}
            #else
                void render();
                void setX(CRfloat x){position.x = x;}
                void setY(CRfloat y){position.y = y;}
                #ifdef PENJIN_3D
                    Vector3df getPosition()const{return position;}
                    void setPosition(const Vector3df& pos){position = pos;}
                    void setZ(CRfloat z){position.z = z;}
                    float getZ()const{return position.z;}
                #endif
            #endif
            void update();
           // bool hasCollided(AnimatedSprite &spr);		//	Has this sprite collided with the passed in sprite?

            void setFrameRate(const TimerScalers& fps){animationTimer.setMode(fps);}
            void setTimerScaler(CRfloat cusScaler){animationTimer.setScaler(cusScaler);}//Set a custom timer update scaler.
            void setLooping(CRint numLoops){this->numLoops = firstLoops = (numLoops-1);}
            void setLooping(CRbool shouldLoop)
            {
                if(shouldLoop)
                    numLoops = firstLoops = -1;
                else
                    numLoops = firstLoops = 0;
            }
            bool getLooping() const {return (firstLoops != 0);}
            int getLoops() const {return firstLoops;}
            void clearFrames(){image.clear();}
            #ifndef PENJIN_3D
                void setScale(CRfloat scale){image.setScale(scale);}
                void setScaleX(CRfloat scaleX){image.setScaleX(scaleX);}
                void setScaleY(CRfloat scaleY){image.setScaleY(scaleY);}
                void setRotation(CRfloat angle){image.setRotation(angle);}
            #endif
            #ifdef PENJIN_SDL
                //void setUseHardware(CRbool useHW){image.setUseHardware(useHW);}
            #else
                #ifdef PENJIN_3D
                    void setScale(const Vector3df& scaleVec){image.setScale(scaleVec);}
                    void setRotation(const Vector3df& rotationVec){image.setRotation(rotationVec);}
                #endif
            #endif
            #ifdef PENJIN_SDL
                Colour getPixel(const Vector2d<int>& pos) const
                {
                    return getPixel(pos.x,pos.y);
                }
                Colour getPixel(CRint x, CRint y) const
                {
                    return image.getPixelInFrame(Vector2d<int> (x,y),currentFrame);
                }
            #endif


            uint getCurrentFrame()const{return currentFrame;}
            bool hasFinished()const {return hasFinishedVal;};
            void setReversePlay(CRbool reverse)
            {
                if (reverse)
                    mode = pmReverse;
                else
                    mode = pmNormal;
            };
            void setPulsePlay(CRbool pulse)
            {
                if (pulse)
                    mode = pmPulse;
                else
                    mode = pmNormal;
            };
            void setPlayMode(PlayMode newMode){mode = newMode;};
            void setPlayMode(int newMode){mode = (PlayMode)newMode;};
            PlayMode getPlayMode() const {return mode;};
            void rewind() // rewind the sprite, resets hasFinished, too
            {
                if (mode == pmReverse)
                    currentFrame = image.size()-1;
                else
                    currentFrame = 0;
                numLoops = firstLoops;
                hasFinishedVal = false;
                reachedEnd = false;
                animationTimer.start();
            }
            void setCurrentFrame(CRint framenumber){currentFrame = framenumber;}
            size_t frameCount() const {return image.size();} // return the number of frames
        protected:
            Colour transparent;
            //Image image;
            //Timer animationTimer;
            int numLoops; // -1 - loop forever, 0 - don't loop, else - number of loops
            int firstLoops;
            PlayMode mode;
            bool hasFinishedVal;
            bool reachedEnd; // used for pulse playing mode
            int currentFrame;
            #ifdef PENJIN_3D
                Vector3df position;
            #else
                Vector2d<float> position;
            #endif
            #ifdef PENJIN_SDL
                SDL_Surface* screen;
            #endif
            */
        protected:
            Colour transparent;
    };
}
#endif	//	ANIMATEDSPRITE_H
