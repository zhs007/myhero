#include "MapInfo.h"

namespace MyHero {
    
    LayerData* NewLayerData(int w, int h)
    {
        LayerData* pData = (LayerData*)malloc(sizeof(int*) * h + sizeof(int) * w * h);
        int* pBuf = (int*)((unsigned char*)pData + sizeof(int*) * h);
        
        for (int y = 0; y < h; ++y) {
            pData->data[y] = pBuf;
            pBuf += w;
        }
        
        return pData;
    }
    
    void DeleteLayerData(LayerData* pData)
    {
        free(pData);
    }
    
}