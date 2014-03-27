
#include "heroAircraft.h"
#include "input/InputManager.h"

#include "util/GB2ShapeCache-x.h"


HeroAircraft* HeroAircraft::create()
{
	HeroAircraft* hero = new HeroAircraft();

	if(hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

HeroAircraft::HeroAircraft()
{
}

bool HeroAircraft::init()
{
	// init base class
	if(Aircraft::init())
	{
		// create gun
		CCPoint velocity(0, 200);
		defaultGun = HeroDefaultGun::create(this, velocity, PhysicsManager::JUSTICE);
		addChild(defaultGun);
		return true;
	}

	return false;
}

HeroAircraft::~HeroAircraft()
{
	CC_SAFE_RELEASE_NULL(graphics);
}

void HeroAircraft::update(float dt)
{
	// move
	InputManager* input = InputManager::sharedInstance();

	if(input->arrowState[input->ARROW_UP] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() + 10);

	if(input->arrowState[input->ARROW_DOWN] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() - 10);

	if(input->arrowState[input->ARROW_LEFT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() - 10);

	if(input->arrowState[input->ARROW_RIGHT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() + 10);

	if(input->arrowState[input->FIRE] == InputManager::ARROW_PRESSED)
	{
		defaultGun->trigger(true);
	}
	else
	{
		defaultGun->trigger(false);
	}
}

CCNode* HeroAircraft::initGraphics()
{
	// create the graphics
	CCSprite* sprite = CCSprite::create("png/hero.png");
	return sprite;
}

b2Body* HeroAircraft::initPhysics()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	// physics world
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

	// body 
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.allowSleep = false;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(screenSize.width/2/PhysicsManager::PTM_RATIO, screenSize.height/2/PhysicsManager::PTM_RATIO);

	b2Body *body = world->CreateBody(&bodyDef);

	// b2PolygonShape shape;
	// shape.SetAsBox(160.0 / PTM_RATIO, 160.0 / PTM_RATIO);
	// body->CreateFixture(&shape, 1);
    
	// add the fixture 
	GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body, "hero");

	// set fixture collide filter
	b2Filter filter;
	filter.groupIndex	= PhysicsManager::JUSTICE;
	filter.categoryBits = PhysicsManager::AIRCRAFT;
	filter.maskBits		= PhysicsManager::AIRCRAFT | 
					PhysicsManager::AMMO;

	b2Fixture* fixtureList = body->GetFixtureList();

	while(NULL != fixtureList)
	{
		fixtureList->SetFilterData(filter);
		fixtureList = fixtureList->GetNext();
	}

	return body;
}
