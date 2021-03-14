#ifndef __Mushroom_H__
#define __Mushroom_H__

#include "cocos2d.h"
#include "player.h"
USING_NS_CC;

enum
{
	E_STATE_M_NONE,
	E_STATE_M_WALK,
	E_STATE_M_FALL,
	E_STATE_M_DIED
};

class CMushroom : public Node
{
public:
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(CMushroom);
	void createAnimations();
	void changeState(int nState);
	// 通过判断与玩家之间的距离来判断是否让它运动
	void checkDistaceWithMario();
	string checkTouchY();
	string checkTouchX();
	void walk(float delta);
	//void jump(float delta);
	void fall(float delta);
	void checkTouchType(string strType, Vec2 vTouchPos);
	string gIdTostrType(int nGid);
	Vec2 getTouchPoint(const Vec2& dir); //(L/R, U/D)
	void setBirthPoint(Vec2 m_vBirthPoint);
	void updateDiedY(float delta);
	int getDiedDurTime();
	CC_SYNTHESIZE_READONLY(Sprite*, m_pImage, Image);
private:
	Vec2 m_vDir;
	Vec2 m_vVelocity;
	int m_nState;
	bool m_bIsAlive;
	Animate* m_aniWalk;
	CPlayer* m_pPlayer;
	Vec2 m_vBirthPoint;
	int m_nDiedDurTime;
};

#endif; 