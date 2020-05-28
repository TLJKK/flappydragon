//
//#include "cocos2d.h"
//using namespace cocos2d;
// 
//class stopMessageBox : public cocos2d::Scene
//{
//public:
//	CREATE_FUNC(stopMessageBox);
//	Scene* create_Scene();
//	stopMessageBox();
//	~stopMessageBox();
//	//初始化弹出框 node:父结点，msg:显示的消息内容，time：弹出框弹出需要的时间，暂时未用，point:显示在父结点的位置
//	//callback: 确认按钮的回调函数
//	bool initWithNode(cocos2d::Node* node,const std::string& msg, 
//		const float& time, cocos2d::Vec2 point ,const cocos2d::ccMenuCallback& callback);
// 
//	//产生一个弹出框 node:父结点，msg:显示的消息内容，time：弹出框弹出需要的时间，暂时未用，point:显示在父结点的位置
//	//callback: 确认按钮的回调函数
//	static stopMessageBox* createToast(cocos2d::Node* node, const std::string& msg, 
//		const float& time, cocos2d::Vec2 point ,const cocos2d::ccMenuCallback& callback);  //std::function<void()> callback
// 
//	virtual void onEnter();
//protected:
//	void OkClick();  //点击OK响应，这里已经不用了，已经改成回调用户定义的callback
//	void CancelClick(Ref* ref);  //点击cancel响应事件
//protected:
//	cocos2d::Sprite* _bg; //背影
//private:
//};
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BgScene.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class stopMessageBox : public cocos2d::Layer
{
public:
	stopMessageBox();
	~stopMessageBox();
	virtual bool init();
	CREATE_FUNC(stopMessageBox);
	ui::Scale9Sprite* box;
	ui::Button* continue_Btn;
	ui::Button* end_gameBtn;
	HelloWorld* to;
	virtual void registerCallback(std::function<void()>continueCallback, std::function<void()>
		endgameCallback);
	virtual void onEnter();//show the fault there is less of ';' ,the possible reason is the namespace;
protected:
	std::function<void()>continueFunc;
	std::function<void()>endGamefunc;
private:
};
