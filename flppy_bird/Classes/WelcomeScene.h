#pragma once
#include "AtlasLoader.h"
#include "WelcomeLayer.h"
#include "BackgroundLayer.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class WelcomeScene : public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
};