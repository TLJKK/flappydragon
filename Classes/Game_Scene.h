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
	// node�����update������ ÿһ֡��ˢ�� this->scheduleUpdate(); ��
	void Game_Scene::update_byScene(float delta, int iSpeed);
	
public:
	Sprite* m_bgSprite1;    // ��������1
	Sprite* m_bgSprite2;    // ��������2
	void initBG();          // ��ʼ��ͼƬ����
	//TextFieldTTF* a;
	/*Sprite* Score;*/
	int frame = 0, tag_now = 0;
	
};

