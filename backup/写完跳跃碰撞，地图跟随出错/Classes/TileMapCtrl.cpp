#include "TileMapCtrl.h"

bool CTileMap::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->getTileMap();
	this->getObjGroup();
	return true;
}

Vec2 CTileMap::getTileByPos(const Vec2& pos)
{
	// 得到每个格子大小
	Size tileSize = m_pTileMap->getTileSize();

	//	得到TileMap每行每列格子的个数
	Size mapSize = m_pTileMap->getMapSize();

	// 计算点击的格子坐标
	//Vec2 TilePos(0,0);
	int nx = pos.x / tileSize.width;
	int ny = (mapSize.height*tileSize.height - pos.y) / tileSize.height;

	return Vec2(nx, ny);
}

Vec2 CTileMap::getPosByTile(const Vec2& pos)
{
	Size tileSize = m_pTileMap->getTileSize();
	Size mapSizse = m_pTileMap->getMapSize();

	float fx = pos.x * tileSize.width + tileSize.width / 2; // 返回格子上顶点
	float fy = tileSize.height * (mapSizse.height - pos.y);
	return Vec2(fx, fy);
}


string CTileMap::checkTouchX(const Vec2& tile)
{
	int nGId = m_pPipe->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return "pipe";
	}
	
	nGId = m_pBlock->getTileGIDAt(tile);
	if (nGId > 0)
	{
		return "block";
	}
	return "none";
}

string CTileMap::checkTouchY(const Vec2& pos)
{
	// 判断pos是否越界
	// 查找该格子
	int nGId = m_pGround->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return "ground";
	}
	nGId = m_pPipe->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return "pipe";
	}
	nGId = m_pBlock->getTileGIDAt(pos);
	if (nGId > 0)
	{
		return "block";
	}
	return "none";
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
	}
}

Vec2 CTileMap::getBirthPoint()
{
	return m_vBirthPoint;
}

void CTileMap::follow(Node* pTarget)
{
	this->stopAllActions();
	Size tileSize = m_pTileMap->getTileSize();
	Size mapSizse = m_pTileMap->getMapSize();
	
	Follow* pFollow = Follow::create(pTarget, Rect(-this->getPositionX(), 0, tileSize.width * mapSizse.width, tileSize.height * mapSizse.height));
	this->runAction(pFollow);
}




