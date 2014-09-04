#include "GameLayer.h"

GameLayer::GameLayer()
{}
GameLayer::~GameLayer()
{}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->m_stGameStatus = GAME_STATUS_READY;
	this->m_iScore = 0;
	this->m_rollLandSign = false;
	if (!initLand()) return false;
	addBird();
	addGround();
	createPips();
	this->shitfLand = schedule_selector(GameLayer::scrollLand);
	this->scheduleUpdate();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameLayer::addBird()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	this->m_pBird = BirdSprite::getInstance();
	this->m_pBird->createBird();

	PhysicsBody* pBody = PhysicsBody::create();
	pBody->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	pBody->setCategoryBitmask(ColliderTypeBird);
	pBody->setCollisionBitmask(ColliderTypeLand & ColliderTypePip);
	pBody->setContactTestBitmask(ColliderTypeLand | ColliderTypePip);
	pBody->setDynamic(true);
	pBody->setLinearDamping(0.0f);
	pBody->setGravityEnable(false);
	this->m_pBird->setPhysicsBody(pBody);
	this->m_pBird->setPosition(origin.x + visibleSize.width/3.0f -5, origin.y + visibleSize.height/2.0f+5);
	this->m_pBird->idle();
	this->addChild(this->m_pBird);

}

void GameLayer::addGround()
{
	this->m_pGroundNode = Node::create();
	float fLandHeight = BackgroundLayer::getLandHeight();
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(288, fLandHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setCategoryBitmask(ColliderTypeLand);
	groundBody->setCollisionBitmask(ColliderTypeBird);
	groundBody->setContactTestBitmask(ColliderTypeBird);
	this->m_pGroundNode->setPhysicsBody(groundBody);
	this->m_pGroundNode->setPosition(144, fLandHeight/2.0f);
	this->addChild(this->m_pGroundNode);
}

bool GameLayer::initLand()
{
	this->m_pLandSprite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_pLandSprite1->setAnchorPoint(Point::ZERO);
	this->m_pLandSprite1->setPosition(Point::ZERO);
	this->addChild(this->m_pLandSprite1, 30);

	this->m_pLandSprite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_pLandSprite2->setAnchorPoint(Point::ZERO);
	this->m_pLandSprite2->setPosition(this->m_pLandSprite1->getContentSize().width-2.0f, -.0f);
	this->addChild(this->m_pLandSprite2, 30);

	return true;
}

bool GameLayer::onContactBegin(PhysicsContact& contact)
{
	this->gameOver();
	return true;
}

void GameLayer::scrollLand(float delta)
{
	this->m_pLandSprite1->setPositionX(this->m_pLandSprite1->getPositionX() - 2.0f);
	this->m_pLandSprite2->setPositionX(this->m_pLandSprite1->getPositionX() + this->m_pLandSprite1->getContentSize().width - 2.0f);
	if (this->m_pLandSprite2->getPositionX() <= 0)
	{
		this->m_pLandSprite1->setPositionX(0);
	}

	for (auto singlePip : this->m_pips)
	{
		singlePip->setPositionX(singlePip->getPositionX() - 2.0f);
		if (singlePip->getPositionX() < -PIP_WIDTH)
		{
			singlePip->setTag(PIP_NEW);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			singlePip->setPositionX(visibleSize.width);
			singlePip->setPositionY(this->getRandomHeight());
		}
	}
}

void GameLayer::onTouch()
{
	if (this->m_stGameStatus == GAME_STATUS_OVER)
	{
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if (this->m_stGameStatus == GAME_STATUS_READY)
	{
		this->delegator->onGameStart();
		this->m_pBird->fly();
		this->m_stGameStatus = GAME_STATUS_START;
		m_rollLandSign = true;
	}
	else if (this->m_stGameStatus == GAME_STATUS_START)
	{
		if (m_rollLandSign)
		{
			this->schedule(this->shitfLand, 0.01f);
			m_rollLandSign = false;
		}
		this->m_pBird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::rotateBird()
{
	float verticalSpeed = this->m_pBird->getPhysicsBody()->getVelocity().y;
	this->m_pBird->setRotation(- min(max(-90, (verticalSpeed*0.2f + 60.0f)), 30));
}

void GameLayer::update(float delta)
{
	if (this->m_stGameStatus == GAME_STATUS_START)
	{
		this->rotateBird();
		this->checkHit();
	}
}

void GameLayer::createPips()
{
	for (int i = 0; i < PIP_COUNT; i++)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite* pPipUp = Sprite::createWithSpriteFrame(
			AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite* pPipDown = Sprite::createWithSpriteFrame(
			AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node* pSinglePip = Node::create();

		pPipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
		pSinglePip->addChild(pPipDown, 0, DOWN_PIP);
		pSinglePip->addChild(pPipUp, 0, UP_PIP);
		pSinglePip->setPosition(visibleSize.width + i*PIP_INTERVAL+WAIT_DISTANCE, this->getRandomHeight());
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(
			pPipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT,Point(0, PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pPipUp->getContentSize()));
		body->setDynamic(false);
		body->setCategoryBitmask(ColliderTypePip);
		body->setCollisionBitmask(ColliderTypeBird);
		body->setContactTestBitmask(ColliderTypeBird);
		pSinglePip->setPhysicsBody(body);
		pSinglePip->setTag(PIP_NEW);

		this->addChild(pSinglePip);
		this->m_pips.push_back(pSinglePip);
	}
}

int GameLayer::getRandomHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::checkHit()
{
	for (auto pip : this->m_pips)
	{
		if (pip->getTag() == PIP_NEW)
		{
			if (pip->getPositionX() < this->m_pBird->getPositionX())
			{
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->m_iScore++;
				this->delegator->onGamePlaying(this->m_iScore);
				pip->setTag(PIP_PASS);
			}
		}
	}
}

void GameLayer::gameOver()
{
	if (this->m_stGameStatus == GAME_STATUS_OVER)
	{
		return ;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");

	int bestScore = UserRecord::getInstance()->getIntegerFromUserDefault("bestScore");

	if (this->m_iScore > bestScore)
	{
		UserRecord::getInstance()->saveIntegerToUserDefault("bestScore", this->m_iScore);
	}
	this->delegator->onGameEnd(this->m_iScore, bestScore);
	this->unschedule(this->shitfLand);
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->m_pBird->die();
	this->m_pBird->setRotation(-90.0f);
	this->birdSpriteFadeOut();
	this->m_stGameStatus = GAME_STATUS_OVER;
}

void GameLayer::birdSpriteFadeOut()
{
	FadeOut* pAnimation = FadeOut::create(1.5);
	CallFunc* pAnimationDone = CallFunc::create(std::bind(&GameLayer::birdSpriteRemove, this));
	Sequence* pSequence = Sequence::createWithTwoActions(pAnimation, pAnimationDone);
	this->m_pBird->stopAllActions();
	this->m_pBird->runAction(pSequence);

}

void GameLayer::birdSpriteRemove()
{
	this->m_pBird->setRotation(0);
	this->removeChild(this->m_pBird);
}