#ifndef __Coin_H__
#define __Coin_H__

#include "cocos2d.h"
USING_NS_CC;

class CCoin : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(CCoin);

	/*static CCoin* getInstance();*/
	CC_SYNTHESIZE(bool, m_bIsExist, IsExist);
private:
	int m_nDir;
	/*static CCoin* m_pInstance;*/
};



#endif; 