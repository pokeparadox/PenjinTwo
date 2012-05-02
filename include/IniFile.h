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
/***************************************************************************************************
*   \file IniFile is a class to handle the reading of simple ini files.
*   \author Kevin Winfield-Pantoja
*/

#ifndef INIFILE_H
#define INIFILE_H

#include "TextFile.h"

namespace Penjin
{
    class SubLine
    {
        public:
            SubLine() : ID(-1) {;}
            int ID;
            string value;
            string comment;
    };
    class IniLine
    {
        public:
            string key;
            vector<SubLine> sub;
    };

    //  This is a section which contains many lines of keys
    //  A section is denoted by this notation:
    //      [SECTION_NAME_01]
    //  if a number is found before the ], that number is used as an ID
    class SubSection
    {
        public:
            SubSection() : ID(-1) {;}
            int ID;
            vector <IniLine> lines;
    };

    class IniSection
    {
        public:
            IniSection() : name("Default"){;}
            vector<SubSection> sub;
            string name;
    };

    class IniFile : public TextFile
    {
        public:
            /** Default constructor */
            IniFile();
            /** Default destructor */
            virtual ~IniFile();

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

            /** \brief set a value into the ConfigFile
             * \param section : The section of the file to add the value.
             * \param ID : The sub section with relavent ID to write to. (Default -1, no subsection.)
             * \param key : The key within the section to add the value.
             * \param keyID : The subKey with relavent ID to write to. (Default -1, no subKey.)
             * \param value : The actual value to be stored.
             * \param comment: Any additional comment you wish to add to the file. (Default no comment.)
             */
            void setValue(const string& section, const int& ID=-1, const string& key="", const int& keyID=-1, const string& value="", const string& comment="");

            /** \brief set a value into the ConfigFile
             * \param section : The section of the file to add the value.
             * \param key : The key within the section to add the value.
             * \param value : The actual value to be stored.
             * \param comment: Any additional comment you wish to add to the file. (Default no comment.)
             */
            void setValue(const string& section, const string& key="", const string& value="", const string& comment="");

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

            virtual void clear();
        protected:
            void processLine(string line);
            string getComment(string raw);
            int getID(string raw);
            string getSection(string raw);
            string getKey(string raw,char separator='=');
            string getValue(string raw, char separator='=');
            string clean(string in);                        //  Removes leading and trailing spaces and line endings.

            void createSection(string section, int ID=-1);
            void setValue(string key, int ID=-1, string value="", string comment="");    //  Sets or updates a value to the key in the current section.

            size_t findSection(string section); //  Find the index in this section.
            size_t findSubSection(string sub);  //  Find this subsection
            size_t findKey(size_t section, string key);

            vector <IniSection> iniData;
            bool changed;
        private:
            unsigned int currentSec;
            unsigned int currentSecID;

            //  These are private helper functions to actually write the values to the raw text file.
            void writeSection(int index, int subSecIndex);
            void writeLine(string key, int ID, string value, string comment="");
    };
}

#endif // INIFILE_H
