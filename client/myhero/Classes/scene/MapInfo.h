#ifndef __MYHERO_MAPINFO__
#define __MYHERO_MAPINFO__

#include <string>
#include <vector>

namespace MyHero {
    
    struct LayerData {
        int*            data[1];
    };
    
    struct LayerInfo {
        std::string     name;
        
        int             x, y;
        
        int             width;
        int             height;
        
        LayerData*      pData;
    };
    
    struct ImageInfo {
        std::string     filename;
        
        int             firstgid;
        int             count;
    };
    
    struct MapInfo {
        std::vector<ImageInfo>      lstImageInfo;
        std::vector<LayerInfo>      lstLayerInfo;
        
        int                         width;
        int                         height;
        
        int                         tileWidth;
        int                         tileHeight;
    };
    
    LayerData* NewLayerData(int w, int h);
    
    void DeleteLayerData(LayerData* pData);
}


#endif
