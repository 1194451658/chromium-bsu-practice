
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


#include "EnemyBoss00.h"
#include "GameController.h"
#include "math.h"

EnemyBoss00* EnemyBoss00::create(AircraftDef def)
{
	EnemyBoss00* hero = new EnemyBoss00();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

EnemyBoss00::EnemyBoss00()
{
}

bool EnemyBoss00::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		name = "EnemyBoss00";

		// create gun
		Gun* lateralGun = Gun::createEnemyBoss00Gun0();
		Gun* middleGun = Gun::createEnemyBoss00Gun1();
		lateralGun->retain();
		middleGun->retain();

		lateralGun->setOwnerAircraft(this);
		middleGun->setOwnerAircraft(this);

		this->lateralGun = lateralGun;
		this->middleGun = middleGun;

		lateralGun->setDirection(ccp(0,-1));
		middleGun->setDirection(ccp(0,-1));

		addChild(lateralGun);
		addChild(middleGun);

		return true;
	}

	return false;
}

EnemyBoss00::~EnemyBoss00()
{

}

void EnemyBoss00::move(float dt)
{
	static float lastMoveX = 0;
	static float lastMoveY = 0;
	static float time = 0;
	static float shiftX = 200;
	static float yDistance = 400;

	time += dt;

	// get hero
	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();

	if(hero)
	{
		CCPoint pos = hero->getPositionInWorldSpace();
		CCPoint selfPos = getPositionInWorldSpace();

		CCPoint distance = pos - selfPos;

		distance.x += shiftX * sin(3.151*2 * time / 2);
		lastMoveX = lastMoveX * 0.97 + distance.x * 0.0003;

		distance.y += yDistance;
		lastMoveY = lastMoveY * 0.97 + distance.y * 0.0003;

		setPositionX(getPositionX() + lastMoveX);
		setPositionY(getPositionY() + lastMoveY);
	}
}

void EnemyBoss00::shot(float dt)
{
	static int frame = 0;
	frame ++;

	// middle gun
	int frameInMiddleGun = frame % (60*3);
	if(frameInMiddleGun > 60*2 + 30)
	{
		middleGun->trigger(true);
	}else
	{
		middleGun->trigger(false);
	}

	// lateral gun
	int frameInLateralGUn = frame % (60*3);
	if(frameInLateralGUn > 60*2)
	{
		lateralGun->trigger(true);
	}else
	{
		lateralGun->trigger(false);
	}
}

void EnemyBoss00::update(float dt)
{
	Aircraft::update(dt);

	// move
	move(dt);

	// shot
	shot(dt);
}