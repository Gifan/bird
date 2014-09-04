#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "StatusLayer.h"
#include "OptionLayer.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	void restart();

	CREATE_FUNC(GameScene);
};