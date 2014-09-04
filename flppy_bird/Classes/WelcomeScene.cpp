#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(){}
WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto _welcomeLayer = WelcomeLayer::create();
	if (_welcomeLayer == NULL) return false;
	this->addChild(_welcomeLayer);
	return true;
}