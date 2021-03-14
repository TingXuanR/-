#ifndef __GameScene_h__
#define __GameScene_h__

#include "cocos2d.h"
#include "TileMapCtrl.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
USING_NS_CC;

class CGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(CGameScene);
	virtual void update(float fDt);
	static CGameScene* getInstance();
	CC_SYNTHESIZE_READONLY(CTileMap*, m_pTileMap, TileMap);
	CC_SYNTHESIZE_READONLY(CPlayer*, m_pPlayer, CPlayer);

	void showCoin(const Vec2& pos);
	void showEnemys();
private:
	void loadRes();
	void initCoin();
private:
	static CGameScene* m_pInstance;
	float m_fCoinTimer;
	CCoin* m_pCoin;
	vector<CEnemy*> m_vEnemys;
};

#endif 