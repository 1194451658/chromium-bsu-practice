
#ifndef __HEROAIRCRAFT_H__
#define __HEROAIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Aircraft.h"

#include "gun/HeroDefaultGun.h"

USING_NS_CC;

class HeroAircraft : public Aircraft, public CCKeypadDelegate
{
public:
	static HeroAircraft* create();
	~HeroAircraft();

public:
    // update
    virtual void update(float time);
protected:

private: 
    HeroAircraft();
    virtual CCNode* initGraphics();
    virtual b2Body* initPhysics();

private:
    bool init();

public:

private:
    HeroDefaultGun* defaultGun;
};

#endif
