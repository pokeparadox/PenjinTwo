/**
    \section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
**********************************************************************************************/
/**
  * \file A class which handles loading tilesheets
  * \author Kevin Winfield-Pantoja
*/#ifndef IMAGESHEET_H
#define IMAGESHEET_H

#include "Image.h"
#include <vector>
using std::vector;

namespace Penjin
{
    class ImageSheet : public Image
    {
        public:
            /** Default constructor */
            ImageSheet();
            /** Default destructor */
            virtual ~ImageSheet();


            /** \brief Function to load an individual image from file.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load(const string& fileName);

            /** \brief Function to load an individual image from SDL_Surface*.
             * \param surface : SDL_Surface* to load.
             * \return PENJIN_OK if surface was loaded successfully.
             */
            virtual Penjin::ERRORS load(SDL_Surface* surface);

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

            /** \brief Render the activeImage to screen */
            virtual void render();

            /** \brief Clear any and all stored images and clip areas. */
            void clear();

            /** \brief Get the dimensions of a subImage from the ImageSheet.
             * \param subImage : The index of the Image that we require the dimensions.
             * \return Vector2d<int> containing the relevent dimensions.
             */
            Vector2d<int> getDimensions(CRuint subImage);

             /** \brief set the image to display in the render function.
             * \param a : The active image.
             */
            void setActiveImage(CRint a);

             /** \brief Return the number of sub-images contained within this ImageSheet.
             * \return the number of images
             */
            size_t size();

        protected:
            Penjin::ERRORS assignClipAreas(CRuint xTiles, CRuint yTiles,CRuint skipTiles,CRuint numTiles);

            bool                    sheetMode;      // true if we have multiple images contained in one file.
            int            activeImage;    // The image to be displayed from image sheet
            vector<SDL_Surface*>    surfaces;       // We store our surfaces here
            vector<SDL_Rect>        clipAreas;      // We store clips of the images stored in the image sheet
    };
}
#endif // IMAGESHEET_H
