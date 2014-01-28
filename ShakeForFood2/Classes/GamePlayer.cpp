#include "GamePlayer.h"
#include "cocos2d.h"
using namespace cocos2d;
GamePlayer::GamePlayer(void)
{
}

GamePlayer::~GamePlayer(void)
{
}
GamePlayer::GamePlayer(const char * s)
{
	mysprite = CCSprite::create(s);
    speed = 3;
    //mystreak = CCMotionStreak::create(1, 2, 50, ccc3(255,255,255), s);
}
void GamePlayer::tick()
{
}
int GamePlayer::getSpeed()
{
    return speed;
}
void GamePlayer::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
bool GamePlayer::iscollision(GameSprite *testsprite)
{
	CCSize ownsize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = (testsprite->getsprite())->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
		return true;
	}
	return false;
}
bool GamePlayer::collision()
{
	return false;
}
CCSize GamePlayer::getMySize()
{
	return mysprite->getContentSize();
}