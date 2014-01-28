#include "MGameOverScene.h"
#include "GamePlayer.h"
#include "MapScene.h"
#include <math.h>

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

CCScene* MGameOverScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MGameOverScene *layer = MGameOverScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MGameOverScene::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	maplayer1 = CCSprite::create("gameoverBG.jpeg");
	maplayer1->setAnchorPoint(ccp(0,0));
	maplayer1->setPosition( ccp(0,0) );
	this->addChild(maplayer1);
    
	setTouchEnabled(true);
    
    scoreLabel = CCLabelTTF::create("游戏结束", "Arial", 30);
    scoreLabel->setColor(ccc3(255, 255, 255));
    scoreLabel->setPosition(ccp(size.width/2,size.height * 3/4));
    this->addChild(scoreLabel);
    
    CCMenuItemImage* restartButton = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MGameOverScene::restartButtonPressed));
    restartButton->setPosition(size.width/2, size.height/2);
    CCMenu* closeMenu = CCMenu::create(restartButton, NULL);
    closeMenu->setPosition(CCPointZero);
    this->addChild(closeMenu);
    
	//scheduleUpdate();
    
    return true;
}

void MGameOverScene::restartButtonPressed(cocos2d::CCObject* obj)
{
    CCDirector::sharedDirector()->replaceScene(MapScene::scene());
}

void MGameOverScene::update(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
}

void MGameOverScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void MGameOverScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void MGameOverScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

