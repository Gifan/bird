#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class UserRecord : public Ref
{
public:
	UserRecord();
	~UserRecord();

	static UserRecord* getInstance();

	static void destroyInstance();

	virtual bool init();

	void saveIntegerToUserDefault(const char* key, int iScore);

	int getIntegerFromUserDefault(const char* key) const;
private:
	static UserRecord* shareUserRecord;
};