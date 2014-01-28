#ifndef __ShakeForFood2__Box__
#define __ShakeForFood2__Box__

#include <cocos2d.h>
#include "GameTile.h"
#include "CCLayer.h"
#include "constants.h"

using namespace cocos2d;

class GameBox: public CCNode
{
public:
    GameTile* first;
    GameTile* second;
    CCSize size;
    CCArray* content;
    CCArray* readyToRemoveTiles;
    CCLayer* layer;
    GameTile* OutBorderTile;
private:
    bool lock;
public:
	GameBox(CCSize asize,int afactor);
    GameTile* objectAtXandY(int posX,int posY);
    void checkWith(Orientation orient);
    bool check();
    void setLock(bool ff);
    bool isLocked();
    void removeSprite(GameTile* sender);
    void afterAllMoveDone();
    bool haveMore();
    int repair();
    int repairSingleColumn(int columnIndex);
};

#endif
