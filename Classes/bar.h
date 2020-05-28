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

class bar : public Node
{
public:
	LabelTTF* x;
	int Score = 0, first = 0;
	CREATE_FUNC(bar);
	void updata_ByScene(Node* node, int iSpeed);
	static bar* getInstance();
	virtual bool init();
	void set_NULL();
	typedef struct
	{
		spine::SkeletonAnimation* skeleton;
		bool is_bottom = 0, is_top = 0;
		int tag;
		Size bound;
		int x, y;
	}bars;
	int add[9];
	void bar::createBarBytag(Node* node, const int order, const int tag_1, const int tag_2);
	Size visibleSize;
	std::map<int, bars>now;
	std::map<int, bars>::iterator begin;
	int get_life();
protected:
	static bar* _instance;
};
