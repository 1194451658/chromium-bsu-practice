/*
ufolrԭ����ת����ע����
ת����ufolr�Ĳ��� ԭ�����ӣ�http://blog.csdn.net/ufolr/article/details/7624851
*/

#include "TestFallingLeaf.h"
#include <stdlib.h>


USING_NS_CC;

enum {TAG_LEAF1 = 101, TAG_LEAF2};  

CCScene* TestFallingLeaf::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestFallingLeaf *layer = TestFallingLeaf::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestFallingLeaf::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float top = origin.y + visibleSize.height;
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// -----
	// title
	// -------
	CCLabelTTF* title = CCLabelTTF::create();
	title->setString("Test Falling Leaf");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	// init
	CCSprite *spriteLeaf1 = CCSprite::create("test/testFallingLeaf1.jpg");  
	spriteLeaf1->setRotation(30);//��ת�Ƕ�  
	spriteLeaf1->setAnchorPoint(ccp(0.5, 3));//���þ���ê��  
	spriteLeaf1->setPosition(ccp(450, 500));//Ҷ��1��һ�γ�ʼλ��  
	spriteLeaf1->setScale(0.5);//����ҶƬ��С  

	this->addChild(spriteLeaf1,100,TAG_LEAF1);  
	this->playLeafAnim(spriteLeaf1);//����play������ʵ��Ҷ����  

	CCSprite *spriteLeaf2 = CCSprite::create("test/testFallingLeaf1.jpg");  
	spriteLeaf2->setRotation(50);  
	spriteLeaf2->setAnchorPoint(ccp(0.5, 3));  
	spriteLeaf2->setPosition(ccp(200, 540));  
	spriteLeaf2->setScale(0.5);  

	this->addChild(spriteLeaf2,101,TAG_LEAF2);  
	this->playLeafAnim(spriteLeaf2);  

	return true;  
}

void TestFallingLeaf::playLeafAnim(CCSprite *spriteLeaf)  
{  
	int iTag = spriteLeaf->getTag();  

	CCLog("playtag%d", iTag);  
	float time, roTime;  
	float fAngle1, fAngle2;  
	if (iTag == TAG_LEAF1)  
	{  
		CCLog("tag1");  
		time = 10;//Ҷ�������ʱ��  
		roTime = 2.5;//Ҷ�ӵ���ڶ�һ��ʱ��  
		fAngle1 = -80;//Ҷ����ʱ��ڶ��Ƕ�  
		fAngle2 = 80;//˳ʱ��ڶ��Ƕ�  
	}  
	else  
	{  
		CCLog("tag2");  
		time = 14;  
		roTime = 3.2;  
		fAngle1 = -100;  
		fAngle2 = 100;  
	}  
	CCLog("rotime%ffAngle1%ffAngle2%f",roTime, fAngle1,fAngle1);  
	//�������Ҷ�Ӻ���ƫ��ֵ  
	srand((UINT)GetCurrentTime());  
	int iRandPos = rand() % 250;  
	CCLog("Pianyi%d", iRandPos);  
	//Ҷ�����˶�����λ��  
	CCMoveTo *moveTo = CCMoveTo::create(time, ccp(CCDirector::sharedDirector()->getWinSize().width - iRandPos, 30));  
	CCCallFuncN *actDone = CCCallFuncN::create(this, callfuncN_selector(TestFallingLeaf::resetLeafPos));  
	CCFiniteTimeAction *putdown = CCSequence::create(moveTo, actDone, NULL);  
	//Ҷ����ת����  
	CCRotateBy *rotaBy1 = CCRotateBy::create(roTime, fAngle1);  
	CCRotateBy *rotaBy2 = CCRotateBy::create(roTime, fAngle2);  

	//Ҷ�ӷ�ת����  
	spriteLeaf->setVertexZ(60);//�������̧��60���������ʹ��CCOrbitCameraʵ�ֿռ䷭תʱ������λ���ڵ�������  
	//CCDirector::sharedDirector()->setDepthTest(false);  
	//�ر���Ȳ���ͬ�����Ա����������⣬�������Ƽ�ʹ���������setVertexZ����ȷ�������Ϊ��ʱ�������Ҫ�ڵ���Ч�����ر���Ȳ��Ժ�����ڵ�Ч����ȱʧ  
	CCOrbitCamera * orbit = CCOrbitCamera::create(8, 1, 0, 0, 360, 45, 0);  
	//����Ҷ����ʼ��ִ����ά��ת�Ķ���  
	CCRepeat *fz3d = CCRepeat::create(orbit, -1);//����ѭ��ִ��ҶƬ��ת�Ķ���  
	//CCRepeatForever *fz3d = CCRepeatForever::actionWithAction(orbit);  
	//��������ʹ��CCSpawnͬʱִ�ж��������Բ�����ʹ�����޴������͵Ķ���������ʹ�����ߴ���ѭ��CCRepeat��ѭ����������Ϊ-1  

	//��CCEaseInOut��װ��Ҷ�ڶ��Ķ���������Ҷ�Ľ��롢���ָ���Ȼ�����뵭��Ч����  
	CCEaseInOut *ease1 = CCEaseInOut::create(rotaBy1, 3);  
	CCEaseInOut *ease2 = CCEaseInOut::create(rotaBy2, 3);  
	//�ڶ������ϳ�  
	CCFiniteTimeAction *seq2 = CCSequence::create(ease1, ease2, NULL);//����ִ��˳ʱ�롢��ʱ��ڶ�  
	CCRepeat *baidong = CCRepeat::create(seq2, -1);//�ڶ��ϳ�  

	//����ִ��->ͬʱִ�����ж���  
	spriteLeaf->runAction(CCSpawn::create(putdown, baidong, fz3d, NULL)); 
	// spriteLeaf->runAction(CCSpawn::create(fz3d, NULL)); 

}

void TestFallingLeaf::resetLeafPos(CCNode* sender)  
{  
	int iTag = int(sender->getTag());//��ñ�����ҶƬ�ı�ǩ  
	int iZoder = int(sender->getZOrder());//��ȡ������ҶƬ��z��ֵ  
	sender->removeFromParentAndCleanup(true);//����Ѿ��䵽�׵��Ҷ��  

	char sImg[] = "test/testFallingLeaf1.jpg";  
	//_snprintf(sImg, sizeof(sImg), "img_yezi_%d.png", iTag % 100);  

	CCPoint pos;  
	float fAngle;  
	//�������Ҷ�ӵ���ʼλ��  
	srand((UINT)GetCurrentTime());  
	int iRand = (rand() % 200);  
	if (iTag == TAG_LEAF1)  
	{  
		pos = ccp(iRand, 600);  
		fAngle = 30;  
	}  
	else  
	{  
		pos = ccp(iRand, 570);  
		fAngle = 50;  
	}  
	//���������µ�ҶƬ������㴦�ͷ�  
	CCSprite *spriteLeaf = CCSprite::create(sImg);  
	spriteLeaf->setScale(0.5);  
	spriteLeaf->setAnchorPoint(ccp(0.5, 3));  
	spriteLeaf->setRotation(fAngle);  
	spriteLeaf->setPosition(pos);  

	this->addChild(spriteLeaf, iZoder,iTag);  
	this->playLeafAnim(spriteLeaf);//���ú����Ҷ�ٴ�ִ��Ʈ�䶯��  
}

