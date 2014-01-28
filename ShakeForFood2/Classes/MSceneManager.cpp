#include "MSceneManager.h"
#include "MStartScene.h"
#include "MGameOverScene.h"
#include "MCoinsGameScene.h"
#include "MapScene.h"
#include "MPlayerSelectScene.h"

void SceneManager::goPlay(int sceneid)
{
    CCLayer* layer;
    switch (sceneid) {
        case kSceneTagStart:
            layer = MStartScene::create();
            break;
        case kSceneTagMainGame:
            layer = MapScene::create();
            break;
        case kSceneTagGameover:
            layer = MGameOverScene::create();
            break;
        case kSceneTagPlayerSelect:
            layer = MPlayerSelectScene::create();
            break;
        case kSceneTagCoinGame:
            layer = MCoinsGameScene::create();
            break;
        default:
            break;
    }
    SceneManager::go(layer);
}

void SceneManager::go(cocos2d::CCLayer* layer)
{
    CCDirector* director = CCDirector::sharedDirector();
    CCScene* newScene = SceneManager::wrap(layer);
    
    if (director->getRunningScene())
    {
        director->replaceScene(newScene);
    }
    else
    {
        director->runWithScene(newScene);
    }
}

cocos2d::CCScene* SceneManager::wrap(cocos2d::CCLayer* layer)
{
    CCScene* newScene = CCScene::create();
    newScene->addChild(layer);
    return newScene;
}

