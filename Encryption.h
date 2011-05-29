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
#ifndef ENCRYPTION_H
#define ENCRYPTION_H
/*
PROJECT:	Simple encryption class
BY:			Kevin Winfield-Pantoja (PokeParadox)
DATE:		Started on 01-07-06
ABOUT:		The encryption algorithm is mainly intended for encrypting game data, such as highscore tables.
			Anyone serious enough could crack it, even without this source.
*/

#include <string>
using namespace std;
#include "Random.h"
#include "NumberUtility.h"

class Encryption
{
    public:
        Encryption();
        ~Encryption();

        //	NOTE: The encryption key(seed value) is stored as the last char of the encrypted string.
        //		  It is stripped from the string on decryption.

        string encryptBuffer(CRstring buff);	//	Takes a string of data and returns an encrypted string.
        string decryptBuffer(string buff);	//	Takes an encrypted string of data and returns a decrypted string.

    private:
        int wrapValue(int val,CRint limit){return (NumberUtility::wrapValue(val,limit));}	//	Brings value with a certain range.
        char key;		//This is the random number seed value
        RandomClass rand;
};

#endif	//	ENCRYPTION_H
