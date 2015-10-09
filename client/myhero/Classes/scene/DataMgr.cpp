#include "DataMgr.h"

namespace MyHero {
    
    std::map<std::string, DataValue*>& getDefaultMap()
    {
        static std::map<std::string, DataValue*> s_map;
        
        return s_map;
    }
    
    DataValue* DataValueMgr::newDataValue(DataValue::TYPE t)
    {
        //DataValue* pVal = NULL;
        
        switch (t)
        {
            case DataValue::TYPE_OBJECT:
                return new DataValue_Object();
            case DataValue::TYPE_INT:
                return new DataValue_Int();
            case DataValue::TYPE_FLOAT:
                return new DataValue_Float();
            case DataValue::TYPE_ARRAY:
                return new DataValue_Array();
            case DataValue::TYPE_STRING:
                return new DataValue_Str("");
            case DataValue::TYPE_NONE:
                return NULL;
        }
        
        return NULL;
    }
    
    void DataValueMgr::deleteDataValue(DataValue* pVal)
    {
        pVal->release();
        
        delete pVal;
    }
}
