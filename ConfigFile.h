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
*/
/**
  * \file ConfigFile class allows the loading of ini files
  * \author Kevin Winfield-Pantoja
  */
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "FileObject.h"
#include "simpleini/SimpleIni.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace Penjin
{
    class ConfigFile : public FileObject
    {
        public:
            /** Default constructor */
            ConfigFile();
            /** Default destructor */
            virtual ~ConfigFile();

            /** \brief loads the ini file for parsing and value extraction.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load(const string& fileName);

            /** \brief saves the changes to the ini file.
             * \param fileName : The file to save.
             * \return PENJIN_OK if file was saved successfully.
             */
            virtual Penjin::ERRORS save(const string& fileName);

            //virtual Penjin::ERRORS save();
            //virtual Penjin::ERRORS load();

            //void setValue(const string& section, const string& key, const string& value);
            /** \brief set a value into the ConfigFile
             * \param section : The section of the file to add the value.
             * \param key : The key within the section to add the value.
             * \param value : The actual value to be stored.
             * \param comment: Any additional comment you wish to add to the file.
             */
            void setValue(const string& section, const string& key, const string& value, const string& comment="");

            /** \brief get a value from the ConfigFile
             * \param section : The section of the file to take the value.
             * \param key : The key within the section to take the value.
             * \return The actual value.
             */
            string getValue(const string& section, const string& key);

             /** \brief get a value from the ConfigFile and set the value if a value is missing
             * \param section : The section of the file to take the value.
             * \param key : The key within the section to take the value.
             * \param value : The value to set if the requested value is missing!
             * \return The actual value.
             */
            string getValue(const string& section, const string& key, const string& value);

            /** If the file contants have been changed*/
            bool hasChanged();

            vector<string> getSections();
            vector<string> getValues(const string& section, const string& key);
            vector<string> getKeys(const string& section);

            // TODO implementation for following 2 functions
            void removeValue(const string& section, const string& key);
            void removeSection(const string& section);

        protected:
            /** \brief get the Penjin error code from the Simple Ini error code
             * \param error : The Simple Ini error code.
             * \return The Penjin::ERRORS error code.
             */
            Penjin::ERRORS getError(const int& error);

            /**< the SimpleIni object */
            CSimpleIniA* ini;
            bool changed;
    };
}
#endif // CONFIGFILE_H
