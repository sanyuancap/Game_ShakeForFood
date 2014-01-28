#ifndef __ShakeForFood2__MStartScene__
#define __ShakeForFood2__MStartScene__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MStartScene:public CCLayer
{
private:
    enum TagForButtons
    {
        kTagForTouchStart = 40,
        kTagForNewGame,
        kTagForExit
    };
	CCSprite* maplayer1;
    CCSprite* logoTitle;
    CCMenu* mainMenu;
    CCMenu* subMenu;
    void bbuttonPressed(cocos2d::CCMenuItem* obj);
public:
	virtual bool init();
	void update(float dt);
	static cocos2d::CCScene* scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(MStartScene);
};

#endif /* defined(__ShakeForFood2__MStartScene__) */
