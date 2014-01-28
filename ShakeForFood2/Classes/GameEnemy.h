#pragma once
#include "GameSprite.h"
#include "GameBullet.h"
#include "cocos2d.h"
using namespace cocos2d;
class GameEnemy :
	public GameSprite
{
private:
	CCMotionStreak *mystreak;
public:
	GameEnemy(void);
	~GameEnemy(void);
	GameEnemy(const char * s);
	void setDead();
	void restart();
	virtual void tick();
	virtual void setPosition(CCPoint mypoint);
	bool iscollision(GameSprite *testsprite);
	CCMotionStreak *getstreak();
	void chooseflytype();
	virtual bool collision(GamePlayer * testsprite);
	virtual CCSize getMySize();
	bool collisionwithbullet(GameBullet *testsprite);
};
