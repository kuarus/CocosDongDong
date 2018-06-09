#pragma once
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer {
public:
	CREATE_FUNC( HelloWorld );//create関数の生成
	static cocos2d::Scene* createScene( );
    virtual bool init( ) override;
    void menuCloseCallback( cocos2d::Ref* pSender );
private:
	void createCloseButton( );
	void createLabel( );
	void createSprite( );
};
