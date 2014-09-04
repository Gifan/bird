#include "BirdSprite.h"

BirdSprite::BirdSprite()
{}

BirdSprite::~BirdSprite()
{}

BirdSprite* BirdSprite::shareBirdSprite = nullptr;
BirdSprite* BirdSprite::getInstance()
{
	if (shareBirdSprite == NULL)
	{
		shareBirdSprite = new BirdSprite();
		if (!shareBirdSprite->init())
		{
			CC_SAFE_DELETE(shareBirdSprite);
			CCLOG("Error: Could not init shareBirdSprite");
		}
	}
	return shareBirdSprite;
}

bool BirdSprite::init()
{
	this->m_isFirstTime = 3;
	return true;
}

bool BirdSprite::createBird()
{
	this->createBirdByRandom();

	if (Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(this->m_birdName)))
	{
		Animation* pAnimation = this->createAnimation(this->m_birdNameFormat.c_str(), 3, 10.0f);
		Animate* pAnimate = Animate::create(pAnimation);
		this->m_pIdleAction = RepeatForever::create(pAnimate);

		ActionInterval* pUp = CCMoveBy::create(0.4f, Point(0, 8));
		ActionInterval* pUpBack = pUp->reverse();
		this->m_pSwingAction = RepeatForever::create(Sequence::createWithTwoActions(pUp, pUpBack));

		return true;
	}
	else
	{
		return false;
	}
}

void BirdSprite::idle()
{
	if (changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_pIdleAction);
		this->runAction(m_pSwingAction);
	}
}

void BirdSprite::fly()
{
	if (changeState(ACTION_STATE_FLY))
	{
		this->stopAction(m_pSwingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void BirdSprite::die()
{
	if (changeState(ACTION_STATE_DIE))
	{
		this->stopAllActions();
	}
}

Animation* BirdSprite::createAnimation(const char* fmt, int iCount, float fps)
{
	Animation* pAnimation = Animation::create();
	pAnimation->setDelayPerUnit(1/fps);

	for (int i = 0; i < iCount; i++)
	{
		const char* filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame* pFrame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		pAnimation->addSpriteFrame(pFrame);
	}
	return pAnimation;
}

bool BirdSprite::changeState(ActionState state)
{
	this->m_stCurrentStatus = state;
	return true;
}

void BirdSprite::createBirdByRandom()
{
	if(this->m_isFirstTime & 1){
		this->m_isFirstTime &= 2;
	}else if(this->m_isFirstTime & 2){
		this->m_isFirstTime &= 1;
		return ;
	}
	srand((unsigned)time(NULL));
	int type = ((int)rand())% 3;
	switch (type)
	{
	case 0:
		this->m_birdName = "bird0_0";
		this->m_birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->m_birdName = "bird1_0";
		this->m_birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->m_birdName = "bird2_0";
		this->m_birdNameFormat = "bird2_%d";
		break;
	default:
		this->m_birdName = "bird2_0";
		this->m_birdNameFormat = "bird2_%d";
		break;
	}
}
