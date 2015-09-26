#ifndef __MYHERO_SCENEMAP__
#define __MYHERO_SCENEMAP__

#include "MapInfo.h"

namespace MyHero {
    
    class SceneMap {
    public:
        SceneMap();
        ~SceneMap();
    public:
        bool load(const char* filename);
        
        void release();
    protected:
        MapInfo*        m_pMapInfo;
    };
    
}

#endif /* defined(__MYHERO_SCENEMAP__) */
