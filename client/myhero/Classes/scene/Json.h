#ifndef __MYHERO_JSON__
#define __MYHERO_JSON__

#include "json/document.h"

namespace MyHero {
    
    int getAsInt(rapidjson::Value& val, const char* child, int valDefault = 0);
    
    const char* getAsString(rapidjson::Value& val, const char* child, const char* valDefault = "");
}

#endif /* defined(__MYHERO_JSON__) */
