/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
#ifndef LOCALISEDSTRINGMANAGER_H
#define LOCALISEDSTRINGMANAGER_H

#include "IniFile.h"
#include "Singleton.h"
#include <string>
using std::string;

namespace Penjin
{
    class LocalisedStringManager : public IniFile
    {
        public:
            //LocalisedStringManager();
            /** get a Singleton instance of this class! */

            //static LocalisedStringManager* getInstance();

            //virtual Penjin::Errors load(const string & file);
            /** \brief loads the locale strings
             * \return the Penjin:ERRORS, error code.
             */
            virtual Penjin::ERRORS load();
            /** \brief saves the locale strings
             * \return the Penjin:ERRORS, error code.
             */
            virtual Penjin::ERRORS save();
            /** \brief sets the locale of the string manager.
             * \param lang : the locale code to search for.
             */
            void setLanguage(const string& lang);
            /** \brief sets the folder where to look for locale files.
             * \param f : the path where the language files are stored.
             */
            void setLanguageFolder(const string& f);
            LocalisedStringManager();

        private:
                                                       // constructor is private
            LocalisedStringManager(LocalisedStringManager const&){;}              // copy constructor is private
            LocalisedStringManager& operator=(LocalisedStringManager const&){return *this;}   // assignment operator is private
            ~LocalisedStringManager();

            string languageFolder;
            string language;

            //static LocalisedStringManager* instance;
    };
    typedef Singleton<LocalisedStringManager> LocaleMan;
    //typedef LocalisedStringManager LocaleMan;
}
#endif // LOCALISEDSTRINGMANAGER_H
