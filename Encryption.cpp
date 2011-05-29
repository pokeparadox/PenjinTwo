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
#include "Encryption.h"
//	Shouldn't have to change these values.
#define LIMIT 256
#define RANDLIM 128

Encryption::Encryption()
{
	//	Get and assign the encryption key.
	key = wrapValue(Random::randSeed(),LIMIT);

	//	Set the seed to this key to make sure.
	rand.setSeed(key);

	//	Now setup the range of the rand gen. (ASCII range)
	rand.setLimits(0,RANDLIM);
}

Encryption::~Encryption()
{
}

string Encryption::decryptBuffer(string buff)
{
	if(!buff.size())
		return buff;
	//	create output strng
	string output;
	int currChar = 0;

	//	first find the encryption key
	//	It is the char before the NULL terminator
	while(buff[currChar] != 0)
	{
		++currChar;
	}

	//	Now get the key from the string
	this->key = buff[currChar-1];

	//	We have the key, so we can remove it from the string.
	buff[currChar-1] = 0;

	//	Reset the count.
	currChar = 0;

	//	seed random number gen with this key
	rand.setSeed(key);

	//	Reverse the encryption
	while(buff[currChar] != 0)
	{
		char temp = 0;

		//	Decode each character one at a time.
		while(temp == 0)
		{
			temp = wrapValue((int)buff[currChar] - (int)rand.nextInt(),LIMIT);
		}

		//	add decoded characters to output string.
		output += temp;
		++currChar;
	}
	return output;
}

string Encryption::encryptBuffer(CRstring buff)
{
	//	Create an encryption key.
	//key = (char)wrapValue((int)randGen.randSeed(),(CRint)LIMIT);
	rand.setSeed(key);

	//	create output string
	string output;

	//	go through the string
	int currChar = 0;
	while(buff[currChar] !=0)
	{
		char temp = 0;

		//	Encrypt each character one at a time.
		while(temp == 0)
		{
			temp = (char)wrapValue((int)buff[currChar] + rand.nextInt(),LIMIT);
		}

		//	Add the encrypted chars to the output string.
		output += temp;
		++currChar;
	}

	//	Save encryption key to string
	output += key;

	//	Copy accross null terminator
	output += '\0';
return output;
}

