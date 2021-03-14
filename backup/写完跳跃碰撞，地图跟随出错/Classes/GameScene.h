#ifndef __GameScene_h__
#define __GameScene_h__

#include "cocos2d.h"
#include "TileMapCtrl.h"
#include "Player.h"
USING_NS_CC;

class CGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(CGameScene);

	static CGameScene* getInstance();
	CC_SYNTHESIZE_READONLY(CTileMap*, m_pTileMap, TileMap);
	CC_SYNTHESIZE_READONLY(CPlayer*, m_pPlayer, CPlayer);


private:
	void loadRes();
private:
	static CGameScene* m_pInstance;
	
};

#endif 