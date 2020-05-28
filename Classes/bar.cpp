#include "bar.h"
#include<cocos2d.h>
#include<stdlib.h>
#include<time.h>
#include "Game_Scene.h"
#include<spine/spine-cocos2dx.h>
#include<spine/spine.h>
#include<vector>
#include<cmath>
#include "BgScene.h"
#include "Dragon.h"
#include<iostream>
#include "HelloWorldScene.h"
using namespace cocos2d;

bar* bar::_instance = nullptr;

bar* bar::getInstance()
{
	if (_instance == nullptr||!_instance->x)
	{
		_instance = new (std::nothrow)bar;
		_instance->init();
	}
	return _instance;
}

bool bar::init()
{
	memset(add, 0, sizeof(add));
	for (int i = 1; i <= 6; i += 2)add[i] = 1;
	if (!Node::init())
	{
		return false;
	}
	now.clear();
	first = 1;
	Score = 0;
	x = LabelTTF::create("0", "GameFont.ttf", 30);
	x->setPosition(500, 40);
	visibleSize = Director::getInstance()->getVisibleSize();
	return true;
}

void bar::createBarBytag(Node* node, const int order, const int tag_1, const int tag_2)
{
	bars a, b;

	a.is_bottom = 1;
	b.is_top = 1;

	a.skeleton = spine::SkeletonAnimation::createWithFile("skeleton.json", "skeleton.atlas");
	//a.skeleton->addAnimation(1, "normal", true);
	b.skeleton = spine::SkeletonAnimation::createWithFile("bar1.json", "bar1.atlas");

	b.tag = tag_2;
	a.tag = tag_1;

	srand(time(NULL));
	b.skeleton->setPosition(Point(1300, (rand() % 414) - 9));
	int dex = b.skeleton->getPositionY() + 275 - 75;
	int ans = (rand() % dex) - 414;
	if (ans > 43)ans = 43;
	a.skeleton->setPosition(1300 - 41, ans);
	
	//b.skeleton->setPosition(700, 0);
	//a.skeleton->setPosition(700, 0);
	//auto bb = b.skeleton->getBoundingBox();
	//auto aa = a.skeleton->getBoundingBox();
	/*a.skeleton->isRunning();
	b.skeleton->isRunning();*/
	node->addChild(a.skeleton, order, tag_1);
	node->addChild(b.skeleton, order, tag_2);

	a.bound = a.skeleton->getBoundingBox().size;
	a.x = a.skeleton->getBoundingBox().origin.x;
	a.y = a.skeleton->getBoundingBox().origin.y;
	b.bound = b.skeleton->getBoundingBox().size;
	b.x = b.skeleton->getBoundingBox().origin.x;
	b.y = b.skeleton->getBoundingBox().origin.y;

	now.insert(std::pair<int, bars>(a.tag, a));
	now.insert(std::pair<int, bars>(b.tag, b));

	return;

}

void bar::updata_ByScene(Node* node,int iSpeed)
{
	x->setString(std::to_string(Score));
	for (begin = now.begin(); begin != now.end(); begin++)
	{
		spine::SkeletonAnimation* br = (spine::SkeletonAnimation*)node->getChildByTag((*begin).first);
		auto dra = Dragon::getInstance()->get_dragon().origin;
		dra.y += 15;
		dra.x += 70;
		auto bou = br->getBoundingBox();
		if (Dragon::getInstance()->getLife() > 0 && !Dragon::getInstance()->die_frame)
		{

			if ((*begin).second.is_top && !add[(*begin).first])
			{
				if (fabs(br->getBoundingBox().origin.x - dra.x) <= 4)
					if (fabs(br->getBoundingBox().origin.x - dra.x) >= 0)
					{
						if (br->getBoundingBox().origin.y < dra.y)
						{
							Dragon::getInstance()->hurt();
							if (Dragon::getInstance()->getLife() > 0)
								Dragon::getInstance()->skeletonNode->runAction(Blink::create(1.5f, 3));
						}
						else if (!add[(*begin).first])
							Score++, add[(*begin).first] = 1;
					}
			}
			else if (add[(*begin).first] && br->getBoundingBox().origin.x - dra.x > 400)
				add[(*begin).first] = 0;
			if ((*begin).second.is_bottom && !add[(*begin).first])
			{
				if (fabs(br->getBoundingBox().origin.x - dra.x) <= 4)
					if (fabs(br->getBoundingBox().origin.x - dra.x) >= 0)
						if (br->getBoundingBox().origin.y + 414 > dra.y)
						{
							Dragon::getInstance()->hurt();
							if (Dragon::getInstance()->getLife() > 0)
								Dragon::getInstance()->skeletonNode->runAction(Blink::create(1.5f, 3));
						}
						else add[(*begin).first] = 1, br->setAnimation(0, "flow", false),
							br->setTimeScale(1.0f);
			}
			else if (add[(*begin).first] && br->getBoundingBox().origin.x - dra.x > 400)
				add[(*begin).first] = 0;
		}
		else if (!Dragon::getInstance()->getLife() && !Dragon::getInstance()->die_frame)
		{
			Dragon::getInstance()->skeletonNode->setTimeScale(5.0f);
			Dragon::getInstance()->skeletonNode->addAnimation(0, "die", false);
			Dragon::getInstance()->the_dragon_die = true;
			Dragon::getInstance()->die_frame = 1;
			Dragon::getInstance()->hurt();
		}
		(*begin).second.skeleton->setPositionX((*begin).second.skeleton->getPositionX() - iSpeed);
		if ((*begin).second.skeleton->getPositionX() < -50)
		{
			auto  a = node->getChildByTag((*begin).first + 1);
			spine::SkeletonAnimation* b = (spine::SkeletonAnimation*) node->getChildByTag((*begin).first);
			srand(time(NULL));
			int Ping = -rand() % 95;
			a->setPosition(Point(1300 + Ping, (rand() % 414) - 9));
			int dex = a->getPositionY() + 275;
			int ans = (rand() % dex) - 414;
			if (a->getPositionY() + 275 - (ans + 414 - 42) < 85)ans = a->getPositionY() - 182;
			if (a->getPositionY() + 275 - (ans + 414 - 42) >= 150)ans = a->getPositionY() - 247;
			if (ans > 43)ans = 43;
			b->setPosition(1300 - 46 + Ping, ans);
			b->setAnimation(0, "normal", true);
			b->setTimeScale(0.0f);
		}
	}
}

void bar::set_NULL()
{
	now.clear();
	Score = 0;
	x = LabelTTF::create("0", "GameFont.ttf", 30);
	x->setPosition(500, 40);
}
