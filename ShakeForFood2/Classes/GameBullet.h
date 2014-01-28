#pragma once
#include "GameSprite.h"
#include "GamePlayer.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameBullet :
	public GameSprite
{
private:
	CCMotionStreak *mystreak;
	int type;
public:
	GameBullet(void);
	~GameBullet();
	GameBullet(const char * s);
	virtual void tick();
	virtual void setPosition(CCPoint mypoint);
	CCMotionStreak *getstreak();
	void setType(int mytype);
	int getType();
	virtual bool collision(GamePlayer * testsprite);
	virtual CCSize getMySize();
};
