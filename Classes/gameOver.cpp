#include "gameOver.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;

gameOver::gameOver()
{

}

gameOver::~gameOver()
{

}


bool gameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));
	submit = ui::Button::create("submit.png");
	box = ui::Scale9Sprite::create("gameOverbk.png");
	continue_Btn = ui::Button::create("over.png");
	//end_gameBtn = ui::Button::create("mainscene2.png");
	txt = TextFieldTTF::textFieldWithPlaceHolder("点我输入密码：", "GameFont.ttf", 27);
	txt->setAnchorPoint(Point(0, 0));
	txt->setColor(Color3B(0, 0, 0));
	txt->setPosition(Vec2(viewSize.width / 2-100, viewSize.height / 2 + 50));
	submit->setPosition(txt->getPosition() - Point(-20, 60));
	submit->setAnchorPoint(Point(0, 0));
	tmp = Label::createWithSystemFont("密码对了就继续游戏，错了就退出了哟~~~", "GameFont.ttf", 20);
	tmp->setPosition(txt->getPosition() - Point(-90, 150));
	tmp->setColor(Color3B(0, 0,255 ));
	/*box->setScale(0.7);
	continue_Btn->setScale(0.8);
	end_gameBtn->setScale(0.8);*/
	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);
	//end_gameBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 2005));
	continue_Btn->setPosition(Point(viewSize.width / 2, viewSize.height / 2 + 225));
	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	this->addChild(continue_Btn);
	this->addChild(txt);
	this->addChild(tmp);
	this->addChild(submit);
	//this->addChild(end_gameBtn);
	//, endGamefunc;
	continue_Btn->addClickEventListener([this](Ref* ref)
		{
			if (continueFunc != nullptr)
				continueFunc();
		});
	submit->addClickEventListener([this](Ref* ref)
		{
			if (submin_Func != nullptr)
				submin_Func();
		});
	addLisener();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
	listener->setSwallowTouches(true);
	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);
	return true;
}

void  gameOver::registerCallback(std::function<void()>continueCallback, std::function<void()>
	endgameCallback)
{
	continueFunc = continueCallback;
	submin_Func = endgameCallback;
}


void gameOver::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.8f, 1.8f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 0.8f, 0.8f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 0.6f, 0.6f)), NULL);
	Sequence* tt = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f,1.0f, 1.0f)), NULL);
	Sequence* tp = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	continue_Btn->runAction(bea);
	submit->runAction(cir);
	tmp->runAction(tp);
	txt->runAction(tt);
}

void gameOver::addLisener()
{
	auto director = Director::getInstance();

	auto hander = [=](Touch*t,Event*e)
	{
		auto target = e->getCurrentTarget();
		if (target->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (target == txt)txt->attachWithIME();
			else if (target == submit)now = txt->getString();
		}
		else txt->detachWithIME();
		return false;
	};

	auto addListen_target = [=](Node* target)
	{
		auto l = EventListenerTouchOneByOne::create();
		l->onTouchBegan = hander;
		director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(l, target);
	};

	addListen_target(txt);
	addListen_target(submit);
}
