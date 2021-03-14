#include "Mushroom.h"
#include "GameScene.h"
bool CMushroom::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_nType = 1;
	m_vDir.x = 0;
	m_nState = 0;
	m_vDir.y = 1; m_fTimer = 0;
	m_vVelocity.y = m_vVelocity.x = 0;
	m_pImage = Sprite::createWithSpriteFrameName("reward_mushroom_01.png");
	this->addChild(m_pImage);
	this->scheduleUpdate();

	return true;
}

void CMushroom::update(float delta)
{
	if (m_nState == E_STATE_MS_DIED)
	{
		//this->removeFromParent();
	}
	else
	{
		if (m_vDir.y == 1)
		{

			raise(delta);
		}
		else if (m_vDir.y == -1)
		{
			fall(delta);
		}
		if (m_vDir.x == 1 || m_vDir.x == -1)
		{
			walk(delta);
		}
	}
	

}

void CMushroom::raise(float delta)
{
	if (m_vVelocity.y == 0)
	{
		m_vVelocity.y = 150;
	}
	m_vVelocity.y += -1000 * delta;
	m_vVelocity.y = m_vVelocity.y <= 0 ? 0 : m_vVelocity.y;

	float fPositionY = this->getPositionY();
	fPositionY += m_vDir.y * delta * m_vVelocity.y; 
	if (fPositionY >= m_fBirthPosY + 9)
	{
		m_vVelocity.y = 0;
		m_vDir.y = 0;
		m_vDir.x = 1;
		this->setPositionY(m_fBirthPosY + 9);
	}
	else
	{
		this->setPositionY(fPositionY);
	}
}

void CMushroom::walk(float delta)
{
	
	m_vVelocity.x = 90;
	float fPositionX = this->getPositionX();
	fPositionX += m_vDir.x * delta * m_vVelocity.x;
	if (checkTouchX() != "none")
	{
		if (checkTouchX() == "trap")
		{
			m_vDir.x = 0;
		}
		else
		{
			Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(fPositionX + 8 * m_vDir.x, this->getPositionY()));
			//取障碍物边缘左上顶点x坐标，减去格子的一半宽度和人物的一半宽度作为positionX。
			fPositionX = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).x - m_vDir.x * 16;
			m_vDir.x *= -1;
			this->setPositionX(fPositionX);
		}
	}
	else
	{
		if (fPositionX <= 3)
		{
			m_nState = E_STATE_MS_DIED;
		}
		this->setPositionX(fPositionX);
	}
	if (checkTouchY() == "none")
	{
		m_vDir.y = -1;
	}
}

void CMushroom::fall(float delta)
{
	m_vVelocity.y += -1000 * delta* m_vDir.y;
	float fPositionY = this->getPositionY();
	fPositionY += m_vDir.y * delta * m_vVelocity.y;
	
	if (fPositionY <= 2)
	{
		fPositionY = 2;
	}
	this->setPositionY(fPositionY);
	string pos = checkTouchY();
	if (pos != "none")
	{
		if (pos == "trap")
		{
			if (fPositionY==2)
			{
				m_nState = E_STATE_MS_DIED;
			}
			
		}
		else
		{
			Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(this->getPositionX(), fPositionY - m_pImage->getContentSize().height / 2));
			//ground上顶点减去自身高度。
			fPositionY = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).y + m_pImage->getContentSize().height / 2;
			m_vDir.y = 0;
			this->setPositionY(fPositionY);
		}
	}
}

void CMushroom::setType(int nType)
{
	if (m_nType == 1)
	{
		m_pImage->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("reward_mushroom_02.png"));
	}
}

void CMushroom::setBirthPosY(float fY)
{
	m_fBirthPosY = fY;
}

cocos2d::Vec2 CMushroom::getTouchPoint(const Vec2& dir)
{
	Vec2 pos = this->getPosition();
	Size playerSize = m_pImage->getContentSize();
	pos.x += dir.x * playerSize.width / 2;
	pos.y += dir.y * playerSize.height / 2;
	return pos;
}

std::string CMushroom::checkTouchY()
{
	Vec2 vTouchPoint;
	if (m_vDir.y == 1)
	{
		vTouchPoint = this->getTouchPoint(Vec2(0, 1));
	}
	else
	{
		if (this->getPositionY() <= m_pImage->getContentSize().height / 2)
		{
			vTouchPoint = this->getTouchPoint(Vec2(0, 0));
		}
		else
		{
			vTouchPoint = this->getTouchPoint(Vec2(0, -1));
		}
		
	}
	CTileMap* pTileMap = CGameScene::getInstance()->getTileMap();
	Vec2 touchPoint = pTileMap->getTileByPos(vTouchPoint);
	int nGid = pTileMap->checkTouchY(touchPoint, m_vDir.y);
	string strTouch = gIdTostrType(nGid);

	return strTouch;
}

std::string CMushroom::checkTouchX()
{
	Vec2 vTouchPoint;
	if (m_vDir.x == 1)
	{
		vTouchPoint = this->getTouchPoint(Vec2(1, 0));
	}
	else
	{
		vTouchPoint = this->getTouchPoint(Vec2(-1, 0));
	}
	CTileMap* pTileMap = CGameScene::getInstance()->getTileMap();
	Vec2 touchPoint = pTileMap->getTileByPos(vTouchPoint);
	int nGid = pTileMap->checkTouchX(touchPoint);
	string strTouch = gIdTostrType(nGid);

	return strTouch;
}
std::string CMushroom::gIdTostrType(int nGid)
{
	if (nGid == 1)
	{
		return "nBlock"; // normal block, without coin.
	}
	else if (nGid == 91)
	{
		return "csBlock"; // block with coins.
	}
	else if (nGid == 29 || nGid == 30 || nGid == 59 || nGid == 60)
	{
		return "pipe";
	}
	else if (nGid == 601)
	{

		return "cBlock"; // block with one coin.
	}
	else if (nGid == 31)
	{
		return "bBlock"; // blank block
	}
	else if (nGid == 121)
	{
		return "ground";
	}
	else if (nGid == 875)
	{
		return "trap";
	}
	else if (nGid == 0)
	{
		return  "none";
	}
}

bool CMushroom::isAlive()
{
	return m_nState != E_STATE_MS_DIED;
}







