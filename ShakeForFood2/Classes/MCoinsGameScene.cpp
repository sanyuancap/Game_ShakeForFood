#include "MCoinsGameScene.h"

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

CCScene* MCoinsGameScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MCoinsGameScene *layer = MCoinsGameScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MCoinsGameScene::init()
{
    box = new GameBox(CCSize(kBoxWidth, kBoxHeight), 6);
    box->layer = this;
    box->setLock(true);
    setTouchEnabled(true);
    //scheduleUpdate();
    return true;
}

void MCoinsGameScene::onEnterTransitionDidFinish()
{
    box->check();
}

void MCoinsGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if(box->isLocked())
        return;
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL( location );
    
    int x = (location.x -kStartX) / kTileSize;
	int y = (location.y -kStartY) / kTileSize;
	
	
	if (selectedTile && selectedTile->x ==x && selectedTile->y == y)
		return;
    GameTile *tile = box->objectAtXandY(x, y);
    if(selectedTile && selectedTile->nearTile(tile))
    {
        box->setLock(true);
        this->changeWithTileABandSel(selectedTile, tile, callfuncND_selector(MCoinsGameScene::checkSenderandData));
        selectedTile = NULL;
    }
    else
    {
        selectedTile = tile;
        this->afterOneShineTrun(tile->sprite);
    }
}

void MCoinsGameScene::changeWithTileABandSel(GameTile* a,GameTile* b,SEL_CallFuncND sel)
{
    CCFiniteTimeAction* actionA = CCSequence::create(CCMoveTo::create(kMoveTileTime, b->pixPosition()),
                                                   CCCallFuncND::create(this, sel, a),
                                                   NULL);
    CCFiniteTimeAction* actionB = CCSequence::create(CCMoveTo::create(kMoveTileTime, a->pixPosition()),
                                                   CCCallFuncND::create(this, sel, b),
                                                   NULL);
    a->sprite->runAction(actionA);
    b->sprite->runAction(actionB);
    a->trade(b);
}

void MCoinsGameScene::checkSenderandData(GameTile* sender,GameTile* data)
{
	if(NULL == firstOne){
		firstOne = data;
		return;
	}
	bool result = box->check();
	if (result)
        box->setLock(false);
	else
    {
        changeWithTileABandSel(data, firstOne, callfuncND_selector(MCoinsGameScene::backcheckSenderandData));
	}
    
    firstOne = NULL;
}

void MCoinsGameScene::backcheckSenderandData(GameTile* sender,GameTile* data)
{
    if(NULL == firstOne)
    {
        firstOne = data;
        return;
    }
    firstOne = NULL;
    box->setLock(false);
}

void MCoinsGameScene::afterOneShineTrun(CCSprite* asprite)
{
    if(selectedTile && asprite == selectedTile->sprite)
    {
        CCSprite* sprite = asprite;
        CCFiniteTimeAction* someAction =
        CCSequence::create(CCScaleBy::create(kMoveTileTime, 0.5f),
                           CCScaleBy::create(kMoveTileTime, 2.0f),
                           CCCallFuncN::create(this, callfuncN_selector(MCoinsGameScene::afterOneShineTrun)),
                           NULL);
        sprite->runAction(someAction);
    }
}