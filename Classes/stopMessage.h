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
//	//��ʼ�������� node:����㣬msg:��ʾ����Ϣ���ݣ�time�������򵯳���Ҫ��ʱ�䣬��ʱδ�ã�point:��ʾ�ڸ�����λ��
//	//callback: ȷ�ϰ�ť�Ļص�����
//	bool initWithNode(cocos2d::Node* node,const std::string& msg, 
//		const float& time, cocos2d::Vec2 point ,const cocos2d::ccMenuCallback& callback);
// 
//	//����һ�������� node:����㣬msg:��ʾ����Ϣ���ݣ�time�������򵯳���Ҫ��ʱ�䣬��ʱδ�ã�point:��ʾ�ڸ�����λ��
//	//callback: ȷ�ϰ�ť�Ļص�����
//	static stopMessageBox* createToast(cocos2d::Node* node, const std::string& msg, 
//		const float& time, cocos2d::Vec2 point ,const cocos2d::ccMenuCallback& callback);  //std::function<void()> callback
// 
//	virtual void onEnter();
//protected:
//	void OkClick();  //���OK��Ӧ�������Ѿ������ˣ��Ѿ��ĳɻص��û������callback
//	void CancelClick(Ref* ref);  //���cancel��Ӧ�¼�
//protected:
//	cocos2d::Sprite* _bg; //��Ӱ
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
