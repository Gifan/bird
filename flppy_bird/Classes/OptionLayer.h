#pragma  once
#include "cocos2d.h"
USING_NS_CC;

class OptionDelegate
{
public:
	virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
	OptionLayer();
	~OptionLayer();

	virtual bool init();
	CREATE_FUNC(OptionLayer);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

	CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};