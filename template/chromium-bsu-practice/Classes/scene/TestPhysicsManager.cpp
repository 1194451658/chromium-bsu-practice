#include "TestPhysicsManager.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/Aircraft.h"
#include "input/InputManager.h"

#include "physics/GB2ShapeCache-x.h"
#include "physics/GLES-Render.h"

#include "physics/PhysicsManager.h"

#include "SimpleAudioEngine.h"

#include <stdlib.h>

#include "cocos-ext.h"

#include "map/AutoTiledBackground.h"

#include "engine/CCDrawGameObjectShadowNode.h"

#include "GameController.h"

USING_NS_CC_EXT;

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* TestPhysicsManager::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestPhysicsManager *layer = TestPhysicsManager::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestPhysicsManager::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// ------------
	// init input manager
	// ---------------
	InputManager* input = InputManager::sharedInstance();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(input);

	// -------------
	// init physics
	// -----------
	b2World* physicsWorld = PhysicsManager::sharedInstance()->getPhysicsWorld();
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("png/physics.plist");

	// step
	schedule(schedule_selector(TestPhysicsManager::stepForPhysicsManager));

	// debug draw
	GLESDebugDraw* debugDraw = new GLESDebugDraw(PTM_RATIO);
	physicsWorld->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	// flags += b2Draw::e_aabbBit;
	// flags += b2Draw::e_pairBit;
	// flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);

	// -----------------
	// Init Audio
	// ------------
	SimpleAudioEngine::sharedEngine()->preloadEffect("wav/exploStd.wav");


	// ------------
	// Hero Aircraft
	// -----------
	Aircraft* hero = Aircraft::createHeroAircraft();
	addChild(hero);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	hero->setPosition(screenSize.width/2, screenSize.height/2);

	GameController::sharedInstance()->setPlayerAircraft(hero);

	//// -------------
	//// Enemy Aircraft
	//// ------------
	//Aircraft* enemy = Aircraft::createEnemyAircraft01();
	//addChild(enemy); 
	//shadowLayer->addGameObject(enemy);
	//enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);

	// enemy boss
	Aircraft* boss = Aircraft::createBoss00();
	addChild(boss);
	boss->setPosition(screenSize.width/2, screenSize.height/2 + 150);



	return true;
}

void TestPhysicsManager::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

void TestPhysicsManager::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();
	world->DrawDebugData();
	kmGLPopMatrix();
}