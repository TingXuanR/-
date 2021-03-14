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

	this->loadRes();

	m_pTileMap = CTileMap::create();
	this->addChild(m_pTileMap);
	
	m_pPlayer = CPlayer::create();
	m_pTileMap->addChild(m_pPlayer);
	m_pPlayer->setPosition(m_pTileMap->getBirthPoint());
	
	m_pTileMap->follow(m_pPlayer);
	m_vEnemys = m_pTileMap->getAllEnemys();
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
	m_pCoin->setPosition(pos.x, pos.y);
	MoveBy* pCoinMoveUp = MoveBy::create(0.3f, Vec2(0, 50));
	MoveBy* pCoinMoveDown = MoveBy::create(0.3f, Vec2(0, -50));
	Action* pAction = Sequence::create(pCoinMoveUp, pCoinMoveDown, NULL);
	m_pCoin->runAction(pAction);
}

void CGameScene::update(float fDt)
{
	//for (int i = 0; i < m_vEnemys.size();++i)
	checkEnemyColli();
	checkMushroom();
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

void CGameScene::checkEnemyColli()
{
	for (int i = m_vEnemys.size() - 1; i >= 0; --i)
	{
		//if (m_vEnemys[i]->getPositionY() <= 2 || m_vEnemys[i]->getPositionX() <= 2)  // 掉出屏幕，移除
		//{
		//	m_vEnemys.erase(m_vEnemys.begin() + i);
		//}
		if (!m_vEnemys[i] || m_vEnemys[i]->getPositionX() <= 2)
		{
			m_vEnemys.erase(m_vEnemys.begin() + i);
		}
		else
		{
			float fPlayerY = m_pPlayer->getPositionY();
			float fPlayerX = m_pPlayer->getPositionX();
			float fMushY = m_vEnemys[i]->getPositionY();
			float fMushX = m_vEnemys[i]->getPositionX();
			float sumWidth = m_pPlayer->getPlayerSize().x / 2 + m_vEnemys[i]->getContentSize().width / 2;
			float sumHeight = m_pPlayer->getPlayerSize().y / 2 + m_vEnemys[i]->getContentSize().height / 2;
			// 12，14代表player和Enemy的高度和宽度的一半之和
			if (abs(fPlayerY - fMushY) <= sumHeight && abs(fMushX - fPlayerX) <= sumWidth && m_vEnemys[i]->getDiedDurTime() == 0)
			{
				// mriao踩死怪的条件：向下落，下边界踩在怪物身上。
				// 当由大玛丽变小玛丽时，由于大玛丽中心点高，变成小玛丽的图片后小玛丽会往下掉。怪物会died
				if (m_pPlayer->getDir().y == -1 && fPlayerY > fMushY && m_pPlayer->getDiedTime() == 0)
				{
					m_vEnemys[i]->changeState(3);
				}
				else
				{
					if (!m_pPlayer->isBig())
					{
						if (m_pPlayer->getInvincibleTime()==0)
						{
							m_pPlayer->changeState(5);
						}
						
					}
					else
					{
						m_pPlayer->turnSmall();
						m_pPlayer->setOpenTimer(true);
					}
				}
			}
		}
	}
}

void CGameScene::showEnemys()
{
	
}

void CGameScene::addMushroom(CMushroom* pMushroom)
{
	m_vMushrooms.push_back(pMushroom);
}

void CGameScene::checkMushroom()
{
	for (int i = m_vMushrooms.size() - 1; i >= 0; --i)
	{
		if (m_vMushrooms[i]->isAlive())
		{
			float fPlayerY = m_pPlayer->getPositionY();
			float fPlayerX = m_pPlayer->getPositionX();
			float fMushY = m_vMushrooms[i]->getPositionY();
			float fMushX = m_vMushrooms[i]->getPositionX();
			float sumWidth = m_pPlayer->getPlayerSize().x / 2 + m_vMushrooms[i]->getContentSize().width / 2;
			float sumHeight = m_pPlayer->getPlayerSize().y / 2 + m_vMushrooms[i]->getContentSize().height / 2;
			// 12，14代表player和Enemy的高度和宽度的一半之和
			if (abs(fPlayerY - fMushY) <= sumWidth && abs(fMushX - fPlayerX) <= sumHeight)
			{
				if (!m_pPlayer->isBig())
				{
					m_pPlayer->turnBig();
					m_pPlayer->setOpenTimer(false);
					m_pPlayer->setInvincibleTime(200);
					m_vMushrooms[i]->removeFromParent();
					m_vMushrooms.erase(m_vMushrooms.begin() + i);
				}
			}
		}
		else
		{
			m_vMushrooms[i]->removeFromParent();
			m_vMushrooms.erase(m_vMushrooms.begin() + i);
		}
		
	}
}


