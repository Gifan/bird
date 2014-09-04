#pragma once
#include "cocos2d.h"
#include "UserRecord.h"
#include "OptionLayer.h"
#include "BirdSprite.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

#define  min(X, Y) ((X) < (Y) ? (X) : (Y))
#define  max(X, Y) ((X) > (Y) ? (X) : (Y))

const int UP_PIP             = 21;
const int DOWN_PIP           = 12;
const int PIP_PASS           = 30;
const int PIP_NEW            = 31;

const int BIRD_RADIUS        = 15;
const int PIP_HEIGHT         = 320;
const int PIP_WIDTH          = 52;
const int PIP_SHIFT_SPEED    = 80.0f;
const int PIP_DISTANCE       = 100;
const int PIP_INTERVAL       = 180;
const int PIP_COUNT          = 2;
const int WAIT_DISTANCE      = 100;

typedef enum tag_game_status
{
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
}GameStatus;

typedef enum tag_collider
{
	ColliderTypeBird    = 1,
	ColliderTypeLand    = 2,
	ColliderTypePip     = 4
}ColliderType;

class StatusDelegate
{
public:
	virtual void onGameStart() = 0;
	virtual void onGamePlaying(int iScore) = 0;
	virtual void onGameEnd(int iCurScore, int iBestScore) = 0;
};

class GameLayer : public Layer, public OptionDelegate
{
public:
	GameLayer();
	~GameLayer();

	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	virtual void onTouch();

	void setPhyWorld(PhysicsWorld* pWorld) { this->m_pWorld = pWorld; }
	void addBird();
	void addGround();
	bool initLand();
	
private:
	void rotateBird();
	void createPips();
	int getRandomHeight();
	void checkHit();
	void birdSpriteFadeOut();
	void birdSpriteRemove();
	void scrollLand(float delta);
	bool onContactBegin(PhysicsContact& contact);
	void gameOver();

	PhysicsWorld* m_pWorld;
	GameStatus m_stGameStatus;
	int m_iScore;
	BirdSprite* m_pBird;
	Node* m_pGroundNode;
	vector<Node*> m_pips;
	Sprite* m_pLandSprite1;
	Sprite* m_pLandSprite2;
	SEL_SCHEDULE shitfLand;
	bool m_rollLandSign;
};