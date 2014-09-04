#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer(){}
WelcomeLayer::~WelcomeLayer(){}

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	time_t t = time(NULL);
	tm* pLt = localtime(&t);
	int hour = pLt->tm_hour;
	
	Sprite* pBackground;
	if (hour >= 6 && hour <=17)
	{
		pBackground = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}
	else
	{
		pBackground = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	pBackground->setAnchorPoint(Point::ZERO);
	pBackground->setPosition(Point::ZERO);
	this->addChild(pBackground);

	Sprite* pTitle = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	pTitle->setPosition(Point(origin.x + visibleSize.width / 2.0f, origin.y + (visibleSize.height*5)/ 7.0f));

	Sprite* pStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* pActiveStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	pActiveStartButton->setPositionY(5.0f);
	auto menuItem = MenuItemSprite::create(pStartButton, pActiveStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Point(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/5));
	this->addChild(menu, 1);

	this->m_pBird = BirdSprite::getInstance();
	this->m_pBird->createBird();
	this->m_pBird->setTag(BIRD_SPRITE_TAG);
	this->m_pBird->setPosition(Point(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height*3/5.0f-10.0f));;
	this->m_pBird->idle();
	this->addChild(this->m_pBird);

	this->m_pLand1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_pLand1->setAnchorPoint(Point::ZERO);
	this->m_pLand1->setPosition(Point::ZERO);
	this->addChild(this->m_pLand1);

	this->m_pLand2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_pLand2->setAnchorPoint(Point::ZERO);
	this->m_pLand2->setPosition(this->m_pLand1->getContentSize().width-2.0f, 0);
	this->addChild(this->m_pLand2);

	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);

	Sprite* pCopyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	pCopyright->setPosition(Point(origin.x + visibleSize.width/2.0f, origin.y + visibleSize.height/6.0f));
	this->addChild(pCopyright, 10);
	return true;
}

void WelcomeLayer::scrollLand(float delta)
{
	this->m_pLand1->setPositionX(this->m_pLand1->getPositionX() - 2.0f);
	this->m_pLand2->setPositionX(this->m_pLand1->getPositionX() + this->m_pLand1->getContentSize().width - 2.0f);

	if (this->m_pLand2->getPositionX() <= 0)
	{
		this->m_pLand1->setPositionX(0);
	}
}

void WelcomeLayer::menuStartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();
	TransitionScene* pTransition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(pTransition);
}