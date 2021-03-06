
// Copyright 2014 Wanwan Zhang

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "EnemyOmni.h"
#include "GameController.h"
#include "math.h"

EnemyOmni* EnemyOmni::create(AircraftDef def)
{
	EnemyOmni* hero = new EnemyOmni();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

EnemyOmni::EnemyOmni()
{
	lastMoveX = 0;
	sensitiveToHero = CCRANDOM_0_1();
}

bool EnemyOmni::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		name = "EnemyOmni";

		createExtraGraphics();

		// create gun
		Gun* gun = Gun::createEnemyOmniGun();
		setDefaultGun(gun);

		return true;
	}

	return false;
}

void EnemyOmni::createExtraGraphics()
{
	// create extra graphics
	CCSpriteExt* extraGraphic = CCSpriteExt::create("png/airCraft/enemy01-extra.png");
	extraGraphic->setColor(ccc3(255,0,0));
	graphics->addChild(extraGraphic);
	//addChild(extraGraphic);

	// center extra grahics
	CCSize graphicsSize = graphics->getContentSize();
	extraGraphic->setPosition(ccp(graphicsSize.width/2, graphicsSize.height/2));

	// create action
	CCRotateBy* rotate = CCRotateBy::create(1.0, 180, 180);
	CCRepeatForever* repeat = CCRepeatForever::create(rotate);
	extraGraphic->runAction(repeat);
}

EnemyOmni::~EnemyOmni()
{

}

void EnemyOmni::move(float dt)
{
	// get hero
	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();

	if(hero)
	{
		CCPoint pos = hero->getPositionInWorldSpace();
		CCPoint selfPos = getPositionInWorldSpace();

		CCPoint distance = pos - selfPos;
		distance.x *= sensitiveToHero;

		lastMoveX = lastMoveX * 0.97 + distance.x * 0.0003;;

		setPositionX(getPositionX() + lastMoveX);

	}

	setPositionY(getPositionY() + aircraftDef.omniYVelocity * dt);
}

void EnemyOmni::shot(float dt)
{
	//static int frame = 0;
	//frame ++;

	if(defaultGun)
	{
		defaultGun->trigger(true);
	}
}

void EnemyOmni::update(float dt)
{
	Aircraft::update(dt);

	// move
	move(dt);

	// shot
	shot(dt);
}
