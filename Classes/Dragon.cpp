#include "Dragon.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Dragon* Dragon::_instance = nullptr;

Dragon* Dragon::getInstance()
{
	if (_instance == nullptr)
	{
		//CabbagePult;
		_instance = new (std::nothrow)Dragon;
		_instance->init();

	}
	return _instance;
}

void Dragon::set_NULL()
{
	skeletonNode->setTimeScale(1.0f);
	skeletonNode->addAnimation(0, "flying", true);
	Size size = Director::getInstance()->getVisibleSize();
	skeletonNode->setPosition(size.width / 4, size.height / 2);
	this->life = 1;
	this->the_dragon_die = false;
	this->die_frame = 0;
	Dragon::getInstance()->skeletonNode->runAction(Blink::create(1.0f, 3));
}

void Dragon::comm_life()
{
	skeletonNode->setTimeScale(1.0f);
	skeletonNode->addAnimation(0, "flying", true);
	Size size = Director::getInstance()->getVisibleSize();
	skeletonNode->setPosition(size.width / 4, size.height / 2);
	this->the_dragon_die = false;
	this->life = 1;
	Dragon::getInstance()->skeletonNode->runAction(Blink::create(2.8f, 5));
}

bool Dragon::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	skeletonNode = spine::SkeletonAnimation::createWithFile("dragon.json", "dragon.atlas", 0.2f);//0.2是设置图片的缩放比例
	skeletonNode->setPosition(size.width / 4, size.height / 2);
	skeletonNode->setAnchorPoint(Point(0.5, 0.5));
	skeletonNode->addAnimation(0, "flying", true);//true是指循环播放walk动作
	//schedule(schedule_selector(Dragon::timer_Hander), 0);
	//skeletonNode->setVisible(false);
	addChild(skeletonNode);
	this->life = 1;
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [this](Touch* t, Event* e)
	{
		//SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
		if (life > 0)
			skeletonNode->runAction(MoveBy::create(0.5, Point(0, 100)));
		//SimpleAudioEngine::getInstance()->playBackgroundMusic("click.mp3", true);
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen, skeletonNode);
	return true;
}

Rect Dragon::get_dragon()
{
	return skeletonNode->boundingBox();
}

void Dragon::timer_Hander_byScene(int go)
{
	if (life > 0 && skeletonNode->getPositionY() > 30 && go)
		skeletonNode->runAction(MoveBy::create(0.02, Point(0, -4)));
	if (Dragon::getInstance()->die_frame && go)
	{
		Dragon::getInstance()->die_frame++;
		if (Dragon::getInstance()->die_frame == 120)
		{
			Dragon::getInstance()->die_frame = 0;
		}
	}
}

void Dragon::hurt() { this->life--; }

int Dragon::getLife() { return this->life; }