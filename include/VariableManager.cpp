#include "VariableManager.h"
using Penjin::VariableManager;
using std::pair;

VariableManager::VariableManager() : boolData(NULL), intData(NULL), floatData(NULL),  stringData(NULL)
{
    //ctor
}

VariableManager::~VariableManager()
{
    //dtor
    delete boolData;
    delete intData;
    delete floatData;
    delete stringData;
}

bool VariableManager::hasBool(const string& identifier)
{
    if(boolData==NULL)
        return false;
    return (boolData->find(identifier) != boolData->end());
}

bool VariableManager::hasInt(const string& identifier)
{
    if(intData==NULL)
        return false;
    return (intData->find(identifier) != intData->end());
}

bool VariableManager::hasFloat(const string& identifier)
{
    if(floatData==NULL)
        return false;
    return (floatData->find(identifier) != floatData->end());
}

bool VariableManager::hasString(const string& identifier)
{
    if(stringData==NULL)
        return false;
    return (stringData->find(identifier) != stringData->end());
}

void VariableManager::add(const bool& boolVal, const string& identifier)
{
    if(boolData == NULL)
        boolData = new map <string, bool>();
    if(!hasBool(identifier))
        boolData->insert(pair<string,bool>(identifier,boolVal));
}

void VariableManager::add(const int& intVal, const string& identifier)
{
    if(intData == NULL)
        intData = new map <string, int>();
    if(!hasInt(identifier))
        intData->insert(pair<string,int>(identifier,intVal));
}

void VariableManager::add(const float& floatVal, const string& identifier)
{
    if(floatData == NULL)
        floatData = new map <string, float>();
    if(!hasFloat(identifier))
        floatData->insert(pair<string,float>(identifier,floatVal));
}

void VariableManager::add(const string& strVal, const string& identifier)
{
    if(stringData == NULL)
        stringData = new map <string, string>();
    if(!hasString(identifier))
        stringData->insert(pair<string,string>(identifier,strVal));
}

bool VariableManager::getBool(const string& identifier)
{
    if(hasBool(identifier))
    {
        map<string,bool>::iterator it;
        it = boolData->find(identifier);
        return it->second;
    }

    return false;
}

int VariableManager::getInt(const string& identifier)
{
    if(hasInt(identifier))
    {
        map<string,int>::iterator it;
        it = intData->find(identifier);
        return it->second;
    }

    return 0;
}

float VariableManager::getFloat(const string& identifier)
{
    if(hasFloat(identifier))
    {
        map<string,float>::iterator it;
        it = floatData->find(identifier);
        return it->second;
    }
    return 0.0f;
}

string VariableManager::getString(const string& identifier)
{
    if(hasString(identifier))
    {
        map<string,string>::iterator it;
        it = stringData->find(identifier);
        return it->second;
    }
    return "";
}
