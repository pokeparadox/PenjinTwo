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
#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "FileObject.h"
#include "Rectangle.h"

namespace Penjin
{
    class Image : public FileObject, public Rectangle
    {
        public:
            Image();
            virtual ~Image();

            /** \brief Function to load an image file.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load(const string& fileName);

            /** \brief Function to load an SDL_Surface.
             * \param s : The SDL_Surface* to load.
             * \return PENJIN_OK if SDL_Surface* was loaded successfully.
             */
            virtual Penjin::ERRORS load(SDL_Surface* s);

            /** \brief Function to save an image file.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was saved successfully.
             */
            virtual Penjin::ERRORS save(const string& fileName);

            /** \brief Render image to the screen */
            virtual void render();

        protected:
            SDL_Surface* surface;
/*
            #ifdef PENJIN_SDL
                void loadImage(SDL_Surface* s) // don't use this function for sharing surfaces (by default)
                {
                    images.push_back(make_pair(s,false));
                    sheetMode = false;
                }
                void disableTransparentColour(CRuint i)
                {
                    SDL_SetColorKey(images.at(i).first, 0, images.at(i).first->format->colorkey);
                    colourKey.a = 0;
                }
                void disableTransparentColour(){disableTransparentColour(images.size()-1);}
            #elif PENJIN_GL || defined (PENJIN_ES) || defined (PENJIN_ES2)
                void loadImage(const Texture& t)
                {
                    textures.push_back(t);
                    sheetMode = false;
                }
                void loadImage(SDL_Surface* s)
                {
                    Texture t;
                    t.loadSurface(s);
                    textures.push_back(t);
                    sheetMode = false;
                }
                void disableTransparentColour()
                {
                    cout << ErrorHandler().getErrorString(PenjinErrors::PENJIN_FUNCTION_IS_STUB) << endl;
                }
            #endif
            Penjin::ERRORS loadImage(CRstring imageName);                                 // Load an image into the vector
            Penjin::ERRORS loadImageNoKey(CRstring imageName);
            Penjin::ERRORS loadImageSheet(CRstring imageName,CRuint xTiles,CRuint yTiles);  // store the separated images on the vector
            Penjin::ERRORS loadImageSheetNoKey(CRstring imageName,CRuint xTiles,CRuint yTiles);
            Penjin::ERRORS loadImageSheet(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles); // use this for caching sprites, so Image objects can share data, surfaces added ny this function won't get deleted when the image gets deleted - keep track of them yourself!
            Penjin::ERRORS loadImageSheetNoKey(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles); // see above comment
            Penjin::ERRORS assignClipAreas(CRuint xTiles, CRuint yTiles,CRuint skipTiles,CRuint numTiles); // extracted identical code from loadImageSheet[NoKey]

            #ifdef PENJIN_3D
                void renderImage(uint i,CRfloat destX,CRfloat destY,CRfloat destZ);
                template <class T>
                void renderImage(const T& destX,const T& destY){renderImage(0,destX,destY,0);}
                template <class T>
                void renderImage(CRuint i, const T& destX,const T& destY){renderImage(i,destX,destY,0);}
                template <class T>
                void renderImage(const T& position){renderImage(0,position.x,position.y,position.z);}
                template <class T>
                void renderImage(const T& destX,const T& destY,const T& destZ){renderImage(0,destX,destY,destZ);}
                template <class T>
                void renderImage(CRuint i,const T& position){renderImage(i,position.x,position.y,position.z);}
            #else
                template <class T>
                void renderImage(const T& destX,const T& destY){renderImage(0,destX,destY);}
                template <class T>
                void renderImage(const T& pos){renderImage(0,pos.x,pos.y);}
                template <class T>
                void renderImage(CRuint i, const T& pos){renderImage(i,pos.x,pos.y);}
                void renderImage(uint i, CRfloat destX,CRfloat destY);
                #ifdef PENJIN_SDL
                    void renderImage(uint i,CRint destx, CRint desty){renderImage(i,screen, destx,desty);}
                    void renderImage(uint i,SDL_Surface *dstimg,CRint destx,CRint desty);    // Render specific image to the surface
                    template <class T>
                    void renderImage(SDL_Surface* dstimg,const T& destX,const T& destY){renderImage(0,dstimg,destX,destY);}            // Render the default image
                    template <class T>
                    void renderImage(SDL_Surface* dstimg,const T& pos){renderImage(dstimg, pos.x, pos.y);}
                    void renderImage(CRuint i, SDL_Surface* screen, CRFixed x, CRFixed y){renderImage(i, screen, fixedpoint::fix2int(x), fixedpoint::fix2int(y));}
                    template <class T>
                    void renderImage(CRuint i, SDL_Surface* screen,const T& pos){renderImage(i, screen, pos.x, pos.y);}
                #endif
            #endif

            Penjin::ERRORS setTransparentColour(CRuint i, const Vector2d<int>& pixel);
            Penjin::ERRORS setTransparentColour(const Vector2d<int>& pixel)
            {
                Penjin::ERRORS error = PENJIN_ERROR;
                uint i;
                #ifdef PENJIN_SDL
                for (i=0;i<images.size();i++)
                {
                    error = setTransparentColour(i,pixel);
                    if (error != PENJIN_OK) return error;
                }
                #elif PENJIN_GL
                for (i=0;i<textures.size();i++)
                {
                    error = setTransparentColour(i,pixel);
                    if (error != PENJIN_OK) return error;
                }
                #endif
                return error;
            }
            Penjin::ERRORS setTransparentColour(CRuint i, const Colour& c);
            Penjin::ERRORS setTransparentColour(const Colour& c)
            {
                Penjin::ERRORS error = PENJIN_ERROR;
                uint i;
                #ifdef PENJIN_SDL
                for (i=0;i<images.size();i++)
                {
                    error = setTransparentColour(i,c);
                    if (error != PENJIN_OK) return error;
                }
                #endif
                #if defined (PENJIN_GL) || defined (PENJIN_SOFT)
                for (i=0;i<textures.size();i++)
                {
                    error = setTransparentColour(i,c);
                    if (error != PENJIN_OK) return error;
                }
                #endif
                return error;
            }
            Colour getTransparentColour() const {return colourKey;}

            size_t size()const;                  // Returns the number of images in the vector
            void clear();                 // Clears all images out of the vector

            uchar getAlpha()const;  // Presumes all images are same dimensionality.
            uint getWidth()const;
            uint getHeight()const;
            void setAlpha(const uchar& alpha); //  alpha 0 to 255
            #ifndef PENJIN_3D
                void setScaleX(CRfloat scaleX){this->scale.x = scaleX;}
                void setScaleY(CRfloat scaleY){this->scale.y = scaleY;}
                float getScaleX()const{return scale.x;}
                float getScaleY()const{return scale.y;}
                void setScale(CRfloat scale){this->scale.x = this->scale.y = scale;}
                Vector2d<float> getScale() const {return scale;}
                void setRotation(CRfloat angle){this->angle = angle;}
                float getRotation()const{return angle;}
            #endif
            #ifdef PENJIN_SDL
                //	Set if to use a HW surface to blit
                void setUseHardware(CRbool useHW){if(useHW){convertToHW();}}
                void setUseHardWare(){convertToHW();}
                /// Pixel manipulation functions
                // check and lock screen
                void screenLock();
                // set a pixel
                void setPixel(CRint x,CRint y,const Colour& colour);
                void setPixel(CRint x,CRint y,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
                void setPixel(CRint x,CRint y,const uchar& r,const uchar& g,const uchar& b);
                // get a pixel
                Colour getPixel(Vector2d<int> pos)const{return GFX::getInstance()->getPixel(images.at(0).first,pos);}
                Colour getPixel(CRuint i,Vector2d<int> pos)const{return GFX::getInstance()->getPixel(images.at(i).first,pos);}
                Colour getPixelInFrame(Vector2d<int> pos, CRint frame) const
                {
                    if (sheetMode)
                        return GFX::getInstance()->getPixel(images.at(0).first, Vector2d<int> (pos.x + clipAreas[frame].x, pos.y + clipAreas[frame].y) );
                    return getPixel(pos);
                }
                //uint* getPixelArray(CRint x,CRint y)const;
                // check and unlock screen
                void screenUnlock();

                /// Override shared state of surfaces
                void setSurfaceSharing(CRbool value, CRint index=-1);
                bool getSurfaceSharing(CRint index=-1) const; // will return true if at least one surface is shared

            #elif defined (PENJIN_GL) || defined(PENJIN_ES) || defined(PENJIN_ES2) || defined (PENJIN_SOFT)
                #ifdef PENJIN_3D
                    void setRotation(const Vector3df& rotationVector) {rotation = rotationVector;}
                    Vector3df getRotationVector()const{return rotation;}
                    void setRotation(CRfloat a){rotation.z = a;}
                    float getRotation()const{return rotation.z;}
                    void setScale(const Vector3df& scaleVector) {scale = scaleVector;}
                    void setScale(CRfloat s){scale.x=scale.y=scale.z=s;}
                    Vector3df getScale()const{return scale;}
                    void setScaleX(CRfloat s){scale.x = s;}
                    void setScaleY(CRfloat s){scale.y=s;}
                    float getScaleX()const{return scale.x;}
                    float getScaleY()const{return scale.y;}
                #endif

                void setAlpha(float alpha) //  alpha in the range of 0 to 1;
                {
                    if(alpha>1.0f)
                        alpha = 1.0f;
                    else if(alpha<0.0f)
                        alpha = 0.0f;
                    setAlpha((uchar)alpha*255);
                }
                 // set a pixel
                void setPixel(CRfloat x,CRfloat y,const Colour& colour);
                void setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
                void setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b);
                void setPixel(CRfloat x,CRfloat y,CRfloat z,const Colour& colour);
                void setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
                void setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b);

                // Get a pixel from the image
                Colour getPixel(CRint x, CRint y);

                /// Override dimensions of texture
                void setWidth(CRint w){textures[0].setWidth(w);}
                void setHeight(CRint h){textures[0].setHeight(h);}
                void setDimensions(const Vector2d<int>& dims){textures[0].setDimensions(dims);}

                // get a pixel
                Colour getPixel(float x, float y);
                uint* getPixelArray(float x, float y);
                Colour getPixel(float x, float y, float z);
                uint* getPixelArray(float x, float y, float z);
            #endif

            //  Effects
            void toGreyScale(); //  convert this image to greyscale
            void toNegative();  //  convert to an inverse image
            void swapRG();      //  Swap the red and green channels
            void swapGB();      //  Swap the green and blue channels
            void swapRB();      //  Swap the red and blue channels

            // Cache rotation config
            #ifdef PENJIN_CACHE_ROTATIONS
                void setDegreesCached(CRuint d){maxCached = d;}
                void precacheRotations();
            #endif
        private:
            // Disabled to revent double freed pointers.
            Image(const Image& BlingRef);
            Image& operator=(const Image& BlingRef);

            Colour colourKey;

            #ifdef PENJIN_SDL
                void convertToHW();
                vector< pair<SDL_Surface*,bool> >images; //  Stores surfaces
                SDL_Surface* screen;        //  The pointer to the screen;

                SDL_Surface* rotoZoom(SDL_Surface& in,SDL_Rect& src, SDL_Rect& dst);    // Rotozoom the passed in surface with the classes current params
                #ifdef PENJIN_CACHE_ROTATIONS
                    void cacheRotation(uint angle, SDL_Surface* s);       //  add the rotation to the cache
                                //  Rotation Caching
                    struct ROT
                    {
                        SDL_Surface* surf;
                        uint useCount;
                    };
                    uint maxCached;             //  x>0:rotations are cached x is the number of angled that will be cached, 0: they are not.
                    uint currCached;            //  The current number of cahced rotations.
                    vector <ROT> rotCache;      //  Cached rotations
                    void setupCaching();        //  Auto config of rotation chaching
                #endif
            #elif defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2) ||defined (PENJIN_SOFT)
                vector<Texture> textures;   //  Stores Textures for image
            #endif

            bool sheetMode;             //  Performs tilesheet style loading/rendering

            uchar alpha;
            vector<SDL_Rect>clipAreas;  //  Stores clipping planes
            #ifdef PENJIN_3D
                Vector3df scale;            //  scale Vector for opengl
                Vector3df rotation;         //  Rotation Vector for opengl
            #else
                Vector2d<float> scale;
                float angle;                //  angle for rotations
            #endif
*/
    };
}
#endif // IMAGE_H_INCLUDED
