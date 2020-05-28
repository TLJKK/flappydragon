
#include "messageBox.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;
 
BDMessageBox::BDMessageBox()
{
 
}
 
BDMessageBox::~BDMessageBox()
{
 
}
 

bool BDMessageBox::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));
	box = ui::Scale9Sprite::create("menu.png");
	continue_Btn = ui::Button::create("ali.png");
	end_gameBtn = ui::Button::create("yes.png");
	box->setScale(0.7);
	continue_Btn->setScale(0.8);
	end_gameBtn->setScale(0.8);
	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);
	continue_Btn->setPosition(Vec2(viewSize.width / 2-275, viewSize.height / 2 - 65));
	end_gameBtn->setPosition(Point(viewSize.width / 2 + 255, viewSize.height / 2 - 155));
	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	this->addChild(continue_Btn);
	this->addChild(end_gameBtn);
	//, endGamefunc;
	continue_Btn->addClickEventListener([this](Ref* ref)
		{
			if (continueFunc != nullptr)
				continueFunc();
		});
	end_gameBtn->addClickEventListener([this](Ref* ref)
		{
			if (endGamefunc != nullptr)
				endGamefunc();
		});

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
	listener->setSwallowTouches(true);
	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);
    label = Label::create("确定退出吗？ali，xyr.", "GameFont.ttf", 30);
	label->setColor(Color3B::BLACK);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //锚点在中间
	label->setTag(TAG_TOAST_LABEL);
	label->setPosition(Vec2(size.width / 2 + 30, size.height / 2 + 10));
	addChild(label);
	return true;
}

void  BDMessageBox::registerCallback(std::function<void()>continueCallback, std::function<void()>
	endgameCallback)
{
	continueFunc = continueCallback;
	endGamefunc = endgameCallback;
}

//bool BDMessageBox::initWithNode(cocos2d::Node* node,const std::string& msg, const float& time, cocos2d::Vec2 point,const ccMenuCallback& callback )
//{
//	if (!Layer::init())
//	{
//		return false;
//	}
//	//背景
//	
//	_bg = Sprite::create("menu.png");
//	_bg->setAnchorPoint(Point(0.5, 0.5));
//	Size size = _bg->getContentSize();
//	/*this->setContentSize(size * 0.5);*/
// 
//	//显示的信息
//	//_labelExplain = Label::create(Explain, "Helvetica-Bold", 16, Size(200, 100), TextHAlignment::LEFT);
//	Label* label = Label::create(msg.c_str(), "GameFont.ttf", 45, Size(200,150), TextHAlignment::LEFT,TextVAlignment::CENTER);
//	label->setColor(Color3B::BLUE);
//	label->ignoreAnchorPointForPosition(false); //开启锚点有效，不设false就是label被addChild后锚点不是原来的锚点而变为(0,0)左下角,设为false还是取原来的锚点
//	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //锚点在中间
//	label->setTag(TAG_TOAST_LABEL);
//	label->setPosition(Vec2(size.width/2, size.height/2));
// 
//	_bg->addChild(label,0.001);
// 
//	//CallFunc* call = CallFunc::create(callback);
//	//确认提交按钮
//	ui::Button* btnOK = ui::Button::create("yes.png");
//	//btnOK->setScale(0.8f);
//	btnOK->addClickEventListener([](Ref* ref)
//		{
//			Director::getInstance()->end();
//		});
//	btnOK->setScale(1.2);
//	btnOK->setPosition(Vec2(size.width - 190, 195));
//	_bg->addChild(btnOK, 3);
// 
//	//取消按钮
//	ui::Button* btnNo = ui::Button::create("ali.png");
//	//btnOK->setScale(0.8f);
//	btnNo->addClickEventListener([=](Ref* ref)
//		{
//			_bg->setVisible(false);
//			this->removeFromParentAndCleanup(true);
//			Sequence* seq = Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5f, 0.01f, 0.01f)), nullptr, nullptr);
//			_bg->runAction(seq);
//		});
//	btnNo->setScale(1.2);
//	btnNo->setPosition(Vec2(70, 220));
//	_bg->addChild(btnNo, 5);
// 
//	node->addChild(_bg);
//	node->addChild(this, 2);
//	Size ze = Director::getInstance()->getVisibleSize();
//	_bg->setPosition(Point(ze.width / 2, ze.height / 2));
//	this->setPosition(Point(ze.width / 2, ze.height / 2));
//
//	auto listener = EventListenerTouchOneByOne::create();
//	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
//	listener->setSwallowTouches(true);
//	_bg->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _bg);
//
//	return true;
//}
//BDMessageBox* BDMessageBox::createToast(cocos2d::Node* node, const std::string& msg, const float& time, 
//							 cocos2d::Vec2 point,const ccMenuCallback& callback)
//{
//	BDMessageBox* pRet = new BDMessageBox();
//	if (pRet && pRet->initWithNode(node, msg, time, point,callback))
//	{
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = nullptr;
//		return pRet;
//	}
//}
// 
void BDMessageBox::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 0.7f, 0.7f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* tx = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	continue_Btn->runAction(bea);
	end_gameBtn->runAction(cir);
	label->runAction(tx);
}
 