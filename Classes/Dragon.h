#pragma once
#include<spine/spine-cocos2dx.h>
#include<spine/spine.h>
#include<iostream>
#include<cocos2d.h>

USING_NS_CC;

class Dragon :public Sprite
{
public:
	//CREATE_FUNC(Dragon);
	static Dragon* getInstance();
	CREATE_FUNC(Dragon);
	virtual bool init();
	spine::SkeletonAnimation* skeletonNode;
	void timer_Hander_byScene(int go);
	Rect get_dragon();
	void set_NULL();
	void hurt();
	void Dragon::comm_life();
	int life, die_frame;
	int getLife();
	bool the_dragon_die;
private:
	static Dragon* _instance;
};

