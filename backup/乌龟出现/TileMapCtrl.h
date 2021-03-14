#ifndef __TileMapCtrl_H__
#define __TileMapCtrl_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;
using namespace std;
class CTileMap : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(CTileMap);
	//virtual void update(float fDt);
	Vec2 getTileByPos(const Vec2& pos);
	Vec2 getPosByTile(const Vec2& pos);

	int checkTouchX(const Vec2& pos);
	int checkTouchY(const Vec2& pos, int nDir);
	Vec2 getBirthPoint();
	Vec2 getEnemyBirthPoint();
	void follow(Node* pTarget);
	void changeCBlock();
	vector<CEnemy*> getAllEnemys();
private:
	void getTileMap();
	void getObjGroup();
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pGround;
	TMXLayer* m_pPipe;
	TMXLayer* m_pBlock;
	TMXLayer* m_pCoin;
	TMXLayer* m_pTrap;
	Vec2 m_vBirthPoint;
	Vec2 m_vEnemyBirthPoint;
	vector<CEnemy*> m_vEnemys;
};

#endif