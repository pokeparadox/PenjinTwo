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
#ifndef STRINGUTILITY_H
#define STRINGUTILITY_H


#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include "PenjinTypes.h"

using namespace std;
namespace Penjin
{
    namespace StringUtility
    {
        ///	OS Format conversion
        //	Note that these only work if the TO target is the same as the host OS as the app is run on!
        string stripLineEndings(string line);

        string xToLin(string line);
        string xToWin(string line);
        string xToMac(string line);
        string xTox(string line);
        //  depracated
        string linToWin(CRstring line);
        string winToLin(CRstring line);
        string macToWin(CRstring line);
        string winToMac(CRstring line);
        string macToLin(CRstring line);
        string linToMac(CRstring line);
        //  end deprecated

        ///	Various to string conversions
        string FixedToString(CRFixed value);
        string floatToString(CRfloat value);
        string doubleToString(CRdouble value);
        string longToString(CRlong value);
        string intToString(CRint value);
        string shortToString(CRshort value);
        string boolToString(CRbool value, CRbool useBoolString=true);
        template <class T>
        string vecToString(const T& vec, CRstring separator=",")
        {
            // using doubleToString for maximum compatibility
            return (doubleToString(vec.x) + separator + doubleToString(vec.y));
        }

        /// Char* string conversions
        Fixed cStringToFixed(char* value);
        float cStringToFloat(char* value);
        double cStringToDouble(char* value);
        long cStringToLong(char* value);
        int cStringToInt(char* value);
        short cStringToShort(char* value);

        ///	String to various conversions
        Fixed stringToFixed(CRstring value);
        float stringToFloat(CRstring value);
        double stringToDouble(CRstring value);
        long stringToLong(CRstring value);
        int stringToInt(CRstring value);
        unsigned int stringToUnsignedInt(CRstring value);
        short stringToShort(CRstring value);
        bool stringToBool(CRstring value);

        ///	Case modifyers
        string upper(string word);
        string lower(string word);
        char upper(CRchar l);	//	converts character to uppercase
        char lower(CRchar l);	//	converts character to lowercase

        ///	Digit/Letter checking
        bool isLetter(CRchar letter);
        bool isDigit(CRchar digit);

        ///	Type modifyers
        int charToInt(CRchar value);
        char intToChar(CRint value);

        ///  Formatting
        string leadingZero(CRint value);     //  prepends a 0 if necessary
        void reverse(char* s);

        /// Additional
        string substrReplace(string text, CRstring oldSubstr, CRstring newSubstr); // replaces all occurrences of oldSubstr in text with newSubstr
        void tokenize(CRstring str, vector<string>& tokens, CRstring delimiters = " "); // splits a string into parts at a certain char and adds the parts to the passed vector
        void tokenize(CRstring str, vector<string>& tokens, CRstring delimiters, CRuint maxParts);
        string combine(const vector<string>& tokens, CRstring delimiter = ","); // compines an array or string parts into one string seperating them with the delimiter char
    }
}
#endif	//	STRINGUTILITY_H
