#ifndef __MushMonster_H__
#define __MushMonster_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class CMushMonster : public CEnemy
{
public:
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(CMushMonster);
	void changeState();
	void initData();
private:

};

#endif; 