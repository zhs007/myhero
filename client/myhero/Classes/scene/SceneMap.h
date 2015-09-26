#ifndef __MYHERO_SCENEMAP__
#define __MYHERO_SCENEMAP__

#include "MapInfo.h"

namespace MyHero {
    
    class SceneMap {
    public:
        SceneMap();
        ~SceneMap();
    public:
        bool init(cocos2d::Node* pRoot, const char* filename);
        
        bool load(const char* filename);
        
        void release();
    protected:
        cocos2d::Texture2D* countTileTex(int tileid, cocos2d::Rect& rect);
    protected:
        MapInfo*                            m_pMapInfo;
        
        std::vector<cocos2d::Node*>         m_pLstLayer;
        std::vector<cocos2d::Texture2D*>    m_pLstTexture;
    };
    
}

#endif /* defined(__MYHERO_SCENEMAP__) */
