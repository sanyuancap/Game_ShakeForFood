#ifndef __ShakeForFood2__MSceneManager__
#define __ShakeForFood2__MSceneManager__

#include "cocos2d.h"

using namespace cocos2d;

enum sceneTag
{
    kSceneTagStart = 0,
    kSceneTagPlayerSelect,
    kSceneTagMainGame,
    kSceneTagCoinGame,
    kSceneTagGameover
};

class SceneManager
{
public:
    static void goPlay(int sceneid = kSceneTagStart);
private:
    static void go(cocos2d::CCLayer* layer);
    static CCScene* wrap(CCLayer* layer);
};

#endif
