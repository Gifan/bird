#include "LoadingScene.h"
LoadingScene::LoadingScene(){}

LoadingScene::~LoadingScene(){}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	Sprite* pBackground = Sprite::create("splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	pBackground->setPosition(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/2.0f);
	this->addChild(pBackground);

	Director::getInstance()->getTextureCache()->addImageAsync(
		"atlas.png",
		CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	return true;
}

void LoadingScene::onEnter()
{
	Scene::onEnter();
}

void LoadingScene::loadingCallBack(Texture2D* pTexture)
{
	AtlasLoader::getInstance()->loadAtlas("atlas.txt", pTexture);

	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");

	auto scene = WelcomeScene::create();
	TransitionScene* pTransition = TransitionFade::create(3, scene);
	Director::getInstance()->replaceScene(pTransition);
}
