/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"ImageScene.h"
#include "stopMessage.h"
#include<ui/CocosGUI.h>
#include "dragon.h"
#include "gameOver.h"
#include<spine/spine.h>
#include "BgScene.h"
#include "bar.h"
#include "Game_Scene.h"
#include<spine/spine-cocos2dx.h>

using namespace spine;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HelloWorld::Init_World()
{

}
HelloWorld::~HelloWorld() { ; }
HelloWorld::HelloWorld()
{
	Dragon_Instance->set_NULL();
	Bar_Instance->set_NULL();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	iSpeed = 4; tag_now = 0; num_des = 2;
	is_show = show_die = 0;
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	CCDirector::getInstance()->setDisplayStats(false);
	schedule(schedule_selector(HelloWorld::tiemer_hander), 0);
	/*auto tt = bar::create();*/
	/*auto game = Game_Scene::create();
	addChild(game);*/

	/*auto visibleSize = Director::getInstance()->getVisibleSize();
	auto stop_Btn = ui::Button::create("stop1.png");
	stop_Btn->setScale(0.6);
	stop_Btn->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(stop_Btn, 10);*/

	addChild(bar::getInstance()->x, 12);//score
	auto Score = Sprite::create("score.png");
	Score->setPosition(55, 25);
	addChild(Score, 12);
	bar::getInstance()->x->setAnchorPoint(Point(0, 1));
	bar::getInstance()->x->setPosition(Score->getPosition() + Point(54, 17));
	//schedule(schedule_selector(Bg::timer_hander), 0);

	/*star_Btn->addClickEventListener([](Ref* ref)
		{
			auto tran = TransitionZoomFlipAngular::create(2, HelloWorld::createScene());
			Director::getInstance()->replaceScene(tran);
		});*/

	initBG();

	addChild(Dragon::getInstance(), 10);
	go = true;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto stop_Btn = ui::Button::create("stop1.png");
	stop_Btn->setScale(0.6);
	stop_Btn->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
	addChild(stop_Btn, 10);
	stop_Btn->addClickEventListener([=](Ref* ref)
		{
			unschedule(schedule_selector(HelloWorld::tiemer_hander));
			auto on = stopMessageBox::create();
			on->to = this;
			on->registerCallback
			([=]() {
				on->to->schedule(schedule_selector(HelloWorld::tiemer_hander), 0);
				on->removeFromParent();
				},
				[=]()
				{
					//on->to->schedule(schedule_selector(HelloWorld::tiemer_hander), 0);
					on->removeFromParent();
					auto tran = TransitionTurnOffTiles::create(2, Bg::create_Scene());
					Director::getInstance()->replaceScene(tran);
				});
			this->addChild(on, 12);
		});

	schedule(schedule_selector(HelloWorld::tiemer_hander, 0));
	return true;
		
}

void HelloWorld::initBG()
{
	//frame = tag_now = 0;
	memset(count, 0, sizeof(count));
	m_bgSprite1 = Sprite::create("1.jpg");
	Size bgSize = m_bgSprite1->getContentSize();
	m_bgSprite1->setPosition(Point(bgSize.width / 2, bgSize.height / 2));
	this->addChild(m_bgSprite1);

	m_bgSprite2 = Sprite::create("2.jpg");
	m_bgSprite2->setPosition(Point(bgSize.width + bgSize.width / 2 - 10, bgSize.height / 2));
	this->addChild(m_bgSprite2);

	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("particle_texture.plist");
	m_emitter1->retain();
	m_emitter1->setPosition(1700, 800);
	m_emitter1->release();
	addChild(m_emitter1);

	ParticleSystem* m_emitter2 = ParticleSystemQuad::create("fire.plist");
	m_emitter2->retain();
	m_emitter2->setPosition(1150, 400);
	m_emitter2->release();
	addChild(m_emitter2, 10);


}

void HelloWorld::tiemer_hander(float dt)
{
	if (is_show)show_die++;
	if (Dragon::getInstance()->the_dragon_die)
	{
		go = false;
		is_show = 1;
		if (show_die == 40)
		{
			count[num] = 1;
			unschedule(schedule_selector(HelloWorld::tiemer_hander));
			
			auto over = gameOver::create();
			over->to = this;
			over->registerCallback([=]() {},
				[=]()
				{
					auto ans = over->txt->getString();
					if (over->txt->getString() == "ILXyr&Tlj&MD")
					{
						over->to->schedule(schedule_selector(HelloWorld::tiemer_hander, 0));
						over->to->go = true;
						over->to->is_show = false;
						over->to->show_die = 0;
						over->removeFromParent();
						Dragon::getInstance()->comm_life();
					}
					else
					{
						over->removeFromParent();
						auto tran = TransitionTurnOffTiles::create(2, Bg::create_Scene());
						Director::getInstance()->replaceScene(tran);
					}
				});
			addChild(over, 16);
		}
	}
	frame++;
	iSpeed + ((float)bar::getInstance()->Score / 20);
	if (frame * iSpeed >= 400 && num_now <= num_des)
	{
		num_now++;
		bar::getInstance()->createBarBytag(this, 1, tag_now + 1, tag_now + 2);
		frame = 0;
		tag_now += 2;
	}
	bar::getInstance()->updata_ByScene(this, iSpeed);
	Dragon::getInstance()->timer_Hander_byScene(go);

	int posX1 = m_bgSprite1->getPositionX();    //背景地图1的Y坐标
	int posX2 = m_bgSprite2->getPositionX();    //背景地图2的Y坐标

	/* 两张地图向左滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
	posX1 -= iSpeed;
	posX2 -= iSpeed;

	/* 图大小 */
	Size bgSize = m_bgSprite1->getContentSize();

	/* 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在
	 第2个地图后面 */
	if (posX1 <= -bgSize.width / 2) {
		posX1 = bgSize.width + bgSize.width / 2;
	}
	/* 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2
	 个地图紧贴在第1个地图后面 */
	if (posX2 <= -bgSize.width / 2) {
		posX2 = bgSize.width + bgSize.width / 2;
	}

	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);

	iSpeed = 4.0;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
