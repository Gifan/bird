#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"

USING_NS_CC;

typedef enum tagActionState
{
	ACTION_STATE_IDLE,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
}ActionState;

const int BIRD_SPRITE_TAG = 10003;

class BirdSprite : public Sprite
{
public:
	BirdSprite();
	~BirdSprite();

	static BirdSprite* getInstance();

	bool virtual init();

	bool createBird();

	void idle();
	void fly();
	void die();

protected:
	static cocos2d::Animation* createAnimation(const char* fmt, int iCount, float fps);

	void createBirdByRandom();

private:
	static BirdSprite* shareBirdSprite;

	bool changeState(ActionState state);

	Action* m_pIdleAction;
	Action* m_pSwingAction;
	ActionState m_stCurrentStatus;
	string m_birdName;
	string m_birdNameFormat;
	unsigned int m_isFirstTime;
};