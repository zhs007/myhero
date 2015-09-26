#include "TMJLoader.h"
#include "Json.h"

namespace MyHero {
    
    MapInfo* TMJLoader::load(const char* filename)
    {
        cocos2d::Data dat = cocos2d::FileUtils::getInstance()->getDataFromFile(filename);
        rapidjson::Document doc;
        
        doc.Parse((char*)dat.getBytes());
        
        if (doc.IsObject()) {
            MapInfo* pMapInfo = new MapInfo;
            
            pMapInfo->height = getAsInt(doc, "height");
            pMapInfo->width = getAsInt(doc, "width");
            
            pMapInfo->tileWidth = getAsInt(doc, "tilewidth");
            pMapInfo->tileHeight = getAsInt(doc, "tileheight");
            
            if (doc.HasMember("layers") && doc["layers"].IsArray()) {
                rapidjson::Value& layers = doc["layers"];
                
                for (rapidjson::SizeType i = 0; i < layers.Size(); ++i) {
                    if (layers[i].IsObject()) {
                        LayerInfo li;
                        
                        li.name = getAsString(layers[i], "name");
                        
                        li.x = getAsInt(layers[i], "x");
                        li.y = getAsInt(layers[i], "y");
                        li.width = getAsInt(layers[i], "width");
                        li.height = getAsInt(layers[i], "height");
                        
                        li.pData = NewLayerData(li.width, li.height);
                        
                        pMapInfo->lstLayerInfo.push_back(li);
                    }
                }
            }
            
            if (doc.HasMember("tilesets") && doc["tilesets"].IsArray()) {
                rapidjson::Value& tilesets = doc["tilesets"];
                
                for (rapidjson::SizeType i = 0; i < tilesets.Size(); ++i) {
                    if (tilesets[i].IsObject()) {
                        ImageInfo ii;
                        
                        ii.filename = getAsString(tilesets[i], "image");
                        
                        ii.firstgid = getAsInt(tilesets[i], "firstgid");
                        ii.count = getAsInt(tilesets[i], "tilecount");
                        
                        pMapInfo->lstImageInfo.push_back(ii);
                    }
                }
            }
            
            return pMapInfo;
        }
        
        return NULL;
    }
    
    void TMJLoader::free(MapInfo* pInfo)
    {
        if (pInfo != NULL) {
            
            for (size_t i = 0; i < pInfo->lstLayerInfo.size(); ++i) {
                DeleteLayerData(pInfo->lstLayerInfo[i].pData);
            }
            
            delete pInfo;
        }
    }
}
