#ifndef __MYHERO_TMJLOADER__
#define __MYHERO_TMJLOADER__

#include "MapInfo.h"

namespace MyHero {
    
    class TMJLoader {
    public:
        static MapInfo* load(const char* filename);
        
        static void free(MapInfo* pInfo);
    };
    
}

#endif /* defined(__MYHERO_TMJLOADER__) */
