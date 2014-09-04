#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;
using namespace std;

typedef enum tag_gravity
{
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
}Gravity;

const int NumberInterval = 4;
class NumberSeries : public Ref
{
public:
	NumberSeries();
	~NumberSeries();

	virtual bool init();
	CREATE_FUNC(NumberSeries);

	void loadNumber(const char* fmt, int base = 0);
	SpriteFrame* at(int index);
protected:
private:
	Vector<SpriteFrame*> m_numberSeries;
};

class Number
{
public:
	Number();
	~Number();

	static Number* getInstance();
	static void destroyInstance();

	virtual bool loadNumber(const char* name, const char* fmt, int base = 0);

	Node* convert(const char* name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);
	virtual bool init();
private:
	Map<string, NumberSeries*> m_numberContainer;
	static Number* sharedNumber;
};
