#pragma once
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "time.h"
#include "cocos2d.h"
#include "BirdSprite.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace CocosDenshion;

const int START_BUTTON_TAG = 100;
class WelcomeLayer : public Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();

	virtual bool init();
	void initBackground();
	void initBird();
	void initLand();
	CREATE_FUNC(WelcomeLayer);
private:
	void menuStartCallback(Ref* pSender);

	void scrollLand(float delta);

	Sprite* m_pLand1;
	Sprite* m_pLand2;
	BirdSprite* m_pBird;
};