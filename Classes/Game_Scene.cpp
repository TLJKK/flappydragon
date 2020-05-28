#include "Game_Scene.h"
//#include "BgScene.h"
#include "Dragon.h"
#include "bar.h"

#pragma execution_character_set("utf-8")
USING_NS_CC;

Scene* Game_Scene::create_Game_Scene()
{
	auto scene = Scene::create();

	auto layer = Game_Scene::create();

	scene->addChild(layer);

	return scene;
}

bool Game_Scene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::init())
	{
		return false;
	}
	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("fire.plist");
	m_emitter1->retain();
	m_emitter1->setPosition(1150, 400);
	m_emitter1->release();
	addChild(m_emitter1, 10);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	initBG();
	frame = 0;

	return true;
}


void Game_Scene::initBG()
{
	frame = tag_now = 0;

	m_bgSprite1 = Sprite::create("1.jpg");
	Size bgSize = m_bgSprite1->getContentSize();
	m_bgSprite1->setPosition(Point(bgSize.width / 2, bgSize.height / 2));
	this->addChild(m_bgSprite1);

	m_bgSprite2 = Sprite::create("2.jpg");
	m_bgSprite2->setPosition(Point(bgSize.width + bgSize.width / 2 - 10, bgSize.height / 2));
	this->addChild(m_bgSprite2);

}
void Game_Scene::update_byScene(float delta, int iSpeed)
{
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

}