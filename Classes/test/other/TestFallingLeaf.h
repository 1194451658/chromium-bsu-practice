

/*
ufolrԭ����ת����ע����
ת����ufolr�Ĳ��� ԭ�����ӣ�http://blog.csdn.net/ufolr/article/details/7624851
*/


#ifndef __TEST_FALLING_LEAF_H__
#define __TEST_FALLING_LEAF_H__

#include "AppMacros.h"

USING_NS_CC;

class TestFallingLeaf : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void resetLeafPos(CCNode* sender);//ҶƬλ�����ú���  
	void playLeafAnim(CCSpriteExt *spriteLeaf);//�������ʵ�ֺ���  

	// implement the "static node()" method manually
	CREATE_FUNC(TestFallingLeaf);
};

#endif // __HELLOWORLD_SCENE_H__
