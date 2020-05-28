//bool stopMessageBox::initWithNode(cocos2d::Node* node,const std::string& msg, const float& time, cocos2d::Vec2 point,const ccMenuCallback& callback )
//{
//	if (!Layer::init())
//	{
//		return false;
//	}
//	//背景
//	_bg = Sprite::create("stopface.png");
//	_bg->setAnchorPoint(Point(0.5, 0.5));
//	_bg->setScale(1.5);
//	Size size = _bg->getContentSize();
//	/*this->setContentSize(size * 0.5);*/
// 
//
// 
//	//CallFunc* call = CallFunc::create(callback);
//	//确认提交按钮
//	ui::Button* btnOK = ui::Button::create("mainscene2.png");
//	//btnOK->setScale(0.8f);
//	btnOK->addClickEventListener([=](Ref* ref)
//		{
//			auto tran = TransitionTurnOffTiles::create(2, Bg::create_Scene());
//			Director::getInstance()->replaceScene(tran);
//		});
//	btnOK->setScale(0.8f);
//	btnOK->setPosition(Vec2(size.width / 2, size.height / 2 - 100));
//	_bg->addChild(btnOK, 5);
// 
//	//取消按钮
//	ui::Button* btnNo = ui::Button::create("continue1.png");
//	btnNo->setScale(0.8f);
//	btnNo->addClickEventListener([=](Ref* ref)
//		{
//			CallFunc* removeC = CallFunc::create([this]()   //飘出后要删除掉自身
//				{
//					_bg->setVisible(false);
//					this->removeFromParentAndCleanup(true);    //这里CallFunc参数是lambda表达式，捕获参数是类自身
//				});
//
//			Sequence* seq = Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5f, 0.01f, 0.01f)), removeC, nullptr);
//			_bg->runAction(seq);
//			
//		});
//	Size ze = Director::getInstance()->getVisibleSize();
//	btnNo->setPosition(Vec2(size.width / 2, 220));
//	_bg->addChild(btnNo, 5);
// 
//	node->addChild(_bg);
//	node->addChild(this, 4);
//	
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
//stopMessageBox* stopMessageBox::createToast(cocos2d::Node* node, const std::string& msg, const float& time, 
//							 cocos2d::Vec2 point,const ccMenuCallback& callback)
//{
//	stopMessageBox* pRet = new stopMessageBox();
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
//void stopMessageBox::onEnter()
//{
//	Layer::onEnter();
//	_bg->setVisible(true);
//	//对话框由小到大
//	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
//		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
//	_bg->runAction(seq);
//}
// 
//void stopMessageBox::OkClick()
//{
// 
//}
// 
//void stopMessageBox::CancelClick(Ref *ref)
//{
//	CallFunc* removeC = CallFunc::create([this]()   //飘出后要删除掉自身
//	{
//		_bg->setVisible(false);
//		this->removeFromParentAndCleanup(true);    //这里CallFunc参数是lambda表达式，捕获参数是类自身
//	});
// 
//	Sequence *seq = Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5f, 0.01f, 0.01f)), removeC, nullptr);
//	_bg->runAction(seq);
//}

#include "stopMessage.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;

stopMessageBox::stopMessageBox()
{

}

stopMessageBox::~stopMessageBox()
{

}


bool stopMessageBox::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));
	box = ui::Scale9Sprite::create("stopface.png");
	continue_Btn = ui::Button::create("continue1.png");
	end_gameBtn = ui::Button::create("mainscene2.png");
	/*box->setScale(0.7);
	continue_Btn->setScale(0.8);
	end_gameBtn->setScale(0.8);*/
	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);
	end_gameBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 25));
	continue_Btn->setPosition(Point(viewSize.width / 2, viewSize.height / 2 - 95));
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
	return true;
}

void  stopMessageBox::registerCallback(std::function<void()>continueCallback, std::function<void()>
	endgameCallback)
{
	continueFunc = continueCallback;
	endGamefunc = endgameCallback;
}


void stopMessageBox::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	continue_Btn->runAction(bea);
	end_gameBtn->runAction(cir);
}
