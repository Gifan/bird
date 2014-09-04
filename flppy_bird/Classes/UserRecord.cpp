#include "UserRecord.h"
UserRecord::UserRecord(){}
UserRecord::~UserRecord(){}

bool UserRecord::init()
{
	return true;
}
UserRecord* UserRecord::shareUserRecord = nullptr;

UserRecord* UserRecord::getInstance()
{
	if (shareUserRecord == NULL)
	{
		shareUserRecord = new UserRecord();
		if (!shareUserRecord->init())
		{
			CC_SAFE_DELETE(shareUserRecord);
		}
	}
	return shareUserRecord;
}

void UserRecord::saveIntegerToUserDefault(const char* key, int iScore)
{
	UserDefault::getInstance()->setIntegerForKey(key, iScore);
}

int UserRecord::getIntegerFromUserDefault(const char* key) const
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}