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
    
    cocos2d::Texture2D* SceneMap::countTileTex(int tileid, cocos2d::Rect& rect)
    {
        if (m_pMapInfo != NULL) {
            int tw = m_pMapInfo->tileWidth;
            int th = m_pMapInfo->tileHeight;
            
            for (size_t i = 0; i < m_pMapInfo->lstImageInfo.size(); i++) {
                if (tileid >= m_pMapInfo->lstImageInfo[i].firstgid && tileid < m_pMapInfo->lstImageInfo[i].firstgid + m_pMapInfo->lstImageInfo[i].count) {
                    
                    cocos2d::Texture2D* pTex = m_pLstTexture[i];
                    
                    int wnums = m_pMapInfo->lstImageInfo[i].imageWidth / tw;
                    
                    int ty = (tileid - 1) / wnums;
                    int tx = (tileid - 1) % wnums;
                    
                    rect.setRect(tx * tw, ty * th, tw, th);
                    
                    return pTex;
                }
            }
        }
        
        return NULL;
    }
    
    bool SceneMap::init(cocos2d::Node* pRoot, const char* filename)
    {
        load(filename);
        
        if (m_pMapInfo == NULL) {
            return false;
        }
        
        int tw = m_pMapInfo->tileWidth;
        int th = m_pMapInfo->tileHeight;
        
        for (size_t i = 0; i < m_pMapInfo->lstImageInfo.size(); i++) {
            std::string str = "scene/";
            str += m_pMapInfo->lstImageInfo[i].filename;
            
            cocos2d::Texture2D* pTex = cocos2d::Director::getInstance()->getTextureCache()->addImage(str);
            
            m_pLstTexture.push_back(pTex);
        }
        
        for (size_t i = 0; i < m_pMapInfo->lstLayerInfo.size(); i++) {
            cocos2d::Node* pNode = cocos2d::Node::create();
            
            pNode->setAnchorPoint(cocos2d::Vec2(0, 0));
            pNode->setPosition(m_pMapInfo->lstLayerInfo[i].x, m_pMapInfo->lstLayerInfo[i].y);
            
            for (int y = 0; y < m_pMapInfo->lstLayerInfo[i].height; ++y) {
                for (int x = 0; x < m_pMapInfo->lstLayerInfo[i].width; ++x) {
                    cocos2d::Rect rect;
                    cocos2d::Texture2D* pTex = countTileTex(m_pMapInfo->lstLayerInfo[i].pData->data[y][x], rect);
                    if (pTex != NULL) {
                        cocos2d::Sprite* pSpr = cocos2d::Sprite::createWithTexture(pTex, rect);
                        pSpr->setAnchorPoint(cocos2d::Vec2(0, 0));
                        pSpr->setPosition(cocos2d::Vec2(tw * (m_pMapInfo->lstLayerInfo[i].x + x), th * (100 - m_pMapInfo->lstLayerInfo[i].y - y) - 2200));
                        pNode->addChild(pSpr);
                    }
                }
            }
            
            pRoot->addChild(pNode);
            
            m_pLstLayer.push_back(pNode);
        }
        
        return true;
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
