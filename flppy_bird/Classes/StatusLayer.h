#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

const string NUMBER_SCORE = "number_score";
const string NUMBER_FONT = "font";
const int CURRENT_SCORE_SPRITE_TAG = 10001;

class StatusLayer : public Layer, public StatusDelegate
{
public:
	StatusLayer();
	~StatusLayer();
	
	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart();
	void onGamePlaying(int iScore);
	void onGameEnd(int curScore, int bestScore);

private:
	void showReadyStatus();
	void showStartStatus();
	void showOverStatus(int curScore, int bestScore);
	void loadWhiteSprite();
	void blinkFullScreen();
	void fadeInGameOver();
	void jumpToScorePanel();
	void fadeInRestartBtn();
	void refreshScoreCallback();
	void refreshScoreExecutor(float delta);
	string getMedalsName(int iScore);
	void setBlinkSprite();
	void blinkAction();
	void menuRestartCallback(Ref* pSender);
	Sprite* m_pBlink;
	Sprite* m_pScoreSprite;

	Sprite* m_pGetreadySprite;

	Sprite* m_pTutorialSprite;

	Sprite* m_pWhiteSprite;

	int m_iCurrentScore;

	int m_piBestScore;

	int m_iTmpScore;

	bool m_bIsNewRecord;

	Point originPoint;

	Size visibleSize;
};