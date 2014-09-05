#include "StatusLayer.h"

StatusLayer::StatusLayer(){}
StatusLayer::~StatusLayer(){}

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->m_piBestScore = 0;
	this->m_iCurrentScore = 0;
	this->m_bIsNewRecord = false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->originPoint = Director::getInstance()->getVisibleOrigin();
	Number::getInstance()->loadNumber(NUMBER_FONT.c_str(), "font_0%02d", 48);
	Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(), "number_score_%02d");
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::showReadyStatus() 
{
	m_pScoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_FONT.c_str(), 0);
	m_pScoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height *5/6));
	this->addChild(m_pScoreSprite);

	m_pGetreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	m_pGetreadySprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2.0f, this->originPoint.y + this->visibleSize.height *2/3.0f));
	this->addChild(m_pGetreadySprite);

	m_pTutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	m_pTutorialSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 1/2.0f));
	this->addChild(m_pTutorialSprite);
}
void StatusLayer::showStartStatus() 
{
	this->m_pGetreadySprite->runAction(FadeOut::create(0.4f));
	this->m_pTutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int m_piBestScore) 
{
	this->m_iCurrentScore = curScore;
	this->m_piBestScore = m_piBestScore;
	if(curScore > m_piBestScore)
	{
		this->m_piBestScore = curScore;
		this->m_bIsNewRecord = true;
	}
	else
	{
		this->m_bIsNewRecord = false;
	}
	this->removeChild(m_pScoreSprite);
	this->blinkFullScreen();
}

void StatusLayer::onGameStart()
{
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score)
{
	this->removeChild(m_pScoreSprite);
	this->m_pScoreSprite = (Sprite* )Number::getInstance()->convert(NUMBER_FONT.c_str(), score);
	m_pScoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height *5/6));
	this->addChild(m_pScoreSprite);
}

void StatusLayer::onGameEnd(int curScore, int m_piBestScore)
{
	this->showOverStatus(curScore,m_piBestScore);
}

void StatusLayer::loadWhiteSprite()
{
	//this white sprite is used for blinking the screen for a short while
	m_pWhiteSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("white"));
	m_pWhiteSprite->setScale(100);
	m_pWhiteSprite->setOpacity(0);
	this->addChild(m_pWhiteSprite,10000);
}

void StatusLayer::blinkFullScreen()
{
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	m_pWhiteSprite->stopAllActions();
	m_pWhiteSprite->runAction(sequence);
	m_pWhiteSprite->setPosition(visibleSize.width/2.0f, visibleSize.height/2.0f);
}

void StatusLayer::fadeInGameOver()
{    
	// create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameoverSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2.0f, this->originPoint.y + this->visibleSize.height *2/3.0f));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel()
{    
	// create the score panel
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);

	//display the  best score on the score panel
	auto bestScoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->m_piBestScore, Gravity::GRAVITY_RIGHT);
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width - 28 ,
		50);
	scorepanelSprite->addChild(bestScoreSprite);


	string medalsName = this->getMedalsName(m_iCurrentScore);
	if(medalsName != "") 
	{
		Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(medalsName));
		medalsSprite->addChild(this->m_pBlink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}

	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if(this->m_bIsNewRecord)
	{
		Sprite* newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("new"));
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height/2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorepanelSprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn()
{
	Node * tmpNode = Node::create();

	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
	//tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);

	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback()
{
	this->m_iTmpScore = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt)
{
	if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
		this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	m_pScoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->m_iTmpScore, Gravity::GRAVITY_RIGHT);
	m_pScoreSprite->setAnchorPoint(Point(1,0));
	m_pScoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width * 3 / 4 + 20.0f, this->originPoint.y + this->visibleSize.height *  1 / 2));
	m_pScoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
	this->addChild(m_pScoreSprite,1000);
	this->m_iTmpScore++;
	if(this->m_iTmpScore > this->m_iCurrentScore){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

void StatusLayer::setBlinkSprite() 
{
	this->m_pBlink = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("blink_00"));
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++)
	{
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--)
	{
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	m_pBlink->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction() 
{
	if(this->m_pBlink && this->m_pBlink->getParent()) {
		Size activeSize = this->m_pBlink->getParent()->getContentSize();
		this->m_pBlink->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}

string StatusLayer::getMedalsName(int score)
{
	this->setBlinkSprite();

	//display the golden silver or bronze iron
	string medalsName = "";
	if(this->m_iCurrentScore >=10 && this->m_iCurrentScore < 20){//iron medals
		medalsName = "medals_0";
	}else if(this->m_iCurrentScore >= 20 && m_iCurrentScore < 30){//bronze medals
		medalsName = "medals_1";
	}else if(m_iCurrentScore >=30 && m_iCurrentScore < 50){//silver medals
		medalsName = "medals_2";
	}else if(m_iCurrentScore >=50){//golden medals
		medalsName = "medals_3";
	}
	return medalsName;
}

void StatusLayer::menuRestartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}