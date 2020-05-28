#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BgScene.h"
using namespace cocos2d;
 
class BDMessageBox : public cocos2d::Layer
{
public:
	BDMessageBox();
	~BDMessageBox();
	virtual bool init();
	CREATE_FUNC(BDMessageBox);
	ui::Scale9Sprite* box;
	ui::Button* continue_Btn;
	ui::Button* end_gameBtn;
	Label* label;
	Bg* to;
	virtual void registerCallback(std::function<void()>continueCallback, std::function<void()>
		endgameCallback);
	virtual void onEnter();//show the fault there is less of ';' ,the possible season is the namespace;
protected:
	std::function<void()>continueFunc;
	std::function<void()>endGamefunc;
private:
};
