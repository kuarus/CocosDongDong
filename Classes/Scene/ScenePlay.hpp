#pragma once
#include "cocos2d.h"

class ScenePlay : public cocos2d::Layer {
public:
	CREATE_FUNC( ScenePlay );//create関数の生成
	static cocos2d::Scene* createScene( );
	virtual bool init( ) override;
private:
	void createSprite( );
};
