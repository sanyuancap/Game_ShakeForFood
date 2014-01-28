#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"
#include "GamePlayer.h"
#include "GameBullet.h"
#include "GameEnemy.h"
#include "HRocker.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MapScene :public CCLayer
{
private:
    enum spriteZ//所有精灵Z轴~Z越大，等于越靠前。
    {
        kZForMap = 0,
        kZForPlayers,
        kZForHP,
        kZForLabel,
        kZForDownMenu,
        kZForJoyStick,
        kZForMyBulletsBase = 100
    };
    CCArray* playerBulletList;
	GamePlayer* player;
    CCArray* enemyList;
    CCPoint targetPoint;
    HRocker* joyStick;
    
	int stepindex;
	int playerlife;
    int playerscore;
	CCSprite* maplayer1;
	CCSprite* maplayer2;
	CCSprite* lifeHP;
    CCSprite* manaHP;
    CCSprite* bottomMenu;
    CCLabelTTF *scoreLabel;
    CCSprite *spRocker;
    CCSprite *spRockerBG;
public:
	virtual bool init(); 
	void updateLife(int deltalife);
	void enemyrestart(CCTime dt);
	void playerFire(CCTime dt);
	void update(float dt);
	static cocos2d::CCScene* scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(MapScene);
};
#endif