#pragma once

#include<cocos2d.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<spine/spine-cocos2dx.h>
#include<map>
#include<vector>
#include<spine/spine.h>
using namespace cocos2d;
using namespace spine;

class Game_Scene :public Sprite
{
public:
	static Scene* create_Game_Scene();
	virtual bool init();
	CREATE_FUNC(Game_Scene);
	Size visibleSize;
	Point origin;
	// node对象的update方法（ 每一帧都刷新 this->scheduleUpdate(); ）
	void Game_Scene::update_byScene(float delta, int iSpeed);
	
public:
	Sprite* m_bgSprite1;    // 背景精灵1
	Sprite* m_bgSprite2;    // 背景精灵2
	void initBG();          // 初始化图片背景
	//TextFieldTTF* a;
	/*Sprite* Score;*/
	int frame = 0, tag_now = 0;
	
};

