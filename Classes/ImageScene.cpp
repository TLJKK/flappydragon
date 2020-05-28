#include "ImageScene.h"

Scene* ImageScene::createscene()
{
	Scene* scene = Scene::create();

	ImageScene* layer = ImageScene::create();
	scene->addChild(layer);

	return scene;
}

bool ImageScene::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	Sprite* ali = Sprite::create();
	ali->setPosition(size.width / 2, size.height / 2);
	addChild(ali);
	return true;
}