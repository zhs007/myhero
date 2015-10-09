#ifndef __MYHERO_DATAMGR__
#define __MYHERO_DATAMGR__

#include <string>
#include <vector>
#include <map>

namespace MyHero {
    
    class DataValue;
    typedef std::map<std::string, DataValue*>::iterator DataValueIterator;
    class DataValueMgr;
    
    static std::map<std::string, DataValue*>& getDefaultMap();
    
    class DataValue {
        friend class DataValueMgr;
    public:
        enum TYPE{
            TYPE_NONE      =   0,
            TYPE_STRING    =   1,
            TYPE_INT       =   2,
            TYPE_FLOAT     =   3,
            TYPE_ARRAY     =   4,
            TYPE_OBJECT    =   5
        };
    public:
        DataValue::TYPE getType() {
            return m_type;
        }
    public:
        virtual int getAsInt() {
            return 0;
        }
        
        virtual float getAsFloat() {
            return 0.0f;
        }
        
        virtual std::string getAsString() {
            return "";
        }
        
        virtual int getChildNums() {
            return 0;
        }
        
        virtual DataValue* getChild(int index) {
            return NULL;
        }
        
        virtual DataValue* getChild(const char* str) {
            return NULL;
        }
        
        virtual void pushChild(DataValue* pVal) {
            
        }
        
        virtual void setChildWithIndex(int index, DataValue* pVal) {
            
        }
        
        virtual void setChild(const char* strName, DataValue* pVal) {
        }
        
        virtual DataValueIterator begin() {
            return getDefaultMap().begin();
        }
        
        virtual DataValueIterator end() {
            return getDefaultMap().end();
        }
        
        virtual void release() {
        }
    protected:
        DataValue(DataValue::TYPE t) : m_type(t) {}
        virtual ~DataValue() {}
    protected:
        TYPE        m_type;
    };
    
    class DataValueMgr {
    public:
        static DataValueMgr& getSingleton() {
            static DataValueMgr s_mgr;
            
            return s_mgr;
        }
    public:
        DataValue* newDataValue(DataValue::TYPE t);
        
        void deleteDataValue(DataValue* pVal);
    private:
        DataValueMgr() {
            m_pRoot = newDataValue(DataValue::TYPE_OBJECT);
        }
        ~DataValueMgr() {
            deleteDataValue(m_pRoot);
        }
    protected:
        DataValue*      m_pRoot;
    };
    
    class DataValue_Int : public DataValue {
        friend class DataValueMgr;
    public:
        virtual int getAsInt() {
            return m_iVal;
        }
        
        virtual float getAsFloat() {
            return m_iVal;
        }
        
        virtual std::string getAsString() {
            char str[16];
            sprintf(str, "%d", m_iVal);
            return str;
        }
    protected:
        DataValue_Int(int def = 0) : DataValue(DataValue::TYPE_INT), m_iVal(def) {}
        virtual ~DataValue_Int() {}
    protected:
        int         m_iVal;
    };
    
    class DataValue_Str : public DataValue {
        friend class DataValueMgr;
    public:
        virtual std::string getAsString() {
            return m_strVal;
        }
    protected:
        DataValue_Str(const char* str) : DataValue(DataValue::TYPE_STRING), m_strVal(str) {}
        virtual ~DataValue_Str() {}
    protected:
        std::string         m_strVal;
    };
    
    class DataValue_Float : public DataValue {
        friend class DataValueMgr;
    public:
        virtual int getAsInt() {
            return m_fVal;
        }
        
        virtual float getAsFloat() {
            return m_fVal;
        }
        
        virtual std::string getAsString() {
            char str[16];
            sprintf(str, "%f", m_fVal);
            return str;
        }
    protected:
        DataValue_Float(float def = 0.0f) : DataValue(DataValue::TYPE_FLOAT), m_fVal(def) {}
        virtual ~DataValue_Float() {}
    protected:
        float         m_fVal;
    };
    
    class DataValue_Array : public DataValue {
        friend class DataValueMgr;
    public:
        virtual int getChildNums() {
            return (int)m_array.size();
        }
        
        virtual DataValue* getChild(int index) {
            if (index >= 0 && index < m_array.size()) {
                return m_array[index];
            }
            
            return NULL;
        }
        
        virtual void pushChild(DataValue* pVal) {
            m_array.push_back(pVal);
        }
        
        virtual void setChildWithIndex(int index, DataValue* pVal) {
            if (index >= 0 && index < m_array.size()) {
                m_array[index] = pVal;
            }
            else {
                m_array.resize(index + 1);
                
                m_array[index] = pVal;
            }
        }
        
        virtual void release() {
            for (std::vector<DataValue*>::iterator it = m_array.begin(); it != m_array.end(); ++it) {
                (*it)->release();
            }
            m_array.clear();
        }
    protected:
        DataValue_Array() : DataValue(DataValue::TYPE_ARRAY) {}
        virtual ~DataValue_Array() {}
    protected:
        std::vector<DataValue*>     m_array;
    };
    
    class DataValue_Object : public DataValue {
        friend class DataValueMgr;
    public:
        virtual DataValue* getChild(const char* str) {
            std::map<std::string, DataValue*>::iterator it = m_obj.find(str);
            if (it != m_obj.end()) {
                return it->second;
            }
            
            return NULL;
        }
        
        virtual void setChild(const char* str, DataValue* pVal) {
            std::map<std::string, DataValue*>::iterator it = m_obj.find(str);
            if (it != m_obj.end()) {
                it->second = pVal;
                
                return ;
            }
            
            std::pair<std::string, DataValue*> p(str, pVal);
            m_obj.insert(p);
        }
        
        virtual int getChildNums() {
            return (int)m_obj.size();
        }
        
        virtual DataValueIterator begin() {
            return m_obj.begin();
        }
        
        virtual DataValueIterator end() {
            return m_obj.end();
        }
        
        virtual void release() {
            for (std::map<std::string, DataValue*>::iterator it = m_obj.begin(); it != m_obj.end(); ++it) {
                it->second->release();
            }
            m_obj.clear();
        }
    protected:
        DataValue_Object() : DataValue(DataValue::TYPE_OBJECT) {}
        virtual ~DataValue_Object() {}
    protected:
        std::map<std::string, DataValue*>       m_obj;
    };
}

#endif /* defined(__MYHERO_DATAMGR__) */
