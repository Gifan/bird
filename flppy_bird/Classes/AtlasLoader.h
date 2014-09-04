#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef struct _atlas
{
	char stName[255];
	int iWidth;
	int iHeight;
	Point start;
	Point end;
}Atlas;

class AtlasLoader
{
public:
	static AtlasLoader* getInstance();

	static void destroyInstance();

	void loadAtlas(const string& filename);

	void loadAtlas(const string& filename, Texture2D* pTexture);

	SpriteFrame* getSpriteFrameByName(const string& name);

protected:

	AtlasLoader();

	virtual bool init();

	static AtlasLoader* shareAtlasLoader;

	Map<std::string, SpriteFrame*> m_pSpriteFrames;

};