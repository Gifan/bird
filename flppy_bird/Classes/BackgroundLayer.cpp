#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(){}
BackgroundLayer::~BackgroundLayer(){}

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	time_t t = time(NULL);
	tm* pLt = localtime(&t);
	int hour = pLt->tm_hour;

	Sprite* pBackground = NULL;
	if (hour >= 6 && hour <= 17)
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

	return true;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}