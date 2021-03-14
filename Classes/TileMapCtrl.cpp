#include "TileMapCtrl.h"
#include "Coin.h"
#include "GameScene.h"
bool CTileMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_pMushroom = nullptr;
	this->getTileMap();
	this->getObjGroup();
	// 得到每个格子大小
	m_sMapSize = m_pTileMap->getMapSize();
	//	得到TileMap每行每列格子的个数
	m_sTileSize = m_pTileMap->getTileSize();

	//scheduleUpdate();
	return true;
}

//void CTileMap::update(float fDt)
//{
//	/*for (auto pEnemy : m_vEnemys)
//	{
//		pEnemy->update(fDt);
//	}*/
//}

Vec2 CTileMap::getTileByPos(const Vec2& pos)
{
	// 计算点击的格子坐标
	int nx = pos.x / m_sTileSize.width;
	int ny = (m_sMapSize.height*m_sTileSize.height - pos.y) / m_sTileSize.height;

	return Vec2(nx, ny);
}

Vec2 CTileMap::getPosByTile(const Vec2& pos)
{
	float fx = pos.x * m_sTileSize.width + m_sTileSize.width / 2; // 返回格子上顶点
	float fy = m_sTileSize.height * (m_sMapSize.height - pos.y);
	return Vec2(fx, fy);
}


int CTileMap::checkTouchX(const Vec2& tile)
{
	int nGId = m_pPipe->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return nGId;
	}

	nGId = m_pBlock->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return nGId;
	}

	nGId = m_pCoin->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return nGId;
	}

	nGId = m_pTrap->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return nGId;
	}
	return nGId;
}

int CTileMap::checkTouchY(const Vec2& pos, int nDir)
{
	// 判断pos是否越界
	// 查找该格子
	int nGId = m_pGround->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return nGId;
	}

	nGId = m_pPipe->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return nGId;
	}

	nGId = m_pBlock->getTileGIDAt(pos);
	if (nGId > 0)
	{
		if (nGId == 601 && nDir == 1)
		{
			m_pBlock->setTileGID(31, pos);
			// 判断砖块是否是蘑菇
			Vec2 vPosition = getPosByTile(pos); // 得到的是上边界的中点
			for (int i = 0; i < m_vMushroomPos.size(); ++i)
			{

				if (vPosition.x >= m_vMushroomPos[i].x - 8 && vPosition.x <= m_vMushroomPos[i].x + 8)
				{
					CMushroom* pMushroom = CMushroom::create();
					pMushroom->setPositionX(vPosition.x);
					pMushroom->setPositionY((m_sMapSize.height - pos.y)*m_sTileSize.height - 8);
					pMushroom->setBirthPosY((m_sMapSize.height - pos.y)*m_sTileSize.height);
					this->addChild(pMushroom);
					CGameScene::getInstance()->addMushroom(pMushroom);
					return 31;
				}
			}
		}
		else if (nGId == 846 && nDir == 1) // addLife mushroom
		{
			m_pBlock->setTileGID(31, pos);
			CMushroom* pMushroom = CMushroom::create();
			pMushroom->setPositionX(getPosByTile(pos).x);
			pMushroom->setPositionY((m_sMapSize.height - pos.y)*m_sTileSize.height - 8);
			pMushroom->setBirthPosY(96);
			pMushroom->setType(1);
			this->addChild(pMushroom);
			CGameScene::getInstance()->addMushroom(pMushroom);
			return 31;
		}
		return nGId;
	}

	nGId = m_pCoin->getTileGIDAt(pos);
	if (nGId > 0)
	{
		m_pCoin->setTileGID(0, pos);
		return nGId;
	}

	nGId = m_pTrap->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return nGId;
	}
	return nGId;
}

void CTileMap::getTileMap()
{
	// 载入TileMap
	m_pTileMap = TMXTiledMap::create("Image/tmx/MarioMap1.tmx");

	this->addChild(m_pTileMap);
	// 获取Layer
	m_pGround = m_pTileMap->getLayer("land");
	m_pPipe = m_pTileMap->getLayer("pipe");
	m_pBlock = m_pTileMap->getLayer("block");
	m_pCoin = m_pTileMap->getLayer("coin");
	m_pTrap = m_pTileMap->getLayer("trap");

}

void CTileMap::getObjGroup()
{
	TMXObjectGroup* pObjGroup = m_pTileMap->getObjectGroup("objects");
	ValueVector objs = pObjGroup->getObjects();
	for (Value& obj : objs)
	{
		ValueMap valueMap = obj.asValueMap();
		string strType = valueMap["type"].asString();
		if ("BirthPoint" == strType)
		{
			m_vBirthPoint.x = valueMap["x"].asFloat();
			m_vBirthPoint.y = valueMap["y"].asFloat();
		}
		else if ("mushroom" == strType || "tortoise" == strType)
		{
			CEnemy* pEnemy = CEnemy::create();
			this->addChild(pEnemy);
			if ("mushroom" == strType)
			{
				pEnemy->setType(1);
			}
			else if ("tortoise" == strType)
			{
				pEnemy->setType(2);
			}
			pEnemy->createAnimations();
			m_vEnemyBirthPoint.x = valueMap["x"].asFloat();
			m_vEnemyBirthPoint.y = valueMap["y"].asFloat();

			pEnemy->setBirthPoint(m_vEnemyBirthPoint);
			pEnemy->setPosition(m_vEnemyBirthPoint);
			m_vEnemys.push_back(pEnemy);
		}
		else if ("MushroomReward" == strType || "MushroomAddLife" == strType)
		{
			m_vMushroomPos.push_back(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
		}
	}
}

Vec2 CTileMap::getBirthPoint()
{
	return m_vBirthPoint;
}

void CTileMap::follow(Node* pTarget)
{
	this->stopAllActions();
	//Size tileSize = m_pTileMap->getTileSize();	 // 16*16
	//Size mapSizse = m_pTileMap->getMapSize();	// 228*14

	Follow* pFollow = Follow::create(pTarget, Rect(0, 0, m_sTileSize.width * m_sMapSize.width, m_sTileSize.height * m_sMapSize.height));
	this->runAction(pFollow);
}


cocos2d::Vec2 CTileMap::getEnemyBirthPoint()
{
	return m_vEnemyBirthPoint;
}

vector<CEnemy*> CTileMap::getAllEnemys()
{
	return m_vEnemys;
}

CMushroom* CTileMap::getMushroom()
{
	return m_pMushroom;
}








