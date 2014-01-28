//
//  MStartScene.cpp
//  ShakeForFood2
//
//  Created by apple on 12-10-12.
//
//

#include "MStartScene.h"
#include "GamePlayer.h"
#include "MapScene.h"
#include "MSceneManager.h"
#include <math.h>

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

CCScene* MStartScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MStartScene *layer = MStartScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MStartScene::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	maplayer1 = CCSprite::create("mainBG.png");
	maplayer1->setAnchorPoint(ccp(0,0));
	maplayer1->setPosition( ccp(0,0) );
	this->addChild(maplayer1);
    
	setTouchEnabled(true);
    
    logoTitle = CCSprite::create("titleLogo.png");
    logoTitle->setPosition(ccp(size.width + logoTitle->getContentSize().width/2,
                               size.height * 3/4));
    this->addChild(logoTitle);
    logoTitle->runAction(CCMoveBy::create(0.5, ccp(-size.width/2,0)));
    
    {
        CCMenuItemFont* touchToStart =
        CCMenuItemFont::create("开始",
                               this,
                               menu_selector(MStartScene::bbuttonPressed));
        touchToStart->setTag(kTagForTouchStart);
        touchToStart->setPosition(size.width/2, size.height/3);
        mainMenu = CCMenu::create(touchToStart, NULL);
        mainMenu->setPosition(CCPointZero);
        this->addChild(mainMenu);
    }
    
    {
        CCMenuItemFont* newgameM =
        CCMenuItemFont::create("新游戏",
                               this,
                               menu_selector(MStartScene::bbuttonPressed));
        newgameM->setTag(kTagForNewGame);
        newgameM->setPosition(size.width/2, size.height/3);
        
        CCMenuItemFont* exitGameN =
        CCMenuItemFont::create("退出",
                               this,
                               menu_selector(MStartScene::bbuttonPressed));
        exitGameN->setTag(kTagForExit);
        exitGameN->setPosition(size.width/2, size.height / 5);
        
        subMenu = CCMenu::create(newgameM, exitGameN,NULL);
        subMenu->setPosition(CCPointZero);
        this->addChild(subMenu);
        subMenu->setVisible(false);
    }
    
    return true;
}

void MStartScene::bbuttonPressed(cocos2d::CCMenuItem* obj)
{
    //CCDirector::sharedDirector()->replaceScene(MapScene::scene());
    switch (obj->getTag()) {
        case kTagForTouchStart:
            mainMenu->setVisible(false);
            subMenu->setVisible(true);
            break;
        case kTagForNewGame:
            SceneManager::goPlay(kSceneTagPlayerSelect);
            break;
        case kTagForExit:
            break;
        default:
            break;
    }
}

void MStartScene::update(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
}

void MStartScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void MStartScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void MStartScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}


