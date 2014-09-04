#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

class LoadingScene : public Scene
{
public:

	LoadingScene();
	~LoadingScene();

	virtual bool init();

	CREATE_FUNC(LoadingScene);

	void onEnter() override;

private:
	void loadingCallBack(Texture2D* pTexture);
};

#endif _LOADING_SCENE_H_