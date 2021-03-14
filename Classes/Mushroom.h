#ifndef __Mushroom_H__
#define __Mushroom_H__

#include "cocos2d.h"
#include "Player.h"
using namespace std;
USING_NS_CC;

enum
{
	E_STATE_MS_NONE,
	E_STATE_MS_MOVE,
	E_STATE_MS_FALL,
	E_STATE_MS_DIED

};

class CMushroom : public Node
{
public:
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(CMushroom);
	void walk(float delta);
	void raise(float delta);
	void fall(float delta);
	void setType(int nType);
	void setBirthPosY(float fY); 
	bool isAlive();
	string checkTouchX();
	string checkTouchY();
	Vec2 getTouchPoint(const Vec2& dir); //(L/R, U/D)
	string gIdTostrType(int nGid);
	

private:
	int m_nType;
	int m_nState;
	float m_fBirthPosY;
	Vec2 m_vDir;
	Vec2 m_vBirthPoint;
	Vec2 m_vVelocity;
	Sprite* m_pImage;
	float m_fTimer;
	CPlayer* m_pPlayer;
};

#endif; 