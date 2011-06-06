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
#include "StringUtility.h"
using namespace Penjin;
string StringUtility::stripLineEndings(string line)
{
    //  strip LF
    line = substrReplace(line,"\r","");
    //  strip CR and return
    return substrReplace(line,"\n","");
}

string StringUtility::xTox(string line)
{
    line = stripLineEndings(line);
    return (line + "\n");
}

string StringUtility::xToWin(string line)
{
    line = stripLineEndings(line);
    line.push_back(0x0D);    //  CR
    line.push_back(0x0A);    //  LF
	return line;
}

string StringUtility::xToLin(string line)
{
    line = stripLineEndings(line);
    //	Add linux LF
    line.push_back(0x0A);
	return line;
}

string StringUtility::xToMac(string line)
{
    line = stripLineEndings(line);
    //	Add Mac CF
    line.push_back(0x0D);
	return line;
}

string StringUtility::linToMac(CRstring line)
{
    return xToMac(line);
}

string StringUtility::macToLin(CRstring line)
{
    return xToLin(line);
}

string StringUtility::winToLin(CRstring line)
{
    return xToLin(line);
}

string StringUtility::linToWin(CRstring line)
{
    return xToWin(line);
}

string StringUtility::winToMac(CRstring line)
{
    return xToMac(line);
}

string StringUtility::macToWin(CRstring line)
{
    return xToWin(line);
}

string StringUtility::doubleToString(CRdouble value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

string StringUtility::floatToString(CRfloat value)
{
	stringstream ss;
	string str;
	#ifdef PENJIN_FIXED
        ss << fixedpoint::fix2float(value);
	#else
        ss << value;
	#endif
	ss >> str;
	return str;
}

string StringUtility::FixedToString(CRFixed value){return floatToString(fixedpoint::fix2float<16>(value.intValue));}

string StringUtility::intToString(CRint n)
{
	stringstream ss;
	string str;
	ss << n;
	ss >> str;
	return str;
}


string StringUtility::boolToString(CRbool value, CRbool useBoolString)
{
    if (value)
    {
        if (useBoolString)
            return "true";
        else
            return "1";
    }
    else
    {
        if (useBoolString)
            return "false";
        else
            return "0";
    }
}

bool StringUtility::isDigit(CRchar digit)
{
	return true;
}

bool StringUtility::isLetter(CRchar l)
{
	if (l >= 'a' && l <= 'z')
		return true;
	else if (l >= 'A' && l <= 'Z')
		return true;
	return false;
}

string StringUtility::longToString(CRlong value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

char StringUtility::lower(CRchar l)
{
	//	if it's lowercase
	char o = l;
	if (isupper(l))
		o = tolower(l);
	return o;
}

string StringUtility::shortToString(CRshort value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

double StringUtility::stringToDouble(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	double out = 0;
	ins >> out;
	return out;
}

float StringUtility::stringToFloat(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	#ifdef PENJIN_FIXED
        FLOAT out = 0;
	#else
        float out = 0;
	#endif
	ins >> out;
	return out;
}

Fixed StringUtility::stringToFixed(CRstring value)
{
	return Fixed(stringToFloat(value));
}

int StringUtility::stringToInt(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	int out = 0;
	ins >> out;
	return out;
}

unsigned int StringUtility::stringToUnsignedInt(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	unsigned int out = 0;
	ins >> out;
	return out;
}

long StringUtility::stringToLong(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	long out = 0;
	ins >> out;
	return out;
}

short StringUtility::stringToShort(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	short out = 0;
	ins >> out;
	return out;
}

bool StringUtility::stringToBool(CRstring value)
{
    if (value == "true" || value == "True" || value == "1")
        return true;
    else
        return false;
}

double StringUtility::cStringToDouble(char* value){return stringToDouble((string)value);}
float StringUtility::cStringToFloat(char* value){return stringToFloat((string)value);}
Fixed StringUtility::cStringToFixed(char* value){return stringToFixed((string)value);}
int StringUtility::cStringToInt(char* value){return stringToInt((string)value);}
long StringUtility::cStringToLong(char* value){return stringToLong((string)value);}
short StringUtility::cStringToShort(char* value){return stringToShort((string)value);}

char StringUtility::upper(CRchar l)
{
    char o = l;
	//	if it's lowercase
	if (islower(l))
		o = toupper(l);
	return o;
}

int StringUtility::charToInt(CRchar n)
{
    char o = n;
	if(n >= 48 && n <= 57)
		o-=48;

	return o;
}

char StringUtility::intToChar(CRint n)
{
    char o = n;
	if(n >= 0 && n <= 57-48)
			o+=48;
	return o;
}

string StringUtility::upper(string word)
{
    for(int i = word.size()-1; i >= 0; --i)
        word[i] = upper((char)word[i]);
    return word;
}

string StringUtility::lower(string word)
{
    for(int i = word.size()-1; i >= 0; --i)
        word[i] = lower((char)word[i]);
    return word;
}
string StringUtility::leadingZero(CRint value){return (value<10?"0":"") + StringUtility::intToString(value);}

void StringUtility::reverse(char* s)
{
  size_t begin = 0;
  size_t end = string(s).size() - 1;

  while (begin < end)
    swap(s[begin++], s[end--]);
}

string StringUtility::substrReplace(string text, CRstring oldSubstr, CRstring newSubstr)
{
    string::size_type found = text.find(oldSubstr,0);

    while(found != string::npos)
    {
        text = text.erase(found,oldSubstr.length());
        text = text.insert(found,newSubstr);
        found = text.find(oldSubstr,found+newSubstr.length()+1);
    }

    return text;

}

/* This is basically the same thing as String.Split in .NET; it splits a string on a token into numerous substrings */
void StringUtility::tokenize(CRstring str,
                      vector<string>& tokens,
                      CRstring delimiters)
{
    tokens.clear();
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void StringUtility::tokenize(CRstring str,
                      vector<string>& tokens,
                      CRstring delimiters,
                      CRuint maxParts)
{
    tokens.clear();
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (tokens.size() < maxParts-1 && (string::npos != pos || string::npos != lastPos))
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
    if (lastPos < str.size())
    {
        tokens.push_back(str.substr(lastPos, str.size()-lastPos));
    }
}

// Combine a Tokenized vector back into a string
string StringUtility::combine(const vector<string>& tokens, CRstring delimiter)
{
	string newString = "";
	unsigned int i;

	for (i=0;i<tokens.size();i++) {
		newString += tokens[i];
		newString += delimiter;
	}

	return newString;
}
