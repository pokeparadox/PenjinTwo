#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include "Singleton.h"
#include <string>
#include <map>
using std::string;
using std::map;

namespace Penjin
{
    class VariableManager : public Object
    {
        public:
            VariableManager();

            void add(const bool& boolVal, const string& identifier);
            void add(const int& intVal, const string& identifier);
            void add(const float& floatVal, const string& identifier);
            void add(const string& strValue, const string& identifier);

            bool hasBool(const string& identifier);
            bool hasInt(const string& identifier);
            bool hasFloat(const string& identifier);
            bool hasString(const string& identifier);

            bool getBool(const string& identifier);
            int getInt(const string& identifier);
            float getFloat(const string& identifier);
            string getString(const string& identifier);


        protected:
        private:
            virtual ~VariableManager();
            map <string, bool>* boolData;
            map <string, int>* intData;
            map <string, float>* floatData;
            map <string, string>*  stringData;
    };

    typedef Singleton<VariableManager> VarMan;

}

#endif // VARIABLEMANAGER_H
