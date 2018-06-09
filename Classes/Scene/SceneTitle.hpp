#pragma once
#include "cocos2d.h"

class SceneTitle : public cocos2d::Layer {
public:
	CREATE_FUNC( SceneTitle );//create関数の生成
	static cocos2d::Scene* createScene( );
	virtual bool init( ) override;
	void update( );
private:
	void createSprite( );
};
