#include "GameSprite.h"
#include "cocos2d.h"
using namespace cocos2d;
GameSprite::GameSprite(void)
{
}

GameSprite::~GameSprite(void)
{
}
GameSprite::GameSprite(char * s)
{
	mysprite = CCSprite::create(s);
}
void GameSprite::tick()
{
}
void GameSprite::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
CCSprite* GameSprite::getsprite()
{
	return mysprite;
}
void GameSprite::setState(int mystate)
{
	state = mystate;
}
int GameSprite::getState()
{
	return state;
}
bool GameSprite::collision()
{
	return false;
}
CCSize GameSprite::getMySize()
{
	return mysprite->getContentSize();
}