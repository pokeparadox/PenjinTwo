/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of PenjinTwo.

	PenjinTwo is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PenjinTwo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with PenjinTwo.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Glyph.h"
using Penjin::Glyph;

Glyph::Glyph()
{
    //ctor
    fontSize = 0;       // no font.
    //position = NULL;
    character = '\0';

    renderMode = GlyphClass::QUICK;
    fileName = "GLYPH";
}

Glyph::~Glyph()
{
    //dtor
}

void Glyph::refresh()
{
    if(!isprint(character) || fontSize == 0)        //  No cursor position is invalid usage.
        return;
#ifdef PENJIN_SDL
    if(surface)
        clear();
#endif
    char t[2];
    t[0] = character;
    t[1] = '\0';
    SDL_Surface* tS;

    if(renderMode == QUICK)
        tS = TTF_RenderText_Solid(font,t,getSDL_Colour());
    else if(renderMode == BOXED)
        tS = TTF_RenderText_Shaded(font,t,getSDL_Colour(),bgColour.getSDL_Colour());
    else
        tS = TTF_RenderText_Blended(font,t,getSDL_Colour());
    load(tS);
}

/*
void Glyph::render()
{
    #ifdef PENJIN_SDL
        glyph.renderImage(*position);
    #else
        //  With the surface now converted to a texture we can render it to a quad
        glColor4f(1.0f, 1.0f, 1.0f, colour.alpha);
        glBindTexture (GL_TEXTURE_2D, glyph.getTextureID());
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            GLfloat tx[] = {0,0, 0,1, 1,1, 1,0};
            #ifdef PENJIN_3D
                GLfloat quad[] = {  position->x,position->y,position->z,
                                    position->x + glyph.getWidth(), position->y, position->z,
                                    position->x + glyph.getWidth(),position->y + glyph.getHeight(),position->z,
                                    position->x,position->y + glyph.getHeight(),position->z};
                glVertexPointer(3, GL_FLOAT, 0,quad);
            #else
                GLfloat quad[] = {  position->x,position->y,
                                    position->x,position->y + glyph.getHeight(),
                                    position->x + glyph.getWidth(),position->y + glyph.getHeight(),
                                    position->x + glyph.getWidth(), position->y
                                    };
                glVertexPointer(2, GL_FLOAT, 0,quad);
            #endif
            glTexCoordPointer(2, GL_FLOAT, 0, tx);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
                glDrawArrays(GL_TRIANGLE_FAN,0,4);
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    #endif
}
*/
