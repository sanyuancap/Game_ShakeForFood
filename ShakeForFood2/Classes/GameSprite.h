#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class GameSprite :
	public CCNode
{
protected:
	CCSprite *mysprite;
	int state;
public:
	GameSprite(void);
	~GameSprite(void);
	GameSprite(char *s);
	virtual void tick();
	virtual void setPosition(CCPoint mypoint);
	CCSprite * getsprite();
	void setState(int mystate);
	int getState();
	virtual bool collision();
	virtual CCSize getMySize();
};
