#ifndef __ShakeForFood2__MGameOverScene__
#define __ShakeForFood2__MGameOverScene__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MGameOverScene :public CCLayer
{
private:
    enum kGameOverZ//所有精灵Z轴~Z越大，等于越靠前。
    {
        kZForMap = 0,
        kZForPlayers,
        kZForHP,
        kZForLabel,
        kZForDownMenu,
        kZForJoyStick,
        kZForMyBulletsBase = 100
    };
	CCSprite* maplayer1;
    CCLabelTTF *scoreLabel;
    void restartButtonPressed(cocos2d::CCObject* obj);
public:
	virtual bool init();
	void update(float dt);
	static cocos2d::CCScene* scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(MGameOverScene);
};

#endif /* defined(__ShakeForFood2__MGameOverScene__) */
