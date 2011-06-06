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

#include <SDL/SDL_image.h>

#include "Image.h"
#include "GFX.h"
using Penjin::Image;


Image::Image() : surface(NULL)
{
    setDrawWidth(1);
    setColour(MAGENTA);
   /* alpha = 255;
    #ifdef PENJIN_3D
        rotation.x = rotation.y = rotation.z = 0.0f;
        scale.x = scale.y = scale.z = 1.0f;
    #else
        scale.x = 1;
        scale.y = 1;
        angle = 0;
    #endif

    #ifdef PENJIN_SDL
        //  Get the screen pointer
        screen = GFX::getInstance()->getSDLVideoSurface();
    #endif
    sheetMode = false;      //  Stores if we use a spritesheet or if we use separate surfaces.
    colourKey.a = 0;    //  Disable colourkey until ready.
    */
}

Image::~Image()
{
	if(surface)
        SDL_FreeSurface(surface);
}


void Image::render()
{
    // If we have a surface, we display it
    if(surface)
    {
        SDL_SetAlpha(surface, SDL_SRCALPHA, a);
        // Set up blitting area
        SDL_Rect src, dst;
        src.x = surface->clip_rect.x;
        src.y = surface->clip_rect.y;
        src.w = surface->w;
        src.h = surface->h;

        dst.x = position.x;
        dst.y = position.y;
        SDL_BlitSurface(surface, &src, GFX::getInstance()->getSDLVideoSurface(), &dst);
        #ifdef _DEBUG
            Rectangle::render();
        #endif
    }
    // Otherwise we display a Rectangle where the image is supposed to be.
    else
        Rectangle::render();
}

Penjin::ERRORS Image::load(SDL_Surface* s)
{
    // If surface is invalid
    if(s == NULL)
        return PENJIN_ERROR;

    // Free already existing surface
    if(surface && (surface!=s))
        SDL_FreeSurface(surface);
    surface = s;

    // Setup correct display format depending on if image contains alpha or not
    SDL_Surface* oldSurface = surface;
    if(surface->flags & SDL_SRCALPHA)
        surface = SDL_DisplayFormatAlpha(surface);
    else
        surface = SDL_DisplayFormat(surface);

    SDL_FreeSurface(oldSurface);

    // update dimensions
    dimensions.x = surface->w;
    dimensions.y = surface->h;

    return PENJIN_OK;
}

Penjin::ERRORS Image::load(const string& file)
{
    fileName = file;
    SDL_Surface* t = IMG_Load(file.c_str());
    Penjin::ERRORS e = Image::load(t);
    return e;
}

Penjin::ERRORS Image::save(const string& file)
{
    return Penjin::PENJIN_FUNCTION_IS_STUB;
}

