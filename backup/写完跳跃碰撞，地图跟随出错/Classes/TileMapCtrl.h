#ifndef __TileMapCtrl_H__
#define __TileMapCtrl_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class CTileMap : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(CTileMap);

	Vec2 getTileByPos(const Vec2& pos);
	Vec2 getPosByTile(const Vec2& pos);

	string checkTouchX(const Vec2& pos);
	string checkTouchY(const Vec2& pos);
	Vec2 getBirthPoint();
	void follow(Node* pTarget);
private:
	void getTileMap();
	void getObjGroup();
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pGround;
	TMXLayer* m_pPipe;
	TMXLayer* m_pBlock;
	Vec2 m_vBirthPoint;
};

#endif