#include "MapScene.h"
#include "GamePlayer.h"
#include "MSceneManager.h"
#include <math.h>

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

CCScene* MapScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MapScene *layer = MapScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	player = new GamePlayer("player.png");
	player->setPosition(ccp(30,120));
	this->addChild((player->getsprite()),kZForPlayers,0);
    
    targetPoint = player->getPosition();
    
    enemyList = CCArray::createWithCapacity(20);// most 20 bullets
    enemyList->retain();
    
	maplayer1 = CCSprite::create("back_img1.png");
    maplayer2 = CCSprite::create("back_img1.png");
	maplayer1->setAnchorPoint(ccp(0,0));
	maplayer2->setAnchorPoint(ccp(0,0));
	maplayer1->setPosition( ccp(0,0) );
	maplayer2->setPosition( ccp(242,0) );
	this->addChild(maplayer1, kZForMap ,1);
	this->addChild(maplayer2, kZForMap ,2);
    
    //HP rect x 20-30 y 5-50
	playerlife = 100;
    lifeHP = CCSprite::create("blood.png");
    lifeHP->setAnchorPoint(ccp(0, 0));
    lifeHP->setPosition(ccp(95, 20));
    this->addChild(lifeHP,kZForHP,200);
    manaHP = CCSprite::create("Mana.png");
    manaHP->setAnchorPoint(ccp(0,0));
    manaHP->setPosition(ccp(95,0));
    this->addChild(manaHP,kZForHP,200);
    
    bottomMenu = CCSprite::create("DownMenu.png");
    bottomMenu->setPosition(ccp(bottomMenu->getContentSize().width/2,bottomMenu->getContentSize().height/2));
    this->addChild(bottomMenu,kZForDownMenu,100);
    
	setTouchEnabled(true);
	stepindex = -1;
    
    playerBulletList = CCArray::createWithCapacity(20);// most 20 bullets
    playerBulletList->retain();
    
    scoreLabel = CCLabelTTF::create("0", "Arial", 30);
    scoreLabel->setAnchorPoint(ccp(0, 0));
    scoreLabel->setColor(ccc3(255, 255, 255));
    scoreLabel->setPosition(ccp(0,290));
    this->addChild(scoreLabel,kZForLabel,301);
    
    spRocker=CCSprite::create("LeftPoint.png");//摇杆
    spRockerBG=CCSprite::create("LeftPlane.png");//摇杆背景
    joyStick = HRocker::HRockerWithCenter(ccp(40.0f,30.0f),30.0f ,spRocker ,spRockerBG,false);//创建摇杆
    this->addChild(joyStick,kZForJoyStick);//摇杆添加到layer中
    
	scheduleUpdate();
    schedule(schedule_selector(MapScene::playerFire), 0.3f);
    schedule(schedule_selector(MapScene::enemyrestart), 0.5f);
    //unschedule(schedule_selector(MapScene::resettouch));
    
    return true;
}
void MapScene::updateLife(int deltalife)
{
    
    playerlife += deltalife;
    if(playerlife <= 0)
    {
        playerlife = 0;
        SceneManager::goPlay(kSceneTagGameover);
    }
    else if(playerlife >= 100)
        playerlife = 100;
    lifeHP->setScaleX(playerlife/100.0);
}

void MapScene::update(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint maplayer1p = maplayer1->getPosition();
	CCPoint maplayer2p = maplayer2->getPosition();
	maplayer1->setPosition(ccp(maplayer1p.x - 5,maplayer1p.y));
	maplayer2->setPosition(ccp(maplayer2p.x - 5,maplayer2p.y));
	if(maplayer2p.x < 0){
        float temp = maplayer2p.x + 242;
        maplayer1->setPosition(ccp(temp,maplayer1p.y));
	}
	if(maplayer1p.x < 0){
        float temp = maplayer1p.x + 242;
        maplayer2->setPosition(ccp(temp,maplayer2p.y));
	}
    
    for(int j = enemyList->count() - 1; j >= 0; j--)
    {
        GameEnemy *enemy = (GameEnemy *)(enemyList->objectAtIndex(j));
        if(enemy->getState() != -1)
        {
            enemy->tick();
            for(int i = playerBulletList->count() - 1; i >= 0; i--)
            {
                GameBullet * mybullet = (GameBullet *)(playerBulletList->objectAtIndex(i));
                if(enemy->collisionwithbullet(mybullet))
                {
                    enemyList->removeObjectAtIndex(j);
                    this->removeChild(enemy->getsprite(), true);
                    delete enemy;
                    playerBulletList->removeObjectAtIndex(i);
                    this->removeChild(mybullet->getsprite(),true);
                    delete mybullet;
                    playerscore++;
                    this->updateLife(1);
                    CCString *scoreLa = CCString::createWithFormat("%i",playerscore);
                    scoreLabel->setString(scoreLa->getCString());
                    break;
                }
            }
        }
    }
    
    for(int i = 0; i < playerBulletList->count(); i++)
    {
        GameBullet* mybullet = (GameBullet *)(playerBulletList->objectAtIndex(i));
        mybullet->tick();
        if((mybullet->getsprite())->getPosition().x > size.width){
            playerBulletList->removeObjectAtIndex(i);
            this->removeChild(mybullet->getsprite(),true);
            delete mybullet;
        }
    }
    
    for(int i = 0; i < enemyList->count(); i++)
    {
        GameEnemy* enemy = (GameEnemy *)(enemyList->objectAtIndex(i));
        if((enemy->getsprite())->getPosition().x < 0){
            this->updateLife(-10);
            enemyList->removeObjectAtIndex(i);
            this->removeChild(enemy->getsprite(),true);
            delete enemy;
        }
    }
    
    //let player move to targetPoint
    if(joyStick->getVelocity() > 0)
    {
        CCPoint orginP = (player->getsprite())->getPosition();
        CCPoint direP = ccpMult(joyStick->getDirection(), player->getSpeed());
        CCPoint lastP = ccp(orginP.x + direP.x, orginP.y + direP.y);
        float minx = (player->getsprite())->getContentSize().width/2;
        float maxx = size.width - minx;
        float miny = bottomMenu->getContentSize().height + (player->getsprite())->getContentSize().height/2;
        float maxy = size.height - (player->getsprite())->getContentSize().height/2;
        if(lastP.x <= minx) lastP.x = minx;
        else if(lastP.x >= maxx) lastP.x = maxx;
        if(lastP.y <= miny) lastP.y = miny;
        else if(lastP.y >= maxy) lastP.y = maxy;
        (player->getsprite())->setPosition(lastP);
    }
}

void MapScene::enemyrestart(CCTime dt)
{
	GameEnemy* enemy = new GameEnemy("enemy.png");
    enemyList->addObject(enemy);
	this->addChild((enemy->getsprite()), kZForPlayers,100);
}

void MapScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void MapScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void MapScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    if(targetPoint.equals(touch->getLocationInView()))
        return;
    targetPoint = touch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void MapScene::playerFire(CCTime dt){
    CCPoint herop = (player->getsprite())->getPosition();
    CCSize herosize = (player->getsprite())->getContentSize();
    int nowS = playerBulletList->count();
    GameBullet* newBullet = new GameBullet("bullet3456.png");
    newBullet->setPosition(ccp(herop.x + herosize.width, herop.y));
    newBullet->setType(0);
    this->addChild(newBullet->getsprite(),kZForMyBulletsBase + nowS);
    playerBulletList->addObject(newBullet);
}