/*
Penjin::ERRORS Image::setTransparentColour(CRuint i, const Colour& c)
{
    #ifdef PENJIN_SDL
        if((size_t)i >= images.size())
            return PENJIN_INVALID_INDEX;
        if(images.at(i).first->flags & SDL_SRCALPHA)
        {
            disableTransparentColour(i);
            return PENJIN_OK;
        }
        if(SDL_SetColorKey(images[i].first, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(images[i].first->format,c.r,c.g,c.b)) == -1)
                return PENJIN_SDL_INVALID_COLORKEY;
        colourKey = c;
        colourKey.a = 255;
        return PENJIN_OK;
    #else
        return PENJIN_FUNCTION_IS_STUB;
    #endif
}

Penjin::ERRORS Image::setTransparentColour(CRuint i, const Vector2d<int>& v)
{
    #ifdef PENJIN_SDL
        if((size_t)i >= images.size())
            return PENJIN_INVALID_INDEX;

        Colour c = GFX::getInstance()->getPixel(images[i].first,Vector2d<int>(v.x,v.y));
        return setTransparentColour(i,c);
    #else
        return PENJIN_FUNCTION_IS_STUB;
    #endif
}

Penjin::ERRORS Image::loadImage(CRstring name)
{
    Penjin::ERRORS error;
    #ifdef PENJIN_SDL
        //  load image
        error = loadImageNoKey(name);
        if(error != PENJIN_OK)
            return error;

        //  Apply colour key
        uint currentI = (uint)images.size()-1;
        colourKey.a = 0;
        error = setTransparentColour(currentI,Vector2d<int>(0,0));
    #else
        textures.resize(textures.size()+1);
        error = (Penjin::ERRORS)textures.back().loadTexture(name);
        if(error != PENJIN_OK)
        {
            textures.pop_back();
            return error;
        }
    #endif
    sheetMode = false;
    return error;
}

Penjin::ERRORS Image::loadImageNoKey(CRstring name)
{
    #ifdef PENJIN_SDL
        uint currentI = (uint)images.size();
        #ifdef PLATFORM_WII
            SDL_Surface* surf = IMG_Load((Penjin::getWorkingDirectory() + name).c_str());
        #else
            SDL_Surface* surf = IMG_Load(name.c_str());
        #endif
        if (surf)
        {
            SDL_Surface* oldSurface = surf;
            if(surf->flags & SDL_SRCALPHA)
            {
                surf = SDL_DisplayFormatAlpha(surf);
            }
            else
            {
                surf = SDL_DisplayFormat(surf);
            }
            SDL_FreeSurface(oldSurface);
            images.push_back(make_pair(surf,false));
        }
        else
            return PENJIN_IMG_UNABLE_TO_OPEN;
        #ifdef PENJIN_CACHE_ROTATIONS
            setupCaching();
        #endif
    #else
        textures.resize(textures.size()+1);
        Penjin::ERRORS error = (Penjin::ERRORS)textures[textures.size()-1].loadTexture(name);
        if(error != PENJIN_OK)
        {
            textures.pop_back();
            return error;
        }
    #endif
    sheetMode = false;
    return PENJIN_OK;
}

Penjin::ERRORS Image::loadImageSheet(CRstring name,CRuint xTiles,CRuint yTiles)
{
    //  We load the image into the image vector
    Penjin::ERRORS error = loadImage(name);
    if(error != PENJIN_OK)
        return error;
    sheetMode = true;  //  successful loading means we have a tilesheet

    return assignClipAreas(xTiles, yTiles, 0, 0);
}

Penjin::ERRORS Image::loadImageSheetNoKey(CRstring name,CRuint xTiles,CRuint yTiles)
{
    //  We load the image into the image vector
    Penjin::ERRORS error = loadImageNoKey(name);
    if(error != PENJIN_OK)
        return error;
    sheetMode = true;  // successful loading means we have a tilesheet

    return assignClipAreas(xTiles, yTiles, 0, 0);
}

Penjin::ERRORS Image::loadImageSheet(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles)
{
    Penjin::ERRORS error;
    //  We load the image into the image vector
    loadImage(surface);

    sheetMode = true;  //  successful loading means we have a tilesheet

    #ifdef PENJIN_SDL
        // Enable sharing
        images[images.size()-1].second = true;
        //  Apply colour key
        uint currentI = (uint)images.size()-1;
        error = setTransparentColour(currentI,Vector2d<int>(0,0));
        if(error != PENJIN_OK)
            return error;
    #endif

    return assignClipAreas(xTiles, yTiles, skipTiles, numTiles);
}

Penjin::ERRORS Image::loadImageSheetNoKey(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles)
{
    //  We load the image into the image vector
    loadImage(surface);
    sheetMode = true;  //  successful loading means we have a tilesheet

    #ifdef PENJIN_SDL
        // Enable sharing
         images[images.size()-1].second = true;
    #endif

    return assignClipAreas(xTiles, yTiles, skipTiles, numTiles);
}

// Build clipping areas - if numTiles is 0, it will be calculated automatically
Penjin::ERRORS Image::assignClipAreas(CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint p_numTiles)
{
    uint numTiles = p_numTiles;
    //  now we have to build the clipping areas based on the tile info we have.
    //second the width and height per tile needs to be calculated
    #ifdef PENJIN_SDL
        uint width = images[0].first->w;
        uint height = images[0].first->h;
    #else
        uint width = textures[0].getWidth();
        uint height = textures[0].getHeight();
    #endif
    uint xTileWidth = width/xTiles;
    uint yTileWidth = height/yTiles;

    if (numTiles == 0) {
        numTiles = (xTiles * yTiles) - skipTiles;
    }

    //  Accomodate clip areas
    clipAreas.resize(numTiles);

    uint currTile = 0;
    //  Run along then down

    for(uint y = 0; y < height; y+=yTileWidth)
    {
        for(uint x = 0; x < width; x+=xTileWidth)
        {
            if (currTile >= skipTiles && (currTile-skipTiles)<numTiles) {
                //  and set the values for the clip plane
                clipAreas[currTile-skipTiles].x = x;
                clipAreas[currTile-skipTiles].y = y;
                clipAreas[currTile-skipTiles].w = xTileWidth;
                clipAreas[currTile-skipTiles].h = yTileWidth;
            }
            ++currTile;
        }
    }
    return PENJIN_OK;
}

#ifdef PENJIN_SDL
    void Image::renderImage(uint i,CRfloat destx, CRfloat desty)
    {
        #ifdef PENJIN_FIXED
            renderImage(i,fixedpoint::fix2int(destx),fixedpoint::fix2int(destx));
        #else
            renderImage(i,(int)destx, (int) desty);
        #endif
    }
    void Image::renderImage(uint i, SDL_Surface* dstimg, CRint destx, CRint desty)
    {
        // Don't render if invisible or if there is no image!
        if(alpha == SDL_ALPHA_TRANSPARENT)
            return;

        if(!images.size() || i >= this->size())
        {
            if(sheetMode)   //  We have a spritesheet
            {
                //  If there is no area to clip the spritesheet we have a problem
                if(!images[0].first || clipAreas.size() || !clipAreas[i].w || !clipAreas[i].h)
                    return;
            }
            else if(!images[i].first)
                return;
        }

       // Set up blitting area
       SDL_Rect src, dst;
        //   If the image is a spritesheet, then set the relevant clips
        if(sheetMode)
        {
            src.x = clipAreas[i].x;
            src.y = clipAreas[i].y;
            src.w = clipAreas[i].w;
            src.h = clipAreas[i].h;
            i = 0;  // only element zero should have spritesheet data
        }
        else    //  Make the clip the size of the image
        {
            src.x = images[i].first->clip_rect.x;
            src.y = images[i].first->clip_rect.y;
            src.w = images[i].first->w;
            src.h = images[i].first->h;
        }

        dst.x = destx;
        dst.y = desty;

        // try to set surface alpha - depends on surface type.
        SDL_SetAlpha(images[i].first, SDL_SRCALPHA, alpha);
        if((angle == 0 && scale.x == 1 && scale.y == 1))
        {
            SDL_BlitSurface(images[i].first, &src, dstimg, &dst);
        }

        else if(angle != 0 || scale.x!= 1 || scale.y!= 1)
        {
            SDL_Surface* tempImage = NULL;
            #ifdef PENJIN_CACHE_ROTATIONS
                //  If not in a tilesheet we can do rotation caching
                if(!sheetMode && scale.x == 1 && scale.y == 1)
                {
                    uint myAngle = NumberUtility::wrapValue((int)angle,(int)359);
                    if(myAngle == 0)
                        SDL_BlitSurface(images.at(i).first, &src, dstimg, &dst);
                    else
                    {
                        if(rotCache.size()>myAngle-1 && rotCache.at(myAngle-1).surf != NULL)
                        {
                            dst.x += (src.w - rotCache.at(myAngle-1).surf->w)*0.5f;
                            dst.y += (src.h - rotCache.at(myAngle-1).surf->h)*0.5f;
                            SDL_BlitSurface(rotCache.at(myAngle-1).surf, NULL, dstimg,&dst);
                            ++rotCache.at(myAngle-1).useCount;
                        }
                        else
                        {
                            //  If the cache is not full we cache more images
                            if(currCached < maxCached)
                            {
                                cacheRotation(myAngle,rotoZoom(*images.at(i).first,src,dst));
                                SDL_BlitSurface(rotCache.at(myAngle-1).surf, NULL, dstimg,&dst);
                            }
                            else    //  We manually render (SLOW)
                            {       //  TODO: FREE least used cache items
                                SDL_Surface* t = rotoZoom(*images.at(i).first,src,dst);
                                SDL_BlitSurface(t, NULL, dstimg,&dst);
                                SDL_FreeSurface(t);
                            }
                        }
                    }
                }
                else
                {
                    tempImage = rotoZoom(*images.at(i).first,src,dst);
                    SDL_BlitSurface(tempImage,NULL, dstimg, &dst);
                    SDL_FreeSurface(tempImage);
                }
            #else
                tempImage = rotoZoom(*images.at(i).first,src,dst);
                SDL_BlitSurface(tempImage,NULL, dstimg, &dst);
                SDL_FreeSurface(tempImage);
            #endif
        }
    }
    #ifdef PENJIN_CACHE_ROTATIONS
        void Image::precacheRotations()
        {
            for(int i = maxCached; i>=1; --i)
            {
                setRotation(i);
                renderImage(NULL,0,0);
            }
        }
    #endif

    //void Image::renderImage(SDL_Surface* dstimg, const Vector2di& pos){renderImage(0, dstimg, pos.x, pos.y);}
    //template <class  T>
    //void Image::renderImage(SDL_Surface* dstimg, const T& destX, const T& destY){renderImage(0,dstimg,destX,destY);}

    void Image::screenLock()
    {
       // Check and lock the surface if necessary.
       if (SDL_MUSTLOCK(images.at(0).first))
            if (SDL_LockSurface(images.at(0).first) < 0 )
                return;
    }

    void Image::setPixel(CRint x, CRint y, CRuchar r, CRuchar g, CRuchar b,CRuchar a)
    {
        GFX::getInstance()->setDrawColour(Colour(r,g,b,a));
        GFX::getInstance()->drawPixel(images.at(0).first, Vector2d<float> (x,y));
    }
    void Image::setPixel(CRint x, CRint y, CRuchar r, CRuchar g, CRuchar b){setPixel(x,y,r,g,b,255);}
    void Image::setPixel(CRint x, CRint y, const Colour& c){setPixel(x,y,c.r,c.g,c.b,c.a);}

    void Image::screenUnlock()
    {
       // Check and unlock the durface if necessary
       if ( SDL_MUSTLOCK(images.at(0).first) )
            SDL_UnlockSurface(images.at(0).first);
    }
#else
    #ifdef PENJIN_3D
        void Image::renderImage(uint i,CRfloat destx, CRfloat desty,CRfloat destz)
    #else
        void Image::renderImage(uint i,CRfloat destx, CRfloat desty)
    #endif
    {
        // Don't render if invisible or if there is no image!
        if(!textures.size() || alpha == 0)
        {
            if(sheetMode)   //  We have a spritesheet
            {
                //  If there is no area to clip the spritesheet we have a problem
                if(!textures[0].isLoaded() || !clipAreas.size() || !clipAreas[i].w || !clipAreas[i].h)
                    return;
            }
            else if(!textures[i].isLoaded())
                return;
        }

        // Set up blitting area
        Vector4df texCoords;
        //   If the image is a spritesheet, then set the relevant clips
        float halfW;
        float halfH;
        Point2df tc;
        if(sheetMode)
        {
            Vector2df dims;
            dims.x = textures[0].getRawWidth();
            dims.y = textures[0].getRawHeight();
            halfW = clipAreas[i].w*0.5f;
            halfH = clipAreas[i].h*0.5f;
            tc = textures.front().getTextureCoords();
            texCoords.x = ((float)clipAreas[i].x / (float)dims.x);
            texCoords.y = ((float)clipAreas[i].y / (float)dims.y);
            texCoords.z = ((float)(clipAreas[i].x + clipAreas[i].w) / (float)dims.x);
            texCoords.w = ((float)(clipAreas[i].y + clipAreas[i].h) / (float)dims.y);
        }
        else    //  Make the clip the size of the image
        {
            tc = textures.at(i).getTextureCoords();
            texCoords.x = 0.0f;
            texCoords.y = 0.0f;
            texCoords.z = tc.x;
            texCoords.w = tc.y;
            halfW = textures[i].getWidth()*0.5f;
            halfH = textures[i].getHeight()*0.5f;
        }

        // Check if we need to alpha blend
        float tAlpha = (float)alpha *0.003921569f;
        //  Set OpenGL alpha
        #ifdef PENJIN_FIXED
            glColor4f(1.0f, 1.0f, 1.0f,fixedpoint::fix2float( tAlpha));
        #else
            glColor4f(1.0f, 1.0f, 1.0f, tAlpha);
        #endif
        // Scale and rotate
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(destx+halfW,desty+halfH,0.0f);
        #ifdef PENJIN_3D
            glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
            glScalef(scale.x, scale.y, scale.z);
        #else
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glScalef(scale.x,scale.y,1.0f);
        #endif

            glEnable(GL_TEXTURE_2D);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                    if(sheetMode)
                        glBindTexture (GL_TEXTURE_2D, textures.front().getTextureID());
                    else
                        glBindTexture (GL_TEXTURE_2D, textures.at(i).getTextureID());
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        #ifdef PENJIN_3D
                            GLfloat quad[] = {  halfW,-halfH,destz,
                                                -halfW,-halfH,destz,
                                                -halfW,halfH,destz,
                                                halfW,halfH,destz};
                            glVertexPointer(3, GL_FLOAT, 0,quad);
                        #else
                            GLfloat quad[] = {  halfW,-halfH,
                                                -halfW,-halfH,
                                                -halfW,halfH,
                                                halfW,halfH};
                            glVertexPointer(2, GL_FLOAT, 0,quad);
                        #endif
                        // x + z // y + w
                        // yyww / zxxz
                    GLfloat tx[] = {    texCoords.z,texCoords.y,
                                        texCoords.x,texCoords.y,
                                        texCoords.x,texCoords.w,
                                        texCoords.z,texCoords.w};
                    glTexCoordPointer(2, GL_FLOAT, 0, tx);
                    glDrawArrays(GL_TRIANGLE_FAN,0,4);
                    glDisableClientState(GL_VERTEX_ARRAY);
                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a)
    {

            //glColor4i(r, g, b, a);
            //glBegin(GL_POINTS);
           //     glVertex3f(x, y, z);
         //   glEnd();

    }
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b){setPixel(x,y,z,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const Colour& c){setPixel(x,y,z,c.red,c.green,c.blue,c.alpha);}
    void Image::setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b,const uchar& a){setPixel(x,y,0.0f,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b){setPixel(x,y,0.0f,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,const Colour& c){setPixel(x,y,0.0f,c.red,c.green,c.blue,c.alpha);}

    Colour Image::getPixel(CRint x, CRint y)
    {
        #ifdef PENJIN_GL
        glPushAttrib(GL_ENABLE_BIT);
        glDrawBuffer(GL_BACK);

        // TODO: save the pixel that was at 0, 0

        // Only clear one point for our operation
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glScissor(0, 0, 1, 1);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glOrtho(0, 1.0, 1.0, 0, -0.001, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBindTexture(GL_TEXTURE_2D, textures.at(0).getTextureID());
        glEnable(GL_TEXTURE_2D);

        // Draw the one point of our texture
        glBegin(GL_POINTS);
            glTexCoord3f(x/getWidth(), y/getHeight(), 0);
            glVertex3f(0, 0, 0);
        glEnd();

        // Read the alpha value: if the pixel was
        // opaque (glAlphaTest succeeded), z-buffer was
        // written to by the above operation, otherwise
        // it should be intact
        GLfloat pix[4*4];
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, pix);

        // TODO: put back the pixel that was at 0, 0

        glScissor(0, 0, 1, 1);

        glMatrixMode(GL_PROJECTION);
        glDepthFunc(GL_LESS);

        glPopAttrib();
        return Colour((float)pix[0],pix[1],pix[2],pix[3]);
        #endif
    }
#endif // PENJIN_SDL

size_t Image::size()const
{
    if(sheetMode)
        return clipAreas.size();
    else
    {
        #ifdef PENJIN_SDL
            return images.size();
        #else
            return textures.size();
        #endif
    }
}

void Image::clear()
{
    #ifdef PENJIN_SDL
        int i = images.size()-1;
        while(i >= 0)
        {
            if(!images[i].second && images[i].first)
            {
                SDL_FreeSurface(images[i].first);
            }
            images[i].first = NULL;
            --i;
        }
        images.clear();
        #ifdef PENJIN_CACHE_ROTATIONS
            i = rotCache.size()-1;
            while(i >= 0)
            {
                if(rotCache.at(i).surf != NULL)
                {
                    SDL_FreeSurface(rotCache.at(i).surf);
                    rotCache.at(i).surf = NULL;
                }
                --i;
            }
            rotCache.clear();
        #endif
    #else
        textures.clear();
    #endif
    if(sheetMode)
        clipAreas.clear();
    sheetMode = false;
}

void Image::setAlpha(const uchar& alpha){this->alpha = alpha;}

uchar Image::getAlpha()const{return alpha;}

uint Image::getHeight()const
{
    if(sheetMode)
        return clipAreas.front().h;

    #ifdef PENJIN_SDL
        return images.front().first->h;
    #else
        return textures.front().getHeight();
    #endif
}

uint Image::getWidth()const
{
    if(sheetMode)
        return clipAreas.front().w;

    #ifdef PENJIN_SDL
        return images.front().first->w;
    #else
        return textures.front().getWidth();
    #endif
}
#ifdef PENJIN_SDL
void Image::convertToHW()
{
    //for(int i = images.size()-1; i>= 0; --i)
    //{
      //  SDL_Surface* temp = images.at(i);
       // images.at(i) = SDL_ConvertSurface(images.at(i), screen->format, SDL_HWSURFACE);
        //SDL_FreeSurface(temp);
    //}
}

SDL_Surface* Image::rotoZoom(SDL_Surface& in, SDL_Rect& src,  SDL_Rect& dst)
{
    SDL_Surface* tempImage = NULL;
    SDL_Surface* subSprite = NULL; // Need to use this for animated sprites to get the subsprite isolated.

    if(sheetMode)
    {
        subSprite = GFX::getInstance()->cropSurface(&in,&src);
        #ifdef PENJIN_FIXED
            tempImage = rotozoomSurfaceXY(subSprite,
            fixedpoint::fix2float(angle),
            fixedpoint::fix2float(scale.x),
            fixedpoint::fix2float(scale.y),SMOOTHING_OFF);
        #else
            tempImage = rotozoomSurfaceXY(subSprite, angle, scale.x, scale.y, SMOOTHING_OFF);
        #endif
        dst.x += (subSprite->w - tempImage->w)*0.5f;
        dst.y += (subSprite->h - tempImage->h)*0.5f;
        SDL_FreeSurface(subSprite);
    }
    else
    {
        //  second check if size has changed
        //  If the size has change then we can't use the cached rotations

        #ifdef PENJIN_FIXED
            tempImage = rotozoomSurfaceXY(in,
            fixedpoint::fix2float(angle),
            fixedpoint::fix2float(scale.x),
            fixedpoint::fix2float(scale.y),SMOOTHING_OFF);
        #else
            tempImage = rotozoomSurfaceXY(&in, angle, scale.x, scale.y, SMOOTHING_OFF);
        #endif
        dst.x += (src.w - tempImage->w)*0.5f;
        dst.y += (src.h - tempImage->h)*0.5f;
    }

    // This code fixes colour keying in 32 bpp mode (otherwise the colour key colour shows)
    // It also caused the rotated images to disappear in 16 bpp mode, so only run for 32 bpp
    if(in.format->BitsPerPixel == 32 && colourKey.a)
    {
        SDL_Surface* another = SDL_CreateRGBSurface(in.flags,tempImage->w, tempImage->h,in.format->BitsPerPixel, tempImage->format->Rmask, tempImage->format->Gmask, tempImage->format->Bmask, tempImage->format->Amask);
        SDL_FillRect(another, NULL, SDL_MapRGB(another->format,colourKey.r,colourKey.g,colourKey.b));
        SDL_SetColorKey(tempImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tempImage->format,0,0,0));
        SDL_BlitSurface(tempImage,NULL, another, NULL);
        SDL_SetColorKey(another, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(another->format,colourKey.r,colourKey.g,colourKey.b));
        SDL_FreeSurface(tempImage);
        return another;
    }

    return tempImage;
}
    #ifdef PENJIN_CACHE_ROTATIONS
        void Image::setupCaching()
        {
            maxCached = currCached = 0;
            Point2di dim;
            dim.x = getWidth();
            dim.y = getHeight();

            // if the image is too big, it's not good to bloat out ram with all copies of rotations
            if((uint)dim.x > GFX::getXResolution() || (uint)dim.y > GFX::getYResolution())
                return;
            //  If the image is less than 2% of the screen dims then we will not see any noticeable benefit from caching
            else if(dim.x < GFX::getXResolution()* 0.02f || dim.y < GFX::getYResolution()*0.02f)
                return;
            //  If the image is less than 5% of the screen dims then we cache all angles
            else if(dim.x < GFX::getXResolution()* 0.05f || dim.y < GFX::getYResolution()*0.05f)
                maxCached = 358;
            else
            {
                //  TODO scale caching relative to size of sprite and screen resolution
                maxCached = 0;
            }
        }

        void Image::cacheRotation(uint angle, SDL_Surface* s)
        {
            //  Bring the angle into range
            //angle = NumberUtility::wrapValue(angle, 359);
            if(s == NULL)
                return;

            //  If the angle is 0 we don't actually need to rotate or cache
            if(angle == 0)
            {
                if(s!=NULL)
                    SDL_FreeSurface(s);
                return;
            }

            //  shift one place for the lack of 0 angle.
            angle-=1;

            ROT r;
            r.surf = NULL;
            r.useCount = 0;

            //  Create enough space to store the rotation.
            while(angle >= rotCache.size())
            {
                rotCache.push_back(r);
            }

            //  now check and store the surface
            if(rotCache.at(angle).surf == NULL)
            {
                rotCache.at(angle).surf = s;
                ++currCached;
            }
            else
                SDL_FreeSurface(s);
        }
    #endif
#endif

void Image::toGreyScale()
{
    #ifdef PENJIN_SDL
        for(int i = images.size()-1; i>= 0; --i)
        {
            Colour t;
            GFX::getInstance()->lockSurface(images.at(i).first);
            for(int x = images.at(i).first->w-1; x>=0; --x)
            {
                for(int y = images.at(i).first->h-1; y >= 0; --y)
                {
                    t = GFX::getInstance()->getPixel(images.at(i).first,Vector2d<int>(x,y));
                    t.toGreyScale();
                    GFX::getInstance()->setDrawColour(t);
                    GFX::getInstance()->drawPixel(images.at(i).first,Vector2d<float>(x,y));
                }
            }
            GFX::getInstance()->unlockSurface(images.at(i).first);
        }
    #else

    #endif
}

void Image::toNegative()
{
    #ifdef PENJIN_SDL
        for(int i = images.size()-1; i>= 0; --i)
        {
            Colour t;
            GFX::getInstance()->lockSurface(images.at(i).first);
            for(int x = images.at(i).first->w-1; x>=0; --x)
            {
                for(int y = images.at(i).first->h-1; y >= 0; --y)
                {
                    t = GFX::getInstance()->getPixel(images.at(i).first,Vector2d<int>(x,y));
                    t = -t;
                    GFX::getInstance()->setDrawColour(t);
                    GFX::getInstance()->drawPixel(images.at(i).first,Vector2d<float>(x,y));
                }
            }
            GFX::getInstance()->unlockSurface(images.at(i).first);
        }
    #else

    #endif
}

void Image::swapGB()
{
    #ifdef PENJIN_SDL
        for(int i = images.size()-1; i>= 0; --i)
        {
            Colour t;
            GFX::getInstance()->lockSurface(images.at(i).first);
            for(int x = images.at(i).first->w-1; x>=0; --x)
            {
                for(int y = images.at(i).first->h-1; y >= 0; --y)
                {
                    t = GFX::getInstance()->getPixel(images.at(i).first,Vector2d<int>(x,y));
                    t.swapGB();
                    GFX::getInstance()->setDrawColour(t);
                    GFX::getInstance()->drawPixel(images.at(i).first, Vector2d<float>(x,y));
                }
            }
            GFX::getInstance()->unlockSurface(images.at(i).first);
        }
    #else

    #endif
}

void Image::swapRB()
{
    #ifdef PENJIN_SDL
        for(int i = images.size()-1; i>= 0; --i)
        {
            Colour t;
            GFX::getInstance()->lockSurface(images.at(i).first);
            for(int x = images.at(i).first->w-1; x>=0; --x)
            {
                for(int y = images.at(i).first->h-1; y >= 0; --y)
                {
                    t = GFX::getInstance()->getPixel(images.at(i).first,Vector2d<int>(x,y));
                    t.swapRB();
                    GFX::getInstance()->setDrawColour(t);
                    GFX::getInstance()->drawPixel(images.at(i).first, Vector2d<float>(x,y));
                }
            }
            GFX::getInstance()->unlockSurface(images.at(i).first);
        }
    #else

    #endif
}

void Image::swapRG()
{
    #ifdef PENJIN_SDL
        for(int i = images.size()-1; i>= 0; --i)
        {
            Colour t;
            GFX::getInstance()->lockSurface(images.at(i).first);
            for(int x = images.at(i).first->w-1; x>=0; --x)
            {
                for(int y = images.at(i).first->h-1; y >= 0; --y)
                {
                    t = GFX::getInstance()->getPixel(images.at(i).first,Vector2d<int>(x,y));
                    t.swapRG();
                    GFX::getInstance()->setDrawColour(t);
                    GFX::getInstance()->drawPixel(images.at(i).first, Vector2d<float>(x,y));
                }
            }
            GFX::getInstance()->unlockSurface(images.at(i).first);
        }
    #else

    #endif
}

#ifdef PENJIN_SDL
void Image::setSurfaceSharing(CRbool value, CRint index)
{
    if (index < 0)
    {
        vector< pair<SDL_Surface*,bool> >::iterator I;
        for (I = images.begin(); I < images.end(); ++I)
        {
            I->second = value;
        }
    }
    else if (index < images.size())
        images[index].second = value;
    else
        cout << "Error: Trying to access out of bounds index in Image::setSurfaceSharing(" << index << ")" << endl;
}

bool Image::getSurfaceSharing(CRint index) const
{
    if (index < 0)
    {
        vector< pair<SDL_Surface*,bool> >::const_iterator I;
        for (I = images.begin(); I < images.end(); ++I)
        {
            if (I->second)
            {
                return true;
            }
        }
        return false;
    }
    else if (index < images.size())
        return images[index].second;
    else
        cout << "Error: Trying to access out of bounds index in Image::getSurfaceSharing(" << index << ")" << endl;
}
#endif
*/
