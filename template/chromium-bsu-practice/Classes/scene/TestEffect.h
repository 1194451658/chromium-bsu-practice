#ifndef __TEST_EFFECT_SCENE_H__
#define __TEST_EFFECT_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

class TestEffectScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	void playEffectCallback(CCObject* pSender);
	void playShieldCallback(CCObject* pSender);
	void playBurstDisappear(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(TestEffectScene);


private:
	void testExplosion();
};

#endif // __HELLOWORLD_SCENE_H__
