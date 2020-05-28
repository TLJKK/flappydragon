/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "bar.h"
#include "Dragon.h"
#include<vector>

class HelloWorld : public cocos2d::Scene
{
public:

	HelloWorld();
	~HelloWorld();
	Dragon* Dragon_Instance = Dragon::getInstance();
	bar* Bar_Instance = bar::getInstance();

    static cocos2d::Scene* createScene();

	void Init_World();

    virtual bool init();

	void tiemer_hander(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	std::vector<bar*>to_con;
	//Dragon* dragon_player;
	int count[107], num = 0;
	Sprite* m_bgSprite1;    // ±³¾°¾«Áé1
	Sprite* m_bgSprite2;    // ±³¾°¾«Áé2
	void initBG();          // ³õÊ¼»¯Í¼Æ¬±³¾°
	int frame = 0, tag_now = 0, num_now = 0, num_des, show_die, is_show;
	bool go;
	float iSpeed = 4;
};

#endif 
