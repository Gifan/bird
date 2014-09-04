#include "AtlasLoader.h"

AtlasLoader* AtlasLoader::shareAtlasLoader = nullptr;

AtlasLoader* AtlasLoader::getInstance()
{
	if (shareAtlasLoader == NULL)
	{
		shareAtlasLoader = new AtlasLoader();
		if (!shareAtlasLoader->init())
		{
			delete shareAtlasLoader;
			shareAtlasLoader = NULL;
			CCLOG("Error: Could not init shareAtlasLoader");
		}
	}
	return shareAtlasLoader;

}

void AtlasLoader::destroyInstance()
{
	CC_SAFE_DELETE(shareAtlasLoader);
}

AtlasLoader::AtlasLoader()
{}

bool AtlasLoader::init()
{
	return true;
}

void AtlasLoader::loadAtlas(const string& filename)
{
	auto textureAtlas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
	this->loadAtlas(filename, textureAtlas);
}

void AtlasLoader::loadAtlas(const string& filename, Texture2D* pTexture)
{
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Atlas atlas;

	pos = data.find_first_of("\n");
	string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while (line != "")
	{
		sscanf(line.c_str(), "%s %d %d %f %f %f %f",
			atlas.stName, &atlas.iWidth, &atlas.iHeight,
			&atlas.start.x, &atlas.start.y,
			&atlas.end.x, &atlas.end.y);

		atlas.start.x *= 1024;
		atlas.start.y *= 1024;
		atlas.end.x  *= 1024;
		atlas.end.y *= 1024;

		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);

		if (atlas.stName == string("land"))
		{
			atlas.start.x += 1;
		}
		Rect rect = Rect(atlas.start.x , atlas.start.y, atlas.iWidth, atlas.iHeight);
		auto frame = SpriteFrame::createWithTexture(pTexture, rect);
		this->m_pSpriteFrames.insert(string(atlas.stName), frame);
	}
}

SpriteFrame* AtlasLoader::getSpriteFrameByName(const string& name)
{
	return this->m_pSpriteFrames.at(name);
}