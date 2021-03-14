#ifndef __Tortoies_H__
#define __Tortoies_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class CTortoies : public CEnemy
{
public:
	virtual bool init();
	CREATE_FUNC(CTortoies);
	void changeState();
private:

};

#endif; 