#ifndef __ShakeForFood2__MPlayerSelectScene__
#define __ShakeForFood2__MPlayerSelectScene__

#include "cocos2d.h"

using namespace cocos2d;

class MPlayerSelectScene:public CCLayer
{
private:
    enum TagForButtons
    {
        kTagForLeftButton = 40,
        kTagForRightButton,
        kTagForNewGame,
        kTagForExit
    };
    enum currentProfession
    {
        kPSoldier = 0,
        kPArcher,
        kPWizard,
        kPSum
    };
    int nowProfession;
	CCSprite* maplayer1;
    CCSprite* playerSoldier;
    CCSprite* playerWizard;
    CCSprite* playerArcher;
    CCMenu* LRButtonMenu;
    CCLabelTTF* contentText;
    void bbuttonPressed(cocos2d::CCMenuItem* obj);
    void professionChanged();
public:
	virtual bool init();
	void update(float dt);
	static cocos2d::CCScene* scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(MPlayerSelectScene);
};

#endif /* defined(__ShakeForFood2__MStartScene__) */
