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
#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "Image.h"
#include "PenjinTypes.h"
namespace Penjin
{
    class Sprite : public Image
    {
        public:
            Sprite();
            virtual ~Sprite();

            Penjin::ERRORS setTransparentColour(const Colour& c);
            Penjin::ERRORS setTransparentColour(const Vector2d<int>& v);
            void disableTransparentColour();

        protected:
            Colour transparent;

            /*
            #ifndef PENJIN_3D
                Sprite(CRint x,CRint y);
                Sprite(const Vector2d<int>& position);
            #else
                Sprite(CRfloat x,CRfloat y);
                Sprite(const Vector2df& position);
                Sprite(CRfloat x,CRfloat y,CRfloat z);
                Sprite(const Vector3df& position);
            #endif
            Penjin::ERRORS loadSprite(CRstring fileName);     // Loads an image for this sprite

            Penjin::ERRORS setTransparentColour(const Colour& c){return image.setTransparentColour(c);}
            Penjin::ERRORS setTransparentColour(const COLOURS& c){return setTransparentColour(Colour(c));}
            Penjin::ERRORS setTransparentColour(const Vector2d<int>& v){return image.setTransparentColour(v);}
            void disableTransparentColour(){image.disableTransparentColour();}
            void setAlpha(const uchar& alpha){image.setAlpha(alpha);}
            uchar getAlpha()const{return image.getAlpha();}
            #ifdef PENJIN_SDL
                void render(SDL_Surface* screen);         // Draws the image onto the screen
                void render(){render(screen);}
                bool hasCollided(Sprite &spr);			//	Has this sprite collided with the passed in sprite?
                void loadSprite(SDL_Surface* s){image.loadImage(s);}
            #else
                void render();
            #endif
            uint getWidth()const{return image.getWidth();}
            uint getHeight()const{return image.getHeight();}
            Vector2d<int> getDimensions()const{return Vector2d<int>(image.getWidth(), image.getHeight());}

            #ifdef PENJIN_CACHE_ROTATIONS
                void setDegreesCached(CRuint d){image.setDegreesCached(d);}
                void precacheRotations(){image.precacheRotations();}
            #endif
            void setRotation(CRfloat angle){image.setRotation(angle);}
            void setScaleX(CRfloat scaleX){image.setScaleX(scaleX);}
            void setScaleY(CRfloat scaleY){image.setScaleY(scaleY);}
            void setScale(CRfloat scale){image.setScale(scale);}
            #ifdef PENJIN_SDL
                void setUseHardware(CRbool useHW){image.setUseHardware(useHW);}
                void setX(CRint x){position.x = x;}
                void setX(CRFixed x){position.x = fixedpoint::fix2int(x);}
                void setY(CRint y){position.y = y;}
                void setY(CRFixed y){position.y = fixedpoint::fix2int(y);}
                Vector2d<float> getPosition(){return position;}
                void setPosition(CRFixed x,CRFixed y){setPosition(Vector2d<Fixed>(x,y));}
                void setPosition(CRint x,CRint y){setPosition(Vector2d<int>(x,y));}
                void setPosition(const Vector2d<Fixed>& position){this->position.x = position.x.intValue >>16;this->position.y = position.y.intValue >>16;}
                template <class T>
                void setPosition(const T& position){this->position.x = position.x;this->position.y = position.y;}
                float getX()const{return position.x;}
                float getY()const{return position.y;}
                Colour getPixel(CRint x,CRint y) const {return image.getPixel(Vector2d<int>(x,y));}
            #else
                void setScale(const Vector3df& scale);
                void setX(CRfloat x){position.x = x;}
                void setY(CRfloat y){position.y = y;}
                #ifdef PENJIN_3D
                    void setZ(CRfloat z){position.z = z;}
                    float getZ()const{return position.z;}
                    Vector3df getPosition()const{return position;}
                #else
                    Vector2df getPosition()const{return position;}
                #endif
                void setRotation(const Vector3df& rotationVector);
                template <class T>
                void setPosition(const T& position){this->position = position;}
                void setPosition(const Vector2df& position){setPosition(Vector3df(position.x, position.y, 0.0f));}
                void setPosition(CRfloat x,CRfloat y,CRfloat z){setPosition(Vector3df(x,y,z));}
                void setPosition(CRfloat x,CRfloat y){setPosition(x,y, 0.0f);}
                float getX()const{return position.x;}
                float getY()const{return position.y;}
            #endif
            void clear(){image.clear();}
        private:
            Image image;
            #ifdef PENJIN_3D
                Vector3d<float> position;
            #else
                Vector2d<float> position;
            #endif
            #ifdef PENJIN_SDL
                SDL_Surface* screen;
            #endif
            */
    };
}
#endif // SPRITE_H_INCLUDED
