#include "GameScene.h"

CGameScene* CGameScene::m_pInstance = nullptr;
CGameScene* CGameScene::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	m_fCoinTimer = 0;
	m_pCoin = nullptr;
	//m_pCoin = CCoin::create();

	this->loadRes();

	m_pTileMap = CTileMap::create();
	this->addChild(m_pTileMap);
	
	m_pPlayer = CPlayer::create();
	m_pTileMap->addChild(m_pPlayer);
	m_pPlayer->setPosition(m_pTileMap->getBirthPoint());
	
	m_pTileMap->follow(m_pPlayer);
	m_vMushrooms = m_pTileMap->getAllMushrooms();
	scheduleUpdate();

	return true;
}

void CGameScene::loadRes()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Image/plist/AllPics.plist");
}

void CGameScene::showCoin(const Vec2& pos)
{
	if (!m_pCoin)
	{
		m_pCoin = CCoin::create();
	}
	m_pTileMap->addChild(m_pCoin);
	m_pCoin->setVisible(true);
	m_pCoin->setPosition(pos.x, pos.y + 20);
	MoveBy* pCoinMoveUp = MoveBy::create(0.3f, Vec2(0, 25));
	MoveBy* pCoinMoveDown = MoveBy::create(0.3f, Vec2(0, -25));
	Action* pAction = Sequence::create(pCoinMoveUp, pCoinMoveDown, NULL);
	m_pCoin->runAction(pAction);
}

void CGameScene::update(float fDt)
{
	for (int i = 0; i < m_vMushrooms.size();++i)
	{
		float fPlayerY = m_pPlayer->getPositionY();
		float fPlayerX = m_pPlayer->getPositionX();
		float fMushY = m_vMushrooms[i]->getPositionY();
		float fMushX = m_vMushrooms[i]->getPositionX();
		// 12，14代表player和mushroom的高度和宽度的一半之和
		if (abs(fPlayerY - fMushY) <= 12 && abs(fMushX - fPlayerX) <= 14 && m_vMushrooms[i]->getDiedDurTime() == 0)
		{
			// mriao踩死怪的条件：向下落，下边界踩在怪物身上。
			if (m_pPlayer->getDir().y == -1 && fPlayerY <= fMushY + 14)
			{
				m_vMushrooms[i]->changeState(3);
			}
			/*else
			{
				m_pPlayer->changeState(5);
			}*/
		}
	}
	if (m_pCoin)
	{
		m_fCoinTimer += fDt;
		if (m_fCoinTimer >= 0.6)
		{
			m_fCoinTimer = 0;
			m_pCoin->setVisible(false);
			
			//m_pCoin->removeFromParent();
			m_pCoin = nullptr;
		}
	}
}

void CGameScene::showMushrooms()
{
	
}
