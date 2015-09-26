#include "SceneMap.h"
#include "TMJLoader.h"

namespace MyHero {
    
    SceneMap::SceneMap()
        : m_pMapInfo(NULL)
    {
        
    }
    
    SceneMap::~SceneMap()
    {
        
    }
    
    bool SceneMap::load(const char* filename)
    {
        m_pMapInfo = TMJLoader::load(filename);
        
        return true;
    }
    
    void SceneMap::release()
    {
        if (m_pMapInfo != NULL) {
            TMJLoader::free(m_pMapInfo);
            
            m_pMapInfo = NULL;
        }
    }
}
