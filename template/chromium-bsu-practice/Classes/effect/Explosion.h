

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "cocos2d.h"
#include "ccMacros.h"

USING_NS_CC;

class Explositon : public CCNode
{
public:
	CREATE_FUNC(Explositon);

	bool init()
	{
		number = 4;
		numberVar = 2;
		x = 0;
		y = 0;
		xVar = 20;
		yVar = 20;
		
		int trueNumber = number + CCRANDOM_MINUS1_1()*numberVar;

		CCArray* spritesActionArray = CCArray::create();
		for(int i=0;i<trueNumber;i++)
		{
			CCSprite* sprite = CCSprite::create("png/enemyExplo.png");
			addChild(sprite);

			CCArray* spriteActArray = CCArray::create();

			// init
			CCArray* initActArray = CCArray::create();

			float trueX = x + CCRANDOM_MINUS1_1() * xVar;
			float trueY = y + CCRANDOM_MINUS1_1() * yVar;

			CCMoveTo* initMove = CCMoveTo::create(0, ccp(trueX,trueY));
			CCScaleTo* initScale = CCScaleTo::create(0, 0.1);
			CCTintTo* tint = CCTintTo::create(0, 255, 255, 255);
			CCFadeTo* fade = CCFadeTo::create(0, 255);

			initActArray->addObject(initMove);
			initActArray->addObject(initScale);
			initActArray->addObject(tint);
			initActArray->addObject(fade);

			CCSpawn* initSpawn = CCSpawn::create(initActArray);
			spriteActArray->addObject(initSpawn);

			// target 
			float time = 0.5;
			CCArray* finalActArray = CCArray::create();
			CCScaleTo* scale = CCScaleTo::create(time, 1.0);
			CCFadeTo* fadeTo = CCFadeTo::create(time, 255*0.2);
			CCTintTo* tintTo = CCTintTo::create(time, 255*0.75, 255*0.75, 255*0.75);

			finalActArray->addObject(scale);
			finalActArray->addObject(fadeTo);
			finalActArray->addObject(tintTo);

			CCSpawn* finalSpawn = CCSpawn::create(finalActArray);
			spriteActArray->addObject(finalSpawn);

			// sprite action 
			CCSequence* spriteAct = CCSequence::create(spriteActArray);
			CCTargetedAction* targetSpriteAct = CCTargetedAction::create(sprite, spriteAct);
			spritesActionArray->addObject(targetSpriteAct);
		}
		// sprites action spawn
		CCSpawn* spritesAction = CCSpawn::create(spritesActionArray);


		// final action
		CCArray* finalActArray = CCArray::create();
		finalActArray->addObject(spritesAction);

		CCRemoveSelf* remove = CCRemoveSelf::create();
		finalActArray->addObject(remove);

		CCSequence* finalSeq = CCSequence::create(finalActArray);

		// run action
		this->runAction(finalSeq);
		return true;
	}

	void removeSelf()
	{
		this->removeFromParentAndCleanup(true);
	}

	int number;
	int numberVar;
	float x;
	float y;
	float xVar;
	float yVar;
};





#endif // !__EXPLOSION_H__



