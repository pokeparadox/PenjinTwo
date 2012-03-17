/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012
        Kevin Winfield-Pantoja

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
/***************************************************************************************************
*   \file ConfigManager is where PenjinTwo stores all settings.
*   \author Kevin Winfield-Pantoja
*/

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Singleton.h"
#include "Errors.h"
#include <string>

using std::string;

namespace Penjin
{
    class IniFile;
    /*************** Constants ****************/
    const std::string CONFIG_FILE = "config/settings.ini";   /**< The configuration file location */

    class ConfigManager
    {
        public:
            /** \brief loads the ini file for parsing and value extraction.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was loaded successfully.
             */
            Penjin::ERRORS load(const string& fileName="");
            /** \brief saves the ini file to disk.
             * \param fileName : The file to save.
             * \return PENJIN_OK if file was saved successfully.
             */
            Penjin::ERRORS save(const string& fileName="");

            //  set which library handles audio.
            void setAudioEngine(const string& engine="SDL");
            //  Set which library handles display.
            void setGFXEngine(const string& engine="SDL");
            //  Set whether to handle the third dimensions (depth)
            void setGFXDimensions(const unsigned int& dims=2);
            //  Set the FrameRate
            void setFrameRate(const int& fps=60);
            //  Set the physics update rate
            void setUpdateRate(const int& fps=60);
            //  Set the Display Width (0 == autodetect)
            void setWidth(const int& w=0);
            //  Set the display height (0 == Autodetect)
            void setHeight(const int& h=0);
            //  Set the Unscaled Display Width (0 == autodetect)
            void setBaseWidth(const int& w=0);
            //  Set the Unscaled display height (0 == Autodetect)
            void setBaseHeight(const int& h=0);
            //  Set the BitsPerPixel of the display (0 == Auto)
            void setBPP(const int& bpp=0);
            //  Set if the application is fullscreen or not (true == fullscreen)
            void setFullscreen(const bool& fs=false);
            //  Set the ScaleMode of the application (None,PreScale,PokeScale)
            void setScaleMode(const string& sm="PreScale");
            //  Set the default SystemFont
            void setSystemFont(const string& sf="fonts/unispace.ttf");
            void setSystemFontSize(const int& fs=10);


            //  Get which library handles audio.
            string getAudioEngine();
            //  Get which library handles display.
            string getGFXEngine();
            //  Get whether to handle the third dimensions (depth)
            unsigned int getGFXDimensions();
            //  Get the FrameRate
            int getFrameRate();
            //  Get the physics update rate
            int getUpdateRate();
            //  Get the Display Width (0 == autodetect)
            int getWidth();
            //  Get the display height (0 == Autodetect)
            int getHeight();
            //  Get the Unscaled Display Width (0 == autodetect)
            int getBaseWidth();
            //  Get the Unscaled display height (0 == Autodetect)
            int getBaseHeight();
            //  Get the BitsPerPixel of the display (0 == Auto)
            int getBPP();
            //  Get if the application is fullscreen or not (true == fullscreen)
            bool getFullscreen();
            //  Get the ScaleMode of the application (None,PreScale,PokeScale)
            string getScaleMode();
            //  Get the default SystemFont
            string getSystemFont();
            int getSystemFontSize();

            //  Expose a feature to the report string.
            bool report(const string& feature);
            //  Check if a feature exists in the report string.
            bool checkReport(const string& feature);
            /** Default constructor */
            ConfigManager();


        protected:
            /** Default destructor */
            virtual ~ConfigManager();
        private:
            IniFile* config;
            string engineAudio;
            string engineGFX;
            string reportList;
            int fps;
            int updateps;
            int width;
            int height;
            int baseWidth;
            int baseHeight;
            int bpp;
            bool fullscreen;
            int dimensions;
            string scaleMode;
            string font;
            int fontSize;
    };
    // Create Singleton instance of class for PenjinTwo
    typedef Singleton <ConfigManager> ConfigMan;
}


#endif // CONFIGMANAGER_H
