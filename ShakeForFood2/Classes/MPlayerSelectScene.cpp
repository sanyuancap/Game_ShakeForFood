//
//  MPlayerSelectScene.cpp
//  ShakeForFood2
//
//  Created by apple on 12-10-15.
//
//

#include "MPlayerSelectScene.h"
#include "MSceneManager.h"
#include <math.h>

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

CCScene* MPlayerSelectScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MPlayerSelectScene *layer = MPlayerSelectScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MPlayerSelectScene::init()
{
    nowProfession = 0;
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	maplayer1 = CCSprite::create("selectbg.jpeg");
	maplayer1->setAnchorPoint(ccp(0,0));
	maplayer1->setPosition( ccp(0,0) );
	this->addChild(maplayer1);
    
    playerSoldier = CCSprite::create("playersoldier.png");
    playerSoldier->setAnchorPoint(ccp(0,0));
    this->addChild(playerSoldier);
    
    playerArcher = CCSprite::create("playerHunter.png");
    playerArcher->setAnchorPoint(ccp(0,0));
    this->addChild(playerArcher);
    
    playerWizard = CCSprite::create("playerWizard.png");
    playerWizard->setAnchorPoint(ccp(0,0));
    this->addChild(playerWizard);
    
    CCMenuItemImage* leftButton =
    CCMenuItemImage::create("AAleft.png",
                            "AAleft.png",
                            this,
                            menu_selector(MPlayerSelectScene::bbuttonPressed));
    leftButton->setTag(kTagForLeftButton);
    leftButton->setPosition(leftButton->getContentSize().width/2, size.height/2);
    
    CCMenuItemImage* rightButton =
    CCMenuItemImage::create("AAright.png",
                            "AAright.png",
                            this,
                            menu_selector(MPlayerSelectScene::bbuttonPressed));
    rightButton->setTag(kTagForRightButton);
    rightButton->setPosition(size.width - rightButton->getContentSize().width/2, size.height/2);
    
    LRButtonMenu = CCMenu::create(leftButton, rightButton,NULL);
    LRButtonMenu->setPosition(CCPointZero);
    this->addChild(LRButtonMenu);
    
    contentText = CCLabelTTF::create("Hello milk", "Marker Felt", 20, CCSize(size.width/2 - leftButton->getContentSize().width/2, size.height), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    contentText->setAnchorPoint(ccp(0,0));
    contentText->setPosition(ccp(leftButton->getContentSize().width , 0));
    this->addChild(contentText);
    
	setTouchEnabled(true);
    
    this->professionChanged();
    
    return true;
}

void MPlayerSelectScene::bbuttonPressed(cocos2d::CCMenuItem* obj)
{
    switch (obj->getTag()) {
        case kTagForLeftButton:
            nowProfession--;
            if(nowProfession < 0)
                nowProfession += kPSum;
            this->professionChanged();
            break;
        case kTagForRightButton:
            nowProfession++;
            if(nowProfession >= kPSum)
                nowProfession -= kPSum;
            this->professionChanged();
            break;
        case kTagForNewGame:
            SceneManager::goPlay(kSceneTagMainGame);
            break;
        case kTagForExit:
            break;
        default:
            break;
    }
}

void MPlayerSelectScene::professionChanged()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    playerSoldier->setVisible(false);
    playerArcher->setVisible(false);
    playerWizard->setVisible(false);
    
    CCSprite* cacheSprite;
    
    CCString *cacheText;
    
    switch (nowProfession) {
        case kPSoldier:
            cacheSprite = playerSoldier;
            cacheText = CCString::create("战士\n生命回复 10\n攻击力 10\n生命值 100\n按得越快，战士的子弹越大！");
            break;
        case kPArcher:
            cacheSprite = playerArcher;
            cacheText = CCString::create("猎人\n生命回复 5\n攻击力 10\n生命值 100\n拥有一个可以自动攻击敌人的宝宝！");
            break;
        case kPWizard:
            cacheText = CCString::create("巫师\n生命回复 5\n攻击力 10\n生命值 50\n可以消耗魔法进行大范围爆炸伤害！");
            cacheSprite = playerWizard;
            break;
        default:
            cacheSprite = playerSoldier;
            break;
    }
    cacheSprite->setVisible(true);
    cacheSprite->setPosition(ccp(size.width,60));
    cacheSprite->runAction(CCMoveBy::create(0.3, ccp(-size.width/2,0)));
    
    contentText->setString(cacheText->getCString());
    
}

void MPlayerSelectScene::update(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
}

void MPlayerSelectScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void MPlayerSelectScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void MPlayerSelectScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}


