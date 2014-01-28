#ifndef __ShakeForFood2__MCoinsGameScene__
#define __ShakeForFood2__MCoinsGameScene__

#include "cocos2d.h"
#import "GameBox.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MCoinsGameScene :public CCLayer
{
private:
	GameBox *box;
	GameTile *selectedTile;
	GameTile *firstOne;
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
    void changeWithTileABandSel(GameTile* a,GameTile* b,SEL_CallFuncND sel);
    void checkSenderandData(GameTile* sender,GameTile* data);
    void backcheckSenderandData(GameTile* sender,GameTile* data);
    void onEnterTransitionDidFinish();
    void afterOneShineTrun(CCSprite* sprite);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(MCoinsGameScene);
};

#endif