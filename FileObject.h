/**
    \section LICENSE
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
/**
  * \file FileObject provides a basic interface for the loading of files.
  * \author Kevin Winfield-Pantoja
  */
#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include "Object.h"
#include "Errors.h"
#include <string>
using std::string;

namespace Penjin
{
    class FileObject : public Object
    {
        public:
            /** Default constructor */
            FileObject();
            /** Default destructor */
            virtual ~FileObject();

            /** \brief pure virtual function to load a file.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load(const string& fileName)=0;

            /** \brief pure virtual function to save a file.
             * \param fileName : The file to load.
             * \return PENJIN_OK if file was saved successfully.
             */
            virtual Penjin::ERRORS save(const string& fileName)=0;

            /** \brief function to load a file from the stored filename.
             * \return PENJIN_OK if file was loaded successfully.
             */
            virtual Penjin::ERRORS load();

            /** \brief function to save a file to the stored filename.
             * \return PENJIN_OK if file was saved successfully.
             */
            virtual Penjin::ERRORS save();

            /** \brief sets the internal fileName of this file.
             *  \param f : the file name.
             */
            void setFileName(const string& f);

        protected:
            string fileName;    //we keep a copy of the the filename if needed.
    };
}
#endif // FILEOBJECT_H
