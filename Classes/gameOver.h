#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<string>
#include "BgScene.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class gameOver : public cocos2d::Layer
{
public:
	gameOver();
	~gameOver();
	virtual bool init();
	CREATE_FUNC(gameOver);
	ui::Scale9Sprite* box;
	ui::Button* continue_Btn;
	//ui::Button* end_gameBtn;
	ui::Button* submit;
	HelloWorld* to;
	std::string now;
	TextFieldTTF* txt;
	Label* tmp;
	void addLisener();
	virtual void registerCallback(std::function<void()>continueCallback, std::function<void()>
		endgameCallback);
	virtual void onEnter();//show the fault there is less of ';' ,the possible reason is the namespace;
protected:
	std::function<void()>continueFunc;
	//std::function<void()>endGamefunc;
	std::function<void()>submin_Func;
private:
};
