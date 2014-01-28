#include "GameBullet.h"
#include <math.h>

GameBullet::GameBullet(void)
{
}

GameBullet::~GameBullet(void)
{
}
GameBullet::GameBullet(const char * s)
{
	mysprite = CCSprite::create(s);
	//mysprite->setAnchorPoint(ccp(0.5,0));
	state = 0;
}
void GameBullet::tick()
{
	switch(type){
	case 0:
	   switch(state){
	   case -1:
	      break;
	   case 0:
	      CCPoint ownp = mysprite->getPosition();
	      mysprite->setPosition(ccp(ownp.x + 3,ownp.y));
	      break;
	   }
	   break;
	case 1:
	   switch(state){
	   case -1:
	      break;
	   case 0:
	      CCPoint ownp = mysprite->getPosition();
	      mysprite->setPosition(ccp(ownp.x - 3,ownp.y));
	      break;
	   }
	   break;
	}
}
void GameBullet::setType(int mytype)
{
    type = mytype;
}
int GameBullet::getType()
{
	return type;
}
void GameBullet::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
CCMotionStreak *GameBullet::getstreak()
{
	return mystreak;
}
bool GameBullet::collision(GamePlayer *testsprite)
{
	return false;
}
CCSize GameBullet::getMySize()
{
	return mysprite->getContentSize();
}
