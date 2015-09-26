#include "Json.h"

namespace MyHero {
    
    int getAsInt(rapidjson::Value& val, const char* child, int valDefault)
    {
        if (val.HasMember(child)) {
            if (val[child].IsInt64()) {
                return (int)val[child].GetInt64();
            }
            
            if (val[child].IsInt()) {
                return val[child].GetInt();
            }
            
            if (val[child].IsString()) {
                return atoi(val[child].GetString());
            }
        }
        
        return valDefault;
    }
    
    const char* getAsString(rapidjson::Value& val, const char* child, const char* valDefault)
    {
        if (val.HasMember(child)) {
            if (val[child].IsString()) {
                return val[child].GetString();
            }
        }
        
        return valDefault;
    }
}