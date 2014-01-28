#pragma once
#include "GameSprite.h"
#include "cocos2d.h"
using namespace cocos2d;
class GamePlayer :
	public GameSprite
{
private:
	int state;
    float speed;
public:
	GamePlayer(void);
	~GamePlayer(void);
	GamePlayer(const char * s);
	virtual void tick();
	virtual void setPosition(CCPoint mypoint);
	bool iscollision(GameSprite *testsprite);
	virtual bool collision();
	virtual CCSize getMySize();
    
    int getSpeed();
};
