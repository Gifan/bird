#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"
#include "time.h"
USING_NS_CC;
using namespace std;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();

	virtual bool init();

	CREATE_FUNC(BackgroundLayer);

	static float getLandHeight();
};