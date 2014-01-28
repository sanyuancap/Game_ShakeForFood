#include "GameEnemy.h"
#include <math.h>

GameEnemy::GameEnemy(void)
{
}

GameEnemy::~GameEnemy(void) 
{
}
GameEnemy::GameEnemy(const char * s)
{
	mysprite = CCSprite::create(s);
    chooseflytype();
	state = 0;
}
void GameEnemy::setDead()
{
    mysprite->stopAllActions();
    mysprite->setVisible(false);
	state = -1;
}
void GameEnemy::chooseflytype()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize pSize = mysprite->getContentSize();
    float minHeight = 90 + pSize.height/2;//90 as downmenu height
    float maxHeight = size.height - pSize.height/2;
    float x = size.width + pSize.width/2;
    float y = CCRANDOM_0_1() * (maxHeight - minHeight) + minHeight;
    mysprite->setPosition(ccp(x,y));
    CCActionInterval *actionTo1 = CCMoveBy::create(2, CCPointMake(-(size.width + mysprite->getContentSize().width ),0));
    mysprite->runAction(CCSequence::create(actionTo1,NULL));
}
void GameEnemy::restart()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int x = size.width;
    int y = CCRANDOM_0_1() * (float)size.height;
	mysprite->setPosition(ccp(x,y));
	mysprite->setVisible(true);
	chooseflytype();
	state = 0;
}
void GameEnemy::tick()
{
	switch(state){
        case -1:
            break;
        case 0:
            CCPoint mypoint = mysprite->getPosition();
            break;
	}
}
void GameEnemy::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
CCMotionStreak *GameEnemy::getstreak()
{
	return mystreak;
}
bool GameEnemy::iscollision(GameSprite *testsprite)
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
bool GameEnemy::collision(GamePlayer *testsprite)
{
	CCSize ownsize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = (testsprite->getsprite())->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
		if(ownp.y + ownsize.height/2 >= otherp.y - othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y - othersize.height/2){
			otherp.y = ownp.y + ownsize.height/2 + othersize.height/2;
			testsprite->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.y + ownsize.height/2 >= otherp.y + othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y + othersize.height/2){
            otherp.y = ownp.y - ownsize.height/2 - othersize.height/2;
            testsprite->setPosition(ccp(otherp.x,otherp.y));
            return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x - othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x - othersize.width/2){
			otherp.x = ownp.x + ownsize.width/2 + othersize.width/2;
			testsprite->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x + othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x + othersize.width/2){
            otherp.x = ownp.x - ownsize.width/2 - othersize.width/2;
            testsprite->setPosition(ccp(otherp.x,otherp.y));
            return true;
	    }
	}
	return false;
}
bool GameEnemy::collisionwithbullet(GameBullet *testsprite)
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
CCSize GameEnemy::getMySize()
{
	return mysprite->getContentSize();
}
